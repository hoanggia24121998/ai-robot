# Nhật ký quyết định kỹ thuật

Ghi lại những lựa chọn quan trọng và **lý do** đằng sau. Sáu tháng nữa khi có người hỏi "sao hồi đó không làm cách kia", câu trả lời nằm ở đây chứ không nằm trong trí nhớ ai cả.

Mỗi quyết định ghi: bối cảnh, lựa chọn, lý do, và cái giá phải trả. Quyết định đổi thì không xoá mục cũ, thêm mục mới và ghi rõ nó thay thế mục nào.

---

## QĐ-01 — Dùng firmware Xiaozhi mã nguồn mở thay vì tự viết từ đầu

**Ngày:** 07/11/2026

`78/xiaozhi-esp32` là dự án mã nguồn mở giấy phép MIT, hỗ trợ hơn 70 loại board, có wake word offline và cơ chế MCP để điều khiển phần cứng.

Tự viết lại toàn bộ đường âm thanh — I2S, mã hoá Opus, WebSocket, đồng bộ thu phát — là công việc nhiều tháng và không phải thứ dự án này muốn học.

**Giá phải trả:** phải đọc hiểu code của người khác, và bị ràng buộc theo kiến trúc của họ.

---

## QĐ-02 — Dùng server có sẵn, không tự host

**Ngày:** 07/11/2026

Firmware mặc định kết nối tới server chính thức xiaozhi.me, cá nhân đăng ký là dùng miễn phí.

Điều quyết định: các tool điều khiển phần cứng nằm trong firmware, không nằm trên server. Nghĩa là vẫn tự viết được toàn bộ phần robot mà không cần server riêng.

**Giá phải trả:** không chọn được model ASR và TTS, không chạy offline, dữ liệu giọng nói đi qua bên thứ ba.

**Xem lại khi:** chất lượng tiếng Việt không đạt ở giai đoạn 3.

---

## QĐ-03 — `Navigator` không được phụ thuộc phần cứng

**Ngày:** 07/11/2026

Thuật toán điều hướng chỉ nhận khoảng cách và mốc thời gian, trả về một quyết định. Không `#include <Arduino.h>`, không gọi `millis()`.

Ba lý do: test chạy trên PC trong vài phần nghìn giây; đổi cảm biến không phải sửa thuật toán; và quan trọng nhất là khi chuyển sang ESP-IDF ở giai đoạn 3, hai file này copy nguyên văn.

**Giá phải trả:** phải truyền thời gian vào qua tham số, hơi dài dòng hơn gọi thẳng `millis()`.

---

## QĐ-04 — Tránh vật cản là phản xạ cục bộ, không đi qua AI

**Ngày:** 07/11/2026

Vòng AI mất một đến hai giây mỗi lượt. Robot chạy 20cm mỗi giây thì trong hai giây đã đâm vào tường và đẩy thêm 20cm.

Vậy nên cảm biến khoảng cách kích hoạt hai đường song song: phản xạ cục bộ xử lý trong 50ms, và một sự kiện báo lên AI để nó phản ứng bằng lời. Hai đường phục vụ hai mục đích, không trộn.

---

## QĐ-05 — PlatformIO với framework Arduino cho giai đoạn học

**Ngày:** 07/11/2026

Giai đoạn 0 đến 2 dùng PlatformIO. Cài bằng một extension VS Code, tự tải toolchain, cú pháp Arduino gần gũi với sinh viên năm hai.

ESP-IDF nặng hơn nhiều và chỉ cần tới ở giai đoạn 3, lúc đó chỉ một người cài.

**Giá phải trả:** code điều khiển phần cứng phải port lại khi sang ESP-IDF. Khoảng ba chục dòng, chấp nhận được. Phần `Navigator` thì không phải port — xem QĐ-03.

---

## QĐ-06 — Một repo, không dùng git submodule

**Ngày:** 07/11/2026

Submodule là nguồn gây rối kinh điển với người mới: clone thiếu `--recursive` là thư mục rỗng, commit ở repo con quên push là người khác build lỗi.

Phần code chia sẻ giữa mô phỏng và firmware thật chỉ gồm hai file `Navigator`. Copy tay rẻ hơn nhiều so với cái giá của submodule.

**Xem lại khi:** việc copy tay bắt đầu gây lệch phiên bản giữa hai nơi.

---

## QĐ-07 — Nút bấm để nói, không dùng wake word

**Ngày:** 07/11/2026

Wake word tiếng Việt cần model đánh thức riêng, không có sẵn trong firmware gốc.

Với robot tặng trẻ con, bấm giữ để nói lại hay hơn: trẻ con thích bấm, và tránh được việc robot tự nói khi TV đang bật.

**Giá phải trả:** không gọi tên robot từ xa được.

---

## QĐ-08 — Hai bánh dẫn động có điểm tỳ, không tự cân bằng

**Ngày:** 07/11/2026

Tự cân bằng cần cảm biến góc và bộ điều khiển PID, là một dự án riêng về độ khó. Với lần đầu làm robot, nó sẽ nuốt hết thời gian đáng lẽ dành cho phần AI.

---

## QĐ-09 — Chú thích và chuỗi ký tự trong code viết tiếng Anh

**Ngày:** 07/11/2026

Toàn bộ chú thích, tên hàm test và chuỗi in ra serial đều dùng tiếng Anh.

Ba lý do: tránh hẳn lỗi mã hoá trên serial monitor và trên máy cài đặt vùng khác nhau; repo công khai nên người ngoài đọc được; và đây là thói quen nghề nghiệp nên tập sớm.

Tài liệu markdown trong `docs/` vẫn viết tiếng Việt có dấu, vì chỉ đọc trên GitHub và trong trình soạn thảo, không qua serial.

**Giá phải trả:** thành viên chưa quen tiếng Anh kỹ thuật sẽ chậm hơn lúc đầu.
