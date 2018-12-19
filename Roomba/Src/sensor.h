#pragma once

class Sensor
{
  public:
    Sensor(){};

    Sensor(const Sensor& other) = delete;

    void sensorSet(bool data);

    const bool sensorRead() const;

  private:
    bool m_data;
};
