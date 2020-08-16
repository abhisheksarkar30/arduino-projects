int f=0,rf=17,rb=16,lf=14,lb=15;//rf-right motor front,rb-right motor back,lf-left motor front,lb-left motor back
//Right motor - 10, left motor - 11
int c=0;
void setup() {
Serial.begin(9600);
for(int i=2;i<18;i++)
pinMode(i,i<8?INPUT:OUTPUT);
}

void loop() {
  if(!f||f&&(digitalRead(2)||digitalRead(3)||digitalRead(4)||digitalRead(5)||digitalRead(6)||digitalRead(7)))
if(!digitalRead(3)&&digitalRead(4)&&digitalRead(5)&&!digitalRead(6)||digitalRead(3)&&digitalRead(4)&&digitalRead(5)&&digitalRead(6))//Forward
{
  digitalWrite(rf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
  digitalWrite(lf,HIGH);
  analogWrite(11,60);
  analogWrite(10,60);
  f=0;
  Serial.println("Forward");
}
else if(!digitalRead(3)&&digitalRead(4)&&digitalRead(5)&&digitalRead(6)&&digitalRead(7))//90 left
{
  delay(150);
  digitalWrite(rf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lb,HIGH);
  digitalWrite(lf,LOW);
  analogWrite(11,60);
  analogWrite(10,60);
  f=1;
  Serial.println("90 left");
  //delay(150);
}
else if(digitalRead(2)&&digitalRead(3)&&digitalRead(4)&&digitalRead(5)&&!digitalRead(6))//90 right
{
  delay(150);
  digitalWrite(rf,LOW);
  digitalWrite(rb,HIGH);
  digitalWrite(lb,LOW);
  digitalWrite(lf,HIGH);
  analogWrite(11,60);
  analogWrite(10,60);
  f=1;
  Serial.println("90 right");
}
else if(!digitalRead(3)&&digitalRead(4)&&digitalRead(5)&&digitalRead(6)||!digitalRead(2)&&!digitalRead(3)&&!digitalRead(4)&&(digitalRead(5)||digitalRead(6)||digitalRead(7)))//45 left
{
  digitalWrite(rf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
  digitalWrite(lf,LOW);
  analogWrite(11,80);
  analogWrite(10,80);
  Serial.println("45 left");
}
else if(digitalRead(3)&&digitalRead(4)&&digitalRead(5)&&!digitalRead(6)||(digitalRead(2)||digitalRead(3)||digitalRead(4))&&!digitalRead(5)&&!digitalRead(6)&&!digitalRead(7))//45 right
{
  digitalWrite(rf,LOW);
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
  digitalWrite(lf,HIGH);
  analogWrite(11,80);
  analogWrite(10,80);
  Serial.println("45 right");
}
else //stop
{  
  delay(150);
  digitalWrite(rf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
  digitalWrite(lf,HIGH);
}
delay(10);
}

