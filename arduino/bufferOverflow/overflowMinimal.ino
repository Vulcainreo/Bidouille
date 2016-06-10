int a[5];
String test = "aaaaaa";
int i = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  a[7] = 2;
  while (i < 100)
  {
    Serial.println(a[i], HEX);
    i++;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
