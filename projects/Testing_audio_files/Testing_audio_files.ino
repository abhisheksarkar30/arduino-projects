#include <SD.h>
#include <TMRpcm.h> 
#include <NewPing.h>


#define MAX_DISTANCE 450 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar1(3, 2, MAX_DISTANCE); // TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE.
NewPing sonar2(5, 4, MAX_DISTANCE);
NewPing sonar3(7, 6, MAX_DISTANCE);
NewPing sonar4(A0, A1, MAX_DISTANCE);
NewPing sonar5(A2, A3, MAX_DISTANCE);

TMRpcm tmrpcm; 

File root;
File entry;
const int chipSelect = 10;    
// ---------------------------------------------------------------------------------

const int oldCard = SPI_HALF_SPEED;
const int newCard = SPI_QUARTER_SPEED;
int cardType = newCard;
// ---------------------------------------------------------------------------------

int inSwitch = 7;
int flag=-1;

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

  tmrpcm.speakerPin = 9;
  
  pinMode(inSwitch,INPUT_PULLUP);
  digitalWrite(inSwitch,HIGH);
  
  root = SD.open("/");
  tmrpcm.setVolume(6);
  File E=entry;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  playNext();
 /*delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  int s1=sonar1.ping_cm(),s2=sonar2.ping_cm(),s3=sonar3.ping_cm(),s4=sonar4.ping_cm(),s5=sonar5.ping_cm();
  Serial.print((String)s1 + " " + s2 + " " + s3 + " " + s4 + " " + s5); // Send ping, get distance in cm and print s1ult (0 = outside set distance range)
  Serial.println("cm");
  if(s1>200&&!flag)
  {
    flag=1;
  tmrpcm.play("TEST.WAV");
  while(tmrpcm.isPlaying());
  tmrpcm.disable();
  flag++;
  }
  else if(s1<200&&flag)
  {
    flag=0;
    tmrpcm.play("TEST1.WAV");
  while(tmrpcm.isPlaying());
  tmrpcm.disable();
  }*/
}
void playNext() {
  entry = root.openNextFile();
  if (entry) {
    entry.close();
    Serial.println(entry.name());
    tmrpcm.play(entry.name()); 
    while(tmrpcm.isPlaying());  
  }
}
