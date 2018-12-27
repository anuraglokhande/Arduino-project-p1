/*

Author : AL
Version: v0.0
Software discription: UART based sensor temp monitoring and load control
Hardware: Arduino nano is used with NTC temp sensor

code includes:
Date: 01.12.2018 
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
                  
*/


/* Global function declarations */
void alarm1(bool control);
void alarm2(bool control);
void load_control(bool control);
void transmision_uart(bool control);

/* Defining global variables */
char read_byte = '0';         // declarationa and defination of char read_byte
long int sum_of_temp = 0;     // as required for adding 10 ADC values
int avg_of_temp = 0;
unsigned int i;               // used for temp loop for(;;)
unsigned char status = 0;      
float measured_temp = 0.0;
/*  status of all indication and load storage byte
 *  ON 1 OFF 0
 *  bit 7  6   5   4   3   2   1   0
 *     |  |   |   |   |   |   |   |
 *     |  |   |   |   |   |   |   Buzzer ON/OFF(if sensor fail ovserved)
 *     |  |   |   |   |   |   Load ON/OFF
 *     |  |   |   |   |   Alarm - Temp in limit(ON - temp in limit, else out of limit) 
 *     |  |   |   |   Data transmision indication(Data transmition is going on) - this is not taken in bit status
 *     |  |   |   Reserved 
 *     |  |   Reserved
 *     |  Reserved
 *     Reserved
 */

bool control = 0;

/* Defining macros */
#define OFF 0
#define ON 1
#define TIME 5000 //in ms for measurement loop
                           
/* below is corrected chart for 270E in series with sensor with 15K at ADC end */
const signed int lookup_4_6k_temperature_sensor[] = {-400,-399,-398,-396,-394,-392,-390,-389,-387,-385,-383,-382,-380,-378,-377,-375,-373,-372,-370,-369,-367,-365,-364,-362,-361,-359,-358,-356,-355,-353,-352,-350,-349,-347,-346,-344,-343,-341,-340,-339,-337,-336,-334,-333,-332,-330,-329,-327,-326,-325,-323,-322,-321,-320,-318,-317,-316,-314,-313,-312,-310,-309,-308,-307,-305,-304,-303,-302,-301,
                        -299,-298,-297,-296,-295,-293,-292,-291,-290,-289,-287,-286,-285,-284,-283,-282,-281,-279,-278,-277,-276,-275,-274,-273,-272,-271,-269,-268,-267,-266,-265,-264,-263,-262,-261,-260,-259,-258,-257,-256,-254,-253,-252,-251,-250,-249,-248,-247,-246,-245,-244,-243,-242,-241,-240,-239,-238,-237,-236,-235,-234,-233,-232,-231,-230,-229,-228,-227,-226,-225,-224,-223,-222,-222,-221,-220,-219,-218,-217,-216,-215,-214,-213,-212,-211,-210,-209,-208,-207,-207,-206,-205,-204,-203,-202,-201,-200,
                        -199,-198,-197,-196,-196,-195,-194,-193,-192,-191,-190,-189,-188,-188,-187,-186,-185,-184,-183,-182,-181,-181,-180,-179,-178,-177,-176,-175,-175,-174,-173,-172,-171,-170,-169,-169,-168,-167,-166,-165,-164,-163,-163,-162,-161,-160,-159,-158,-158,-157,-156,-155,-154,-153,-153,-152,-151,-150,-149,-148,-148,-147,-146,-145,-144,-143,-143,-142,-141,-140,-139,-139,-138,-137,-136,-135,-135,-134,-133,-132,-131,-130,-130,-129,-128,-127,-126,-126,-125,-124,-123,-122,-122,-121,-120,-119,-118,-118,-117,-116,-115,-115,-114,-113,-112,-111,-111,-110,-109,-108,-107,-107,-106,-105,-104,-103,-103,-102,-101,-100,-100,
                        -99,-98,-97,-96,-96,-95,-94,-93,-93,-92,-91,-90,-89,-89,-88,-87,-86,-86,-85,-84,-83,-82,-82,-81,-80,-79,-79,-78,-77,-76,-76,-75,-74,-73,-72,-72,-71,-70,-69,-69,-68,-67,-66,-66,-65,-64,-63,-62,-62,-61,-60,-59,-59,-58,-57,-56,-56,-55,-54,-53,-52,-52,-51,-50,-49,-49,-48,-47,-46,-46,-45,-44,-43,-43,-42,-41,-40,-39,-39,-38,-37,-36,-36,-35,-34,-33,-33,-32,-31,-30,-29,-29,-28,-27,-26,-26,-25,-24,-23,-23,-22,-21,-20,-19,-19,-18,-17,-16,-16,-15,-14,-13,-13,-12,-11,-10,-9,-9,-8,-7,-6,-6,-5,-4,-3,-2,-2,-1,0,
                        1,1,2,3,4,5,5,6,7,8,8,9,10,11,12,12,13,14,15,16,16,17,18,19,20,20,21,22,23,23,24,25,26,27,27,28,29,30,31,31,32,33,34,35,35,36,37,38,39,39,40,41,42,43,43,44,45,46,47,48,48,49,50,51,52,52,53,54,55,56,57,57,58,59,60,61,61,62,63,64,65,66,66,67,68,69,70,71,71,72,73,74,75,76,77,77,78,79,80,81,82,83,83,84,85,86,87,88,89,89,90,91,92,93,94,95,95,96,97,98,99,
                        100,101,102,103,103,104,105,106,107,108,109,110,111,111,112,113,114,115,116,117,118,119,120,121,121,122,123,124,125,126,127,128,129,130,131,132,133,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,190,191,192,193,194,195,196,197,198,199,
                        200,201,203,204,205,206,207,208,209,210,212,213,214,215,216,217,218,220,221,222,223,224,225,227,228,229,230,231,233,234,235,236,237,239,240,241,242,244,245,246,247,249,250,251,252,254,255,256,257,259,260,261,263,264,265,267,268,269,271,272,273,275,276,277,279,280,282,283,284,286,287,289,290,291,293,294,296,297,299,
                        300,302,303,305,306,308,309,311,312,314,315,317,318,320,322,323,325,326,328,330,331,333,334,336,338,339,341,343,344,346,348,350,351,353,355,357,358,360,362,364,366,367,369,371,373,375,377,379,381,382,384,386,388,390,392,394,396,398};

