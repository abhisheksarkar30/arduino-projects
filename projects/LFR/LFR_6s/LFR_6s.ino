int f=0,rf=17,rb=16,lf=14,lb=15;//rf-right motor front,rb-right motor back,lf-left motor front,lb-left motor back
void setup() {
Serial.begin(9600);
for(int i=2;i<18;i++)
pinMode(i,i<8?INPUT:OUTPUT);
analogWrite(11,255);
analogWrite(10,255);
}

void loop() {
  if(!f||f&&digitalRead(3)&&!digitalRead(4)&&!digitalRead(5)&&digitalRead(6))
if(digitalRead(3)&&!digitalRead(4)&&!digitalRead(5)&&digitalRead(6)||!digitalRead(3)&&!digitalRead(4)&&!digitalRead(5)&&!digitalRead(6))//Forward
{
  digitalWrite(rf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
  digitalWrite(lf,HIGH);
  f=0;
  Serial.println("Forward");
}
else if(digitalRead(3)&&!digitalRead(4)&&!digitalRead(5)&&!digitalRead(6)&&!digitalRead(7))//90 left
{
  /*digitalWrite(rf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lb,HIGH);
  digitalWrite(lf,LOW);*/
  digitalWrite(rf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
  digitalWrite(lf,LOW);
  f=1;
  Serial.println("90 left");
}
else if(!digitalRead(2)&&!digitalRead(3)&&!digitalRead(4)&&!digitalRead(5)&&digitalRead(6))//90 right
{
  /*digitalWrite(rf,LOW);
  digitalWrite(rb,HIGH);
  digitalWrite(lb,LOW);
  digitalWrite(lf,HIGH);*/
  digitalWrite(rf,LOW);
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
  digitalWrite(lf,HIGH);
  f=1;
  Serial.println("90 right");
}
else if(digitalRead(3)&&!digitalRead(4)&&!digitalRead(5)&&!digitalRead(6)||digitalRead(2)&&digitalRead(3)&&digitalRead(4)&&(!digitalRead(5)||!digitalRead(6)||!digitalRead(7)))//45 left
{
  digitalWrite(rf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
  digitalWrite(lf,LOW);
  Serial.println("45 left");
}
else if(!digitalRead(3)&&!digitalRead(4)&&!digitalRead(5)&&digitalRead(6)||(!digitalRead(2)||!digitalRead(3)||!digitalRead(4))&&digitalRead(5)&&digitalRead(6)&&digitalRead(7))//45 right
{
  digitalWrite(rf,LOW);
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
  digitalWrite(lf,HIGH);
  Serial.println("45 right");
}
else //stop
{
  digitalWrite(rf,LOW);
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
  digitalWrite(lf,LOW);
  Serial.println("stop");
}
delay(10);
}
