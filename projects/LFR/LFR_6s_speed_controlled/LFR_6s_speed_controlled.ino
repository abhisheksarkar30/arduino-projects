int f=0,rf=17,rb=16,lf=14,lb=15;//rf-right motor front,rb-right motor back,lf-left motor front,lb-left motor back
//Right motor - 10, left motor - 11
void setup() {
Serial.begin(9600);
for(int i=2;i<18;i++)
pinMode(i,i<8?INPUT:OUTPUT);
}

void loop() {
  if(!f||f&&digitalRead(3)&&!digitalRead(4)&&!digitalRead(5)&&digitalRead(6))
if(digitalRead(3)&&!digitalRead(4)&&!digitalRead(5)&&digitalRead(6)||!digitalRead(3)&&!digitalRead(4)&&!digitalRead(5)&&!digitalRead(6))//Forward
{
  digitalWrite(rf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
  digitalWrite(lf,HIGH);
  analogWrite(11,100);
  analogWrite(10,100);
  f=0;
  Serial.println("Forward");
}
else if(digitalRead(3)&&!digitalRead(4)&&!digitalRead(5)&&!digitalRead(6)&&!digitalRead(7))//90 left
{
  //delay(100);
  digitalWrite(rf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
  digitalWrite(lf,LOW);/*
  digitalWrite(rf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lb,HIGH);
  digitalWrite(lf,LOW);*/
  analogWrite(11,80);
  analogWrite(10,80);
  f=1;
  Serial.println("90 left");
  delay(200);
}
else if(!digitalRead(2)&&!digitalRead(3)&&!digitalRead(4)&&!digitalRead(5)&&digitalRead(6))//90 right
{
  //delay(100);
  digitalWrite(rf,LOW);
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
  digitalWrite(lf,HIGH);/*
  digitalWrite(rf,LOW);
  digitalWrite(rb,HIGH);
  digitalWrite(lb,LOW);
  digitalWrite(lf,HIGH);*/
  analogWrite(11,80);
  analogWrite(10,80);
  f=1;
  delay(200);
  Serial.println("90 right");
}
else if(digitalRead(3)&&!digitalRead(4)&&!digitalRead(5)&&!digitalRead(6)||digitalRead(2)&&digitalRead(3)&&digitalRead(4)&&(!digitalRead(5)||!digitalRead(6)||!digitalRead(7)))//45 left
{
  digitalWrite(rf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
  digitalWrite(lf,LOW);
  analogWrite(11,80);
  analogWrite(10,80);
  Serial.println("45 left");
}
else if(!digitalRead(3)&&!digitalRead(4)&&!digitalRead(5)&&digitalRead(6)||(!digitalRead(2)||!digitalRead(3)||!digitalRead(4))&&digitalRead(5)&&digitalRead(6)&&digitalRead(7))//45 right
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
  digitalWrite(rf,LOW);
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
  digitalWrite(lf,LOW);
  Serial.println("stop");
}
delay(10);
}

