// This project implements the simulation of the reading a DHT sensor using an ESP32 
// The source code is available on my git repo at : https://github.com/Bamamou/DHT11_ESP32.git
// the only difference is the sensor, Here; we use a DHT11 while in Platform io we use a DHT22
#include <DHT.h>  
// Set up the DHT sensor 
DHT dht(4, DHT22);
float temperature ;
float  humidity;
int power;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(5, OUTPUT); // red
  pinMode(18, OUTPUT); // green
  pinMode(19, OUTPUT); //blue
  pinMode(2, INPUT); // power
  pinMode(14, OUTPUT); // heater
  pinMode(12, OUTPUT); // buzzer
}

void setColor(int redValue, int greenValue,  int blueValue) {
  analogWrite(5, redValue);
  analogWrite(18,  greenValue);
  analogWrite(19, blueValue);
}

void loop() {
  // put your main code here, to run repeatedly:
  temperature  = dht.readTemperature(false);
  humidity     = dht.readHumidity();
  // Print the values of temperature in Celsus
  
  power = digitalRead(2);
  if(power == 0){
    setColor(0,0,0);
    Serial.println("State - IDLE");
  }
  if(power == 1){
    setColor(255,255,255);
    Serial.print("Temperatue:\t");
    Serial.print(dht.readTemperature(false));
    Serial.println("C");
    if(temperature<=18.00||temperature<78){   //Heating
      setColor(255,255,0);
      digitalWrite(14,LOW);
      Serial.println("State - Heating");
    }
    if(temperature>78.00){  //Overheating
      setColor(255,0,0);
      tone(12, 262, 250);
      digitalWrite(14,HIGH);
      Serial.println("State - Overheating");

    }
    if(temperature>=70.00 && temperature<75){  //Stablizing
      setColor(0,0,255);
      digitalWrite(14,LOW);
      Serial.println("State - Stablizing");
    }
    if(temperature>75 && temperature<78){  //Target Reached
      setColor(0,255,0);
      digitalWrite(14,HIGH);
      Serial.println("State - Target Reached");
    }
  }
  
  delay(1000); // this speeds up the simulation
}
