#include <TinyGPS++.h>
#include <SoftwareSerial.h>
static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;
SoftwareSerial SIM900(7, 8); // configure software serial port
// The TinyGPS++ object
String a="",b="";
TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
int c=0;

void setup() {     
  SIM900.begin(19200);
  Serial.begin(19200);
  ss.begin(GPSBaud); 
  Serial.print("power up" );
  delay(3000); 
   
}
void loop(){
 while (ss.available() > 0)
    if (gps.encode(ss.read())){
     if (gps.location.isValid())
      {
        Serial.println("Hello");
        a=String(gps.location.lat(),6);//lat
        Serial.println(a);
        //Serial.print(F(","));
        b=String(gps.location.lng(),6);//long
        Serial.println(b);
        SubmitHttpRequest();            
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
 }
