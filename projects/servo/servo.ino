#include <Servo.h>                  

 

Servo Servo1;                 // defining a servo named servo1

int angle=90;                            // initial value on servo angle

float Left_Sensor_AVG=0;     // variable to store average value (Global variable)

float Right_Sensor_AVG=0;           
void setup()

{

   Servo1.attach(9);          //declaring the pin at which servo is attached

   Servo1.write(90);          //initially writing 90 to servo

   delay(2000);                          //hold at 90 degrees, give enough delay as required



   Servo1.write(75);             //turn shaft to 75 degrees

   delay(1000);                               
   int left_1=analogRead(A0);       //read left and right sensor values

   int right_1=analogRead(A1);

   delay(1000);                                  

   Servo1.write(105);           // turn shaft to 105 degrees

   delay(1000);                                

   int left_2=analogRead(A0);       //2nd set of value

   int right_2=analogRead(A1);

 delay(1000);

   Left_Sensor_AVG= (left_1+left_2)/2;       //calculating average and store it in global variable

   Right_Sensor_AVG= (right_1+right_2)/2;

  

 }

 


void loop()

{

 

  int Left_LDR  = analogRead(A0);             // read the input on analog pins.

  int Right_LDR = analogRead(A1);

    if(Left_LDR > Left_Sensor_AVG)              /*if left LDR's value is greater than average then it is in shadow.*/

  {

    angle=angle+1;                            /*increment servo angle, this angle will be written at the end of if statement*/

    if (angle>=180)                           //don't let angle value go beyond 180

    {

      angle=180;                              

    }

  }
  else if(Right_LDR > Right_Sensor_AVG)       /* if left sensor is in light then program will compare right sensor value*/

  {

    angle=angle-1;                            // decrement servo angle if right sensor is in shadow.  

    if (angle<=0)

      {

        angle=0;                              // again, don't let servo angle go below 0 degrees

      }

  } 

 Servo1.write(angle);                  // write the corrected angle to servos

  delay(10);                                         

}
