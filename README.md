# Prot-tipo-Anem-metro
Código desenvolvido em Arduíno
# Driver de sensor unificado Adafruit #

Muitos pequenos sistemas incorporados existem para coletar dados de sensores, analisar os dados e tomar uma ação apropriada ou enviar os dados do sensor para outro sistema para processamento.

Um dos muitos desafios do projeto de sistemas embarcados é o fato de que as peças que você usa hoje podem estar fora de produção amanhã, ou os requisitos do sistema podem mudar e você pode precisar escolher um sensor diferente no futuro.

Criar novos drivers é uma tarefa relativamente fácil, mas integrá-los aos sistemas existentes é suscetível a erros e demorado, pois os sensores raramente usam exatamente as mesmas unidades de medida.

Reduzindo todos os dados a um único ** sensores \ _evento \ _t ** 'tipo' e estabelecendo em ** unidades SI padronizadas ** específicas para cada família de sensores, os mesmos tipos de sensores retornam valores que são comparáveis ​​a qualquer outro sensor semelhante. Isso permite que você alterne os modelos de sensor com muito pouco impacto no resto do sistema, o que pode ajudar a mitigar alguns dos riscos e problemas de disponibilidade do sensor e reutilização de código.

A camada de abstração de sensor unificado também é útil para registro e transmissão de dados, uma vez que você só tem um tipo conhecido para registrar ou transmitir pelo ar ou com fio.

## Drivers de sensor unificado ##

Os seguintes drivers são baseados no Driver do Sensor Unificado Adafruit:

