#pragma once

class Sensor
{
  public:
    void sensorSet(bool data);

    const bool sensorRead() const;

  private:
    bool m_data;
};
