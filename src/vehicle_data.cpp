#include "vehicle_data.h"

VehicleData::VehicleData(QObject *parent)
    : QObject(parent)
{
}

int VehicleData::speed() const
{
    return m_speed;
}

void VehicleData::setSpeed(int speed)
{
    if (m_speed == speed) {
        return;
    }

    m_speed = speed;
    emit speedChanged();
}

void VehicleData::increaseSpeed()
{
    setSpeed(m_speed + 10);
}