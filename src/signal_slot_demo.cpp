#include "signal_slot_demo.h"

#include <QDebug>

SignalSlotDemo::SignalSlotDemo(QObject *parent)
    : QObject(parent)
{
    // Connect this object's signal to its C++ slot for demonstration.
    QObject::connect(
        this,
        &SignalSlotDemo::messageChanged,
        this,
        &SignalSlotDemo::handleMessage);
}

void SignalSlotDemo::triggerSignal()
{
    // emit notifies every receiver connected to messageChanged.
    emit messageChanged(QStringLiteral("Signal received successfully"));
}

void SignalSlotDemo::handleMessage(const QString &message)
{
    qDebug() << "C++ slot handled message:" << message;
}