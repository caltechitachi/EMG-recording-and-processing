const int analogPin = A0;           // Chân analog kết nối tín hiệu EMG
const double adcRef = 5.0;          // Điện áp tham chiếu ADC (thường là 5V)
const int adcMax = 1023;            // Giá trị tối đa ADC 10-bit
const double emgOffset = 0.75;       // Offset DC của tín hiệu EMG đầu ra (V)
const double gain = 1900.0;         // Hệ số khuếch đại

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Khai báo LCD I2C tại địa chỉ 0x27, kích thước 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);
byte degree[8] = {
0B01110,
0B01010,
0B01110,
0B00000,
0B00000,
0B00000,
0B00000,
0B00000
};
void setup() {
  Serial.begin(9600);
  Serial.println("Time (ms),EMG (uV)");
  lcd.init();                   // Khởi động LCD
  lcd.backlight();             // Bật đèn nền
  lcd.setCursor(0, 0);
  lcd.print("Gia tri EMG:");     // Dòng 1: Tiêu đề
}

void loop() {
  int rawValue = analogRead(analogPin);

  // B1: Tính điện áp đầu vào (V)
  double voltage = (rawValue / (double)adcMax) * adcRef;

  // B2: Loại bỏ offset (tính hiệu điện áp thực sự)
  double centeredVoltage = voltage - emgOffset;

  // B3: Chuyển sang giá trị EMG sinh lý (μV)
  double emg_uV = (centeredVoltage * 1e6) / gain;  // μV

  // B4: In ra thời gian và giá trị EMG
  unsigned long currentTime = millis();
  Serial.print(currentTime);
  Serial.print(",");
  Serial.println(emg_uV, 1);  // Hiển thị 1 chữ số thập phân (ví dụ: 1270.3 μV)
// Hiển thị kết quả lên LCD
  lcd.setCursor(0, 1);
  lcd.print("                ");  // Xoá dòng
  lcd.setCursor(0, 1);
  lcd.print(emg_uV, 2); //In 2 chu so phan thap phan
  //delayMicroseconds(1950);  // 1950 µs = 1.95 ms ≈ 512 Hz


   delay(200); // Tần số lấy mẫu ~50Hz
}
