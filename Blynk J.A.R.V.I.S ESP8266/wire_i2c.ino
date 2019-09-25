void expansionDWrite(int pin, int value){
  pin = pin-100;
  Wire.beginTransmission(8);
  Wire.write(pin);
  Wire.write(value);
  Wire.write('D');
  Wire.write('W');
  Wire.endTransmission();
  Serial.print(pin);
  Serial.print(value);
}
void expansionAWrite(int pin, int value){
  pin = pin-100;
  Wire.beginTransmission(8);
  Wire.write(pin);
  Wire.write(value);
  Wire.write('A');
  Wire.write('W');
  Wire.endTransmission();
  Serial.print(pin);
  Serial.print(value);
}

int expansionARead(int pin){
  pin = pin-100;
  Wire.beginTransmission(8);
  Wire.write(pin);
  Wire.write(0);
  Wire.write('A');
  Wire.write('R');
  Wire.endTransmission();
  //int value = Wire.read();
  int value=Wire.requestFrom(8,2);
  //Wire.read(value);
  Serial.print(pin);
  Serial.print(value);
  return value;
}

int expansionDRead(int pin){
  pin = pin-100;
  Wire.beginTransmission(8);
  Wire.write(pin);
  Wire.write(0);
  Wire.write('D');
  Wire.write('R');
  //int value = Wire.read();
  Wire.endTransmission();
  //int value = Wire.read();
  int value=Wire.requestFrom(8,2);
  //Wire.read(value);
  Serial.print(pin);
  Serial.print(value);
  return value;
}
