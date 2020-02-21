#include "SensorController.h" 

void SensorController::init() {
  
  
  BT = new SoftwareSerial(BLUETOOTH_RX, BLUETOOTH_TX); // RX, TX
  GPS = new SoftwareSerial(7, 8);
  BT->begin(BLUETOOTH_BAUD_RATE);
  BTPrint("Bluetooth initalized");
  GPS->begin(9600);
  BTPrint("GPS initalized");
  
  //Serial.begin(SERIAL_BAUD_RATE);
  //while (!Serial); // HAHA THIS WAS THE BLUETOOTH ISSUE ALL ALONG
  //Serial.println("Serial initalized");
  
  initBNO();
  
  for (uint8_t i = 0; i < sizeof(BMPAddresses) / sizeof(uint8_t); i++) { // initalize all BMPs
    initBMP(&Wire1, BMPAddresses[i]);
    initBMP(&Wire, BMPAddresses[i]);
  }
  
  BTPrint("Sensor controller fully initalized");
}

void SensorController::BTPrint(String text, bool newline) {
  if (newline) {
    BT->println(text);
  } else {
    BT->print(text);
  }
}

void SensorController::initBNO() {
  bno = new Adafruit_BNO055(BNO_ID, BNO_ADDRESS);
  if (!bno->begin()) {
    BTPrint("BNO sensor not detected. Check wiring / I2C address.");
    //while (1) {}
  }
  BTPrint("BNO sensor initalized");
  
}

void SensorController::initBMP(TwoWire *theWire, uint8_t address) {
  
  Adafruit_BMP280* bmp = new Adafruit_BMP280(theWire);
  
  bmp->setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  
  if (!bmp->begin(address)) {
    BTPrint("BMP sensor not detected. Check wiring.");
    //while (1) {}
  }
  
  bmps[initalizedBmps] = bmp;
  initalizedBmps++;
  
  BTPrint("BMP sensor initalized");
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
    float altitude = bmps[i]->readAltitude(STANDARD_PRESSURE);
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
    float pressure = bmps[i]->readPressure();
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
    float temperature = bmps[i]->readTemperature();
    sum += temperature; // add error correction here
  }
  return sum / BMP_AMOUNT;
}

float SensorController::getTemperature() {
  return getAverageTemperature();
}

void SensorController::gpsListener() {
  if (GPS->available()) {
    String gpsInput = GPS->readString();
    BTPrint(gpsInput);
  }
}

void SensorController::bluetoothListener() {
  //BTPrint("Transmitting"); // show that bluetooth is transmitting
  if (BT->available()) { // if text has arrived from bluetooth serial user input¨
    char userInput = BT->read();
    if (userInput == 'p' && !bmpDebugPressure) {
        bmpDebugPressure = true;
    } else if (userInput == 'p' && bmpDebugPressure) {
        bmpDebugPressure = false;
    } else if (userInput == 'a' && !bmpDebugAltitude) {
        bmpDebugAltitude = true;
    } else if (userInput == 'a' && bmpDebugAltitude) {
        bmpDebugAltitude = false;
    } else if (userInput == 't' && !bmpDebugTemperature) {
        bmpDebugTemperature = true;
    } else if (userInput == 't' && bmpDebugTemperature) {
        bmpDebugTemperature = false;
    }
  }
  debugPrints();
}

void SensorController::debugPrints() {
  if (bmpDebugAltitude || bmpDebugPressure || bmpDebugTemperature) {
    String debugMsg = "";
    for (int i = 0; i < BMP_AMOUNT; i++) {
      debugMsg = "BMP" + String(i) + " |";
      // print individual sensor readings for debugging
      if (bmpDebugAltitude) {
        debugMsg += " Altitude: " + String(bmps[i]->readAltitude(STANDARD_PRESSURE)) + " |";
      }
      if (bmpDebugPressure) {
        debugMsg += " Pressure: " + String(bmps[i]->readPressure()) + " |";
      }
      if (bmpDebugTemperature) {
        debugMsg += " Temperature: " + String(bmps[i]->readTemperature()) + " |";
      }
      BTPrint(debugMsg);
    }
  }
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
