#include <PS2X_lib.h> // Thư viện PS2X cho tay cầm PS2

PS2X ps2x; // Tạo class cho tay cầm PS2

// Xác định các chân kết nối với tay cầm PS2
#define PS2_DAT 12
#define PS2_CMD 13
#define PS2_SEL 15
#define PS2_CLK 14

#define TOP_SPEED 4095 // Xác định tốc độ tối đa cho motor

// Xác định các biến trạng thái
bool halfAutomaticMode = false; 
bool ballLaunchMotorState = false; 
bool ballLaunchGateState = false;
bool ballDropGateState = false;

// Hàm thiết lập tay cầm PS2
void setupPS2controller()
{
  int err = -1;
  while (err != 0)
  {
    err = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);
  }
}
// Hàm xử lý các tín hiệu đầu vào của tay cầm PS2
bool PS2control()
{
  if (ps2x.Button(PSB_GREEN)) // Nút xanh lá (nút tam giác) mở / đóng cổng bắn bóng
  {
    ballLaunchGateState = !ballLaunchGateState;
    if (ballLaunchGateState)
    {
      pwm.setPWM(5, 310, 410); // Mở cổng
    }
    else
    {
      pwm.setPWM(5, 0, 0); // Đóng cổng
    }
  }
  if (ps2x.Button(PSB_PINK)) // Nút hồng (nút vuông) mở / đóng cổng thả bóng
  {
    ballDropGateState = !ballDropGateState;
    if (ballDropGateState)
    {
      pwm.setPWM(6, 310, 410); // Mở cổng
      pwm.setPWM(7, 310, 410);
    }
    else
    {
      pwm.setPWM(6, 0, 0); // Đóng cổng
      pwm.setPWM(7, 0, 0); 
    }
  }
  if (ps2x.Button(PSB_BLUE)) // Nút xanh dương (nút X) bật / tắt máy bắn bóng
  {
    ballLaunchMotorState = !ballLaunchMotorState
    if (ballLaunchMotorState)
    {
      pwm.setPWM(8, 0, 0); // Bật máy
      pwm.setPWM(9, 0, TOP_SPEED);
    }
    else 
    {
      pwm.setPWM(8, 0, 0); // Tắt máy
      pwm.setPWM(9, 0, 0);
    } 
  }
  if (ps2x.Button(PSB_RED)) // Nút đỏ (nút tròn) bật / tắt chế độ bán tự động
  {
    halfAutomaticMode = !halfAutomaticMode;
    pwm.setPWM(4, 0, 0); // Đóng cổng
  }
}
// Hàm xử lý thao tác di chuyển của robot
void robotManeuver()
{
  if (ps2x.Button(PSB_L3) || ps2x.Button(PSB_R3))
  {
    int leftJoystick = ps2x.Analog(PSS_LY); // Nhập giá trị trục y của joystick trái
    int rightJoystick = ps2x.Analog(PSS_RY); // Nhập giá trị trục y của joystick phải
    if (leftJoystick < 480)
    {
      // Chạy động cơ hướng về phía sau
      int speed = map(leftJoystick, 480, 0, 0, TOP_SPEED);
      pwm.setPWM(10, 0, speed);
      pwm.setPWM(11, 0, 0);
    } 
    else if (leftJoystick > 520)
    {
      // Chạy động cơ hướng về phía trước
      int speed = map(leftJoystick, 520, 1023, 0, TOP_SPEED);
      pwm.setPWM(10, 0, 0);
      pwm.setPWM(11, 0, speed);
    } 
    else 
    {
      // Dừng động cơ
      pwm.setPWM(10, 0, 0);
      pwm.setPWM(11, 0, 0);
    }
    if (rightJoystick < 480)
    {
      // Chạy động cơ hướng về phía sau
      int speed = map(rightJoystick, 480, 0, 0, TOP_SPEED);
      pwm.setPWM(12, 0, speed);
      pwm.setPWM(13, 0, 0);
    } 
    else if (rightJoystick > 520)
    {
      // Chạy động cơ hướng về phía trước
      int speed = map(leftJoystick, 520, 1023, 0, TOP_SPEED);
      pwm.setPWM(12, 0, 0);
      pwm.setPWM(13, 0, speed);
    } 
    else 
    {
      // Dừng động cơ
      pwm.setPWM(12, 0, 0);
      pwm.setPWM(13, 0, 0);
    }
  }
}