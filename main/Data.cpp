#include "Data.h"

Data* Data::instance = 0;
DynamicJsonDocument Data::document(JSON_ALLOCATION);

Data* Data::getInstance() {
  if (instance == 0) {
    instance = new Data();
  }
  return instance;
}

Data::Data() {
  document.createNestedObject(RAW);
  document.createNestedObject(PROCESSED);
  document.createNestedObject(FILTERED);
  document.createNestedObject(STATUS);
  document.createNestedArray(DEBUG);
  set(STATUS, "airbrake_usage", false);
}

String Data::getString(bool pretty) {
  String output = "";
  if (pretty) {
    serializeJsonPretty(document, output);
  } else {
    serializeJson(document, output);
  }
  return output;
}

void Data::set(String format, String type, int value) {
  document[format][type] = value;
}

void Data::set(String format, String type, float value) {
  document[format][type] = value;
}

void Data::set(String format, String type, double value) {
  document[format][type] = value;
}

void Data::set(String format, String type, float values[], int length) {
  JsonArray d = document[format].createNestedArray(type);
  for (int i = 0; i < length; i++) {
    d.add(values[i]);
  }
}

void Data::set(String format, String type, bool value) {
  document[format][type] = value;
}

void Data::set(String format, String type, Vector3D value) {
  // Vector string
  //document[format][type] = String(value);
  // JSON array alternative
  JsonArray d = document[format].createNestedArray(type);
  d.add(value.x);
  d.add(value.y);
  d.add(value.z);
}

void Data::set(String format, String value) {
  document[format].add(value);
}

void Data::clear(String format) {
  if (document[format].is<JsonArray>()) { // debug
    JsonArray array = document[format].as<JsonArray>();
    //Serial.println("Clearing " + String(array.size()) + " debug entries");
    for(JsonArray::iterator it=array.begin(); it!=array.end(); ++it) {
      array.remove(it);
    }
  } else {
    for (JsonObject::iterator it=document[format].as<JsonObject>().begin(); it!=document[format].as<JsonObject>().end(); ++it) {
      document[format].remove(it->key().c_str());
    }
  }
}

void Data::clearData() {
  clear(RAW);
  clear(PROCESSED);
  clear(FILTERED);
}
