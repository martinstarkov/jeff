
void setup()  
{
  // set the data rate for the SoftwareSerial port
  Serial2.begin(9600);
  // Send test message to other device
}
void loop() 
{
  Serial2.println("Hi");
}