/* Pin declaration and defination */
const int LED_PIN_RED = 4;    //used for RED LED as a Alarm - Temp in limit(OFF - temp in limit, else out of limit)
const int LED_PIN_GREEN1 = 5; //used for RED LED as a Load control - Relay connection
const int LED_PIN_GREEN2 = 6; //used for RED LED as a Data transmision indication(Data transmition is going on) 
const int BUZZER_PIN1 = 8;    //Used to drive BUZZER - Buzzer ON/OFF(if sensor fail obvserved)
const int BUZZER_PIN2 = 9;    //Used to drive BUZZER - Buzzer ON/OFF(if sensor fail obvserved)

const int TEMP_SENSOR_PIN = A0;    // select the input pin for the temperature sensor sensing 
                                   // by default Analog channel is configured for 10 bit resolution 

// the setup function runs once when you press reset or power the board
void setup() {
  /* Configuration of output pins */
  pinMode(LED_PIN_RED, OUTPUT);   // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_PIN_GREEN1, OUTPUT);// initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_PIN_GREEN2, OUTPUT);// initialize digital pin LED_BUILTIN as an output.
  pinMode(BUZZER_PIN1, OUTPUT);// initialize digital pin LED_BUILTIN as an output.
  pinMode(BUZZER_PIN2, OUTPUT);// initialize digital pin LED_BUILTIN as an output.

  /* Initialize serial and wait for port to open */
  Serial.begin(9600);

  /* Configuration of analog pin */
  
}

