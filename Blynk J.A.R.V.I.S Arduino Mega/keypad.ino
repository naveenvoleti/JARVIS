void getPassKey() {

  if (customKey)
  {
    passcode[i++] = customKey;
    lcd.print(customKey);
    Serial.print(customKey);
    //    beep();
  }
  if (i == 4)
  {
    delay(200);
    for (int j = 0; j < 4; j++)
      pass0[j] = EEPROM.read(j);
    if (!(strncmp(passcode, pass0, 4)))
    {
      //Serial.println("place ur finger");
      //fpsRead();
      //digitalWrite(led, HIGH);
      //      beep();
      lcd.clear();
      lcd.print("Passkey Accepted");
      Serial.print("Passkey Accepted");
      delay(1000);
      lcd.setCursor(0, 1);
      lcd.print("#.Change Passkey");
      Serial.print("#.Change Passkey");
      delay(1000);
      //lcd.clear();
      //lcd.print("Enter Passkey:");
      //Serial.print("Enter Passkey:");
      lcd.setCursor(0, 1);
      //digitalWrite(led, LOW);
      scanned = false;
      fpsRead();
      customKey = 0;
      i = 0;
      lcd.clear();
      lcd.print("Enter Ur Passkey:");
      Serial.print("Enter Ur Passkey:");
      lcd.setCursor(0, 1);
    }

    else
    {
      //digitalWrite(buzzer, HIGH);
      lcd.clear();
      lcd.print("Access Denied...");
      Serial.print("Access Denied...");
      lcd.setCursor(0, 1);
      lcd.print("#.Change Passkey");
      Serial.print("#.Change Passkey");
      delay(2000);
      lcd.clear();
      lcd.print("Enter Passkey:");
      Serial.print("Enter Passkey:");
      lcd.setCursor(0, 1);
      i = 0;
      //    digitalWrite(buzzer, LOW);
      scanned = false;
    }
  }
}

void change()
{
  int j = 0;
  int k = 0;
  lcd.clear();
  lcd.print("UR Current Passk");
  Serial.print("UR Current Passk");
  lcd.setCursor(0, 1);
  while (j < 4)
  {
    char key = customKeypad.getKey();
    if (key)
    {
      pass1[j++] = key;
      lcd.print(key);
      Serial.print(key);
      //      beep();
    }
    key = 0;
  }
  delay(500);

  if ((strncmp(pass1, pass0, 4)))
  {
    lcd.clear();
    lcd.print("Wrong Passkey...");
    Serial.print("Wrong Passkey...");
    lcd.setCursor(0, 1);
    lcd.print("Better Luck Again");
    Serial.print("Better Luck Again");
    delay(1000);
  }
  else
  {
    j = 0;
    k = 0;
    Serial.print("press * to fpEnroll and # to passcode change");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("*.to fpEnroll");
    lcd.setCursor(0, 1);
    lcd.print("#.to pass change");
    while (k < 1) {
      char newKey = customKeypad.getKey();
      if (newKey == '*') {
        newKey = 0;
        fpsEnroll();
        k++;
      }
      else if (newKey == '#')
      {
        newKey = 0;
        lcd.clear();
        lcd.print("Enter New Passk:");
        Serial.print("Enter New Passk:");
        lcd.setCursor(0, 1);
        while (j < 4)
        {
          char key = customKeypad.getKey();
          if (key)
          {
            pass0[j] = key;
            lcd.print(key);
            Serial.print(key);
            EEPROM.write(j, key);
            j++;
            //        beep();
          }
        }
        lcd.print("  Done......");
        Serial.print("  Done......");
        delay(1000);
        k++;
      }
    }
  }
  lcd.clear();
  lcd.print("Enter Ur Passk:");
  Serial.print("Enter Ur Passk:");
  lcd.setCursor(0, 1);
  j = 0;
}

/*void beep()
  {
  digitalWrite(buzzer, HIGH);
  delay(20);
  digitalWrite(buzzer, LOW);
  }*/

