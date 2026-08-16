#ifndef SIGNAL_SLOT_DEMO_H
#define SIGNAL_SLOT_DEMO_H

#include <QObject>
#include <QString>

// A separate class used only to demonstrate Qt signals and slots.
class SignalSlotDemo : public QObject
{
    Q_OBJECT

public:
    explicit SignalSlotDemo(QObject *parent = nullptr);

    // QML calls this method to start the signal flow.
    Q_INVOKABLE void triggerSignal();

signals:
    // A signal announces that a message is ready.
    void messageChanged(const QString &message);

public slots:
    // A slot receives and handles the signal in C++.
    void handleMessage(const QString &message);
};

#endif // SIGNAL_SLOT_DEMO_H