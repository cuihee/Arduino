void setup()
{
  Serial.begin(9600);
}

void loop()
{
  while(Serial.available())//70:48
  {
    char c = Serial.read();
    if (c == 'A')
    {
      Serial.println("Hello I am ana");
    }
  }
}
