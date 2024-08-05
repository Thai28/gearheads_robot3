#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// Hàm khởi chạy cảm biến màu sắc
void initSort()
{
  if (tcs.begin())
  {
    Serial.println("Da tim thay cam bien");
  }
  else 
  {
    Serial.println("Khong tim thay cam bien");
    while(1); // Dừng tìm nếu không tìm thấy cảm biến
  }
}

// Hàm đọc dữ liệu từ cảm biến màu sắc và điều khiển cơ chế phân loại bóng
void readAndSort()
{
  if (halfAutomaticMode) return; // Không phân loại bóng nếu chế độ phân loại tự động đang bật
  uint16_t clear, red, green, blue;
  tcs.getRawData(&red, &green, &blue, &clear); // Nhận dữ liệu thô từ cảm biến màu sắc
  if (clear > 1000 && red > 1000 && green > 1000 && blue > 1000) // Bóng trắng
  {
    pwm.setPWM(4, 310, 410); // Mở servo
  }
  else if (clear < 500 && red < 500 && green < 500 && blue < 500) // Bóng đen
  {
    pwm.setPWM(4, 0, 0); // Đóng servo
  }
}