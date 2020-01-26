#include "SensorController.h"
  
void SensorController::init() {
  
  // past midnight, this was the only way I could figure out how to make temperature compabile with the rest.
  temperatureData.type = SENSOR_TYPE_TEMPERATURE;
  
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Serial initalized");
  initBNO();
  initBMPs();
  Serial.println("Sensor controller fully initalized");
}

void SensorController::initBNO() {
  bno = new Adafruit_BNO055(sensorID, address);
  if (!bno->begin()) {
    Serial.println("BNO sensor not detected. Check wiring / I2C address.");
    while (1);
  }
  Serial.println("BNO sensor initalized");
  
}

void SensorController::initBMPs(){
  Adafruit_BMP280 bmp1;
  Adafruit_BMP280 bmp2;
  Adafruit_BMP280 bmp3;

  if (!bmp1.begin() || !bmp2.begin() || !bmp3.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1);
  }

    /* Default settings from datasheet. */
  bmp1.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
    /* Default settings from datasheet. */
  bmp2.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
    /* Default settings from datasheet. */
  bmp3.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  Serial.println("all BMP sensors initialized");
}

void SensorController::recordData() {
  bno->getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
  bno->getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
  bno->getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);
  bno->getEvent(&accelerometerData, Adafruit_BNO055::VECTOR_ACCELEROMETER);
  bno->getEvent(&magnetometerData, Adafruit_BNO055::VECTOR_MAGNETOMETER);
  bno->getEvent(&gravityData, Adafruit_BNO055::VECTOR_GRAVITY);

  //record BMP data
  bmp1Data[0] = bmp1.readTemperature();
  bmp1Data[1] = bmp1.readPressure();
  bmp1Data[2] = bmp1.readAltitude();
  //bmp1.readAltitude(101500); Need to adjust to local forecast

  bmp2Data[0] = bmp2.readTemperature();
  bmp2Data[1] = bmp2.readPressure();
  bmp2Data[2] = bmp2.readAltitude();
  //bmp2.readAltitude(101500); Need to adjust to local forecast

  bmp3Data[0] = bmp3.readTemperature();
  bmp3Data[1] = bmp3.readPressure();
  bmp3Data[2] = bmp3.readAltitude();
  //bmp3.readAltitude(101500); Need to adjust to local forecast
}

void SensorController::correctData(){
  //Temperature
  if(abs(bmp1Data[0] - bmp2Data[0]) < bmpTemp_Threshold && abs(bmp2Data[0] - bmp3Data[0]) < bmpTemp_Threshold && abs(bmp3Data[0] - bmp1Data[0]) < bmpTemp_Threshold){
    bmpCorrectedData[0] = (bmp1Data[0] + bmp2Data[0] + bmp3Data[0]) / 3;
  }
  else if (abs(bmp1Data[0] - bmp2Data[0]) < bmpTemp_Threshold){
    bmpCorrectedData[0] = (bmp1Data[0] + bmp2Data[0]) / 2;
  }
  else if(abs(bmp2Data[0] - bmp3Data[0]) < bmpTemp_Threshold){
    bmpCorrectedData[0] = (bmp2Data[0] + bmp3Data[0]) / 2;
  }
  else if(abs(bmp3Data[0] - bmp1Data[0]) < bmpTemp_Threshold){
    bmpCorrectedData[0] = (bmp3Data[0] + bmp1Data[0]) / 2;
  }
  else{
    //not sure what to do here (although probably won't happen. Hopefully.)
//    int delta1 = abs(bmpCorrectedData[0] - bmp1Data[0]);
//    int delta2 = abs(bmpCorrectedData[0] - bmp2Data[0]);
//    int delta3 = abs(bmpCorrectedData[0] - bmp3Data[0]);
  }

  //Pressure
  if(abs(bmp1Data[1] - bmp2Data[1]) < bmpPressure_Threshold && abs(bmp2Data[1] - bmp3Data[1]) < bmpPressure_Threshold && abs(bmp3Data[1] - bmp1Data[1]) < bmpPressure_Threshold){
    bmpCorrectedData[1] = (bmp1Data[1] + bmp2Data[1] + bmp3Data[1]) / 3;
  }
  else if (abs(bmp1Data[1] - bmp2Data[1]) < bmpPressure_Threshold){
    bmpCorrectedData[1] = bmp1Data[1];
  }
  else if(abs(bmp2Data[1] - bmp3Data[1]) < bmpPressure_Threshold){
    bmpCorrectedData[1] = bmp2Data[1];
  }
  else if(abs(bmp3Data[1] - bmp1Data[1]) < bmpPressure_Threshold){
    bmpCorrectedData[1] = bmp3Data[1];
  }
  else{
    //not sure what to do here (although probably won't happen. Hopefully.)
//    int delta1 = abs(bmpCorrectedData[1] - bmp1Data[1]);
//    int delta2 = abs(bmpCorrectedData[1] - bmp2Data[1]);
//    int delta3 = abs(bmpCorrectedData[1] - bmp3Data[1]);
  }

  //Altitude
  if(abs(bmp1Data[2] - bmp2Data[2]) < bmpAltitude_Threshold && abs(bmp2Data[2] - bmp3Data[2]) < bmpAltitude_Threshold && abs(bmp3Data[2] - bmp1Data[2]) < bmpAltitude_Threshold){
    bmpCorrectedData[2] = (bmp1Data[2] + bmp2Data[2] + bmp3Data[2]) / 3;
  }
  else if (abs(bmp1Data[2] - bmp2Data[2]) < bmpAltitude_Threshold){
    bmpCorrectedData[2] = bmp1Data[2];
  }
  else if(abs(bmp2Data[2] - bmp3Data[2]) < bmpAltitude_Threshold){
    bmpCorrectedData[2] = bmp2Data[2];
  }
  else if(abs(bmp3Data[2] - bmp1Data[2]) < bmpAltitude_Threshold){
    bmpCorrectedData[2] = bmp3Data[2];
  }
  else{
    //not sure what to do here (although probably won't happen. Hopefully.)
//    int delta1 = abs(bmpCorrectedData[2] - bmp1Data[2]);
//    int delta2 = abs(bmpCorrectedData[2] - bmp2Data[2]);
//    int delta3 = abs(bmpCorrectedData[2] - bmp3Data[2]);
  }
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
  } else if (type == "temperature") {
    event = &temperatureData;
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
    case SENSOR_TYPE_TEMPERATURE: {
      Serial.println("TEMPERATURE (Celsius)");
      Serial.println(String(bno->getTemp()));
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

void SensorController::printBMPData(){
    Serial.print(F("Temperature = "));
    Serial.print(bmpCorrectedData[0]);
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmpCorrectedData[1]);
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmpCorrectedData[2]); /* Adjusted to local forecast! */
    Serial.println(" m");
}

void SensorController::readData() {

}

/*
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
