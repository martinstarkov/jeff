#include "SensorController.h" 

SensorController::SensorController() {
  initBNOs();
  initBMPs();
  Bluetooth::print(SUCCESS + "Sensor Controller initialized");
}

void SensorController::initBMPs() {
  bmpCount = 0;
  if (BMP_AMOUNT > 0) {
    for (uint8_t i = 0; i < sizeof(BMPAddresses) / sizeof(uint8_t); i++) { // initalize all BMPs
      BMP280* bmp = new BMP280(&Wire, BMPAddresses[i], STANDARD_PRESSURE);
      if (bmp->initialized()) {
        bmps[bmpCount] = bmp;
        bmpCount++;
      }
      bmp = new BMP280(&Wire1, BMPAddresses[i], STANDARD_PRESSURE);
      if (bmp->initialized()) {
        bmps[bmpCount] = bmp;
        bmpCount++;
      }
    }
    if (bmpCount == BMP_AMOUNT) {
      Bluetooth::print(SUCCESS + String(bmpCount) + "/" + String(BMP_AMOUNT) + " BMP sensor(s) initialized");
    } else if (bmpCount == 0) {
      Bluetooth::print(FAILURE + "No BMP sensor(s) detected");
    } else { // some sensors but not all have initialized correctly
      Bluetooth::print(WARNING + String(bmpCount) + "/" + String(BMP_AMOUNT) + " BMP sensor(s) initialized");
    }
  }
}

void SensorController::initBNOs() {
  bnoCount = 0;
  if (BNO_AMOUNT > 0) {
    for (uint8_t i = 0; i < sizeof(BNOAddresses) / sizeof(uint8_t); i++) {
      BNO055* bno = new BNO055(&Wire, BNOAddresses[i], BNOIds[i]);
      if (bno->initialized()) {
        bnos[bnoCount] = bno;
        bnoCount++;
      }
    }
    if (bnoCount == BNO_AMOUNT) {
      Bluetooth::print(SUCCESS + String(bnoCount) + "/" + String(BNO_AMOUNT) + " BNO sensor(s) initialized");
    } else if (bnoCount == 0) {
      Bluetooth::print(FAILURE + "No BNO sensor(s) detected");
    } else { // some sensors but not all have initialized correctly
      Bluetooth::print(WARNING + String(bnoCount) + "/" + String(BNO_AMOUNT) + " BNO sensor(s) initialized");
    }
  }
}

RawData SensorController::getRawData() {
  RawData d = {
    .BMPTemperature1 = bmps[0]->getTemperature(), .BMPTemperature2 = bmps[1]->getTemperature(), .BMPTemperature3 = bmps[2]->getTemperature(),
    .pressure1 = bmps[0]->getPressure(), .pressure2 = bmps[1]->getPressure(), .pressure3 = bmps[2]->getPressure(),
    .altitude1 = bmps[0]->getAltitude(), .altitude2 = bmps[1]->getAltitude(), .altitude3 = bmps[2]->getAltitude(),
    .BNOTemperature = bnos[0]->getTemperature(),
    .orientation = bnos[0]->getOrientation(),
    .angularVelocity = bnos[0]->getAngularVelocity(),
    .linearAcceleration = bnos[0]->getLinearAcceleration(),
    .netAcceleration = bnos[0]->getNetAcceleration(),
    .gravity = bnos[0]->getGravity(),
    .magneticField = bnos[0]->getMagneticField()
  };
  return d;
}

ProcessedData SensorController::getProcessedData() {
  ProcessedData d = {
    .BMPTemperature = average(bmps, bmpCount, &BMP280::getTemperature),
    .pressure = average(bmps, bmpCount, &BMP280::getPressure),
    .altitude = average(bmps, bmpCount, &BMP280::getAltitude),
    .BNOTemperature = average(bnos, bnoCount, &BNO055::getTemperature),
    .orientation = average(bnos, bnoCount, &BNO055::getOrientation),
    .angularVelocity = average(bnos, bnoCount, &BNO055::getAngularVelocity),
    .linearAcceleration = average(bnos, bnoCount, &BNO055::getLinearAcceleration),
    .netAcceleration = average(bnos, bnoCount, &BNO055::getNetAcceleration),
    .gravity = average(bnos, bnoCount, &BNO055::getGravity),
    .magneticField = average(bnos, bnoCount, &BNO055::getMagneticField)
  };
  return d;

}

template <typename Array, typename Data, typename Sensor>
Data SensorController::average(Array sensorArray, int count, Data (Sensor::*functionPointer)()) {
  Data sum = Data(); // initialize data type so compiler doesn't complain
  if (count > 0) {
    for (int i = 0; i < count; i++) {
      Data value = (sensorArray[i]->*functionPointer)(); // call function pointer parameter for array parameter
      // pass value through error correction here (check that it isn't crazy)
      sum = sum + value; 
    }
    return sum / count;
  } else {
    return sum;
  }
}

/*
Altitude units: hPa
Altitude inaccuracy: ±1m (±0.12 hPa)

SENSOR_TYPE_ACCELEROMETER = (1) // Gravity + linear acceleration
SENSOR_TYPE_MAGNETIC_FIELD = (2)
SENSOR_TYPE_ORIENTATION = (3)
SENSOR_TYPE_GYROSCOPE = (4)
SENSOR_TYPE_LIGHT = (5)
SENSOR_TYPE_PRESSURE = (6)
SENSOR_TYPE_PROXIMITY = (8)
SENSOR_TYPE_GRAVITY = (9)
SENSOR_TYPE_LINEAR_ACCELERATION = (10) // Acceleration not including gravity
SENSOR_TYPE_ROTATION_VECTOR = (11)
SENSOR_TYPE_RELATIVE_HUMIDITY = (12)
SENSOR_TYPE_AMBIENT_TEMPERATURE = (13)
SENSOR_TYPE_OBJECT_TEMPERATURE = (14)
SENSOR_TYPE_VOLTAGE = (15)
SENSOR_TYPE_CURRENT = (16)
SENSOR_TYPE_COLOR = (17)

SENSOR_TYPE_TEMPERATURE_BNO 69420
SENSOR_TYPE_TEMPERATURE_BMP 69422
SENSOR_TYPE_PRESSURE 69424
SENSOR_TYPE_ALTITUDE 69426
SENSOR_TYPE_SEA_PRESSURE 69428

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
} sensors_event_t;

*/