** Acelerômetros **
  - [Adafruit \ _ADXL345] (https://github.com/adafruit/Adafruit_ADXL345)
  - [Adafruit \ _LSM303DLHC] (https://github.com/adafruit/Adafruit_LSM303DLHC)
  - [Adafruit \ _MMA8451 \ _Library] (https://github.com/adafruit/Adafruit_MMA8451_Library)

** Giroscópio **
  - [Adafruit \ _L3GD20 \ _U] (https://github.com/adafruit/Adafruit_L3GD20_U)

**Luz**
  - [Adafruit \ _TSL2561] (https://github.com/adafruit/Adafruit_TSL2561)
  - [Adafruit \ _TSL2591 \ _Library] (https://github.com/adafruit/Adafruit_TSL2591_Library)

** Magnetômetros **
  - [Adafruit \ _LSM303DLHC] (https://github.com/adafruit/Adafruit_LSM303DLHC)
  - [Adafruit \ _HMC5883 \ _Unified] (https://github.com/adafruit/Adafruit_HMC5883_Unified)
  
**Pressão barométrica**
  - [Adafruit \ _BMP085 \ _Unified] (https://github.com/adafruit/Adafruit_BMP085_Unified)
  - [Adafruit \ _BMP183 \ _Unified \ _Library] (https://github.com/adafruit/Adafruit_BMP183_Unified_Library)

** Umidade e temperatura **
  - [DHT-sensor-library] (https://github.com/adafruit/DHT-sensor-library)

** Umidade, temperatura e pressão barométrica **
  - [Adafruit_BME280_Library] (https://github.com/adafruit/Adafruit_BME280_Library/)

**Orientação**
 - [Adafruit_BNO055] (https://github.com/adafruit/Adafruit_BNO055)

** Tudo em um dispositivo **
- [Adafruit_LSM9DS0] (https://github.com/adafruit/Adafruit_LSM9DS0_Library) (acelerômetro, giroscópio, magnetômetro)
- [Adafruit_LSM9DS1] (https://github.com/adafruit/Adafruit_LSM9DS1/) (acelerômetro, giroscópio, magnetômetro)


## Como funciona? ##

Qualquer driver que suporte a camada de abstração de sensor unificado Adafruit implementará a classe base Adafruit \ _Sensor. Existem dois typedefs principais e um enum definido em Adafruit_Sensor.h que são usados ​​para 'abstrair' os detalhes e valores do sensor:

** Tipos de sensor (sensores \ _type \ _t) **

Esses tipos de sensores predefinidos são usados ​​para lidar adequadamente com os dois typedefs relacionados abaixo e nos permitem determinar quais tipos de unidades o sensor usa, etc.

`` `c ++
/ ** Tipos de sensores * /
typedef enum
{
  SENSOR_TYPE_ACCELEROMETER = (1),
  SENSOR_TYPE_MAGNETIC_FIELD = (2),
  SENSOR_TYPE_ORIENTATION = (3),
  SENSOR_TYPE_GYROSCOPE = (4),
  SENSOR_TYPE_LIGHT = (5),
  SENSOR_TYPE_PRESSURE = (6),
  SENSOR_TYPE_PROXIMITY = (8),
  SENSOR_TYPE_GRAVITY = (9),
  SENSOR_TYPE_LINEAR_ACCELERATION = (10),
  SENSOR_TYPE_ROTATION_VECTOR = (11),
  SENSOR_TYPE_RELATIVE_HUMIDITY = (12),
  SENSOR_TYPE_AMBIENT_TEMPERATURE = (13),
  SENSOR_TYPE_VOLTAGE = (15),
  SENSOR_TYPE_CURRENT = (16),
  SENSOR_TYPE_COLOR = (17)
} sensores_tipo_t;
`` `

** Detalhes do sensor (sensor \ _t) **

Este typedef descreve os recursos específicos desse sensor e nos permite saber qual sensor estamos usando abaixo da camada de abstração.

`` `c ++
/ * Detalhes do sensor (40 bytes) * /
/ ** struct sensor_s é usado para descrever informações básicas sobre um sensor específico. * /
estrutura de typedef
{
    nome do char [12];
    versão int32_t;
    int32_t sensor_id;
    int32_t type;
    float max_value;
    float min_value;
    resolução de flutuação;
    int32_t min_delay;
} sensor_t;
`` `

Os campos individuais devem ser usados ​​da seguinte forma:

- ** nome **: O nome ou ID do sensor, com no máximo doze caracteres (por exemplo, "MPL115A2")
- ** versão **: A versão do sensor HW e do driver para nos permitir diferenciar as versões da placa ou driver
- ** sensor \ _id **: um identificador de sensor exclusivo que é usado para diferenciar esta instância de sensor específica de qualquer outra que esteja presente no sistema ou na rede de sensores
- ** tipo **: o tipo de sensor, com base em ** sensores \ _tipo \ _t ** em sensores.h
- ** max \ _value **: O valor máximo que este sensor pode retornar (na unidade SI apropriada)
- ** min \ _value **: O valor mínimo que este sensor pode retornar (na unidade SI apropriada)
- ** resolução **: A menor diferença entre dois valores que este sensor pode relatar (na unidade SI apropriada)
- ** min \ _delay **: O atraso mínimo em microssegundos entre dois eventos de sensor, ou '0' se não houver taxa de sensor constante

** Dados / eventos do sensor (sensores \ _event \ _t) **

Este typedef é usado para retornar dados de sensor de qualquer sensor suportado pela camada de abstração, usando escalas e unidades SI padrão.

`` `c ++
/ * Evento do sensor (36 bytes) * /
/ ** struct sensor_event_s é usado para fornecer um único evento de sensor em um formato comum. * /
estrutura de typedef
{
    versão int32_t;
    int32_t sensor_id;
    int32_t type;
    int32_t reserved0;
    int32_t timestamp;
    União
    {
        dados flutuantes [4];
        sensores_vec_t aceleração;
        sensores_vec_t magnético;
        orientação sensores_vec_t;
        sensores_vec_t gyro;
        temperatura de flutuação;
        distância de flutuação;
        luz flutuante;
        pressão de flutuação;
        float relative_humidity;
        float current;
        tensão flutuante;
        sensores_color_t color;
    };
} sensores_evento_t;
`` `
Inclui os seguintes campos:

- ** versão **: contém 'sizeof (sensores \ _event \ _t)' para identificar qual versão da API estamos usando, caso isso mude no futuro
- ** sensor \ _id **: um identificador de sensor exclusivo que é usado para diferenciar esta instância de sensor específica de qualquer outra que esteja presente no sistema ou na rede de sensores (deve corresponder ao valor do sensor \ _id no sensor correspondente \ _t enum acima!)
- ** tipo **: o tipo de sensor, baseado em ** sensores \ _tipo \ _t ** em sensores.h
- ** carimbo de data / hora **: tempo em milissegundos em que o valor do sensor foi lido
- ** dados [4] **: uma matriz de quatro valores de 32 bits que nos permite encapsular qualquer tipo de dados do sensor por meio de uma união simples (descrito com mais detalhes abaixo)

** Funções necessárias **

Além dos dois tipos padrão e do tipo de sensor enum, todos os drivers baseados em Adafruit_Sensor também devem implementar as duas funções a seguir:

`` `c ++
bool getEvent (sensores_event_t *);
`` `
Chamar esta função preencherá a referência \ _event \ _t dos sensores fornecidos com os dados de sensor mais recentes disponíveis. Você deve chamar esta função sempre que desejar atualizar seus dados.

`` `c ++
void getSensor (sensor_t *);
`` `
Chamar esta função fornecerá algumas informações básicas sobre o sensor (o nome do sensor, versão do driver, valores mínimo e máximo, etc.

** Valores SI padronizados para sensores \ _event \ _t **

Uma parte fundamental da camada de abstração é a padronização de valores em unidades SI de uma escala particular, que é realizada por meio da união de dados [4] nos sensores \ _evento \ _t acima. Esta união de 16 bytes inclui campos para cada tipo de sensor principal e usa as seguintes unidades e escalas SI:

- ** aceleração **: os valores estão em ** metros por segundo por segundo ** (m / s ^ 2)
- ** magnético **: os valores estão em ** micro-Tesla ** (uT)
- ** orientação **: os valores estão em ** graus **
- ** giroscópio **: os valores estão em ** rad / s **
- ** temperatura **: valores em ** graus centígrados ** (Celsius) 
- ** distância **: os valores estão em ** centímetros **
- ** luz **: os valores estão em unidades ** SI lux **
- ** pressão **: os valores estão em ** hectopascal ** (hPa)
- ** relativa \ _umidade **: os valores estão em ** por cento **
- ** atual **: os valores estão em ** miliamperes ** (mA)
- ** tensão **: os valores estão em ** volts ** (V)
- ** cor **: os valores estão em 0..1.0 luminosidade do canal RGB e formato RGBA de 32 bits

## A camada de abstração de driver unificada na prática ##

Usar a camada de abstração de sensor unificado é relativamente fácil, uma vez que um driver compatível foi criado.

Cada sensor compatível agora pode ser lido usando um único 'tipo' conhecido (sensores \ _event \ _t), e há uma maneira padronizada de interrogar um sensor sobre suas capacidades específicas (via sensor \ _t).

Um exemplo de leitura do sensor de luz [TSL2561] (https://github.com/adafruit/Adafruit_TSL2561) pode ser visto abaixo:

`` `c ++
 Adafruit_TSL2561 tsl = Adafruit_TSL2561 (TSL2561_ADDR_FLOAT, 12345);
 ...
 / * Obter um novo evento de sensor * / 
 sensores_event_t event;
 tsl.getEvent (& event);
 
 / * Exibir os resultados (a luz é medida em lux) * /
 if (event.light)
 {
   Serial.print (event.light); Serial.println ("lux");
 }
 outro
 {
   / * Se event.light = 0 lux o sensor provavelmente está saturado
      e nenhum dado confiável pôde ser gerado! * /
   Serial.println ("Sobrecarga do sensor");
 }
`` `

Da mesma forma, podemos obter os recursos técnicos básicos deste sensor com o seguinte código:

`` `c ++
 sensor_t sensor;
 
 sensor_t sensor;
 tsl.getSensor (& sensor);

 / * Exibir os detalhes do sensor * /
 Serial.println ("------------------------------------");
 Serial.print ("Sensor:"); Serial.println (sensor.name);
 Serial.print ("Driver Ver:"); Serial.println (sensor.version);
 Serial.print ("ID exclusivo:"); Serial.p ... mais
