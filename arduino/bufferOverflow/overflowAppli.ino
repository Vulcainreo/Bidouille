#include <SoftwareSerial.h>

SoftwareSerial debug(10, 11); // RX, TX
char rx_byte = 0;
char rx_buff[8];
boolean access = false;
String password = "password";
char pwdArray[8];
int i = 0;
int iterStack = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  debug.begin(9600);
  debug.println("Programm starting");
  debug.print("Variables settings .. access=");
  debug.print(access, BIN);
  debug.println(" | password="+password);

  password.toCharArray(pwdArray, sizeof(password));
  Serial.println("Enter your personnal code ...");  
}

void loop() {
  if (Serial.available() > 0) {    // is a character available?
    rx_byte = Serial.read();       // get the character
    if (rx_byte != '\n') {
      // a character of the string was received
      if (i > 7)
      {
        printStack();
      }
      rx_buff[i] = rx_byte;
      i++;
    }
    else if ( (compareCharArray(rx_buff,password)) || access ) {
      if (!access) {
         Serial.println("Access granted");
         Serial.println("Welcome "+arrayToString(rx_buff));;
      }
      access = true;
      switch (rx_buff[0])
      {
        case 'u':
          Serial.println("Light on");
          break;
        case 'd':
          Serial.println("Light off");
          break;
        default :
          help();
          break;
      }
        i=0;
    }
    else {
      Serial.println("Error, wrong code with :"+arrayToString(rx_buff));
      i=0;
    }
  }
}

void help()
{
  Serial.println("Available commands");
  Serial.println("u -> start the light");
  Serial.println("d -> shutdown the light");
  Serial.println("Other -> print help");
}

void printStack()
{
  while (iterStack < 300)
  {
    debug.println(rx_buff[iterStack], HEX);
    iterStack++;
  }
}

boolean compareCharArray(char a[8], String b)
{
  boolean result = false;
  String str(b);
  
  for (int s=0; s < 8; s++)
  {
    if (a[s] == b[s]) {
      result = true;
    }
    else
    {
      result = false;
    }
  }
  return result;
}

String arrayToString (char a[])
{
  String result = "";
  for (int s=0; s < 8; s++)
  {
    result += a[s];
  }
  return result;
}

