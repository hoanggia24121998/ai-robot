# Phân công và vai trò

Nhóm 4 người. Mỗi người sở hữu một mảng và chịu trách nhiệm chính ở đó, nhưng ai cũng đọc và review code của người khác.

---

## Vai trò

| Vai trò | Người | Trách nhiệm |
|---|---|---|
| Leader | Naa | Duyệt pull request, phân công, chốt kiến trúc, giữ lộ trình, làm mảng firmware và AI ở giai đoạn 3 |
| Thành viên A | | Thuật toán điều hướng |
| Thành viên B | | Chuyển động |
| Thành viên C | | Cảm biến và giao diện |

Điền tên vào bảng khi nhóm đã chốt, rồi cập nhật `.github/CODEOWNERS` cho khớp.

---

## Bốn mảng công việc

Mỗi mảng là một thư mục riêng, nên hai người làm cùng lúc hiếm khi đụng file nhau. Đây là lý do cấu trúc thư mục được chia như vậy ngay từ đầu.

### Mảng 1 — Thuật toán điều hướng
**Thư mục:** `lib/Navigator/`, `test/test_navigator/`

Cải tiến cách tránh vật cản, phát hiện và thoát kẹt góc, giảm tốc mượt theo khoảng cách. Mỗi hành vi mới phải có test đi kèm.

Đây là mảng học được nhiều nhất về C++ thuần và về cách thiết kế để test được. Không đụng phần cứng dòng nào.

### Mảng 2 — Chuyển động
**Thư mục:** `lib/MotorController/`

Tăng giảm ga mượt thay vì giật, bù lệch tốc giữa hai bánh, quay theo góc thay vì theo thời gian. Giai đoạn 2 thì hiệu chỉnh trên động cơ thật.

Mảng này đụng tới PWM và timer của ESP32, học được về điều khiển phần cứng.

### Mảng 3 — Cảm biến
**Thư mục:** `lib/DistanceSensor/`

Lọc nhiễu bằng trung vị nhiều lần đo, chuyển sang cách đo không chặn luồng, hiệu chỉnh số đo trên phần cứng thật.

Mảng này nhỏ hơn hai mảng trên nên thường gộp với mảng 4.

### Mảng 4 — Giao diện và mạch ảo
**Thư mục:** `lib/RobotDisplay/`, `diagram.json`

Vẽ mặt biểu cảm trên OLED thay cho chữ, thêm linh kiện vào sơ đồ Wokwi, làm nút bấm phản hồi trực quan.

Mảng dễ vào nhất cho người mới, và kết quả nhìn thấy ngay nên dễ giữ hứng.

---

## Việc của leader

**Duyệt pull request.** Nhánh `main` được khoá, mọi thay đổi phải qua PR và cần leader chấp thuận. Xem cấu hình ở `docs/gop-code.md`.

**Phân công.** Tạo issue cho từng việc, gán người, gắn nhãn theo mảng. Thành viên tự nhận việc từ danh sách issue thay vì chờ được giao miệng.

**Chốt kiến trúc.** Những thay đổi chạm vào ranh giới giữa các mảng — đổi kiểu dữ liệu `NavDecision`, đổi chữ ký hàm công khai — phải bàn trước khi code, vì nó làm hỏng việc của người khác. Chốt xong thì ghi vào `docs/quyet-dinh.md`.

**Giữ lộ trình.** Mỗi tuần nhìn lại `docs/lo-trinh.md`, tick những mục đã xong, và nói rõ tuần tới tập trung vào đâu.

**Làm mảng firmware và AI.** Giai đoạn 3 cần cài ESP-IDF và hiểu kiến trúc Xiaozhi — phần này leader làm, các thành viên tiếp tục ba mảng còn lại trên mô phỏng.

---

## Nguyên tắc giữ cho bốn người không giẫm chân

**Một pull request một việc.** Tiện tay sửa thêm thứ khác thì tách PR riêng.

**Không sửa file ngoài mảng của mình mà không báo.** Cần đổi một hàm trong mảng người khác thì mở issue hoặc nhắn trước, đừng sửa thẳng rồi mới nói.

**`NavDecision` và `NavConfig` là hợp đồng chung.** Ba mảng cùng dùng hai kiểu dữ liệu này. Đổi chúng là đổi hợp đồng, phải bàn với cả nhóm.

**Pull `main` trước khi bắt đầu việc mới.** Nhánh tạo từ `main` cũ sẽ xung đột khi merge.

---

## Nhịp làm việc gợi ý

Mỗi tuần một lần, 30 phút: ai đã xong gì, ai đang kẹt ở đâu, tuần tới làm gì. Kẹt quá hai ngày thì nói ra, đừng tự xoay.

Leader duyệt PR trong vòng một ngày. Để PR treo lâu là cách nhanh nhất làm nhóm mất đà — người gửi không dám làm tiếp vì sợ xung đột.
