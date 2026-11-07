# Kiến trúc

## Ba tầng, ba tốc độ

Một sự kiện từ cảm biến đi theo hai đường khác hẳn nhau về tốc độ, và việc tách chúng ra là quyết định thiết kế quan trọng nhất của dự án.

**Tầng phản xạ** chạy cục bộ trên vi điều khiển, chu kỳ 50ms. Đây là nơi `Navigator` sống. Thấy vật cản thì dừng và lùi ngay, không hỏi ai cả.

**Tầng hành động** là các lệnh do AI gọi xuống, mất một đến hai giây mỗi lượt. "Đi tới ba giây rồi quay lại" thuộc tầng này.

**Tầng sự kiện** là robot kể cho AI nghe chuyện vừa xảy ra, để nó phản ứng bằng lời.

Vì sao tránh vật cản không được đi qua AI: vòng AI mất một đến hai giây. Robot chạy 20cm mỗi giây thì trong hai giây nó đã đâm vào tường và đẩy thêm 20cm nữa. Phản xạ phải nằm trên chip.

## Tại sao Navigator không biết gì về phần cứng

```
DistanceSensor  ──số cm──>  Navigator  ──NavDecision──>  MotorController
   (phần cứng)              (thuật toán thuần)              (phần cứng)
```

`Navigator` không gọi `digitalWrite`, không gọi `millis()`, không biết động cơ tồn tại. Nó nhận khoảng cách và mốc thời gian, trả về một quyết định.

Ba lợi ích cụ thể:

Test chạy trên PC trong vài phần nghìn giây. Thử năm mươi kịch bản kẹt góc nhanh hơn thời gian Wokwi khởi động một lần.

Thay phần cứng không phải sửa thuật toán. Đổi HC-SR04 sang cảm biến laser VL53L0X thì chỉ `DistanceSensor` thay đổi.

Chuyển sang ESP-IDF không phải viết lại. Đây là lý do thật sự.

## Đường sang firmware thật

Repo này dùng framework Arduino cho dễ học. Firmware Xiaozhi trên robot thật dùng ESP-IDF, API khác.

Khi tới lúc chuyển:

`Navigator.h` và `Navigator.cpp` copy nguyên văn, không sửa một ký tự.

`MotorController` giữ nguyên cấu trúc, đổi phần gọi LEDC sang API của ESP-IDF. Khoảng ba chục dòng.

`DistanceSensor` đổi `pulseIn` sang cách đo của ESP-IDF, và phải chuyển vào một task riêng để không chặn luồng âm thanh.

`main.cpp` bỏ đi. Thay vào đó là một class board trong `main/boards/` của firmware Xiaozhi, nơi các hành động được khai báo thành MCP tool để mô hình ngôn ngữ gọi được.

Phần test thì giữ nguyên và vẫn chạy được, vì nó chưa bao giờ phụ thuộc phần cứng.

## Những gì chưa có trong repo này

Toàn bộ phần giọng nói. Trình mô phỏng Wokwi không hỗ trợ I2S, tức là không có micro và không có loa. Phần đó chỉ chạy được trên phần cứng thật, với firmware Xiaozhi.

Điều này không cản trở gì giai đoạn hiện tại: những gì đang làm ở đây — chuyển động, cảm biến, thuật toán — đều không dùng tới I2S.
