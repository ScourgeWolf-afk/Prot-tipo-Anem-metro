/ *
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licenciado sob a Licença Apache, Versão 2.0 (a "Licença");
 * você não pode usar este arquivo, exceto em conformidade com a Licença.
 * Você pode obter uma cópia da Licença em
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * A menos que exigido pela lei aplicável ou acordado por escrito, software </ span>
 * distribuído sob a Licença é distribuído "COMO ESTÁ",
 * SEM GARANTIAS OU CONDIÇÕES DE QUALQUER TIPO, expressas ou implícitas.
 * Consulte a Licença para as permissões específicas que regem o idioma e
 * limitações sob a Licença.
 * /

/ * Atualização de K. Townsend (Adafruit Industries) para typedefs mais leves, e
 * suporte de sensor estendido para incluir cor, tensão e corrente * /

#ifndef _ADAFRUIT_SENSOR_H
#define _ADAFRUIT_SENSOR_H

#ifndef ARDUINO
#include <stdint.h>
#elif ARDUINO> = 100
#include "Arduino.h"
#include "Print.h"
#outro
#include "WProgram.h"
#fim se

/ * Constants * /
#define SENSORS_GRAVITY_EARTH (9.80665F) / ** <gravidade da Terra em m / s ^ 2 * /
#define SENSORS_GRAVITY_MOON (1.6F) / ** <A gravidade da lua em m / s ^ 2 * /
#define SENSORS_GRAVITY_SUN (275.0F) / ** <A gravidade do sol em m / s ^ 2 * /
#define SENSORS_GRAVITY_STANDARD (SENSORS_GRAVITY_EARTH)
#define SENSORS_MAGFIELD_EARTH_MAX \
  (60.0F) / ** <Campo magnético máximo na superfície da Terra * /
#define SENSORS_MAGFIELD_EARTH_MIN \
  (30.0F) / ** <Campo magnético mínimo na superfície da Terra * /
#define SENSORS_PRESSURE_SEALEVELHPA \
  (1013,25F) / ** <A pressão média ao nível do mar é 1013,25 hPa * /
#define SENSORS_DPS_TO_RADS \
  (0,017453293F) / ** <Multiplicador de graus / s a ​​rad / s \
                  * /
#define SENSORS_RADS_TO_DPS \
  (57,29577793F) / ** <Rad / s para multiplicador de graus / s * /
#define SENSORS_GAUSS_TO_MICROTESLA \
  (100) / ** <Multiplicador de Gauss para micro-Tesla * /

/ ** Tipos de sensores * /
typedef enum {
  SENSOR_TYPE_ACCELEROMETER = (1), / ** <Gravidade + aceleração linear * /
  SENSOR_TYPE_MAGNETIC_FIELD = (2),
  SENSOR_TYPE_ORIENTATION = (3),
  SENSOR_TYPE_GYROSCOPE = (4),
  SENSOR_TYPE_LIGHT = (5),
  SENSOR_TYPE_PRESSURE = (6),
  SENSOR_TYPE_PROXIMITY = (8),
  SENSOR_TYPE_GRAVITY = (9),
  SENSOR_TYPE_LINEAR_ACCELERATION =
      (10), / ** <Aceleração não incluindo gravidade * /
  SENSOR_TYPE_ROTATION_VECTOR = (11),
  SENSOR_TYPE_RELATIVE_HUMIDITY = (12),
  SENSOR_TYPE_AMBIENT_TEMPERATURE = (13),
  SENSOR_TYPE_OBJECT_TEMPERATURE = (14),
  SENSOR_TYPE_VOLTAGE = (15),
  SENSOR_TYPE_CURRENT = (16),
  SENSOR_TYPE_COLOR = (17)
} sensores_tipo_t;

