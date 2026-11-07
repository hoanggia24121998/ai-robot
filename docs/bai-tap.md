# Bài tập cho nhóm

Toàn bộ phần cài đặt trong `lib/` đang để trống, chỉ còn phần khai báo và chú thích hướng dẫn. Bảy trong chín bài test cũng để trống. Việc của nhóm là viết cả hai.

Bài chia ba mức. Nhận bài theo sức mình, làm xong mức dưới thì lên mức trên. Không ai phải làm hết.

```bash
pio test -e native     # chạy test, hiện tại đỏ
pio run -e esp32s3     # biên dịch firmware
```

Mẹo quan trọng: **chạy test trước khi viết dòng nào.** Xem bài nào đỏ, làm cho bài đó xanh, chạy lại. Đừng viết hết rồi mới chạy — lúc đó mười lỗi chồng nhau, không biết lỗi nào gây lỗi nào.

---

## Mức 1 — Dễ

Hợp với bạn mới quen cú pháp. Không cần nghĩ nhiều về thuật toán, chủ yếu là gọi đúng hàm theo tài liệu.

### 1A. Đọc cảm biến khoảng cách
**File:** `lib/DistanceSensor/DistanceSensor.cpp` — các mục `TODO [D1]` đến `[D7]`

Bắn một xung kích, đo độ dài xung dội về, đổi ra centimet.

Học được: `pinMode`, `digitalWrite`, `delayMicroseconds`, `pulseIn`, và cách xử lý trường hợp đọc thất bại.

**Xong khi:** mở mô phỏng Wokwi, kéo thanh trượt trên cảm biến, dòng `d=...cm` trên serial đổi theo đúng giá trị bạn kéo.

Cái bẫy hay gặp: quên chia 2. Âm thanh đi và về nên quãng đường gấp đôi khoảng cách thật.

### 1B. Hiển thị lên màn hình
**File:** `lib/RobotDisplay/RobotDisplay.cpp` — `TODO [R1]` đến `[R6]`

Khởi động màn OLED, vẽ trạng thái và khoảng cách.

Học được: dùng thư viện người khác viết, đọc tài liệu API, và khái niệm bộ đệm màn hình.

**Xong khi:** màn hình trong Wokwi hiện chữ và số đổi theo thời gian thực.

Cái bẫy hay gặp: quên gọi `oled.display()`. Mọi lệnh vẽ chỉ ghi vào bộ nhớ đệm, không gọi `display()` thì màn hình trắng trơn dù code đúng hết.

### 1C. Nút bấm và nhịp vòng lặp
**File:** `src/main.cpp` — `TODO [P1]` đến `[P3]`

Ba việc nhỏ trong file chính: in tên lệnh ra serial, chống dội phím cho nút bấm, và giới hạn nhịp vòng lặp.

`[P1]` là bài khởi động, một câu `switch` là xong.

`[P2]` chống dội phím: tiếp điểm cơ khí rung trong vài mili giây khi bấm, đọc thẳng sẽ thấy hàng chục lần bấm nhả chỉ trong một cú ấn tay. Cách chữa là chỉ chấp nhận thay đổi nếu lần trước đã cách đây trên 250ms.

`[P3]` giới hạn nhịp: hiện khối chính chạy hết tốc lực, vài chục nghìn lần mỗi giây. Cảm biến siêu âm bị bắn xung liên tục không kịp nghe tiếng dội nên số đo loạn hết. Cần chạy đúng 20 lần mỗi giây.

Học được: vì sao `delay()` là lựa chọn tồi trong vòng lặp chính — nó chặn toàn bộ chương trình, nút bấm sẽ không ăn trong lúc đang chờ. Cách dùng mốc thời gian thay cho `delay()` là nền tảng của mọi code nhúng nghiêm túc.

**Xong khi:** bấm nút một cái thì robot bật hoặc tắt đúng một lần, và serial in ổn định.

**Phần còn lại của `main.cpp` giữ nguyên, đừng sửa.** Đó là phần nối dây giữa các thư viện. Nhờ nó mà bạn cài đặt xong `DistanceSensor` là thấy ngay số đo chạy trên serial, không phải chờ ai khác làm xong.

---

## Mức 2 — Vừa

Hợp với bạn đã quen class và con trỏ. Cần hiểu phần cứng một chút.