void fpsEnroll() {
  fps.Open();         //send serial command to initialize fps
  fps.SetLED(true);
  int enrollid = 0;
  bool usedid = true;
  while (usedid == true)
  {
    usedid = fps.CheckEnrolled(enrollid);
    if (usedid == true) enrollid++;
  }
  fps.EnrollStart(enrollid);

  // enroll
  Serial.print("Press finger to Enroll#");
  lcd.clear();
  lcd.print("Press to Enroll#");
  Serial.println(enrollid);
  while (fps.IsPressFinger() == false) delay(100);
  bool bret = fps.CaptureFinger(true);
  int iret = 0;
  if (bret != false)
  {
    Serial.println("Remove finger");
    fps.Enroll1();
    lcd.clear();
    lcd.println("Remove finger");
    while (fps.IsPressFinger() == true) delay(100);
    lcd.clear();
    lcd.println("Press same fingr");
    lcd.setCursor(0, 1);
    lcd.println("again");
    Serial.println("Press same finger again");
    while (fps.IsPressFinger() == false) delay(100);
    bret = fps.CaptureFinger(true);
    if (bret != false)
    {
      lcd.clear();
      lcd.println("Remove finger");
      Serial.println("Remove finger");
      fps.Enroll2();
      while (fps.IsPressFinger() == true) delay(100);
      lcd.clear();
      lcd.println("Press same fingr");
      lcd.setCursor(0, 1);
      Serial.println("yet again");
      Serial.println("Press same finger yet again");
      while (fps.IsPressFinger() == false) delay(100);
      bret = fps.CaptureFinger(true);
      if (bret != false)
      {
        lcd.clear();
        lcd.println("Remove finger");
        Serial.println("Remove finger");
        iret = fps.Enroll3();
        if (iret == 0)
        {
          lcd.clear();
          lcd.println("Enrolling Succes");
          Serial.println("Enrolling Successful");
        }
        else
        {
          lcd.clear();
          lcd.print("Enroll Fail with");
          lcd.setCursor(0, 1);
          lcd.print("error code:");
          lcd.println(iret);
          Serial.print("Enrolling Failed with error code:");
          Serial.println(iret);
        }
      }
      else {
        Serial.println("Failed to capture third finger");
        lcd.clear();
        lcd.print("Failed to capture");
        lcd.setCursor(0, 1);
        lcd.print("third finger");
      }
    }
    else {
      Serial.println("Failed to capture second finger");
      lcd.clear();
      lcd.print("Failed to capture");
      lcd.setCursor(0, 1);
      lcd.print("second finger");
    }
  }
  else {
    Serial.println("Failed to capture first finger");
    lcd.clear();
    lcd.print("Failed to capture");
    lcd.setCursor(0, 1);
    lcd.print("first finger");
  }
}

/*unsigned long timeOut(){
    if (millis() > previousTime+fpsTime){
      return true;
      previousTime= millis();
      Serial.print("time Out");
  }
  else{
    return false;
  }
  }*/

void fpsRead() {
  //Serial.print("started");
  delay(100);
  fps.Open();         //send serial command to initialize fps
  fps.SetLED(true);

  if (fps.IsPressFinger())
  {
    fps.CaptureFinger(false);
    int id = fps.Identify1_N();
    if (id < 200) //<- change id value depending model you are using
    { //if the fingerprint matches, provide the matching template ID
      Serial.print("Verified ID:");
      lcd.clear();
      lcd.print("Verified ID:");
      Serial.println(id);
      lcd.print(id);
      lcd.clear();
      lcd.print("welcome ");
      lcd.print(id);
      scanned = true;
      //digitalWrite(2, HIGH);
      delay(500);
      //digitalWrite(2, LOW);
      lcd.clear();
      lcd.print("Enter Ur Passkey:");
      fps.SetLED(false);
      fps.Close();         //send serial command to initialize fps
      //getPassKey();
      //break;
    }
    //    break;
    else
    { //if unable to recognize
      Serial.println("Finger not found");
      lcd.clear();
      lcd.print("Finger not found");
      delay(100);
      if (scanned == false) {
        if (s <= 1) {
          lcd.setCursor(0, 1);
          Serial.println("try again: ");
          Serial.println(s + 2);
          lcd.println("try again: ");
          lcd.println(s + 2);
          //lcd.println(" ");
          delay(50);
        }
        else {
          Serial.println("scanned true");
          scanned = true;
          if (s >= 1) {
            Serial.println("Not matched");
            lcd.clear();
            lcd.println("Not matched");
            delay(100);
            fps.SetLED(false);
            fps.Close();
            //delay(1000);
            s = 0;
          }
        }
        s++;
        //scanned = false;
      }
    }
  }
  else
  {
    Serial.println("Please press finger");
    lcd.clear();
    lcd.print("Press Finger");
    scanned = false;
  }
  delay(100);
  while (!scanned) {
    fpsRead();
  }
  //lcd.clear();
  //lcd.print("Enter Ur Passkey:");
  lcd.setCursor(0,1);
  //  break;
}



void fpDelete(int selectedID) {
  fps.Open();         //send serial command to initialize fps
  fps.SetLED(true);
  fps.CaptureFinger(false); //captures the finger for identification
  int id = fps.Identify1_N(); //identifies print and stores the id

  if (id < 200)
  {
    Serial.print("Verified ID:");
    Serial.println(id);
    fps.DeleteID(selectedID); //delete data
    delay(100);
    Serial.print("deleted ID:");
    Serial.println(selectedID);
    delay(1000);
  }
  else
  { //if unable to recognize
    Serial.println("Finger not found");
  }
}
