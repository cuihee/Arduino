#include<stdlib.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <MsTimer2.h>

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
const int PWM_ENA = 8;
const int N1 = 9;
const int N2 = 10;
const int fullRate = 10;
int rate = fullRate;
int alterRate = fullRate / 5;
int MOTOR_STATUS = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(N1, OUTPUT);
  pinMode(N2, OUTPUT);
  sensors.begin();
  MsTimer2::set(1, PWM_PLUS);
  MsTimer2::start();
}
void PWM_PLUS()
{ 
  static int tempPWM = 0;
  if (tempPWM < fullRate) tempPWM += 1;
  else tempPWM = 0;
  if (tempPWM<rate)
    digitalWrite(PWM_ENA, HIGH);
  if (tempPWM>=rate)
    digitalWrite(PWM_ENA, LOW);

  switch(MOTOR_STATUS)
  {
    case 0://不转
      digitalWrite(N1, LOW);
      digitalWrite(N2, LOW);
      break;
    case 1://反转
      digitalWrite(N1, HIGH);
      digitalWrite(N2, LOW);
      break;
    case 2://不转
      digitalWrite(N1, HIGH);
      digitalWrite(N2, HIGH);
      break;
    case 3://正转
      digitalWrite(N1, LOW);
      digitalWrite(N2, HIGH);
      break;
    default:
      MOTOR_STATUS = 0;
  } 
}


void test_control()
{  
  if (Serial.available())   //70:48
  {
    char c = Serial.read();    
    if (c == 'h')
    {
      Serial.print("LIQINLIAN & CUIHE");
      Serial.println(" ");
      Serial.println("q:+ w:- a:50% s:100%  d:STOP  x:+10%  z:-10%");
    }
    if (c == 'q')
    {
      MOTOR_STATUS = 3;
      if (rate < fullRate/5) rate = fullRate;
      Serial.println("+");      
    }
    if (c == 'w')
    {
      MOTOR_STATUS = 1;
      if (rate < fullRate/5) rate = fullRate;
      Serial.println("-");
    }
    if (c == 'a')
    {
      rate = fullRate / 2;
      Serial.println("50%");
    }
    if (c == 's')
    {
      rate = fullRate;
      Serial.println("100%");
    }
    if (c == 'd')
    {
      MOTOR_STATUS = 2;
      Serial.println("STOP");
    }
    if (c == 'x')
    {
      if (rate + fullRate / 10 <= fullRate)
        rate = rate + fullRate / 10;
      Serial.print(rate*100/fullRate);
      Serial.println("%");      
    }
    if (c == 'z')
    {
      if (rate - fullRate / 10 >= alterRate)
        rate = rate - fullRate / 10;
      Serial.print(rate*100/fullRate);
      Serial.println("%");      
    }
    if (c == 'p')
    {
      MsTimer2::stop();
      sensors.requestTemperatures();
      Serial.print(sensors.getTempCByIndex(0)); 
      Serial.println("`C"); 
      
      MsTimer2::start();
    }
  }
}

void loop()
{
//  PWM_PLUS();
  test_control();
}
