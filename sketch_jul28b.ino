#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;

//Librerias para sensor temperatura
#include <OneWire.h>
#include <DallasTemperature.h>

const int BUTTON = 9;
int BUTTONstate = 0;

OneWire oneWire(6);
DallasTemperature sensors(&oneWire);
//int deviceCount = 0;
//float tempC;

void setup() {
  // put your setup code here, to run once:
    delay(1000);

    Serial.begin(9600);

  pinMode(BUTTON, INPUT);
  pinMode(A0, INPUT);

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
  
  sensors.begin();
  
  Serial.print("Temp_suelo");
  Serial.print(";");
  Serial.print("Humedad_suelo");
  Serial.print(";");
  Serial.print("Comentario");
  Serial.println(";");
}

void loop() {
  // put your main code here, to run repeatedly:
   BUTTONstate = digitalRead(BUTTON);
   int rhValue = analogRead(A0);
   sensors.requestTemperatures();
   float temp = sensors.getTempCByIndex(0);

   // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog2.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    //dataFile.println(dataString);
    
  if (BUTTONstate == HIGH)
  {
    Serial.print(temp);
        dataFile.print(temp);

    Serial.print(";");
        dataFile.print(";");

    Serial.print(rhValue);
        dataFile.print(rhValue);

    Serial.print(";");
        dataFile.print(";");

      if(rhValue >= 1000) {
        Serial.print("Sensor is not in the Soil or DISCONNECTED");
                dataFile.print("Sensor is not in the Soil or DISCONNECTED");

      } 
      if(rhValue < 1000 && rhValue >= 600) {
        Serial.print("Soil is DRY");
                dataFile.print("Soil is DRY");

      } if(rhValue < 600 && rhValue >= 370) {
        Serial.print("Soil is HUMID"); 
                dataFile.print("Soil is HUMID"); 

      } 
      if(rhValue < 370) {
        Serial.print("Sensor in WATER");
                dataFile.print("Sensor in WATER");

      }
      Serial.println(";");
                dataFile.println(";");} 
  else{
  }

dataFile.close();
    // print to the serial port too:
    //Serial.println("all good");
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
    

 //Serial.print("Temperatura= ");

  //Serial.println(" C");
  
    delay(150);
}
