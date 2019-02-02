#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 6

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float temp=0.0,tempC=0.0,thresholdTemp=0.0;
int potValue=0;
int buzzerPin= 8;

const int rs = 12, en = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(void)
{
  Serial.begin(9600);
  sensors.begin();
  lcd.begin(16, 2);
  lcd.setCursor(2,0);
  lcd.print("Welcome to");
  lcd.setCursor(2, 1);
  lcd.print("HEATBUZZER");
  delay(1000);
  pinMode(buzzerPin,OUTPUT);  

}

void loop(void)
{ 
  temp=getTemp();
  potValue = analogRead(A2);
  thresholdTemp=(float)map((float)potValue,0,1009,-30.0,100.0);
  
 if(temp>=thresholdTemp)   
 {
   digitalWrite(buzzerPin,LOW);

   lcd.setCursor(0,0);
   lcd.print("Current:");
   lcd.setCursor(8,0);
   lcd.print(temp);
   lcd.print(" C  ");
   lcd.setCursor(0,1);
   lcd.print("ReadyAt:");
   lcd.setCursor(8,1);
   lcd.print(thresholdTemp);
   lcd.print(" C ");        
 }
 else
 {
   //buzz
   lcd.setCursor(0,0);
   lcd.print("Current:");
   lcd.setCursor(8,0);
   lcd.print(temp);
   lcd.print(" C");

   lcd.setCursor(0,1);
   lcd.print("ReadyAt:");
   lcd.setCursor(8,1);
   lcd.print(thresholdTemp);
   lcd.print(" C");
   digitalWrite(buzzerPin,HIGH);
   
 }
}

float getTemp(void)
{
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  Serial.print("Temperature for the device 1 (index 0) is: ");
  tempC=sensors.getTempCByIndex(0);
  Serial.println(tempC);  
  
  return tempC;
}


