#include "RTClib.h"
#include <Wire.h>
#include <DS3231.h>
#include "SPI.h"
RTC_DS3231 RTC;
int SensorB = A4;
int SensorS = A0;
int Auto = 2;
int Reset = 4;
int Home = 7;
int Relay1 = 11;
int Relay2 = 10;
int Relay3 = 9;
DS3231 clock;
RTCDateTime dt;
void setup()
{
  pinMode(SensorB,INPUT);
  pinMode(SensorS,INPUT);
  pinMode(Auto,INPUT);
  pinMode(Reset,INPUT);
  pinMode(Home,INPUT);
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  Serial.begin(9600);
  Serial.println("Initialize DS1307");;
  Wire.begin();
  RTC.begin();
  RTC.adjust(DateTime(__DATE__, __TIME__));
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  DateTime now = RTC.now();

  }
}
/////////////////////////////////////เปิด ฟังก์ชั่น1///////////////////////////////////////////////////
void function1Open(){    //ทำเวลา 18.00-06.00
  if (Switch == HIGH)
  {
    if (SensorValue <= 808)//0V-11.3V
    {
      analogWrite(Relay1, 0);
      analogWrite(Relay3, 255);
    }
    else if (SensorValue >= 943)//13.5V
    {
      analogWrite(Relay1, 255);
      analogWrite(Relay3, 0);
    }
  }
  else
  {
    analogWrite(Relay1, 0);
    analogWrite(Relay3, 0);
  }
  if (SwitchH == HIGH)
  {
    analogWrite(Relay3, 255);
    analogWrite(Relay1, 0);
  }
  else{
    
  }
  if (SwitchEmer == HIGH)
  {
    analogWrite(Relay1, 0);
    analogWrite(Relay2, 0);
    analogWrite(Relay3, 0);
  }
  else{
    
  }
}
/////////////////////////////เปิดฟังก์ชั่น 2/////////////////////////////////////////////////
void function2 (){     // ทำเวลา 9.00-15.00
if (SensorS >= 0 && SensorS <= 690)
  {
    analogWrite(Relay2, 0);
  }
  else if (SensorS > 690 && SensorS <= 1023)
  {
    analogWrite(Relay2, 255);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////

void loop()
{
  
  dt = clock.getDateTime();
  int SensorValue = analogRead(SensorB);
  int SensorS = analogRead(SensorS);
  int Switch = digitalRead(Auto);
  int SwitchEmer = digitalRead(Reset);
  int SwitchH = digitalRead(Home);
  Serial.print("\n");
  Serial.print(SensorValue);
  Serial.print("\t");
  Serial.print(SensorS);
  Serial.print("\t");
  Serial.print(Switch);
  Serial.print("\t");
  Serial.print(SwitchEmer);
  Serial.print("\t");
  Serial.print(SwitchH);
  if (now.hour() == 18 || now.hour() == 06){
  function1Open();
  }else if(now.hour() == 9 || now.hour() == 15.00)){
  function2Open();
  }else{
}
 
 





}

