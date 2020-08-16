 int groundpin = 18;             // analog input pin 4 -- ground
 int powerpin = 19;              // analog input pin 5 -- voltage
 int xpin = A3;                  // x-axis of the accelerometer
 int ypin = A2;                  // y-axis
 int zpin = A1;                  // z-axis (only on 3-axis models)
 int a=0;
unsigned long last,start;


void setup()
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  digitalWrite(groundpin, LOW); 
  digitalWrite(powerpin, HIGH);
  a=analogRead(xpin);
  start=last=millis();  
 }
void loop()
{
  int x=analogRead(xpin);
  Serial.println(x);
  if((a+20)>=x&&(a-20)<=x)
  {
    last=millis();
    if((last-start)>10000)
    digitalWrite(13,HIGH);
  /*  Serial.println(last);
    Serial.println(start);
    Serial.println(a);
    Serial.println(x);*/
  }
  else
  {
    a=x;
    digitalWrite(13,LOW);
    start=millis();
   /* Serial.println(last);
    Serial.println(start);
    Serial.println(a);
    Serial.println(x);*/
  }
    delay(500);
}
