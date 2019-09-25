/////////////////////////////////////////////////MOTOR///////////////////////////////////////
BLYNK_WRITE(V2) {
  int speed = param.asInt();
  if (speed <= 100) {
    speed = map(speed, 0, 100, 0, 255);
    expansionAWrite(motorSpeed, speed);
    Serial.print("Fan speed set to" + speed);
  }
}

BLYNK_WRITE(V3) {
  int motorDir = param.asInt();
  if (motorDir == 0) {
    expansionDWrite(motorA, HIGH);
    expansionDWrite(motorB, LOW);
  }
  else if (motorDir == 1) {
    expansionDWrite(motorA, LOW);
    expansionDWrite(motorB, HIGH);
  }
}
//////////////////////////////////////////MOTOR END/////////////////////////////////////////////
