#include <TinyGPS++.h>
#include <SoftwareSerial.h>
static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;
SoftwareSerial SIM900(9, 8); // configure software serial port
// The TinyGPS++ object
String a="",b="";
double lat1,long1,lat2,long2;
TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
int c=0;
int sensorPin=A1;
int ledPin =  12;
int sensorValue=0;
int xpin = A0;
unsigned long last,start;
int z=0;
void setup() {
  z=analogRead(xpin);
  start=last=millis();
  pinMode(13,OUTPUT);
  pinMode(ledPin, OUTPUT);  
  SIM900.begin(19200);
  Serial.begin(19200);
  ss.begin(GPSBaud); 
  Serial.println("power up" );
  delay(3000); 
  lat1=gps.location.lat();
  long1=gps.location.lng();
  Serial.println(lat1 );
  Serial.println(long1);
   
}
void loop(){
    int x=analogRead(xpin);
    sensorValue= analogRead(sensorPin);
    
    digitalWrite(ledPin,HIGH);
   while (ss.available() > 0)
    if (gps.encode(ss.read())){
     if (gps.location.isValid())
      {
        lat2=gps.location.lat();
        long2=gps.location.lng();
//        Serial.println("Hello");
        if((lat2>(lat1+.00002)||lat2<(lat1-.00002))||(long2>(long1+.00002)||long2<(long1-.00002)))
         { 
           sensorValue= analogRead(sensorPin);
          if((sensorValue>=430)&&((z+20)>=x && (z-20)<=x))
           {
             Serial.println("Hello!!!");
             last=millis();
             if((last-start)>1000 && x>100)
             {
               Serial.println("Here!!!");
              digitalWrite(13,HIGH);
              digitalWrite(ledPin,LOW);
             }
           }
           a=String(lat2,6);//lat
           Serial.println(a);
        //Serial.print(F(","));
           b=String(long2,6);//long
           Serial.println(b);
           SubmitHttpRequest();
          lat1=lat2;
          long1=long2;          
         }
         else
         Serial.println("same");
       }
    }  
}
void SubmitHttpRequest()
{
   SIM900.println("AT+CSQ"); // Signal quality check
   delay(100);
   SIM900.println("AT+CGATT?"); //Attach or Detach from GPRS Support
   delay(100);
   SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection type is using gprs
   delay(500);
   SIM900.println("AT+SAPBR=3,1,\"APN\",\"CMNET\"");//setting the APN, Access point name string
   delay(1000);
   SIM900.println("AT+SAPBR=1,1");//setting the SAPBR
   delay(500);
   SIM900.println("AT+HTTPINIT"); //init the HTTP request
   delay(500); 
   //String name="abc";
   //String sem="xyz"
   String url="AT+HTTPPARA=\"URL\",\"http://creditcrunchers.16mb.com/Redirect2.php?Name=Abhishek&CarNo=WB-02Q-3518&Lat="+a+"&Lng="+b+"&Status=No"+"\"";
   SIM900.println(url);// setting the httppara, the second parameter is the website you want to access
  delay(1000);
  SIM900.println("AT+HTTPACTION=0");//submit the request 
  //delay(2000);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
  Serial.println("value send");
 }
