 
void setup() {                

  for(int p=9;p<=12;p++)
    pinMode(p, OUTPUT);
    for(int b=2;b<=7;b++)
    pinMode(b, INPUT);
    
}

void loop() { 
   int in[6];
   for(int b=2;b<=7;b++)
   in[b-2]=digitalRead(b);
   //2,3- mode and kick
   digitalWrite(9,in[0]);
   digitalWrite(10,in[1]);
   //buttons:- 4-forward, 5-backward, 6-left, 7-right
   //outputs:- 11-forward, 00-backward, 10-left, 01-right
   digitalWrite(11,(in[2]+in[4])!=0);  
   digitalWrite(12,(in[2]+in[5])!=0);
   delay(1);        // delay in between reads for stability
}

