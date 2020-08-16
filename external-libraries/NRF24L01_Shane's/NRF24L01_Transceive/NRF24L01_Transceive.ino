/*
1) I am not English. so no comments needed about spelling
2) IF you find error or improvement please email me.
3) andre.witbank@gmail.com
4) I found code at http://shanes.net/another-nrf24l01-sketch-string-sendreceive/

*/
//Libraries needed
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

/* 1 - GND
2 - VCC 3.3V ONLY!!!
3 - CE to Arduino pin 9
4 - CSN to Arduino pin 10
5 - SCK to Arduino pin 13
6 - MOSI to Arduino pin 11
7 - MISO to Arduino pin 12
8 - NA
This sketch receives and sent strings from nrf24
and prints them out via serial.
*/
int msg[1]; //Holding your sent message
#define CE_PIN 9
#define CSN_PIN 10
RF24 radio(CE_PIN, CSN_PIN);
// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipe = 0xE8E8F0F0E1LL;

String theMessage = ""; //Received Message
String inputString = ""; //Hold incoming Message from Serial

void setup(void) {
Serial.begin(57600);
while (!Serial) {} //Needed for Leonardo
radio.begin(); //Start the radio
radio.setRetries(15, 15); // optionally, increase the delay between retries & # of retries
radio.setPayloadSize(8);// optionally, reduce the payload size.
radio.openWritingPipe(pipe);
radio.openReadingPipe(1, pipe);
radio.startListening();
}

void loop(void) {
if (radio.available()) { //Wait for incoming message from radio
receiveText(); //Call funtion to receive message
}
}

void receiveText() {
radio.read(msg, 1); //Read radio 1 char at a time
char theChar = msg[0]; //Stor it in theChar
if (msg[0] != 2) { //If you get \n char then
theMessage.concat(theChar); //link all together
}
else { //If done then
Serial.println(theMessage); //Print to serial
theMessage = ""; //Clear Message
}
}
//This is same as EXAMPLE CODE it just works this better. NO ERRORS
void serialEvent() { //if something happens in serial do this
while (Serial.available()) { //Do till you get all from serial
char inChar = (char)Serial.read(); // get the new byte:
delay(3); //*****I add this else you get broken messages******
inputString += inChar;// add it to the inputString:
}
sentText(); //Call function to sent message to other radio
}

void sentText() {
radio.stopListening(); // First, stop listening so we can talk.
// String theMessage = inputString; //
int messageSize = inputString.length(); //Calculate String length
for (int i = 0; i < messageSize; i++) { //Sending 1 char at a time to other radio
int charToSend[1]; //Hold the char to be send
charToSend[0] = inputString.charAt(i); //First char stored
bool ok = radio.write(charToSend, 1); //Sent char
if (ok) //This is not needed but will make you feel better
Serial.println("OK...");
else
Serial.println("ERROR...");
}
msg[0] = 2; //send the 'terminate string' value...
radio.write(msg, 1);
inputString = ""; // clear the string
radio.startListening(); // Now, continue listening
}
