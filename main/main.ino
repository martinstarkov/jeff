#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "SensorController.h"

SensorController* controller;

void setup(void)
{
  controller = new SensorController();
  controller->init();
  
  delay(1000);
}

void loop(void)
{
  controller->recordData();
  controller->printData(controller->getData("orientation"));
  controller->printData(controller->getData("l_acceleration"));
  controller->printData(controller->getData("a_acceleration"));
  controller->printData(controller->getData("gyroscope"));
  controller->printData(controller->getData("magnetic"));
  controller->printData(controller->getData("temperature"));
  
  delay(controller->refresh_delay);
  /*
  //could add VECTOR_ACCELEROMETER, VECTOR_MAGNETOMETER,VECTOR_GRAVITY...
  sensors_event_t orientationData , angVelocityData , linearAccelData;
  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
  bno.getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
  bno.getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);

  //printEvent(&orientationData);
  //printEvent(&angVelocityData);
  //printEvent(&linearAccelData);

  int8_t boardTemp = bno.getTemp();
  //Serial.print(F("temperature: "));
  //Serial.println(boardTemp);


  delay(BNO055_SAMPLERATE_DELAY_MS);*/
}
/*
void printEvent(sensors_event_t* event) {
  bno.getSensorOffsets(accel_offset_x);
  Serial.println("accel_offset_x: " + String(*accel_offset_x));
  //Serial.print(event->type);
  double x = -1000000, y = -1000000 , z = -1000000; //dumb values, easy to spot problem
  if (event->type == SENSOR_TYPE_ACCELEROMETER) {
    Serial.println("SENSOR_TYPE_ACCELEROMETER");
    x = event->acceleration.x;
    y = event->acceleration.y;
    z = event->acceleration.z;
  }
  else if (event->type == SENSOR_TYPE_ORIENTATION) {
    Serial.println("SENSOR_TYPE_ORIENTATION");
    x = event->orientation.x;
    y = event->orientation.y;
    z = event->orientation.z;
  }
  else if (event->type == SENSOR_TYPE_MAGNETIC_FIELD) {
    Serial.println("SENSOR_TYPE_MAGNETIC_FIELD");
    x = event->magnetic.x;
    y = event->magnetic.y;
    z = event->magnetic.z;
  }
  else if ((event->type == SENSOR_TYPE_GYROSCOPE) || (event->type == SENSOR_TYPE_ROTATION_VECTOR)) {
    Serial.println("SENSOR_TYPE_GYROSCOPE OR SENSOR_TYPE_ROTATION_VECTOR");
    x = event->gyro.x;
    y = event->gyro.y;
    z = event->gyro.z;
  } else {
    
  }

  Serial.print(": x= ");
  Serial.print(x);
  Serial.print(" | y= ");
  Serial.print(y);
  Serial.print(" | z= ");
  Serial.println(z);
}*/
