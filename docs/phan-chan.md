# Bảng phân chân — ESP32-S3-DevKitC-1

Khai báo thật nằm trong `include/pinmap.h`. Bảng này giải thích lý do chọn.

| Chức năng | GPIO | Ghi chú |
|---|---|---|
| Động cơ trái, tiến | 4 | PWM qua LEDC |
| Động cơ trái, lùi | 5 | PWM |
| Động cơ phải, tiến | 6 | PWM |
| Động cơ phải, lùi | 7 | PWM |
| OLED SDA | 8 | I2C |
| OLED SCL | 9 | I2C |
| HC-SR04 TRIG | 15 | ra |
| HC-SR04 ECHO | 16 | vào |
| Nút bấm | 17 | INPUT_PULLUP, nối xuống GND |

Tổng cộng 9 chân. Trên phần cứng thật sẽ cần thêm khoảng 6 chân nữa cho micro và loa I2S, vẫn còn dư.

## Những chân tuyệt đối không dùng

**GPIO 0, 45, 46** là chân strapping, quyết định chế độ khởi động của chip. Nối sai mức logic lúc bật nguồn là board không boot, và triệu chứng rất khó đoán.

**GPIO 19, 20** là USB gốc trên chip. Dùng mất thì không nạp được qua cổng USB native.

**GPIO 26 đến 32** nối với flash và PSRAM. Đụng vào là chip chết ngay.

**GPIO 35, 36, 37** dùng cho PSRAM octal trên các bản N16R8 và N8R8. Board không có PSRAM octal thì dùng được, nhưng đừng mạo hiểm — chọn bản nào thì mang đi cả dự án.

**GPIO 43, 44** là UART0, chính là cổng serial dùng để nạp và xem log.

## Khi muốn đổi chân

Sửa `include/pinmap.h`, rồi sửa luôn `diagram.json` cho khớp. Hai file này phải đi đôi với nhau, lệch một chân là mô phỏng chạy mà không ra gì, rất mất thời gian dò.

## Lưu ý cho phần cứng thật

Những điều dưới đây không xuất hiện trong mô phỏng nhưng sẽ xuất hiện ngay khi lắp mạch:

Động cơ khi khởi động kéo dòng lớn làm sụt áp, ESP32 reset giữa chừng. Tách nguồn động cơ khỏi nguồn logic, thêm tụ 470µF sát driver.

`pulseIn` của HC-SR04 chặn luồng tới vài chục mili giây. Trong mô phỏng không sao, nhưng khi ghép vào firmware có xử lý âm thanh thì phải đẩy việc đo sang task riêng.

Số đo khoảng cách trong Wokwi là lý tưởng. Trên phần cứng thật phải hiệu chỉnh lại, vì tốc độ âm thanh đổi theo nhiệt độ và cảm biến có sai số riêng.

Mic đặt càng xa động cơ càng tốt, dây mic ngắn và xoắn lại, nếu không tiếng ồn động cơ sẽ lọt vào.
