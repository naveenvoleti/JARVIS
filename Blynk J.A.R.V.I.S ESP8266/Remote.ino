///////////////////////////////////////////////REMOTE ////////////////////////////////
int tv = 0;

BLYNK_WRITE(V1) {
  String command = param.asStr();
  if (command == "turn on TV" || "On") {
    if (tv = 0) {
      remote(0);
      //irSend(0x80BF1EE1);
      int tv = 1;
    }
  }
  else if (command == "turn off TV" || "Off") {
    if (tv = 1) {
      remote(1);
      //irSend(0x80BF1EE1);
      int tv = 0;
    }
  }
  else if (command == "next channel") {
    remote(2);
    //irSend(0x80BF53AC);
  }
  else if (command == "previous channel") {
    remote(3);
    //irSend(0x80BF4BB4);
  }
  else if (command == "mute TV") {
    remote(4);
    //irSend(0x80BF33CC);
  }
  else if (command == "volume up") {
    remote(5);
    //irSend(0x80BF837C);
  }
  else if (command == "volume down") {
    remote(6);
    //irSend(0x80BF9966);
  }
  //Blynk.virtualWrite(V6, command);
}

/*void irSend(byte code) {
  //for (int i = 0; i < 3; i++) {
  irsend.sendNEC(code , 32);  //(0xD000068A, 32);
  //delay(40);
  //}
}*/
//////////////////////////////////////////REMOTE END//////////////////////////////////////////
