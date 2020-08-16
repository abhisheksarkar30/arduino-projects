/* Simple Serial ECHO script : Written by ScottC 03/07/2012 */

/* Use a variable called byteRead to temporarily store
   the data coming from the computer */
char Read;

void setup() {                
// Turn the Serial Protocol ON
  Serial.begin(9600);
  for(int p=4;p<=7;p++)
    pinMode(p, OUTPUT);
}

void loop() {
   /*  check if data has been sent from the computer: */
  while (Serial.available()) {
    /* read the most recent byte */
     Read = Serial.read();     
  switch(Read)
  {
    case 'w':
    case 'W':   for(int p=4;p<8;p++)
                digitalWrite(p,(p==4||p==7)?HIGH:LOW);
                delay(1000);
                Serial.println(Read);
                break;
    case 's':
    case 'S':   for(int p=4;p<8;p++)
                digitalWrite(p,(p==5||p==6)?HIGH:LOW);
                delay(1000);
                Serial.println(Read);
                break;
    case 'a':
    case 'A':   for(int p=4;p<8;p++)
                digitalWrite(p,p==4?HIGH:LOW);
                delay(1000);
                Serial.println(Read);
                break;
    case 'd':
    case 'D':   for(int p=4;p<8;p++)
                digitalWrite(p,p==7?HIGH:LOW);
                delay(1000);
                Serial.println(Read);
                break;
    default: Serial.println("Invalid Choice");
  }
      // turn the LED on (HIGH is the voltage level)
  }
}

