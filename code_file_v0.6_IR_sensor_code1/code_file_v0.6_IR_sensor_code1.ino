/*
 * 
 */

const int IR_read = 4;    //used for RED LED
const int ledPin =  LED_BUILTIN;// the number of the LED pin
unsigned int count = 0;
char flag = 0;

void setup() {
  // put your setup code here, to run once:
  /* Configuration of output pins */
  pinMode(IR_read, INPUT);   // initialize digital pin 4 IR_read as an input.
  pinMode(ledPin, OUTPUT);
    
  Serial.begin(9600); //init serial port
}

void loop() {

       if(digitalRead(IR_read) == HIGH)
       {
        while(digitalRead(IR_read) == HIGH);
        digitalWrite(ledPin, HIGH);
        count++;
        Serial.print(count);
        Serial.print("\n");
       }
       if(digitalRead(IR_read) == LOW)
       {
        digitalWrite(ledPin, LOW);
       }
}
