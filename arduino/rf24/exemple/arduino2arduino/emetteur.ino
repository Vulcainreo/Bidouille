#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);

const byte rxAddr[6] = "00001";


void setup()
{
  pinMode(13, OUTPUT);
  radio.begin();
  radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr[6]);
  radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening();
}

void loop()
{
  const char text[] = "Hello World ";
  radio.write(&text, sizeof(text));
   digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
   delay(1000);
}