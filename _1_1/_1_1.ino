void setup() //系统的初始化 
{ 
  Serial.begin(9600);//设置串口波特率 
} 
void loop() //程序循环执行，运转 Arduino 
{ 
  Serial.println("HelloArduino"); //打印 HelloArduino 
  delay(1000); //延时 1000ms 
} 
