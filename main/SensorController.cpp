#include "SensorController.h" 

void SensorController::init() {
  
  Bluetooth::print("Bluetooth initalized");
  Bluetooth::print("GPS initalized");
  
  initBNO();
  
  initBMPs();
  
  Bluetooth::print("Sensor controller fully initalized");
}

void SensorController::initBMPs() {
  for (uint8_t i = 0; i < sizeof(BMPAddresses) / sizeof(uint8_t); i++) { // initalize all BMPs
    BMP280* bmp1 = new BMP280(&Wire, BMPAddresses[i], 1005);
    BMP280* bmp2 = new BMP280(&Wire1, BMPAddresses[i], 1005);
    bmps[initalizedBmps] = bmp1;
    bmps[(initalizedBmps + 1)] = bmp2;
    initalizedBmps++;
  }
}

void SensorController::initBNO() {
  bno = new Adafruit_BNO055(BNO_ID, BNO_ADDRESS);
  if (!bno->begin()) {
    Bluetooth::print("BNO sensor not detected. Check wiring / I2C address.");
    //while (1) {}
  }
  Bluetooth::print("BNO sensor initalized");
}

void SensorController::recordData() {
  bno->getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
  bno->getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
  bno->getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);
  bno->getEvent(&accelerometerData, Adafruit_BNO055::VECTOR_ACCELEROMETER);
  bno->getEvent(&magnetometerData, Adafruit_BNO055::VECTOR_MAGNETOMETER);
  bno->getEvent(&gravityData, Adafruit_BNO055::VECTOR_GRAVITY);
}

float SensorController::getAverageAltitude() {
  float sum = 0;
  for (int i = 0; i < BMP_AMOUNT; i++) {
    float altitude = bmps[i]->getAltitude();
    sum += altitude; // add error correction here
  }
  return sum / BMP_AMOUNT;
}

float SensorController::getAltitude() {
  return getAverageAltitude();
}

float SensorController::getAveragePressure() {
  float sum = 0;
  for (int i = 0; i < BMP_AMOUNT; i++) {
    float pressure = bmps[i]->getPressure();
    sum += pressure; // add error correction here
  }
  return sum / BMP_AMOUNT;
}

float SensorController::getPressure() {
  return getAveragePressure();
}

float SensorController::getAverageTemperature() {
  float sum = 0;
  for (int i = 0; i < BMP_AMOUNT; i++) {
    float temperature = bmps[i]->getTemperature();
    sum += temperature; // add error correction here
  }
  return sum / BMP_AMOUNT;
}

float SensorController::getTemperature() {
  return getAverageTemperature();
}

/*
 Altitude units: hPa
 Altitude inaccuracy: ±1m (±0.12 hPa)
SENSOR_TYPE_ACCELEROMETER = (1), // Gravity + linear acceleration
SENSOR_TYPE_MAGNETIC_FIELD = (2),
SENSOR_TYPE_ORIENTATION = (3),
SENSOR_TYPE_GYROSCOPE = (4),
SENSOR_TYPE_LIGHT = (5),
SENSOR_TYPE_PRESSURE = (6),
SENSOR_TYPE_PROXIMITY = (8),
SENSOR_TYPE_GRAVITY = (9),
SENSOR_TYPE_LINEAR_ACCELERATION = (10), // Acceleration not including gravity
SENSOR_TYPE_ROTATION_VECTOR = (11),
SENSOR_TYPE_RELATIVE_HUMIDITY = (12),
SENSOR_TYPE_AMBIENT_TEMPERATURE = (13),
SENSOR_TYPE_OBJECT_TEMPERATURE = (14),
SENSOR_TYPE_VOLTAGE = (15),
SENSOR_TYPE_CURRENT = (16),
SENSOR_TYPE_COLOR = (17)

typedef struct {
  int32_t version;   // must be sizeof(struct sensors_event_t) 
  int32_t sensor_id; // unique sensor identifier 
  int32_t type;      // sensor type 
  int32_t reserved0; // reserved 
  int32_t timestamp; // time is in milliseconds 
  union {
    float data[4];              // Raw data
    sensors_vec_t acceleration; // acceleration values are in meter per second per second (m/s^2) 
    sensors_vec_t magnetic; // magnetic vector values are in micro-Tesla (uT) 
    sensors_vec_t orientation; // orientation values are in degrees 
    sensors_vec_t gyro;        // gyroscope values are in rad/s 
    float temperature; // temperature is in degrees centigrade (Celsius) 
    float distance;    // distance in centimeters 
    float light;       // light in SI lux units 
    float pressure;    // pressure in hectopascal (hPa) 
    float relative_humidity; // relative humidity in percent 
    float current;           // current in milliamps (mA) 
    float voltage;           // voltage in volts (V) 
    sensors_color_t color;   // color in RGB component values 
  };                         // Union for the wide ranges of data we can carry
} sensors_event_t;


*/
