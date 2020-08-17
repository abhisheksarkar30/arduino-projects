#include <SD.h>
#include <TMRpcm.h> 
#include <NewPing.h>

#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar1(3, 2, MAX_DISTANCE); // TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE.
NewPing sonar2(5, 4, MAX_DISTANCE);
NewPing sonar3(7, 6, MAX_DISTANCE);
NewPing sonar4(A0, A1, MAX_DISTANCE);
NewPing sonar5(A3, A5, MAX_DISTANCE);

TMRpcm tmrpcm; 

File root;
File entry;
const int chipSelect = 10;    
// ---------------------------------------------------------------------------------

const int oldCard = SPI_HALF_SPEED;
const int newCard = SPI_QUARTER_SPEED;
int cardType = newCard;
// ---------------------------------------------------------------------------------
int height=A2,cutoff=150;
int vcc=A4;
int flag=-1;
int in = 8;
int lang=0;//0-Eng,1-Hin
int front,left,back,right,below;//sensor placement. flag 1,2,3,4,5 respectively. 0 - all direction block

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("\nInitializing SD card...");
  pinMode(chipSelect, OUTPUT); 
  if (!SD.begin(chipSelect,cardType)) {
    Serial.println("failed!");
    return;
  }
  Serial.println("done.");

  pinMode(vcc,OUTPUT);
  digitalWrite(vcc,HIGH);
  pinMode(in,INPUT_PULLUP);
  digitalWrite(in,HIGH);
  pinMode(height,INPUT);
  
  tmrpcm.speakerPin = 9;  
  root = SD.open("/");
  tmrpcm.setVolume(5);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  //Serial.print("Ping: ");
  front=sonar1.ping_cm();left=sonar2.ping_cm();back=sonar3.ping_cm();right=sonar4.ping_cm();below=sonar5.ping_cm();//sensor placement. flag 1,2,3,4,5 respectively. 0 - all direction block
  Serial.println((String)front + " " + right + " " + back + " " + left + " " + below); // Send ping, get distance in cm and print s1ult (0 = outside set distance range)
  cutoff=(1023-analogRead(height))*400.0/1024;
  Serial.println(cutoff);
  if(!digitalRead(in))
  {
    while(!digitalRead(in))
    delay(100);
    lang=++lang%2;
  }
  Serial.println(lang);
  switch(lang)
  {
    case 0:english();break;
    case 1:hindi();break;
  }
}
void english()
{
  if((below>=0 && below<cutoff) || below>cutoff+5)
  {
    if(flag!=5)
    {
      flag=5;
      tmrpcm.play("OBSTACLE.WAV");
      while(tmrpcm.isPlaying());
      tmrpcm.play("BELOW.WAV");
      while(tmrpcm.isPlaying());
    }
  }
  else if(front==0 || front>=120)
  {
    if(flag!=1)
    {
      flag=1;
      tmrpcm.play("MOVE.WAV");
      while(tmrpcm.isPlaying());
      tmrpcm.play("AHEAD.WAV");
      while(tmrpcm.isPlaying());
    }
  }
  else if(left==0 || (left>=100))
  {
    if(flag!=4)
    {
      flag=4;
      tmrpcm.play("MOVE.WAV");
      while(tmrpcm.isPlaying());
      tmrpcm.play("LEFT.WAV");
      while(tmrpcm.isPlaying());
    }
  }
  else if(right==0 || (right>=100))
  {
    if(flag!=2)
    {
      flag=2;
      tmrpcm.play("MOVE.WAV");
      while(tmrpcm.isPlaying());
      tmrpcm.play("RIGHT.WAV");
      while(tmrpcm.isPlaying());
    }
  }
  else if(back==0 || back>=80)
  {
    if(flag!=3)
    {
      flag=3;
      tmrpcm.play("MOVE.WAV");
      while(tmrpcm.isPlaying());
      tmrpcm.play("BACK.WAV");
      while(tmrpcm.isPlaying());
    }
  }
  else if((front>0 && front<120) && (left>0 && left<100) && (right>0 && right<100) && (back>0 && back<80))
  {
    if(flag)
    {
      flag=0;
      tmrpcm.play("CONGEST.WAV");
      while(tmrpcm.isPlaying());
      tmrpcm.play("SYSTEM.WAV");
    }
  }
}
void hindi()
{
  if((below>0 && below<cutoff) || below>cutoff+5)
  {
    if(flag!=5)
    {
      flag=5;
      tmrpcm.play("NICHEY.WAV");
      while(tmrpcm.isPlaying());
      tmrpcm.play("BADHA.WAV");
      while(tmrpcm.isPlaying());
    }
  }
  else if(front==0 || front>=120)
  {
    if(flag!=1)
    {
      flag=1;
      tmrpcm.play("AAGEY.WAV");
      while(tmrpcm.isPlaying());
      tmrpcm.play("CHALE.WAV");
      while(tmrpcm.isPlaying());
    }
  }
  else if(left==0 || (left>=100))
  {
    if(flag!=4)
    {
      flag=4;
      tmrpcm.play("BAYEIN.WAV");
      while(tmrpcm.isPlaying());
      tmrpcm.play("CHALE.WAV");
      while(tmrpcm.isPlaying());
    }
  }
  else if(right==0 || (right>=100))
  {
    if(flag!=2)
    {
      flag=2;
      tmrpcm.play("DAYEIN.WAV");
      while(tmrpcm.isPlaying());
      tmrpcm.play("CHALE.WAV");
      while(tmrpcm.isPlaying());
    }
  }
  else if(back==0 || back>=80)
  {
    if(flag!=3)
    {
      flag=3;
      tmrpcm.play("PICHEY.WAV");
      while(tmrpcm.isPlaying());
      tmrpcm.play("CHALE.WAV");
      while(tmrpcm.isPlaying());
    }
  }
  else if((front>0 && front<120) && (left>0 && left<100) && (right>0 && right<100) && (back>0 && back<80))
  {
    if(flag)
    {
      flag=0;
      tmrpcm.play("KSHETRA.WAV");
      while(tmrpcm.isPlaying());
      tmrpcm.play("PRANALI.WAV");
    }
  }
}
