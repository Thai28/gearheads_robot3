#include <stdio.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Hàm khởi chạy động cơ
void initMotors()
{
  Wire.begin(); // Bắt đầu giao tiếp I2C
  pwm.begin(); // Khởi chạy drive của PWM
  pwm.setOscillatorFrequency(27000000); // Thiết lập tần số giao động
  pwm.setPWMFreq(1600); // Thiết lập tần số giao động là 1600Hz
  Wire.setClock(400000); 
  for (i = 8; i < 15; i++) // Đặt giá trị PWM ban đầu của các DC Motors là 0
  {
    pwm.setPWM(i, 0, 0);
  }
}
