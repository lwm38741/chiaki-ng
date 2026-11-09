#include <guitranslator.h>
#include <QDir>

bool GuiTranslator::Install(QCoreApplication &app, const QString &language)
{
    if(language == QStringLiteral("en"))
        return true;
    if(language != QStringLiteral("zh_CN"))
        return false;

    const QString directory = QDir(QCoreApplication::applicationDirPath()).filePath("translations");
    if(qtbase.load("qtbase_zh_CN", directory))
        app.installTranslator(&qtbase);
    if(qtdeclarative.load("qtdeclarative_zh_CN", directory))
        app.installTranslator(&qtdeclarative);

    if(!application.load(QStringLiteral(":/i18n/chiaki_zh_CN.qm")))
        return false;
    return app.installTranslator(&application);
}
