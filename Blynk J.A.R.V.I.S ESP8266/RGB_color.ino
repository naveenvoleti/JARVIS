//////////////////////////////////////////COLOR/////////////////////////////////////////////////
#define commonAnode

BLYNK_WRITE(V4) {
  String Color = param.asStr();
  Serial.println(Color);
  //while(set=0){
  colorChange(Color);
  //}
}

void setColor(int red, int green, int blue)
{
#ifdef commonAnode
  //expansionDWrite(vcc, HIGH);
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  expansionAWrite(redPin, red);
  expansionAWrite(greenPin, green);
  expansionAWrite(bluePin, blue);
}

BLYNK_WRITE(V5) {
  int r = param[0].asInt(); // getting first value
  int g = param[1].asInt(); // getting second value
  int b = param[2].asInt(); // getting thrid value
  setColor(r, g, b);
}

void colorChange(String Color) {
  if (Color == "green") {
    setColor(0, 255, 0);                      // green
  }
  else if (Color == "red") {
    setColor(255, 0, 0);                      // red
  }
  else if (Color == "blue") {
    setColor(0, 0, 255);                      // blue
  }
  else if (Color == "yellow") {
    setColor(255, 255, 0);                   // yellow
  }
  else if (Color == "purple") {
    setColor(80, 0, 80);                     // purple
  }
  else if (Color == "Aqua") {      // aqua
    setColor(0, 255, 255);
  }
  else if (Color == "Magenta") {
    setColor(255, 0, 255);                    // Magenta
  }
  else if (Color == "white") {
    setColor(255, 255, 255);                  // white
  }
  else if (Color == "Raspberry") {
    setColor(255, 255, 125); // Raspberry
  }
  else if (Color ==  "off") {
    setColor(0, 0, 0);                        // off
  }
  else {
    setColor(0, 0, 0);
    //expansionDWrite(vcc,HIGH);// off
    Serial.print("i can't find " + Color + " color");
  }
  //Blynk.virtualWrite(V6, "set color " + Color);
}

///////////////////////////////////////////////////EFFECT MODE///////////////////////////////////
/*
  0 OFF
  1 Candle
  2 Red
  3 Blue
  4 Green
  5 Tricolor
  6 Strobe
  7 Pure White
  8 Broken Light
  9 Yellow flashing (caution)
  10 Psychedelic
  11 Pulse
*/

int potval = 200; // adjusts for magnitude and rate
int choice = 0; // your mode selection


long rprev = 128;
long gprev = 128;
long bprev = 128;

BLYNK_WRITE(V7) {
  int   choice = param.asInt();
  effectMode(choice);
}

