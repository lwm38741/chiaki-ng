param([string]$Directory = 'chiaki-ng-Win')
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Windows.Forms
Add-Type @'
using System;
using System.Runtime.InteropServices;
public class SmokeWindow {
  [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
}
'@
$evidence = New-Item -ItemType Directory -Force smoke-evidence
$env:SDL_AUDIODRIVER = 'dummy'
$env:GALLIUM_DRIVER = 'llvmpipe'
function Save-Window($process, [string]$name) {
    $rect = [SmokeWindow+RECT]::new()
    [void][SmokeWindow]::GetWindowRect($process.MainWindowHandle, [ref]$rect)
    $bitmap = [System.Drawing.Bitmap]::new($rect.Right-$rect.Left, $rect.Bottom-$rect.Top)
    $graphics = [System.Drawing.Graphics]::FromImage($bitmap)
    try {
        $graphics.CopyFromScreen($rect.Left, $rect.Top, 0, 0, $bitmap.Size)
        $bitmap.Save((Join-Path $evidence.FullName "$name.png"))
    } finally { $graphics.Dispose(); $bitmap.Dispose() }
}
foreach ($language in @('zh_CN', 'en')) {
    # Isolated profile on the disposable build runner; never uses a real PSN account.
    $settings = 'HKCU:\Software\Chiaki\Chiaki-ci-smoke\settings'
    New-Item -Path $settings -Force | Out-Null
    New-ItemProperty -Path $settings -Name add_steam_shortcut_ask -Value 'false' -PropertyType String -Force | Out-Null
    New-ItemProperty -Path $settings -Name remote_play_ask -Value 'false' -PropertyType String -Force | Out-Null
    $arguments = @('--profile', 'ci-smoke', '--opengl')
    if ($language -eq 'en') { $arguments += @('--language', 'en') }
    $p = Start-Process -FilePath (Resolve-Path "$Directory/chiaki.exe") -ArgumentList $arguments -PassThru -RedirectStandardError "$($evidence.FullName)/$language-stderr.txt" -RedirectStandardOutput "$($evidence.FullName)/$language-stdout.txt"
    try {
        for ($i=0; $i -lt 45; $i++) {
            Start-Sleep -Seconds 1
            $p.Refresh()
            if ($p.HasExited) { throw "GUI exited during $language startup: $($p.ExitCode)" }
            if ($p.MainWindowHandle -ne [IntPtr]::Zero) { break }
        }
        if ($p.MainWindowHandle -eq [IntPtr]::Zero) { throw 'No GUI window appeared' }
        [void][SmokeWindow]::SetForegroundWindow($p.MainWindowHandle)
        Start-Sleep -Seconds 3
        Save-Window $p "$language-main"
        # Open the top-right Settings button; record all nine tabs for visual review.
        $rect = [SmokeWindow+RECT]::new()
        [void][SmokeWindow]::GetWindowRect($p.MainWindowHandle, [ref]$rect)
        $point = (($rect.Right-$rect.Left-55) -band 0xffff) -bor (65 -shl 16)
        [void][SmokeWindow]::PostMessage($p.MainWindowHandle, 0x201, [IntPtr]1, [IntPtr]$point)
        [void][SmokeWindow]::PostMessage($p.MainWindowHandle, 0x202, [IntPtr]0, [IntPtr]$point)
        Start-Sleep -Seconds 2
        Save-Window $p "$language-settings-0"
        if ($language -eq 'zh_CN') {
            for ($tab=1; $tab -le 8; $tab++) {
                [System.Windows.Forms.SendKeys]::SendWait('{PGDN}')
                Start-Sleep -Milliseconds 600
                Save-Window $p "$language-settings-$tab"
            }
        }
        $p.Refresh()
        if ($p.HasExited) { throw 'GUI exited during smoke test' }
        "PASS: $language portable GUI launched and remained running" | Tee-Object -FilePath "$($evidence.FullName)/result.txt" -Append
    } finally {
        if (!$p.HasExited) { Stop-Process -Id $p.Id -Force }
    }
}
