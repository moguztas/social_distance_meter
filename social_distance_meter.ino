/*
 Project Name   : PORTABLE SOCIAL DISTANCE MEASUREMENT DEVICE
 Revision Date  : 01.12.2020
 Author         : MOT
 // ---------------------------------------------------------------------------------------------------------------------------
 Purpose        : Implementing a distance measurement system for maintaining social distance, which is critical in the fight 
                  against the COVID-19 epidemic, and ensuring a warning sound when social distance is not provided.
 // ---------------------------------------------------------------------------------------------------------------------------
 System Input   : 
                  1) Potentiometer : To adjust the volume of the buzzer
                  2) HC SR-04      : To measure the distance between people
 System Output  : 
                  1) Buzzer        : To alert with sound
                  2) LED           : To indicate the system is active or not
 // ---------------------------------------------------------------------------------------------------------------------------
 System Work    : Distance sensing process is carried out with HC SR-04 ultrasonic distance sensor, and when the distance value 
                  falls below certain threshold values, it is provided to give a alert with sounds at different frequencies. 
                  The volume of the buzzer can be adjusted with the help of the potentiometer in the system.
 // ---------------------------------------------------------------------------------------------------------------------------          
 */

// ---------------------------------------------------------------------------------------------------------------------------          

// DEFINITIONS
int trig_pin = 9;       // Trigger pin of the HC SR-04 is connected to Digital 9 pin. 
int echo_pin = 10;      // Echo pin of the HC SR-04 is connected to Digital 10 pin. 
int buzz_pin = 11;      // Buzzer is connected to the Digital 11 pin.
int led_pin  = 13;      // Indicator LED is connected to Digital 13 pin.
int pot_pin  = A0;      // Potentiometer is connected to Analog 0 pin.
long pot_val;           // To store the value from the potentiometer.                              
long buzz_val;          // To adjust the volume by using the pot_val.
long duration;          // To store the total time (in microseconds) of the sound wave propagation and return. 
int distance;           // To store distance.
// ---------------------------------------------------------------------------------------------------------------------------

// SETUP CODE AREA
void setup()
{
  Serial.begin(9600);               // Sets the baud rate for serial data transmission. 
  pinMode(echo_pin, INPUT);         // Echo pin defined as INPUT.
  pinMode(trig_pin, OUTPUT);        // Trigger pin defined as OUTPUT.
  pinMode(buzz_pin, OUTPUT);        // Buzzer pin defined as OUTPUT.
  pinMode(led_pin,  OUTPUT);        // LED pin defined as OUTPUT
  digitalWrite(led_pin, HIGH);      // When power is ON, green LED is HIGH.
  Serial.println("Setup is done !");
}
// ---------------------------------------------------------------------------------------------------------------------------

//MAIN CODE AREA
void loop() 
{
  pot_val  = analogRead(pot_pin);          // Read the analog potentiometer value.    
  buzz_val = map(pot_val,0,1023,0,255);    // Map the pot_value between 0-255 (It is used to adjust buzzer volume).                     
  digitalWrite(trig_pin, LOW);             // LOW pulse to ensure a clean HIGH pulse.   
  delayMicroseconds(2);                    // Wait for a short time
  digitalWrite(trig_pin, HIGH);            // The sensor is triggered by a HIGH pulse. 
  delayMicroseconds(10);                   // The sensor is triggered 10 microseconds.
  digitalWrite(trig_pin, LOW);             // LOW pulse again.
  duration = pulseIn(echo_pin, HIGH);      // It measures the time taken for the US wave to return back to the sensor.
  distance = duration*0.034/2;             // Distance = (time_travel / 2)*sound velocity 
  Serial.print("Distance: "); Serial.print(distance); Serial.println(" cm"); // Write the distance value to the Serial Monitor.

  // If distance is between 100-150 cm, buzzer is ON for 0.5 second, OFF for 0.5 second.
  if(distance > 100 && distance <= 150)
  {
    analogWrite(buzz_pin, buzz_val);    // Buzzer is ON and voice is controlled by potentiometer using the PWM technique.
    delay(500);                         // Wait for a 500 miliseconds.
    digitalWrite(buzz_pin,LOW);         // Buzzer is OFF.
    delay(500);                         // Wait for a 500 miliseconds.
  }
  // If distance is less than or equal 100 cm, buzzer is ON for 0.1 second, OFF for 0.1 second.
  else if(distance <= 100)
  {
    analogWrite(buzz_pin, buzz_val);    // Buzzer is ON and voice is controlled by potentiometer using the PWM technique.
    delay(100);                         // Wait for a 100 miliseconds.
    digitalWrite(buzz_pin,LOW);         // Buzzer is OFF.
    delay(100);                         // Wait for a 100 miliseconds.
  }
  // If distance is greater than 150 cm, buzzer is OFF.
  else 
  {
    digitalWrite(buzz_pin, LOW);        // Buzzer is OFF.
  }
}
// ---------------------------------------------------------------------------------------------------------------------------