int effectMode(int choice) {
  //int potpin = 3; // the pin the potentiometer is on
  //int button = 7; // the pin the button is on.

  // various variables


  // these 'prev' values are for the psychedelic choice

  // initialize the pwm pins as outputs.
  // seed the random number generator
  randomSeed(100);

  /* read the pushbutton to see if it's been pushed
    int val;
    val = digitalRead(button);

    // val = HIGH means the button has been pushed
    // and the mode is to be changed.

    // SELECT CHOICE //////////////////////////////////////////////////
    if(val==HIGH){
    choice = choice + 1;

    expansionAWrite(blue,255);
    expansionAWrite(green,255);
    expansionAWrite(red,255);
    delay(500);

    // indicate mode transition with blue flashes
    for(int i = 0; i<5; i++){
    expansionAWrite(blue,125);
    delay(20);
    expansionAWrite(blue,255);
    delay(40);
    }

    delay(500);*/

  // change this if you want more modes

  if (choice == 12) {
    choice = 0;
  }

  /*
    //TIME TO LIFT BUTTON //////////////////////////////
    // (for debounce)

    while (val == HIGH){
    delay(100);
    val = digitalRead(button);
    }
  */
  //////////////////////////////

  // read the potentiometer value
  //potval = analogRead(potpin);

  // OFF
  if (choice == 0) {
    setColor(0, 0, 0);
  }

  // CANDLE FLAME
  if (choice == 1) {
    flicker();
  }

  // RED

  if (choice == 2) {
    int x = 255 - potval / 4;
    setColor(0 + potval / 4, 0, 0);
  }

  // GREEN
  if (choice == 3) {
    int x = 255 - potval / 4;
    setColor(0, 0 + potval / 4, 0);
  }

  // BLUE

  if (choice == 4) {
    int x = 255 - potval / 4;
    setColor(0, 0, 0 + potval / 4);
    //expansionAWrite(red,255);
    //expansionAWrite(green,255);
    //expansionAWrite(blue,255 - potval/4);
  }

  // tricolor
  if (choice == 5) {
    setColor(0, 0, 0);
    int tricolor;
    for (int j = 0; j < 4; j++) {
      if (j == 0) {
        tricolor = redPin;
      }
      if (j == 1) {
        tricolor = greenPin;
      }
      if (j == 2) {
        tricolor = bluePin;
      }
      expansionAWrite(tricolor, 0);
      delay(522 - potval / 2);
      expansionAWrite(tricolor, 255);
      delay(522 - potval / 2);

    }

  } // end of tricolor

  // STROBE

  if (choice == 6) {
    setColor(255, 255, 255);
    delay(10);
    setColor(0, 0, 0);
    delay(1023 - potval);
  }

  //this is white
  if (choice == 7) {
    setColor(0 + potval / 4, 0 + potval / 4, 0 + potval / 4);
  }

  // Oh no, your light is broken!
  if (choice == 8) {
    int mag8 = random(0, 255);
    setColor(mag8, mag8, mag8);
    int d8 = random(0, 100);
    delay(d8);
    if (random(0, 30) == 0) {
      setColor(0, 0, 0);
      delay(500);
    }
  }

  // Caution-warning yellow flashing light
  if (choice == 9) {
    setColor(255, 130, 0);
    delay(100);
    setColor(0, 0, 0);
    delay(1200);

  }

  // Psychedelic
  if (choice == 10) {

    // When tweaking code, careful with variable types.

    long rnew = random(256);
    long gnew = random(256);
    long bnew = random(256);
    long rval;
    long gval;
    long bval;

    for (int i; i < 101; i++) {
      rval = rprev + long(i * (rnew - rprev) / 100);
      expansionAWrite(redPin, rval);
      delay(5);
    }
    for (int i; i < 101; i++) {
      gval = gprev + long(i * (gnew - gprev) / 100);
      expansionAWrite(greenPin, gval);
      delay(5);
    }
    for (int i; i < 300;) {
      int p = bluePin;
    }
    if (potval > 600) {
      int p = greenPin;
    }
    for (int i = 0; i < 256; i++) {
      //expansionAWrite(p,0+i);
      delay(4);
    }
    for (int i = 0; i < 256; i++) {
      //expansionAWrite(p,i);
      delay(4);
    }
    delay(500);

  } // end of choice 11

} // end of loop, loop, loopy-doop!
////////////////////////////////////////////////////////////

void flicker() {

  // makes a flickering candle light

  int k = random(0, 100);
  //potval = analogRead(potpin);
  float p = float(potval) / 1023;

  int rmag = 255 - (15 + 155 * k / 100) * p;
  int gmag = 255 - (10 + 55 * k / 100) * p;

  expansionAWrite(redPin, rmag);
  expansionAWrite(greenPin, gmag);

  int d = 50 + 300 * random(0, 100) / 300;

  delay(d);

}

////////////////////////////////////////////////

void tricolor() {

  // transitions between red, blue, and green lights
  setColor(0, 0, 0);

  expansionAWrite(redPin, 0);
  delay(500);
  expansionAWrite(redPin, 255);
  delay(500);

  expansionAWrite(greenPin, 0);
  delay(500);
  expansionAWrite(greenPin, 255);
  delay(500);

  expansionAWrite(bluePin, 0);
  delay(500);
  expansionAWrite(bluePin, 255);
  delay(500);

}

///////////////////////////////////////////////////COLOR END///////////////////////////////////
