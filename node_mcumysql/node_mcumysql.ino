#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

//settingjaringan
const char* ssid = "LUBINAR";
const char* password = "password123";
const char* host = "156.67.222.182"; //alamat ip server


int analogPin = A0;
int analogPin1 = 2;
 
//Variabel untuk menyimpan data suhu
float sensor = 00;
int suhu1=00;

float enginetemp = 01;
int enginetemp1=01;

 
void setup(){
//Komunikasi serial dengan baud 9600
Serial.begin(9600);
WiFi.hostname("NodeMCU");
WiFi.begin(ssid, password);
 pinMode(analogPin1, INPUT);

while(WiFi.status() !=WL_CONNECTED)
{ Serial.print(".");
delay(500);
}

Serial.println("WiFIConnected");
}
 
void loop(){
//Baca pin input
suhu1 = analogRead(analogPin);
sensor = suhu1 / 2.0479;
Serial.println(sensor);

enginetemp1 = analogRead(analogPin1);
enginetemp = enginetemp1 / 2.0479;
Serial.println(enginetemp);

//cek koneksi ke server
WiFiClient client;
if(!client.connect (host, 80))
{
  Serial.println("connection Failed");
  return;
}
//proses pengiriman data ke server
String Link ;
HTTPClient http;
Link = "http://workshopelearning.com/sigit-iot/sensor/data_sensor?sensor=" + String(sensor);
//eksekusilink
http.begin(Link);
//mode GET
http.GET();
http.end();
delay(1000);
}
