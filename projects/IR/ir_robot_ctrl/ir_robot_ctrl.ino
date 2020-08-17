/*Type your 5 button s code in if else if statement in bellow code. The shown value is my remote value.

Use 5 button to control robot forward, reverse, left right and stop*/

#include <IRremote.h>

int RECV_PIN = 11;

int statusled = 13;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()

{

irrecv.enableIRIn();

pinMode(statusled,OUTPUT);

pinMode(7,OUTPUT);

pinMode(6,OUTPUT);

pinMode(5,OUTPUT);

pinMode(4,OUTPUT);

digitalWrite(statusled,LOW);

}

void loop() {

if (irrecv.decode(&results)) {

digitalWrite(statusled,HIGH);

irrecv.resume();

if (results.value == 0xFF50AF){ // type your remote forward robot control button hex value in underlined area.

digitalWrite(7,HIGH);

digitalWrite(6,LOW);

digitalWrite(5,HIGH);

digitalWrite(4,LOW);

}else if(results.value == 0xFF30CF){ // type your remote left robot control button hex value in underlined area.

digitalWrite(7,HIGH);

digitalWrite(6,LOW);

digitalWrite(5,LOW);

digitalWrite(4,LOW);

}

else if(results.value == 0xFFB04F){ // type your remote right robot control button hex value in underlined area.

digitalWrite(7,LOW);

digitalWrite(6,LOW);

digitalWrite(5,HIGH);

digitalWrite(4,LOW);

} else if(results.value == 0xFFD02F){ // type your remote backward robot control button hex value in underlined area.

digitalWrite(7,LOW);

digitalWrite(6,HIGH);

digitalWrite(5,LOW);

digitalWrite(4,HIGH);

}else if(results.value == 0xFF9867){ // type your remote stop robot control button hex value in underlined area.

digitalWrite(7,LOW);

digitalWrite(6,LOW);

digitalWrite(5,LOW);

digitalWrite(4,LOW);

}

}

}
