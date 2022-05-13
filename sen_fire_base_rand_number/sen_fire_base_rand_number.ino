#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

#define FIREBASE_HOST "getdata-940fd-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "iHA8wrRuHccqSje4yDcDdm7O2lXouVisxMGTgRrX"

#define ON_Board_LED 2 //--> Defining an On Board LED, used for indicators when the process of connecting to a wifi router
long randNumber;
//----------------------------------------SSID and Password of your WiFi router.
const char* ssid = "Wifi Rumah" ;
const char* password = "masukinaja" ;
//----------------------------------------

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(500);
  
  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");
    
  pinMode(ON_Board_LED,OUTPUT); //--> On Board LED port Direction output
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off Led On Board

  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  //----------------------------------------If successfully connected to the wifi router, the IP Address that will be visited is displayed in the serial monitor.
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //----------------------------------------

  //----------------------------------------Firebase Realtime Database Configuration.
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  //----------------------------------------
}

void loop() {
  // put your main code here, to run repeatedly:

  //----------------------------------------Send data in the form of random value data to the Firebase Realtime Database.
  randNumber = random(100, 1000);
  String dataSend = String(randNumber); 
  Serial.print("Random Number : ");
  Serial.println(dataSend);

  Firebase.setString("RandomVal/Value",dataSend); //--> Command or code to send data or update data (String data type) to the Firebase Realtime Database.

  // Conditions for handling errors.
  if (Firebase.failed()) { 
      Serial.print("Setting /Value failed :");
      Serial.println(Firebase.error());  
      delay(500);
      return;
  }

  Serial.println("Setting successful");
  Serial.println();
  delay(2000);
}
