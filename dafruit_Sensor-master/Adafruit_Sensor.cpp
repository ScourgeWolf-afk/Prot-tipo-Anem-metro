#include "Adafruit_Sensor.h"

/ *************************************************** ************************* /
/ *!
    @brief Imprime informações do sensor no console serial
* /
/ *************************************************** ************************* /
void Adafruit_Sensor :: printSensorDetails (void) {
  sensor_t sensor;
  getSensor (& sensor);
  Serial.println (F ("------------------------------------"));
  Serial.print (F ("Sensor:"));
  Serial.println (sensor.name);
  Serial.print (F ("Tipo:"));
  switch ((sensores_type_t) sensor.type) {
  case SENSOR_TYPE_ACCELEROMETER:
    Serial.print (F ("Aceleração (m / s2)"));
    pausa;
  case SENSOR_TYPE_MAGNETIC_FIELD:
    Serial.print (F ("Magnético (uT)"));
    pausa;
  case SENSOR_TYPE_ORIENTATION:
    Serial.print (F ("Orientação (graus)"));
    pausa;
  case SENSOR_TYPE_GYROSCOPE:
    Serial.print (F ("Gyroscopic (rad / s)"));
    pausa;
  case SENSOR_TYPE_LIGHT:
    Serial.print (F ("Light (lux)"));
    pausa;
  case SENSOR_TYPE_PRESSURE:
    Serial.print (F ("Pressão (hPa)"));
    pausa;
  case SENSOR_TYPE_PROXIMITY:
    Serial.print (F ("Distância (cm)"));
    pausa;
  case SENSOR_TYPE_GRAVITY:
    Serial.print (F ("Gravidade (m / s2)"));
    pausa;
  case SENSOR_TYPE_LINEAR_ACCELERATION:
    Serial.print (F ("Linear Acceleration (m / s2)"));
    pausa;
  case SENSOR_TYPE_ROTATION_VECTOR:
    Serial.print (F ("Vetor de rotação"));
    pausa;
  case SENSOR_TYPE_RELATIVE_HUMIDITY:
    Serial.print (F ("Umidade relativa (%)"));
    pausa;
  case SENSOR_TYPE_AMBIENT_TEMPERATURE:
    Serial.print (F ("Temperatura ambiente (C)"));
    pausa;
  case SENSOR_TYPE_OBJECT_TEMPERATURE:
    Serial.print (F ("Object Temp (C)"));
    pausa;
  case SENSOR_TYPE_VOLTAGE:
    Serial.print (F ("Voltagem (V)"));
    pausa;
  case SENSOR_TYPE_CURRENT:
    Serial.print (F ("Atual (mA)"));
    pausa;
  case SENSOR_TYPE_COLOR:
    Serial.print (F ("Cor (RGBA)"));
    pausa;
  }

  Serial.println ();
  Serial.print (F ("Driver Ver:"));
  Serial.println (sensor.version);
  Serial.print (F ("ID exclusivo:"));
  Serial.println (sensor.sensor_id);
  Serial.print (F ("Valor mínimo:"));
  Serial.println (sensor.min_value);
  Serial.print (F ("Valor máximo:"));
  Serial.println (sensor.max_value);
  Serial.print (F ("Resolução:"));
  Serial.println (sensor.resolution);
  Serial.println (F ("------------------------------------ \ n"));
}
