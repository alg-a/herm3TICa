// function to send the given integer value to the serial port
void sendBinary(int value){
  // send the two byte that comprise an integer
  Serial.write(lowByte(value));
  Serial.write(highByte(value));
}
