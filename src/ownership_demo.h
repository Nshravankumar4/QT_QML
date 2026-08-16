#ifndef OWNERSHIP_DEMO_H
#define OWNERSHIP_DEMO_H

#include <QObject>
#include <QPointer>

// A separate class used to demonstrate QObject ownership and lifetime.
class OwnershipDemo : public QObject
{
    Q_OBJECT

public:
    explicit OwnershipDemo(QObject *parent = nullptr);

    // QML creates a child whose lifetime is owned by this object.
    Q_INVOKABLE void createChild();

    // QML requests deferred destruction through the event loop.
    Q_INVOKABLE void scheduleChildDeletion();

signals:
    void statusChanged(const QString &status);

private:
    // QPointer becomes nullptr automatically if the observed object is destroyed.
    QPointer<QObject> m_child;
};

#endif // OWNERSHIP_DEMO_H