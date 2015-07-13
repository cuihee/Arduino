#include<OneWire.h>
#include<DallasTemperature.h>

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup(void)
{ 
  Serial.begin(9600); //波特率设置为 9600
  Serial.println("Dallas Temperature IC Control Library Demo");
  sensors.begin();//启动单总线
}

void loop(void)
{
  Serial.print("Requesting Temperature..."); 
  sensors.requestTemperatures();//发送温度测量请求
  Serial.println("DONE");
  
  Serial.print("Temperature for the device 1 (index 0) is:");
  Serial.print(sensors.getTempCByIndex(0));//
  Serial.println("℃"); 
  Serial.print("Temperature for the device 2 (index 0) is:");
  Serial.print(sensors.getTempCByIndex(1));//
  Serial.println("℃"); 
  delay(1000); //一秒刷新一次
}
