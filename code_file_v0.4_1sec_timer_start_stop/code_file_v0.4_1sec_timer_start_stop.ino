const int LED_PIN_RED = 4;    //used for RED LED
const int LED_PIN_GREEN1 = 5; //used for RED LED
const int LED_PIN_GREEN2 = 6; //used for RED LED

char state_b;
char flag = 0;
int pinStateA6 = 0;
int pinStateA7 = 0;
unsigned int count = 0;

void setup() {
  // put your setup code here, to run once:
  /* Configuration of output pins */
  pinMode(LED_PIN_RED, OUTPUT);   // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_PIN_GREEN1, OUTPUT);// initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_PIN_GREEN2, OUTPUT);// initialize digital pin LED_BUILTIN as an output.
  pinMode(A2, INPUT);

  
    digitalWrite(LED_PIN_RED, HIGH);
    delay(2000);//delay in ms
    digitalWrite(LED_PIN_RED, LOW);
    delay(2000);//delay in ms
    
    Serial.begin(9600);

}

void loop() {

    flag = 0; 
    while(1)
    {
       if(digitalRead(A3) == HIGH)
        flag = 1;
       if(digitalRead(A2) == HIGH)
        flag = 0;
      if(flag == 1)
      {
        Serial.print("sec ");
        Serial.print(count);
        Serial.print("\n");
        delay(1000);//delay in ms
        count++;
      }
      if(flag == 0)
      {
        count = 0;
        Serial.print("TImer stopped\n");
        delay(1000);//delay in ms
      }
      
    }
}

/*
 *   // put your main code here, to run repeatedly:
     //pinStateA6 = analogRead(A6) > 100 ? 0 : 1;
     //pinStateA7 = analogRead(A7) > 100 ? 0 : 1;
     

         
    
    {
      digitalWrite(LED_PIN_RED, HIGH);
      delay(100);//delay in ms
    }
    else
    {
      digitalWrite(LED_PIN_RED, LOW);
      delay(500);//delay in ms
    }
    //Serial.print("out is : \n");
    //Serial.print(state_b);
    delay(500);//delay in ms
     
 */
