#include "Data.h"

String Data::debug = "";
String Data::raw = "";
String Data::processed = "";
String Data::filtered = "";
String Data::status = "";
String Data::combined = "";
String Data::command = "";

String& Data::getString(String format) {
  if (format == PROCESSED) {
    return processed;
  } else if (format == FILTERED) {
    return filtered;
  } else if (format == STATUS) {
    return status;
  } else if (format == DEBUG) {
    return debug;
  } else if (format == RAW) {
    return raw;
  }
  combined = processed + raw + filtered + status + debug;
  return combined;
}

void Data::add(String type, String value) {
  processed += type + SEPARATE_CHAR + value + END_CHAR;
}

void Data::clearData() {
  raw = "";
  processed = "";
  filtered = "";
}

void Data::set(String format, String type, String value) {
  String& string = getString(format);
  int startIndex = string.indexOf(type);
  String replacement = type + SEPARATE_CHAR + value + END_CHAR;
  if (startIndex == -1) { // string does not contain type
    string += replacement;
  } else { // replace old with new
    int stopIndex = string.indexOf(END_CHAR, startIndex);
    String current = string.substring(startIndex, stopIndex + END_CHAR.length());
    string.replace(current, replacement);
  }
}

String Data::get(String format, String type) {
  String& string = getString(format);
  int startIndex = string.indexOf(type);
  int stopIndex = string.indexOf(END_CHAR, startIndex);
  return string.substring(startIndex + type.length() + SEPARATE_CHAR.length(), stopIndex);
}
