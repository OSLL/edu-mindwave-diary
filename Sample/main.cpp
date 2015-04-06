#include <QApplication>
#include <QQmlApplicationEngine>
#include <QPushButton>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "thinkgear.h"
#include "test.h"

/**
 * Prompts and waits for the user to press ENTER.
 */


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
