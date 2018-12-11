#include "sensor.h"

void Sensor::sensorSet(bool data) { m_data = data; }

const bool Sensor::sensorRead() const { return m_data; }
