#include "SensorController.h"

void SensorController::init() {
  
  // past midnight, this was the only way I could figure out how to make temperature compabile with the rest.
  bnoTemperatureData.type = SENSOR_TYPE_TEMPERATURE_BNO;
  bmpTemperatureData.type = SENSOR_TYPE_TEMPERATURE_BMP;
  pressureData.type = SENSOR_TYPE_PRESSURE;
  altitudeData.type = SENSOR_TYPE_ALTITUDE;
  seaPressureData.type = SENSOR_TYPE_SEA_PRESSURE;
  
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Serial initalized");
  initBNO();
  initBMP();
  Serial.println("Sensor controller fully initalized");
}

void SensorController::initBNO() {
  bno = new Adafruit_BNO055(sensorID, address);
  if (!bno->begin()) {
    Serial.println("BNO sensor not detected. Check wiring / I2C address.");
    while (1) {}
  }
  Serial.println("BNO sensor initalized");
  
}

void SensorController::initBMP() {
  bmp = new Adafruit_BMP280();
    bmp->setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
    Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
    Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
    Adafruit_BMP280::FILTER_X16,      /* Filtering. */
    Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  if (!bmp->begin()) {
    Serial.println("BMP sensor not detected. Check wiring.");
   // while (1) {}
  }
  Serial.println("BMP sensor initalized");
}

void SensorController::recordData() {
  bno->getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
  bno->getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
  bno->getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);
  bno->getEvent(&accelerometerData, Adafruit_BNO055::VECTOR_ACCELEROMETER);
  bno->getEvent(&magnetometerData, Adafruit_BNO055::VECTOR_MAGNETOMETER);
  bno->getEvent(&gravityData, Adafruit_BNO055::VECTOR_GRAVITY);
}

sensors_event_t* SensorController::getData(String type) {
  sensors_event_t* event = nullptr;
  if (type == "orientation") {
    event = &orientationData;
  } else if (type == "gyroscope") {
    event = &angVelocityData;
  } else if (type == "a_acceleration") {
    event = &linearAccelData;
  } else if (type == "l_acceleration") {
    event = &accelerometerData;
  } else if (type == "magnetic") {
    event = &magnetometerData;
  } else if (type == "gravity") {
    event = &gravityData;
  } else if (type == "bnoTemperature") {
    event = &bnoTemperatureData;
  } else if (type == "bmpTemperature") {
    event = &bmpTemperatureData;
  } else if (type == "pressure") {
    event = &pressureData;
  } else if (type == "sea_pressure") {
    event = &seaPressureData;
  } else if (type == "altitude") {
    event = &altitudeData;
  }
  return event;
}

void SensorController::printData(sensors_event_t* event) {
  switch (event->type) {
    case SENSOR_TYPE_ORIENTATION: {
      Serial.println("ORIENTATION (degrees)");
      Serial.println("x = " + String(event->orientation.x) + ", y = " + String(event->orientation.y) + ", z = " + event->orientation.z);
      break;
    }
    case SENSOR_TYPE_ACCELEROMETER: {
      Serial.println("ACCELEROMETER (gravity) (m/s^2)");
      Serial.println("x = " + String(event->acceleration.x) + ", y = " + String(event->acceleration.y) + ", z = " + event->acceleration.z);
      break;
    }
    case SENSOR_TYPE_LINEAR_ACCELERATION: {
      Serial.println("LINEAR ACCELERATION (no gravity) (m/s^2)");
      Serial.println("x = " + String(event->acceleration.x) + ", y = " + String(event->acceleration.y) + ", z = " + event->acceleration.z);
      break;
    }
    case SENSOR_TYPE_MAGNETIC_FIELD: {
      Serial.println("MAGNETIC FIELD (uT)");
      Serial.println("x = " + String(event->magnetic.x) + ", y = " + String(event->magnetic.y) + ", z = " + event->magnetic.z);
      break;
    }
    case SENSOR_TYPE_TEMPERATURE_BNO: {
      Serial.println("TEMPERATURE (Celsius)");
      Serial.println(String(bno->getTemp()));
      break;
    }
    case SENSOR_TYPE_TEMPERATURE_BMP: {
      Serial.println("BMP TEMPERATURE (Celsius)");
      Serial.println(String(bmp->readTemperature()));
      break;
    }
    /*case SENSOR_TYPE_TEMPERATURE_BNO: {
      Serial.println("BNO TEMPERATURE (Celsius)");
      Serial.println(String(bno->getTemp()));
      break;
    }*/
    case SENSOR_TYPE_PRESSURE: {
      Serial.println("PRESSURE (Pa)");
      Serial.println(String(bmp->readPressure()));
      break;
    }
    case SENSOR_TYPE_ALTITUDE: {
      // Calculate altitude assuming 'standard' barometric
      // pressure of 1013.25 millibar = 101325 Pascal
      Serial.println("ALTITUDE (m)");
      Serial.println(String(bmp->readAltitude(103520)));
      break;
    }
    case SENSOR_TYPE_ROTATION_VECTOR:
    case SENSOR_TYPE_GYROSCOPE: {
      Serial.println("GYROSCOPE / ROTATION (rad/s)");
      Serial.println("x = " + String(event->gyro.x) + ", y = " + String(event->gyro.y) + ", z = " + event->gyro.z);
      break;
    }
  }
  Serial.println("-------------------------------------------------------");
}

void SensorController::readData() {

}

float SensorController::getAltitude(float standardPressure) {
  return bmp->readAltitude(standardPressure);
}

float SensorController::getPressure() {
  return bmp->readPressure();
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
