#include <SoftwareSerial.h>

#include <stdlib.h>


#define DEBUG true
#define DEVICETYPE "wireless"
#define SSID "Abhishek"     // "SSID-WiFiname"
#define PASS "12345asa" // "password"
#define IP "192.168.43.74"  //IP to connect
#define PORT 8100

String MAC = "";
SoftwareSerial esp8266(11,12);

void setup()
{
  pinMode(7,OUTPUT);
  Serial.begin(115200); //or use default 115200.
  esp8266.begin(115200);
  Serial.println("AT");
  esp8266.println("AT");
 delay(5000);

 
}

void registerThis(){
  Serial.println("Registering this device on the server");
  char* response = "";
  do{
    String msg = "/api/register?mac="+MAC+"&type="+DEVICETYPE;
    httpRequest(msg);
    delay(3000);
    response = waitForResponse();
    Serial.println("Response in register this()");
    Serial.println(response);
  }while(strstr(response,"OK") < 0);
}

void getMAC()
{
  esp8266.println("AT+CIFSR");
  String response = waitForResponse();
  Serial.println("get mac response: "+response+"/////");
  int q0 = response.indexOf("\""); //Index of first qoute
  int q1 = response.indexOf("\"",q0+1); //Index of second qoute
  int q2 = response.indexOf("\"",q1+1);
  int q3 = response.indexOf("\"",q2+1);
  MAC = response.substring(q2+1,q3);
  Serial.println("Device Mac Address: "+MAC+"/////");
}

char* waitForResponse(){
    const char* response;
    while(1){
        if(esp8266.available()){
            while(esp8266.available())
            {
                response = strcat(response,esp8266.read());
                //Serial.println("Response in waitfor response()" + response+"/////");
            } 
            break;
        }
    }
    return response;
}

boolean connectWiFi()
{
  esp8266.println("AT+CIOBAUD?");
  Serial.println(waitForResponse());
  esp8266.println("AT+CWMODE=1");
  Serial.println("connectWifi() call"+esp8266.readString()+"///");
  delay(2000);
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  
  esp8266.println(cmd);
  Serial.println("esp8266.readString: " +esp8266.readString()+"////");
  delay(5000);
  if(esp8266.find("OK"))
  {
    return true;
  }
  else
  {
    return false;
  }
}

void httpRequest(String msg){
  String response = "";
  String AT = "AT+CIPSTART=\"TCP\",\""+String(IP)+"\","+PORT;
  esp8266.println(AT);
//  Serial.println("wait for response in http"+waitForResponse()+"/////");
  String request = "GET "+msg+" HTTP/1.1\r\n\r\n\r\n";
  Serial.println("request from server: "+request+ "////");
  int len = request.length();
  AT = "AT+CIPSEND=";
  AT += len;
  do{
    Serial.println("AT in httpRequest() "+AT+ "////");
    esp8266.println(AT);
    response = waitForResponse();
    Serial.println("Response in do loop: "+response+ "/////");
  }while(response.indexOf('>') < 0);
  esp8266.print(request);
}

void roger2(String res){
  int q1 = res.indexOf("<cmd>");
  int q2 = res.indexOf("</cmd>");
  String cmd = res.substring(q1+5,q2);
  Serial.println("Command Update : "+cmd);
  //TO-DO obey the command
  
   led(10);
  //Acknowledge the command
  String msg = "/api/command/ack?mac="+MAC;
  delay(3000);
  httpRequest(msg);
}
void roger(String res){
  int q1 = res.indexOf("<cmd>");
  int q2 = res.indexOf("</cmd>");
  String cmd = res.substring(q1+5,q2);
  Serial.println("Command: "+cmd);
  //TO-DO obey the command

  //Acknowledge the command
  String msg = "/api/command/ack?mac="+MAC;
  httpRequest(msg);
}

void led(int a)
{
  for(int i=1;i<=a;i++)
  {
    digitalWrite(7,HIGH);
    delay(500);
    digitalWrite(7,LOW);
    delay(500);
    
  }
}

void loop()
{
  /* Serial.println("Checking for commands/////////////////////////////");
  String msg = "/api/command?mac="+MAC;
  Serial.println("query: "+msg);
  httpRequest(msg);
  String response = waitForResponse();
  Serial.println("Command available: "+response);

  roger(response);

  //Optional Delay
  delay(3000);

  Serial.println("Updating Scales");
  //TO-DO get value from the sacles
  int value = analogRead(A1);
  msg = "/api/update?mac="+MAC+"&value="+value;
  httpRequest(msg);
  response = waitForResponse();
  Serial.println("Command available: "+response);

  //Optional Delay
  delay(3000);

  Serial.println("Updating Battery Status");
  //TO-DO get battery level
  int level = 0;
  msg = "/api/battery?mac="+MAC+"&level="+level;
  httpRequest(msg);
  response = waitForResponse();
  Serial.println("Command available: "+response); */
  
 if(esp8266.available()) // check if the esp is sending a message 
 {
   while(esp8266.available())
   {
     // The esp has data so display its output to the serial window 
     String c = esp8266.readString(); // read the next character.
     Serial.println(c);
   }  
 }
 

 
 if(Serial.available())
 {
   // the following delay is required because otherwise the arduino will read the first letter of the command but not the rest
   // In other words without the delay if you use AT+RST, for example, the Arduino will read the letter A send it, then read the rest and send it
   // but we want to send everything at the same time.
   delay(1000); 
   
   String command;
   
   while(Serial.available()) // read the command character by character
   {
       // read one character
     command=Serial.readString();
   }
   esp8266.println(command); // send the read character to the esp8266
 }
}


  
