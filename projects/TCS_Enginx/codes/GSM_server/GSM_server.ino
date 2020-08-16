#include <SoftwareSerial.h>
SoftwareSerial SIM900(7, 8); // configure software serial port
int c=0;
void setup() {     
  SIM900.begin(19200);
  Serial.begin(19200); 
  Serial.print("power up" );
  delay(3000); 

}
void loop()
{
  if(c<=15){
  Serial.println("SubmitHttpRequest - started" );
  SubmitHttpRequest();
  c++;
  Serial.println("SubmitHttpRequest - finished" );
  delay(2000);
  }
}

void SubmitHttpRequest()
{
   SIM900.println("AT+CSQ"); // Signal quality check
   delay(100);
   SIM900.println("AT+CGATT?"); //Attach or Detach from GPRS Support
   delay(100);
   SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection type is using gprs
   delay(1000);
   SIM900.println("AT+SAPBR=3,1,\"APN\",\"CMNET\"");//setting the APN, Access point name string
   delay(4000);
   SIM900.println("AT+SAPBR=1,1");//setting the SAPBR
   delay(2000);
   SIM900.println("AT+HTTPINIT"); //init the HTTP request
   delay(2000); 
   //String name="abc";
   //String sem="xyz"
   //String url="AT+HTTPPARA=\"URL\",\"http://gpshostandy.esy.es/roger.php?Name=hhjhjk&Sem=gjh"";
   SIM900.println("AT+HTTPPARA=\"URL\",\"http://gpshostandy.esy.es/roger.php?Name=hhjhjk&Sem=gjh\"");// setting the httppara, the second parameter is the website you want to access
  delay(1000);
  SIM900.println("AT+HTTPACTION=0");//submit the request 
  delay(2000);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
 }
