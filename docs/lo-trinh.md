# Lộ trình phát triển

Cập nhật lần cuối: 07/11/2026

Dự án chia làm năm giai đoạn. Mỗi giai đoạn có tiêu chí hoàn thành rõ ràng — đạt tiêu chí mới sang giai đoạn sau, không làm song song, vì mỗi giai đoạn loại bỏ một nhóm biến số trước khi thêm nhóm mới.

Nguyên tắc xuyên suốt: **chỉ thêm một thứ khó tại một thời điểm.** Nếu vừa thay firmware vừa thay phần cứng cùng lúc, lúc hỏng sẽ không biết lỗi ở đâu.

---

## Giai đoạn 0 — Nền tảng (đang làm)

Dựng chỗ làm việc chung và chạy được mô phỏng. Không ai cần mua gì.

- [x] Dựng repo, cấu trúc thư mục, tách `Navigator` khỏi phần cứng
- [x] Viết đề bài ba mức trong `docs/bai-tap.md`
- [x] Dựng khung bốn thư viện và `main.cpp`, phần cài đặt để trống cho nhóm làm
- [x] Chín bài test logic điều hướng
- [x] Sơ đồ mạch ảo `diagram.json`, cấu hình CI
- [ ] Mỗi thành viên clone về, `pio test -e native` chạy xanh trên máy mình
- [ ] Mô phỏng Wokwi chạy được trong VS Code, kéo thanh khoảng cách thấy robot phản ứng
- [ ] Thêm secret `WOKWI_CLI_TOKEN`, CI xanh cả ba bước
- [ ] Mỗi thành viên mở thử một pull request nhỏ cho quen quy trình
- [ ] Hoàn thành bài mức 1: `DistanceSensor`, `RobotDisplay`, nút bấm và nhịp vòng lặp
- [ ] Hoàn thành bài mức 2: `MotorController`
- [ ] Hoàn thành bài mức 3: tự viết 7 bài test còn thiếu, rồi cài đặt `Navigator` cho cả 9 bài xanh

**Hoàn thành khi:** cả nhóm push được code, CI tự chạy, ai cũng xem được robot ảo chạy trên máy mình.

---

## Giai đoạn 1 — Hoàn thiện hành vi trên mô phỏng

Vẫn chưa mua linh kiện. Toàn bộ công sức đổ vào thuật toán, vì sửa trong mô phỏng rẻ hơn sửa trên mạch hàn rồi.

- [ ] Lọc nhiễu cảm biến: lấy trung vị ba lần đo thay vì tin một lần
- [ ] Thoát kẹt góc: phát hiện robot lặp lại cùng một hành vi và đổi chiến thuật
- [ ] Giảm tốc mượt theo khoảng cách thay vì hai mức cứng
- [ ] Mặt biểu cảm trên OLED thay cho chữ: vui, giật mình, đang nghĩ
- [ ] Nút bấm: bấm giữ để nói, bấm nhanh để bật tắt tự chạy
- [ ] Mỗi hành vi mới đều có test đi kèm

**Hoàn thành khi:** robot ảo chạy năm phút liên tục trong một mê cung có vật cản mà không kẹt cứng ở đâu.

---

## Giai đoạn 2 — Phần cứng thật, chưa có AI

Lắp mạch và nạp đúng firmware PlatformIO này lên board. Vẫn chưa đụng tới Xiaozhi.

- [ ] Chốt bảng phân chân cuối cùng, mua linh kiện theo `docs/linh-kien.md`
- [ ] Hàn thử trên breadboard trước khi hàn cố định
- [ ] Nạp firmware, kiểm từng khối: động cơ, cảm biến, nút, màn hình
- [ ] Hiệu chỉnh số đo khoảng cách — số trong mô phỏng là lý tưởng, thực tế lệch
- [ ] Xử lý sụt áp khi động cơ khởi động (tách nguồn, thêm tụ)
- [ ] Cân chỉnh lệch tốc giữa hai bánh để robot đi thẳng

**Hoàn thành khi:** robot vật lý chạy trên sàn nhà và tự tránh vật cản thật, chưa cần nói năng gì.

---

## Giai đoạn 3 — Ghép phần AI

Chuyển sang firmware Xiaozhi. Đây là lúc cần ESP-IDF, và chỉ một người cần cài.

- [ ] Cài ESP-IDF v6.1, build thành công một board mẫu để thông chuỗi công cụ
- [ ] Fork `78/xiaozhi-esp32`, tạo thư mục board riêng theo `docs/custom-board.md`
- [ ] Chép nguyên `Navigator.h` và `Navigator.cpp` sang, không sửa
- [ ] Port `MotorController` và `DistanceSensor` sang API ESP-IDF
- [ ] Đưa việc đo khoảng cách vào task riêng để không chặn luồng âm thanh
- [ ] Khai báo các hành động thành MCP tool cho mô hình gọi
- [ ] Đăng ký tài khoản xiaozhi.me, chỉnh tính cách và giọng nói trong console
- [ ] Nghe thử chất lượng tiếng Việt, quyết định có cần tự host server không

**Hoàn thành khi:** nói "đi tới đi" thì robot đi, và gặp tường nó tự lùi mà không chờ lệnh.

---

## Giai đoạn 4 — Hoàn thiện để tặng

- [ ] Thiết kế và in vỏ 3D, bọc kín pin và mạch
- [ ] Mạch sạc, công tắc nguồn, kiểm tra an toàn
- [ ] Viết prompt tính cách phù hợp với trẻ con, chặn chủ đề không mong muốn
- [ ] Chạy thử dài ngày, xem pin được bao lâu
- [ ] Tuỳ chọn: MCP server riêng bằng Java để thêm kho truyện, nhắc giờ

**Hoàn thành khi:** đưa cho trẻ con chơi được mà không cần ai đứng cạnh canh.

---

## Những gì cố ý chưa đưa vào kế hoạch

Robot tự cân bằng. Hai bánh có điểm tỳ đã đủ khó cho lần đầu, thêm PID vào là mất cả tháng.

Nhận dạng hình ảnh qua camera. Hay, nhưng để dành dự án sau.

Tự host server AI. Chỉ làm nếu giai đoạn 3 cho thấy chất lượng tiếng Việt của server có sẵn không đạt.
