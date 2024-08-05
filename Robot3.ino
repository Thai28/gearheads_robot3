// Nhập các thư viện đã tạo
#include "Sort.h" // Hệ thông phân loại bóng tự động
#include "motors.h" // Khởi chạy motor
#include "Control.h" // Khởi chạy và điều khiển chức năng trên tay cầm PS2

void setup()
{
  Serial.begin(115200); 
  initMotors(); // Khởi chạy motor
  setupPS2controller(); // Thiết lập tay cầm PS2
  initSort(); // Khởi chạy cảm biến màu sắc
  Serial.println("Hoan thanh thiet lap");
  pwm.setPWMFreq(50); // Đặt tần số PWM cho motor
}

void loop()
{
  robotFunction();
  delay(50);
}
// Hàm điều khiển hoạt động của robot
void robotFunction()
{
  ps2x.read_gamepad(0, 0); // Đọc trạng thái của tay cầm PS2
  PS2control(); // Xử lý các tín hiệu đầu vào của tay cầm PS2
  robotManeuver(); // Xử lý thao tác di chuyển của robot qua tín hiệu analog trên joystick của tay cầm PS2
  readAndSort(); // Phân loại bóng dựa theo giá trị dọc được từ cảm biến màu sắc
}