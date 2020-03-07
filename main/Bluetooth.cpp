#include "Bluetooth.h"

SoftwareSerial* Bluetooth::ss;

void Bluetooth::init(int RX, int TX, int baud) {
  if (ss == 0) {
    ss = new SoftwareSerial(RX, TX);
    ss->begin(baud);
    if (!ss) {
      while (1);
    }
  }
}

bool Bluetooth::available() {
  if (ss->available() > 0) {
    return true;
  }
  return false;
}

String Bluetooth::read() {
  return ss->read();
}

void Bluetooth::print(String text, bool newline) {
  if (newline) {
    ss->println(text);
  } else {
    ss->print(text);
  }
}
