#include "ownership_demo.h"

#include <QDebug>

OwnershipDemo::OwnershipDemo(QObject *parent)
    : QObject(parent)
{
}

void OwnershipDemo::createChild()
{
    if (m_child != nullptr) {
        emit statusChanged(QStringLiteral("Child already exists"));
        return;
    }

    // Passing this as parent transfers lifetime ownership to OwnershipDemo.
    m_child = new QObject(this);
    m_child->setObjectName(QStringLiteral("OwnedChild"));

    qDebug() << "Parent created child:" << m_child->objectName();
    emit statusChanged(QStringLiteral("Child created and owned by parent"));
}

void OwnershipDemo::scheduleChildDeletion()
{
    if (m_child == nullptr) {
        emit statusChanged(QStringLiteral("No child to delete"));
        return;
    }

    // deleteLater() safely deletes the child when control returns to the event loop.
    m_child->deleteLater();
    m_child = nullptr;

    emit statusChanged(QStringLiteral("Child scheduled for deleteLater()"));
}