// the loop function runs over and over again forever
void loop() 
{
  /* after every 5 sec loop will run and check for temp and all related conditions */
  delay(5000);//delay in ms

  /* measurement of temp sensor ADC and converting ADC output to temperature in Degree cel 
   * making average of temp value for temp reading stability
   */
  sum_of_temp = 0;
  for (i=0;i<10;i++)   
  {
    sum_of_temp = sum_of_temp + analogRead(TEMP_SENSOR_PIN);
  }

  avg_of_temp = sum_of_temp/10;                               // average of 10 ADC count for count stability
  avg_of_temp = avg_of_temp - 80;                             // see loop uptable

  /* below code is to check the sensor failure if it sense more than 40 degree cel
   *  and less than -39.8 degree cel
   */
  if (avg_of_temp < 88)
  {
     avg_of_temp = 88;  // this count is for -40 degree cel. below this it will not measure and shows sensor fail.
     Serial.print("\nTemperature sensor failed\n");
     alarm1(ON);
     load_control(OFF);
     
  }
  else if (avg_of_temp > 864)
  {
     avg_of_temp = 864; // this count is for 39.8 degree cel. above this it will not measure and shows sensor fail.
     Serial.print("\nTemperature sensor failed\n");
     alarm1(ON);
     load_control(OFF);
  }
  else 
  {
      measured_temp = lookup_4_6k_temperature_sensor[avg_of_temp];// converting ADC count to lookup table value
      measured_temp = measured_temp/10.0;                         // converting value to actual temperature
      Serial.print("Current room temperature = ");                // sending string to uart
      Serial.print(measured_temp);                                // sending current temp to uart
      Serial.print(" Deg Cel");                                   // sending string to uart
      Serial.print("\n");                                         // sending new line char to uart

      /* condition check for temp above 30 degree cel 
      * controlling of Alarm and load signal
      */
      if ( measured_temp > 30.0)
      {
        load_control(OFF);
        alarm2(ON);
        Serial.print("Temperature is above 30 deg Cel");
        Serial.print("\n");
      }
      else
      {
        load_control(ON);
        alarm2(OFF);
      }    
  }
      
  
  
/*
  alarm1(ON);
  alarm2(ON);
  Serial.write(status);
  delay(5000);//delay in ms
  alarm1(OFF);
  alarm2(OFF);
  Serial.write(status);
  */

}

/* Definations of global functions */

/* Buzzer ON/OFF(if sensor fail obvserved) */
void alarm1(bool control)
{
  if (control == ON)
  {
    for(int i = 0; i<100; i++)
    {  
      digitalWrite(BUZZER_PIN1, HIGH);
      digitalWrite(BUZZER_PIN2, LOW);
      delay(1);
      digitalWrite(BUZZER_PIN1, LOW);
      digitalWrite(BUZZER_PIN2, HIGH);
      delay(1);
    }
    status = status | 0x01;
  }
  else
  {
    digitalWrite(BUZZER_PIN1, LOW);
    digitalWrite(BUZZER_PIN2, LOW);
    status = status & 0xFE;
  }
}

/* Alarm - Temp in limit(ON - temp in limit, else out of limit) */
/* RED LED */
void alarm2(bool control)
{
  if (control == ON)
  {
    digitalWrite(LED_PIN_RED, HIGH);
    status = status | 0x04;
  }
  else
  {
    digitalWrite(LED_PIN_RED, LOW);
    status = status & 0xFB;
  }
}

/* Load ON/OFF */
void load_control(bool control)
{
  if (control == ON)
  {
    digitalWrite(LED_PIN_GREEN1, HIGH);
    status = status | 0x02;
  }
  else
  {
    digitalWrite(LED_PIN_GREEN1, LOW);
    status = status & 0xFD;
  }
}

/* Data transmision indication(Data transmition is going on) */
void transmision_uart(bool control)
{
  //control is reserved for future use
  unsigned char i=0;
  for (i=0;i<10;i++)
  {
  digitalWrite(LED_PIN_GREEN2, HIGH);
  delay(10);
  digitalWrite(LED_PIN_GREEN2, HIGH);
  delay(10);
  }
}
/****************************************END OF FILE**************************************/
