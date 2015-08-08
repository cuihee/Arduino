#include <MsTimer2.h>
int count=0; 
void flash() 
{
  Serial.print("lamps```"); 
  count++; 
  Serial.println(count);
}
void setup() 
{ 
  
  Serial.begin(115200); 
  pinMode(13, OUTPUT); 
  MsTimer2::set(500, flash); // 500ms
  MsTimer2::start();
}
void loop() 
{ 
    static boolean output = HIGH; 
    digitalWrite(13, output); 
    output = !output; 
    delay(1000); 
}
