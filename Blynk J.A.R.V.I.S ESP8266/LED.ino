BLYNK_WRITE(V6) {
  int ledValue = param.asInt();
    if (ledValue <= 100) {
    ledValue = map(ledValue, 0, 100, 0, 255);
    expansionAWrite(hall, ledValue);
    }
}
BLYNK_WRITE(V20){
 int ledValue = param.asInt();
 Serial.print("value = ");
 Serial.print(expansionDRead(112)); 
}

BLYNK_WRITE(V0) {
  String led = param[0].asStr();
  int ledValue = param[1].asInt();
  Serial.println(led);
  //Blynk.virtualWrite(V6, led);
  //Blynk.virtualWrite(V6, ledValue);
  if (ledValue <= 100) {
    ledValue = map(ledValue, 0, 100, 0, 1024);
    if (led == "hall") {
      expansionAWrite(hall, ledValue);
    }
    else if (led == "bedroom") {
      expansionAWrite(bedroom, ledValue);
    }
  }
}
