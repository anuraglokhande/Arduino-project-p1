/*
 * 
 */
int sensor = A0;
unsigned int count = 0;
char flag = 0;
float vin = 0;
void setup() {

  Serial.begin(9600); //init serial port
}

void loop() {

count = analogRead(sensor);
Serial.print("count is ");
Serial.print(count);
Serial.print("\n");
delay(1000);
vin = (5000/1024.0)*(count+1);
Serial.println("Voltage is V");
Serial.print(vin);
Serial.print("\n");

float T = vin/10;
Serial.println("Voltage is V");
Serial.print(T);
Serial.print("\n");

}
