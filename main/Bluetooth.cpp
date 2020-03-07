#include "Bluetooth.h"

SoftwareSerial* Bluetooth::ss;

void Bluetooth::init(int RX, int TX, int baud) {
  if (ss == 0) {
    ss = new SoftwareSerial(RX, TX);
    ss->begin(baud);
    ss->println("Bluetooth initalized successfully"):
  }
}

void Bluetooth::print(String text, bool newline) {
  if (newline) {
    ss->println(text);
  } else {
    ss->print(text);
  }
}
