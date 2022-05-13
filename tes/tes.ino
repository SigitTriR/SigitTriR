#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define Password_Length 8 

int relay1 = 10;
int relay2 = 11;
int relay3 = 12;
int relay4 = 13;

char Data[Password_Length]; 
char pintu1[Password_Length] = "123A456";
char pintu2[Password_Length] = "123B789";
char pintu3[Password_Length] = "123A654";
char pintu4[Password_Length] = "123B987";
char tutup[Password_Length] = "1234567";
 
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 16, 2);  

void setup(){
  lcd.init(); 
  lcd.backlight();
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);

  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);

  delay(400);
}

void loop(){

  lcd.setCursor(0,0);
  lcd.print("Enter Password:");

  customKey = customKeypad.getKey();
  if (customKey){
    Data[data_count] = customKey; 
    lcd.setCursor(data_count,1); 
    lcd.print(Data[data_count]); 
    data_count++; 
    }

  if(data_count == Password_Length-1){
    lcd.clear();

    if(!strcmp(Data, pintu1)){
      lcd.print("Locker terbuka");
      digitalWrite(relay1, LOW); 
      delay(2000);
      
      }

      if(!strcmp(Data,pintu2)){
      lcd.print("Laci 1 Terbuka");
      digitalWrite(relay2, LOW); 
      
      }
      
      if(!strcmp(Data,pintu3)){
      lcd.print("Laci 2 Terbuka");
      digitalWrite(relay3, LOW); 
      
      }
      
      if(!strcmp(Data,pintu4)){
      lcd.print("Laci 3 Terbuka");
      digitalWrite(relay4, LOW); 
      
      }

      if(!strcmp(Data,tutup)){
      lcd.print("benar");
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH); 
     
     digitalWrite(relay3, HIGH);
      digitalWrite(relay4, HIGH); 
     
       delay(2000);
      }
      
    else{
      lcd.print("Incorrect");
      delay(1000);
      }
    
    lcd.clear();
    clearData();  
  }
}

void clearData(){
  while(data_count !=0){
    Data[data_count--] = 0; 
  }
  return;
}