### 2A. Điều khiển động cơ
**File:** `lib/MotorController/MotorController.cpp` — `TODO [M1]` đến `[M7]`

Bốn chân PWM, hai động cơ, năm chuyển động: tiến, lùi, quay trái, quay phải, dừng.

Học được: PWM, cầu H, và cách một lớp phần cứng nhận lệnh trừu tượng rồi dịch ra tín hiệu thật.

**Xong khi:** bốn LED trong Wokwi sáng đúng kiểu. Lệnh tiến thì hai LED xanh sáng. Lệnh quay trái thì LED vàng bên trái và LED xanh bên phải cùng sáng.

Hai điều phải nhớ:

Không bao giờ bật đồng thời cả chân tiến và chân lùi của cùng một bên. Cầu H sẽ bị ngắn mạch. Trong mô phỏng thì chỉ sai kết quả, nhưng trên mạch thật là cháy chip.

Cẩn thận tràn số khi đổi phần trăm sang duty. `maxDuty_ * percent` với số nguyên 16 bit sẽ tràn, phải ép sang `long` trước.

### 2B. Lọc nhiễu cảm biến (nâng cao)
**File:** `lib/DistanceSensor/`

Cảm biến siêu âm thỉnh thoảng trả về số vô lý. Thay vì tin một lần đo, đo ba lần rồi lấy giá trị ở giữa.

Vì sao lấy trung vị chứ không lấy trung bình: một giá trị rác cực lớn sẽ kéo lệch trung bình, nhưng không ảnh hưởng tới trung vị.

---

## Mức 3 — Khó

Hợp với bạn muốn học thiết kế chứ không chỉ viết code. Đây là phần đáng giá nhất của dự án.

### 3A. Viết test cho Navigator
**File:** `test/test_navigator/test_navigator.cpp` — `TODO [T1]` đến `[T8]`

Làm phần này **trước** khi viết `Navigator`.

Trong file có sẵn hai bài test viết đầy đủ làm mẫu: một bài đơn giản để thấy cấu trúc, một bài kiểm thử theo thời gian để thấy cách xử lý phần khó. Bảy bài còn lại chỉ có yêu cầu viết bằng lời, bạn dịch sang code.

Chưa viết test bao giờ thì đọc mục **Cách viết test** ở cuối tài liệu này trước.

**Xong khi:** đủ chín bài test, tất cả đều đỏ — vì `Navigator` chưa viết. Đỏ ở bước này là đúng.

### 3B. Cài đặt Navigator
**File:** `lib/Navigator/Navigator.cpp` — `TODO [N1]` đến `[N7]`

Một máy trạng thái bốn trạng thái: Idle, Cruise, Backup, Turn. Nhận vào khoảng cách và mốc thời gian, trả về một quyết định.

**Xong khi:** cả chín bài test bạn vừa viết đều xanh.

**Luật bắt buộc:** file này không được `#include <Arduino.h>`, không gọi `millis()`, không gọi `digitalWrite()`. Thời gian đã truyền vào qua tham số rồi.

Vì sao luật này quan trọng đến mức được nhắc ba lần trong repo: nhờ nó mà test chạy được trên máy tính trong vài phần nghìn giây thay vì phải nạp vào chip. Và sau này ở giai đoạn 3, hai file `Navigator` sẽ được chép thẳng sang firmware thật mà không sửa một ký tự. Vi phạm luật là mất cả hai.

Ba chỗ dễ sai:

Khi cảm biến trả về `-1`, phải coi như đường thông chứ không phải có vật cản. Nếu xử lý nhầm, robot sẽ đứng im mỗi lần cảm biến trở chứng.

Sau mỗi lần quay phải đổi chiều cho lần sau. Không đổi thì robot gặp góc tường sẽ xoay vòng tròn mãi không thoát.

Bộ đếm `consecutiveBlocks_` chỉ tăng khi hai lần vướng xảy ra gần nhau về thời gian. Vướng cách nhau năm phút thì không phải là kẹt góc.

### 3C. Những bài mở rộng

Làm xong chín bài test rồi thì đây là phần tự do sáng tạo. Mỗi bài vẫn viết test trước, rồi mới viết code — đó chính là nhịp làm việc mà hai bài trên đang tập cho bạn.

Thêm trạng thái Quét: trước khi quay, dừng lại quay đầu sang trái rồi sang phải để đo, chọn hướng thông thoáng hơn thay vì quay bừa.

