/*

Author : AL
Version: v0.2
Software discription: 
Making Real Time Clock with UART 
Setting Clock with UART


code includes:
Date: 13.12.2018 
              --> LED RED configuration and LED ON and OFF. Pin D4 is used.
              --> LED GREEN configuration and LED ON and OFF. Pin D5 is used.
              --> 3LED GREEN configuration and LED ON and OFF. Pin D6 is used.
              --> UART0 configured for data communication with PC software.
Date: 02.12.2018
              --> BUZZER configured
              --> Status char added for reading the status of different alarms and loads
Date: 04.12.2018
              --> Added temperature measurement
              --> Added UART data sending - temp and alarm condition
              --> Added temp failure alarm
              --> Added load control when sensor is failed
              --> Added PC communication and software 
                  
*/
/* Include files */
#include <Wire.h>

/* Global function declarations */

/* Defining global variables */
char read_sec;
char read_min;
char read_hour;

/* status of all indication and load storage byte

/* Defining macros */
#define RTC_Address_w 0xD0
#define RTC_Address_r 0xD1                           
/* Pin declaration and defination */
const int DS_PIN = 19;

// the setup function runs once when you press reset or power the board
void setup() {
  /* Configuration of output pins */
  pinMode(DS_PIN, OUTPUT);   // initialize digital pin DS as an output.
  digitalWrite(DS_PIN, HIGH);
  
  /* Initialize serial and wait for port to open */
  Serial.begin(9600);
  Wire.begin(); // Initiate the Wire library
  
  /* after every 5 sec loop will run and check for temp and all related conditions */
  delay(5000);//delay in ms
  Serial.print("I2C RTC communication started in setup\n");
  Wire.beginTransmission(RTC_Address_w); // Begin transmission to the RTC
  Wire.write(0x00);
  Wire.write(0x01);
  Wire.write(0x01);
  Wire.write(0x02);
  Wire.endTransmission();
  
}

// the loop function runs over and over again forever
void loop() 
{
  /* after every 5 sec loop will run and check for temp and all related conditions */
  delay(5000);//delay in ms
  Serial.print("\nI2C RTC communication started");
  Wire.beginTransmission(RTC_Address_r); // Begin transmission to the RTC
  read_sec = Wire.read();
  read_min = Wire.read();
  read_hour = Wire.read();
  Wire.endTransmission();
  Serial.print("\nsec is ");
  Serial.print(read_sec);
  Serial.print("\nmin is ");
  Serial.print(read_min);
  Serial.print("\nhour is ");
  Serial.print(read_hour);
}


/****************************************END OF FILE**************************************/
