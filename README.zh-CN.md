# chiaki-ng Windows 简体中文版

这是基于 [chiaki-ng](https://github.com/chiaki-ng/chiaki-ng) **v1.10.1** 的非官方汉化分支，只提供 **Windows x64 便携版**（Intel / AMD）。

[下载中文版 ZIP](https://github.com/lwm38741/chiaki-ng/releases/latest)

## 使用

1. 解压整个 ZIP，运行 `chiaki-ng-Win/chiaki.exe`，默认显示简体中文。
2. 要使用英文，运行同目录的 `Start-English.cmd`，或执行 `chiaki.exe --language en`。
3. 保留全部 DLL、QML 和 translations 文件。便携版免安装，但沿用上游的 Windows 用户设置存储位置；升级前可在“设置 > 配置”导出配置。

仅支持 x64。本版不提供 ARM64、安装程序、macOS 或 Linux 构建。

## 汉化范围

主界面、设置、主机注册、PSN 登录流程中的客户端提示、手柄映射、显示与串流菜单等，翻译目录共 722 条。保留格式占位符、品牌和技术名。

Sony 登录网页和外部账户查询网页由对应服务提供。底层库诊断日志与部分附加错误详情保留原文，便于排障。默认中文与英文模式共用上游原有配置键名，自定义键位不会因切换语言而分离。

## 构建与验证

[Windows 专用工作流](.github/workflows/build-windows-zh.yml) 使用上游 MSYS2 x64 构建路径，编译 Qt TS 为嵌入式 QM 资源，再打包免安装 ZIP。没有使用上游多平台发布、安装程序或 Discord 通知工作流。

- `python scripts/check-translations.py`：检查翻译完成度、占位符、HTML、URL 和换行。
- CTest：上游单元测试、Qt 实际加载、英文回退、中英文键位读写和重置。
- 部署目录中的独立测试：验证 Qt 标准按钮也显示中文。
- Windows GUI 启动及设置页面截图检查；CI 使用软件 OpenGL 和虚拟音频，未验证真实 GPU 解码、音频或手柄。

实体 PS4/PS5 配对、PSN 授权、远程串流、HDR 和手柄端到端功能没有进行硬件验证。每次发布的实际检查结果见 Release 说明。

## 许可与署名

保留上游作者及许可证，见 [COPYING](COPYING) 和 [LICENSES](LICENSES)。本分支按上游 AGPL v3 条款提供对应源码，包内 `SOURCE-COMMIT.txt` 标明构建提交。

本项目与 Sony / PlayStation 无隶属关系。问题可提交到本 fork；上游原版下载请使用其官方仓库。
