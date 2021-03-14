/*
This code shows Temperature(℃) and Humidity(%RH) of RKI-4879 Industrial grade Temperature & Humidity Sensor.

Connections of Sensor, Arduino and MAX485 TTL to RS485 Converter
Serial Port 0 is not used to connect to drive because its connected to USB-Serial and used to show information on console.

For Arduino Uno Software serial needs to be used as there is only one hardware serial port and its connected to USB-Serial. 
   Sensor         MAX485 TTL to RS485 Converter
     A+         -       A
     B-         -       B
    GND         -       GND
    
   MAX485 TTL to RS485 Converter    Arduino (Software Serial)
     R0                  -            D2              
     DE & RE             -            D8
     DI                  -            D3
     GND                 -            GND
   
For more information see :https://robokits.co.in/sensors/temperature-humidity/industrial-grade-temperature-humidity-transmitter-sht20-sensor-high-precision-monitoring-modbus-rs485
*/

#include <ModbusMaster.h>   
#include <SoftwareSerial.h> 
SoftwareSerial mySerial(2,3);    //Software Serial port For Arduino Uno
#define MODBUS_DATA_TRANSACTION_PIN 8   //DE & RE Pin of MAX485
ModbusMaster node;                      //object for ModbusMaster

short a1,a2;
uint8_t Slave_ID = 1;   //Slave ID of the Sensor

void setup() 
{
    pinMode(MODBUS_DATA_TRANSACTION_PIN, OUTPUT);
    digitalWrite(MODBUS_DATA_TRANSACTION_PIN, 0);
    Serial.begin(9600);     //Baud rate is 9600 8N1
    mySerial.begin(9600);   //Modbus Baud rate is 9600 8N1
    node.begin(mySerial);
    node.preTransmission(preTransmission);
    node.postTransmission(postTransmission);
    Serial.println("RKI-4879 XY-MD02 Temperature And Humidity Sensor");
    Serial.print("Slave ID :");
    Serial.println(Slave_ID);
}

void loop() 
{
   a1 = node.Read_Temperature(Slave_ID);    
   a2 = node.Read_Humidity(Slave_ID);  

   Serial.print("Temperature :"); //if value is 293 that means it is 29.3℃ temperature
   Serial.print(a1);
   Serial.print("\t\tHumidity :"); //if value is 493 that means it is 49.3% humidity
   Serial.println(a2);  
}

void preTransmission() 
{
  digitalWrite(MODBUS_DATA_TRANSACTION_PIN, 1);
}

void postTransmission()
{
  digitalWrite(MODBUS_DATA_TRANSACTION_PIN, 0);
}
