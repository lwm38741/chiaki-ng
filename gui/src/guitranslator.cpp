#include <guitranslator.h>
#include <QDir>

bool GuiTranslator::Install(QCoreApplication &app, const QString &language)
{
    if(language == QStringLiteral("en"))
        return true;
    if(language != QStringLiteral("zh_CN"))
        return false;

    const QString directory = QDir(QCoreApplication::applicationDirPath()).filePath("translations");
    // windeployqt merges the required Qt catalogs into this single file.
    if(qt.load("qt_zh_CN", directory))
        app.installTranslator(&qt);

    if(!application.load(QStringLiteral(":/i18n/chiaki_zh_CN.qm")))
        return false;
    return app.installTranslator(&application);
}
