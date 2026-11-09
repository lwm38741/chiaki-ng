#include <guitranslator.h>
#include <QCoreApplication>
#include <QDebug>
#include <QSettings>
#include <QTemporaryDir>
#include <settings.h>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    QTemporaryDir directory;
    if(!directory.isValid()) return 10;
    QCoreApplication::setOrganizationName("ChiakiTranslationTest");
    QCoreApplication::setApplicationName("KeyMappingTest");
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, directory.path());
    {
        Settings original(QString{});
        original.SetControllerButtonMapping(CHIAKI_CONTROLLER_BUTTON_CROSS, Qt::Key_X);
    }
    {
        GuiTranslator translator;
        if(!translator.Install(app)) return 1;
        if(QCoreApplication::translate("SettingsDialog", "Settings") != QString::fromUtf8("设置")) return 2;
        if(QCoreApplication::translate("RegistDialog", "Register") != QString::fromUtf8("注册")) return 3;
        if(app.arguments().contains("--require-qt-translations") &&
            QCoreApplication::translate("QPlatformTheme", "Cancel") != QString::fromUtf8("取消")) return 17;
        Settings chinese(QString{});
        if(chinese.GetControllerMapping().value(CHIAKI_CONTROLLER_BUTTON_CROSS) != Qt::Key_X) return 11;
        chinese.SetControllerButtonMapping(CHIAKI_CONTROLLER_BUTTON_CROSS, Qt::Key_Y);
        QSettings stored("ChiakiTranslationTest", "KeyMappingTest");
        if(stored.value("keymap/cross").toString() != "Y") return 12;
        if(stored.contains(QString::fromUtf8("keymap/叉键"))) return 13;
        const QString missing = QCoreApplication::translate("UnknownContext", "Untranslated fallback");
        if(missing != QStringLiteral("Untranslated fallback")) return 4;
    }
    {
        GuiTranslator translator;
        if(!translator.Install(app, "en")) return 5;
        if(QCoreApplication::translate("QPlatformTheme", "Cancel") != QStringLiteral("Cancel")) return 18;
        Settings english(QString{});
        if(english.GetControllerMapping().value(CHIAKI_CONTROLLER_BUTTON_CROSS) != Qt::Key_Y) return 14;
        if(QCoreApplication::translate("SettingsDialog", "Settings") != QStringLiteral("Settings")) return 6;
    }
    {
        GuiTranslator translator;
        if(translator.Install(app, "unsupported")) return 7;
    }
    {
        GuiTranslator translator;
        if(!translator.Install(app)) return 15;
        Settings chinese(QString{});
        chinese.ClearKeyMapping();
        QSettings stored("ChiakiTranslationTest", "KeyMappingTest");
        if(stored.contains("keymap/cross")) return 16;
    }
    qInfo() << "PASS: default Chinese, English override, missing-string fallback, invalid language, cross-language key mapping and reset";
    return 0;
}
