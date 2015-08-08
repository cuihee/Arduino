#include<stdlib.h>
const int PWM_ENA = 9;
const int N1 = 10;
const int N2 = 11;
int rate=1000;
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
      Serial.println("LIQINLIAN & CUIHE\n");
      Serial.print("  b:+");
      Serial.print("  c:-");
      Serial.print("  d:50%");
      Serial.print("  e:100%");      
      Serial.print("  f:STOP");
    }
    if (c == 'b')
    {
      MOTOR_STATUS = 3;
      if (rate == 0) rate = 1000;
      Serial.println("+");      
    }
    if (c == 'c')
    {
      MOTOR_STATUS = 1;
      if (rate == 0) rate = 1000;
      Serial.println("-");
    }
    if (c == 'd')
    {
      rate = 500;
      Serial.println("50%");
    }
    if (c == 'e')
    {
      rate = 1000;
      Serial.println("100%");
    }
    if (c == 'f')
    {
      MOTOR_STATUS = 2;
      Serial.println("STOP");
    }    
  }
}

void loop()
{
  PWM_PLUS();
  ControlMotor();
  test_control();
}
