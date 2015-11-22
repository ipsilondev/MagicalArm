void setup()
{
  Serial.begin(9600);  // Begin the serial monitor at 9600bps

  Serial3.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  //Serial3.print("$");  // Print three times individually
  //Serial3.print("$");
  //Serial3.print("$");  // Enter command mode
  delay(100);  // Short delay, wait for the Mate to send back CMD
  //Serial3.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  //Serial3.begin(9600);  // Start bluetooth serial at 9600
}

void loop()
{
  if(Serial3.available())  // If the bluetooth sent any characters
  {
    // Send any characters the bluetooth prints to the serial monitor
    Serial.print((char)Serial3.read());  
  }
  if(Serial.available())  // If stuff was typed in the serial monitor
  {
    // Send any characters the Serial monitor prints to the bluetooth
    Serial3.print((char)Serial.read());
  }
  // and loop forever and ever!
}
