#ifndef VEHICLE_DATA_H
#define VEHICLE_DATA_H

#include <QObject>

// A separate class used to demonstrate Q_PROPERTY and QML binding.
class VehicleData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)

public:
    explicit VehicleData(QObject *parent = nullptr);

    int speed() const;
    void setSpeed(int speed);

    // QML calls this method to change the property value.
    Q_INVOKABLE void increaseSpeed();

signals:
    // QML bindings are refreshed when this signal is emitted.
    void speedChanged();

private:
    int m_speed{0};
};

#endif // VEHICLE_DATA_H