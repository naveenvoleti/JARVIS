/////////////////////////////////////////////////ULTRASONIC////////////////////////////////

long duration, distance;

void ultrasonic() {
  expansionDWrite(TRIGGERPIN, 0);
  delayMicroseconds(3);

  expansionDWrite(TRIGGERPIN, 1);
  delayMicroseconds(12);

  expansionDWrite(TRIGGERPIN, 0);
  duration = pulseIn(ECHOPIN, 1);
  distance = (duration / 2) / 29.1;
  if (distance > 200) {
    distance = 200;
  }
  Blynk.virtualWrite(V30, distance);
  //Blynk.virtualWrite(V6, distance);
}

//BLYNK_READ(V30){
// Blynk.virtualWrite(V30, distance);
//}

BLYNK_READ(V30) {
  expansionDWrite(TRIGGERPIN, 0);
  delayMicroseconds(3);

  expansionDWrite(TRIGGERPIN, 1);
  delayMicroseconds(12);

  expansionDWrite(TRIGGERPIN, 0);
  duration = pulseIn(ECHOPIN, 1);
  distance = (duration / 2) / 29.1;
  Blynk.virtualWrite(V30, distance);
}

/////////////////////////////////////////////ULTRASONIC END///////////////////////////