/ ** struct sensores_vec_s é usado para retornar um vetor em um formato comum. * /
typedef struct {
  União {
    float v [3]; /// <elementos do vetor 3D
    struct {
      float x; /// <componente X do vetor
      float y; /// <componente Y do vetor
      float z; /// <componente Z do vetor
    }; /// <Struct para segurar o componente XYZ
    / * Sensores de orientação * /
    struct {
      rolo flutuante; / ** <Rotação em torno do eixo longitudinal (o corpo do plano, 'X
                     eixo'). O roll é positivo e aumenta quando se move
                     para baixo. -90 graus <= roll <= 90 graus * /
      passo de flutuação; / ** <Rotação em torno do eixo lateral (envergadura, 'Y
                        eixo'). O tom é positivo e aumenta durante o movimento
                        para cima. -180 graus <= inclinação <= 180 graus) * /
      posição flutuante; / ** <Ângulo entre o eixo longitudinal (o corpo do plano)
                        e norte magnético, medido no sentido horário durante a visualização de
                        a parte superior do dispositivo. 0-359 graus * /
    }; /// <Struct para segurar roll / pitch / header
  }; /// <União que pode conter matriz vetorial 3D, componentes XYZ ou
                     /// <roll / pitch / posição
  status int8_t; /// <byte de status
  uint8_t reservado [3]; /// <Reservado
} sensores_vec_t;

/ ** struct sensores_color_s é usado para retornar dados de cores em um formato comum. * /
typedef struct {
  União {
    float c [3]; /// <Dados brutos de 3 elementos
    / * Espaço de cor RGB * /
    struct {
      float r; / ** <Componente vermelho * /
      float g; / ** <componente verde * /
      float b; / ** <Componente azul * /
    }; /// <dados RGB em notação de ponto flutuante
  }; /// <União de várias maneiras de descrever o espaço de cores RGB
  uint32_t rgba; / ** <valor RGBA de 24 bits * /
} sensores_cor_t;

/ * Evento do sensor (36 bytes) * /
/ ** struct sensor_event_s é usado para fornecer um único evento de sensor em um comum
 * formato. * /
typedef struct {
  versão int32_t; / ** <deve ser sizeof (struct sensores_event_t) * /
  int32_t sensor_id; / ** <identificador de sensor exclusivo * /
  int32_t type; / ** <tipo de sensor * /
  int32_t reserved0; / ** <reservado * /
  int32_t timestamp; / ** <o tempo está em milissegundos * /
  União {
    dados flutuantes [4]; /// <Dados brutos
    sensores_vec_t aceleração; / ** <os valores de aceleração estão em metros por segundo
                                   por segundo (m / s ^ 2) * /
    sensores_vec_t
        magnético; / ** <os valores do vetor magnético estão em micro-Tesla (uT) * /
    orientação sensores_vec_t; / ** <valores de orientação estão em graus * /
    sensores_vec_t gyro; / ** <os valores do giroscópio estão em rad / s * /
    temperatura de flutuação; / ** <a temperatura está em graus centígrados (Celsius) * /
    distância de flutuação; / ** <distância em centímetros * /
    luz flutuante; / ** <luz em unidades SI lux * /
    pressão de flutuação; / ** <pressão em hectopascal (hPa) * /
    float relative_humidity; / ** <umidade relativa em porcentagem * /
    float current; / ** <corrente em miliamperes (mA) * /
    tensão flutuante; / ** <tensão em volts (V) * /
    sensores_color_t color; / ** <cor nos valores do componente RGB * /
  }; /// <União para a ampla gama de dados que podemos transportar
} sensores_evento_t;

/ * Detalhes do sensor (40 bytes) * /
/ ** struct sensor_s é usado para descrever informações básicas sobre um
 * sensor. * /
typedef struct {
  nome do char [12]; / ** <nome do sensor * /
  versão int32_t; / ** <versão do hardware + driver * /
  int32_t sensor_id; / ** <identificador de sensor exclusivo * /
  int32_t type; / ** <tipo deste sensor (ex. SENSOR_TYPE_LIGHT) * /
  float max_value; / ** <valor máximo do valor deste sensor em unidades SI * /
  float min_value; / ** <valor mínimo do valor deste sensor em unidades SI * /
  resolução de flutuação; / ** <menor diferença entre dois valores relatados por este
                       sensor * /
  int32_t min_delay; / ** <min atraso em microssegundos entre eventos. zero = não um
                        taxa constante * /
} sensor_t;

/ ** @brief Interface de sensor comum para unificar vários sensores.
 * Modelado intencionalmente após sensores.h na API Android:
 * https://github.com/android/platform_hardware_libhardware/blob/master/include/hardware/sensors.h
 * /
class Adafruit_Sensor {
público:
  // Construtor (es)
  Adafruit_Sensor () {}
  virtual ~ Adafruit_Sensor () {}

  // Devem ser definidos pela subclasse

  / *! @brief Se devemos alterar automaticamente o intervalo (se possível) para
     maior precisão
      @param habilitado Verdadeiro se tentarmos autorange * /
  virtual void enableAutoRange (bool enabled) {
    (vazio) ativado; / * suprimir aviso não utilizado * /
  };

  / *! @brief Obtenha o evento de sensor mais recente
      @returns True se for capaz de buscar um evento * /
  bool getEvent virtual (sensores_event_t *) = 0;
  / *! @brief Obtenha informações sobre o próprio sensor * /
  virtual void getSensor (sensor_t *) = 0;

  void printSensorDetails (void);

privado:
  bool _autoRange;
};

#fim se
