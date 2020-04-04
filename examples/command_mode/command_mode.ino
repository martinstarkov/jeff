void setup()
{
  Serial.println("Enter AT commands:");
  Serial2.begin(38400);
}

void loop()
{

  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (Serial2.available())
    Serial.write(Serial2.read());

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
    Serial2.write(Serial.read());
}
