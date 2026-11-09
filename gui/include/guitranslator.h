#pragma once

#include <QCoreApplication>
#include <QTranslator>

// Keep translators alive for the full lifetime of the GUI.
class GuiTranslator
{
public:
    bool Install(QCoreApplication &app, const QString &language = QStringLiteral("zh_CN"));

private:
    QTranslator application;
    QTranslator qt;
};
