#include <guitranslator.h>
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    {
        GuiTranslator translator;
        if(!translator.Install(app)) return 1;
        if(QCoreApplication::translate("SettingsDialog", "Settings") != QString::fromUtf8("设置")) return 2;
        if(QCoreApplication::translate("RegistDialog", "Register") != QString::fromUtf8("注册")) return 3;
        const QString missing = QCoreApplication::translate("UnknownContext", "Untranslated fallback");
        if(missing != QStringLiteral("Untranslated fallback")) return 4;
    }
    {
        GuiTranslator translator;
        if(!translator.Install(app, "en")) return 5;
        if(QCoreApplication::translate("SettingsDialog", "Settings") != QStringLiteral("Settings")) return 6;
    }
    {
        GuiTranslator translator;
        if(translator.Install(app, "unsupported")) return 7;
    }
    qInfo() << "PASS: default Chinese, English override, missing-string fallback, invalid language";
    return 0;
}