Phát hiện đi vòng tròn: nhớ lại năm lần vướng gần nhất, nếu thấy lặp lại một chu kỳ thì đổi hẳn chiến thuật.

Giảm tốc tuyến tính: thay vì hai mức cứng nhanh và chậm, tính tốc độ theo công thức dựa trên khoảng cách.

Nhớ đường đã đi: ghi lại các hướng đã thử ở một chỗ, tránh thử lại hướng vừa thất bại.

---

## Cách viết test

Phần này dành cho ai chưa viết test bao giờ. Đọc một lượt rồi quay lại `test_navigator.cpp` sẽ thấy dễ hơn nhiều.

### Ba bước của một bài test

Mọi bài test đều cùng một hình dạng:

```cpp
void test_ten_noi_ro_hanh_vi() {
    Navigator n(cfg());                      // 1. chuẩn bị
    n.start(0);

    NavDecision d = n.update(200, 50);       // 2. gọi thứ cần kiểm

    TEST_ASSERT_TRUE(d.command == DriveCommand::Forward);   // 3. khẳng định
    TEST_ASSERT_EQUAL_UINT8(70, d.speed);
}
```

Chuẩn bị, gọi, khẳng định. Giữ đúng thứ tự này thì người đọc hiểu ngay bài test nói gì.

### Các câu khẳng định hay dùng

| Câu lệnh | Dùng khi |
|---|---|
| `TEST_ASSERT_TRUE(x)` | `x` phải đúng |
| `TEST_ASSERT_FALSE(x)` | `x` phải sai |
| `TEST_ASSERT_EQUAL_UINT8(mong_doi, thuc_te)` | so sánh hai số, giá trị mong đợi viết trước |

So sánh enum thì viết `TEST_ASSERT_TRUE(d.command == DriveCommand::Forward)`.

### Kiểm thử thứ phụ thuộc thời gian

Đây là chỗ hay làm người mới bối rối, nhưng ở đây lại dễ bất ngờ.

`Navigator` không bao giờ gọi `millis()`. Thời gian do bạn truyền vào. Nghĩa là muốn nhảy tới 400ms sau, chỉ cần truyền `400` thay vì ngồi chờ.

```cpp
n.update(10, 100);    // vật cản lúc t=100
n.update(10, 300);    // t=300, vẫn đang lùi
n.update(10, 600);    // t=600, đã hết thời gian lùi
```

Toàn bộ kịch bản chạy xong trong vài phần triệu giây. Đó chính là lý do `Navigator` phải tách khỏi phần cứng.

### Bốn nguyên tắc

**Một bài test kiểm một hành vi.** Nếu tên bài phải có chữ "và" thì nên tách làm hai.

**Tên bài nói hành vi, không nói code.** `test_failed_read_counts_as_clear` tốt hơn `test_update_2`. Khi test đỏ, đọc tên là biết cái gì hỏng.

**Kiểm cả hai phía của ranh giới.** Ngưỡng 400ms thì kiểm ở 300ms và ở 600ms. Chỉ kiểm một phía sẽ bỏ lọt lỗi lệch một đơn vị.

**Viết test trước, viết code sau.** Test viết sau code thường chỉ mô tả lại những gì code đang làm, kể cả chỗ sai.

### Thế nào là một bài test đáng giá

Xem `TODO [T3]`: nó kiểm chuyện cảm biến đọc thất bại trả về `-1`.

Bài này đáng giá vì cách cài đặt hiển nhiên nhất — "khoảng cách nhỏ hơn 20 là có vật cản" — sẽ coi `-1` là vật cản, và robot đứng im mỗi lần cảm biến trở chứng. Đó là lỗi thật, và bài test này bắt được.

Test đáng giá là test bắt được lỗi mà người viết code dễ mắc, không phải test lặp lại điều hiển nhiên.

---

## Khi bí

Đọc kỹ chú thích trong chính file đang làm — mỗi `TODO` đều có gợi ý và nêu sẵn cái bẫy hay gặp.

Đọc file test, nó là đề bài chính xác nhất.

Bí quá hai ngày thì mở issue, mô tả rõ đã thử gì và kết quả ra sao. Hỏi sớm tốt hơn tự xoay cả tuần.

Đừng đi tìm lời giải chép về. Mục đích của dự án là học, và phần khó chịu lúc bí chính là lúc đang học nhiều nhất.
