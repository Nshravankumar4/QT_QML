#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

// 1. Backend class
// Inherits QObject to use Qt's meta-object system
class Backend : public QObject
{
    Q_OBJECT

public:

    // Constructor
    // parent is used for Qt parent-child ownership
    explicit Backend(QObject *parent = nullptr);

    // Q_INVOKABLE allows QML to call this function
    Q_INVOKABLE void showMessage();
};


// 2. Backend_Next class
// Another QObject-based C++ class exposed to QML
class Backend_Next : public QObject
{
    Q_OBJECT

public:

    // Constructor
    explicit Backend_Next(QObject *parent = nullptr);

    // Callable from QML
    Q_INVOKABLE void showMessage_Next();
};

#endif // BACKEND_H
