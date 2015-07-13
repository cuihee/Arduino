#include<stdlib.h>
const int PWM_ENA = 9;
const int N1 = 10;
const int N2 = 11;
int rate = 1000;
int MOTOR_STATUS = 3;
void setup()
{
  Serial.begin(9600);//设置串口波特率 
  pinMode(N1, OUTPUT);
  pinMode(N2, OUTPUT);  
}
void PWM_PLUS()
{ 
  digitalWrite(PWM_ENA, HIGH);
  delayMicroseconds(rate);
  digitalWrite(PWM_ENA, LOW);
  delayMicroseconds(1000 - rate);
}

void ControlMotor()
{
  //MOTOR_STATUS = 3;
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
    if (c == 'a')
    {
      Serial.println("LIQINLIAN & CUIHE");      
    }
    if (c == 'b')
    {
      MOTOR_STATUS = 3;
      Serial.println("ZHENG ZHUAN");
    }
    if (c == 'c')
    {
      MOTOR_STATUS = 1;
      Serial.println("FAN ZHUAN");
    }
    if (c == 'd')
    {
      rate = 500;
      Serial.println("rate = 500");
    }
    if (c == 'e')
    {
      rate = 1000;
      Serial.println("rate = 1000");
    }
  }
}

void loop()
{  
  PWM_PLUS();
  ControlMotor();
  test_control();
}
