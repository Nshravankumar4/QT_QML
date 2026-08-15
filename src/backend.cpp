#include "backend.h"

#include <QDebug>

// 1. Backend Constructor
// Initializes the QObject parent
// Parent-child relationship allows Qt to manage object lifetime
Backend::Backend(QObject *parent)
    : QObject(parent)
{
    qDebug() << "Backend Object Created";
}

// 2. Backend Function
// This function is called from QML using:
// backend.showMessage()
void Backend::showMessage()
{
    qDebug() << "Backend Function Called";
}


// 3. Backend_Next Constructor
// Initializes the QObject parent
Backend_Next::Backend_Next(QObject *parent)
    : QObject(parent)
{
    qDebug() << "Backend_Next Object Created";
}

// 4. Backend_Next Function
// This function is called from QML using:
// backendnext.showMessage_Next()
void Backend_Next::showMessage_Next()
{
    qDebug() << "Backend_next Function Called";
}
