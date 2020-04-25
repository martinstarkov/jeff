#include "Data.h"

String Data::data = "";
String Data::command = "";
Stage Data::stage;

void Data::setCommand(String newCommand) {
  command = newCommand;
}

String Data::getCommand() {
  return command;
}

void Data::setStage(Stage newStage) {
  stage = newStage;
}

Stage Data::getStage() {
  return stage;
}

String Data::getData() {
  return data;
}

void Data::clearData() {
  data = "";
}

String Data::get(String property) {
  int startIndex = data.indexOf(property);
  int stopIndex = data.indexOf(END_PROPERTY_CHAR, startIndex);
  return data.substring(startIndex + property.length() + strlen(SEPARATE_PROPERTY_CHAR), stopIndex);
}

void Data::add(String property, String value) {
  data += property + SEPARATE_PROPERTY_CHAR + value + END_PROPERTY_CHAR;
}
