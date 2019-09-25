#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#ifndef STASSID
#define STASSID "your network id"
#define STAPSK  "your password"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <PolledTimeout.h>
//#include <IRremote.h>

#define SDA_PIN D14
#define SCL_PIN D15
#define commonAnode
#define TRIGGERPIN 114
#define ECHOPIN    115
#define motorSpeed 147
#define motorA 145
#define motorB 143
#define redPin 102 //12
#define greenPin 111//11
#define bluePin 110//10
#define vcc 113


int redColor = 0;
int greenColor = 0;
int blueColor = 0;
//Values used for calibration
int redMin;
int redMax;
int greenMin;
int greenMax;
int blueMin;
int blueMax;
int color = 0;
//Arduino pins:
#define S0 116
#define S1 117
#define S2 118
#define S3 119
#define sensorOut 120
//Output from the sensor:
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
//Formatted color values:



const int16_t I2C_MASTER = 0x42;
const int16_t I2C_SLAVE = 0x08;

int bedroom = 101;
int hall = 112;
int kitchenLed = 103;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "your auth token";

// Your WiFi credentials.
// Set password to "" for open networks.
//char ssid[] = "Teck Team";
//char pass[] = "teckteams";

/*BLYNK_WRITE(V0) {
  int ledValue = param.asInt();
  if (ledValue <= 100) {
    ledValue = map(ledValue, 0, 100, 0, 255);
   Wire.beginTransmission(I2C_SLAVE); // transmit to device #8
   Wire.write(ledValue);
   Wire.endTransmission();;
    }
  }*/

//IRsend irsend;

//WidgetTerminal terminal(V6);
void setup() {
  Serial.begin(9600);
  Wire.begin(SDA_PIN, SCL_PIN); // join i2c bus (address optional for master)
  expansionDWrite(112, 1);
  delay(1000);
  expansionDWrite(112, 0);
  expansionDWrite(S0, 1);
  expansionDWrite(S1, 0);
  for(int i=0;i<5;i++){
   temperature();
    delay(200);
  }
  Serial.print("value=");
  Serial.print(expansionDRead(133));
  //calibrate();//calibrate sensor (look at serial monitor)
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Blynk.begin(auth, ssid, password);
}

void loop() {
  //using periodic = esp8266::polledTimeout::periodicMs;
  //static periodic nextPing(1000);
  ArduinoOTA.handle();
  Blynk.run();
}

void remote(int code) {
  Wire.beginTransmission(8);
  Wire.write(code);
  Wire.endTransmission();
}
