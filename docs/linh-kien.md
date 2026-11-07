# Linh kiện dự kiến

Danh sách cho giai đoạn 2. **Chưa mua vội** — chốt bảng phân chân sau giai đoạn 1 rồi hẵng đặt hàng, lúc đó sẽ biết chính xác cần gì.

Giá là ước lượng theo thị trường linh kiện trong nước thời điểm ghi tài liệu, cần kiểm lại khi mua thật.

| Món | Gợi ý cụ thể | Khoảng giá | Ghi chú |
|---|---|---|---|
| Vi điều khiển | ESP32-S3 N16R8 | 150–250k | **Bắt buộc có PSRAM** |
| Micro | INMP441 (I2S) | 30–50k | Cho giai đoạn 3 |
| Khuếch đại | MAX98357A | 30–50k | Cho giai đoạn 3 |
| Loa | 3W 4Ω | 15–30k | |
| Màn hình | OLED 1.3" SSD1306 I2C | 40–60k | Mã trong repo dùng loại này |
| Động cơ | 2× N20 giảm tốc + bánh xe | 100–160k | |
| Driver động cơ | DRV8833 hoặc TB6612FNG | 30–50k | |
| Cảm biến khoảng cách | HC-SR04 | 20–35k | Xem ghi chú bên dưới |
| Bánh đỡ | Bánh mắt trâu | 10–20k | |
| Nguồn | 18650 + đế + TP4056 + boost 5V | 80–120k | |
| Nút bấm, dây, điện trở | | 30–50k | |

**Tổng khoảng 550–900k**, chưa tính vỏ.

## Những chỗ đừng tiết kiệm

**PSRAM.** Đừng mua ESP32-C3 hay bản S3 không PSRAM. Wake word offline và bộ đệm âm thanh ngốn RAM rất nặng, thiếu PSRAM là tắc ngay ở giai đoạn 3, lúc đó mua lại board mất nhiều hơn tiền tiết kiệm được.

**Nguồn.** Động cơ khởi động kéo dòng lớn làm sụt áp, ESP32 reset giữa câu nói. Đây là lỗi phổ biến nhất của robot tự làm. Tách nguồn động cơ khỏi nguồn logic, thêm tụ 470µF sát driver.

**Mỏ hàn.** Mua loại tử tế một chút, dùng được nhiều năm cho các dự án sau.

## Cân nhắc thay thế

**HC-SR04 so với VL53L0X.** HC-SR04 rẻ, nhưng đo bằng cách chờ xung dội nên chặn luồng tới vài chục mili giây — phải đặt trong task riêng. VL53L0X đo bằng laser qua I2C, không chặn, chính xác hơn, nhưng đắt hơn và tầm đo ngắn hơn. Nếu đến giai đoạn 3 thấy việc đo làm giật tiếng nói thì đổi sang loại này.

**Động cơ có encoder.** Đắt hơn nhưng cho phép đi thẳng chính xác và quay đúng góc. Chưa cần ở giai đoạn 2; nếu robot cứ lệch hướng mãi thì cân nhắc.

## Vật tư khung và vỏ

Hai hướng: in 3D cho vỏ kín và gọn, hoặc uốn khung bằng dây đồng 1.5–2mm cho vẻ handmade.

Nếu người nhận là trẻ con, nên in 3D bọc kín phần pin và mạch. Khung đồng trần nằm sát pin lithium là điểm cần cẩn thận, và góc nhọn cũng vậy. Có thể giữ khung đồng làm chi tiết trang trí bên ngoài.

Dây tín hiệu 0.7mm loại tráng men phải cạo sạch lớp men ở đầu mối trước khi hàn. Không cạo thì mối hàn trông rất đẹp mà không thông mạch — lỗi kinh điển làm mất cả buổi dò.
