/*
 * 
 */



const int LED_PIN_RED = 4;    //used for RED LED

char flag = 0;

int pinStateA6 = 0;//cant not use as digital input or output
int pinStateA7 = 0;//cant not use as digital input or output

unsigned int msec_count = 0;
unsigned int sec_count = 0;
unsigned int min_count = 0;
unsigned int hour_count = 0;

void setup() {
  // put your setup code here, to run once:
  /* Configuration of output pins */
  pinMode(LED_PIN_RED, OUTPUT);   // initialize digital pin LED_BUILTIN as an output.
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  
    digitalWrite(LED_PIN_RED, HIGH);
    delay(2000);//delay in ms
    digitalWrite(LED_PIN_RED, LOW);
    delay(2000);//delay in ms
    
    //Serial.begin(9600); //due to this output out serial will be delayed and added to timer count so it will not be actual time 
    //if we take baud rate of 9600
    Serial.begin(115200);

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
        msec_count++;
        if(msec_count > 100)
        {
          sec_count++;
          msec_count = 0;
          
            if(sec_count > 59)
              {
                min_count++;
                sec_count = 0;

                if(min_count > 59)
                  {
                    min_count = 0;
                    hour_count++;

                    if(hour_count > 24)
                    {
                      hour_count = 0;
                    }
                  }
              }
        }

        Serial.print("H: ");
        Serial.print(hour_count);
        Serial.print(" M: ");
        Serial.print(min_count);
        Serial.print(" S: ");
        Serial.print(sec_count);
        Serial.print(" mS: ");
        Serial.print(msec_count);
        Serial.print("\n");
        delay(10);//delay in ms        
      }
      if(flag == 0)
      {
        sec_count = 0;
        min_count = 0;
        hour_count = 0;
        
        Serial.print("Timer stopped\n");
        delay(500);//delay in ms
        flag = 2;
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
