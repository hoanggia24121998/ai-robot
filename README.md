# AI Robot

[![CI](https://github.com/hoanggia24121998/ai-robot/actions/workflows/ci.yml/badge.svg)](https://github.com/hoanggia24121998/ai-robot/actions/workflows/ci.yml)

Robot AI hai bánh tự làm, đặt tên **AI Robot**. Giai đoạn này chạy hoàn toàn trên mô phỏng — **không ai cần mua linh kiện** để tham gia.

Về sau, phần logic trong repo này sẽ được mang nguyên sang firmware Xiaozhi chạy trên ESP32-S3 thật, để robot vừa biết nói chuyện vừa biết tránh vật cản.

---

## Chạy thử trong 5 phút

Cần cài: [VS Code](https://code.visualstudio.com/), extension **PlatformIO IDE**, extension **Wokwi for VS Code**.

```bash
git clone <địa-chỉ-repo>
cd ai-robot

pio test -e native     # chạy test logic ngay trên máy, vài giây
pio run -e esp32s3     # biên dịch firmware (lần đầu hơi lâu, PlatformIO tải toolchain)
```

**Lần đầu chạy test sẽ thấy đỏ. Đó là đúng.** Phần cài đặt trong `lib/` đang để trống, và bảy trong chín bài test cũng vậy. Việc của nhóm là viết cả hai cho tới khi tất cả xanh. Đề bài ở `docs/bai-tap.md`.

Rồi trong VS Code bấm `F1` → **Wokwi: Start Simulator**. Mạch hiện ra, bấm nút xanh START, kéo thanh trượt khoảng cách trên con HC-SR04 để giả lập vật cản.

Bốn con LED bên phải chính là hai động cơ: LED xanh sáng nghĩa là bánh đó quay tới, LED vàng là quay lui, độ sáng là mức ga.

---

## Cấu trúc thư mục

```
ai-robot/
├── platformio.ini              cấu hình 2 môi trường build
├── diagram.json                sơ đồ mạch ảo (Wokwi)
├── wokwi.toml                  trỏ Wokwi tới file firmware đã build
├── include/pinmap.h            bảng phân chân — sửa ở đây, đừng rải rác
├── src/main.cpp                vòng lặp chính, ghép các mảnh lại
├── lib/
│   ├── Navigator/              THUẬT TOÁN — không đụng phần cứng
│   ├── MotorController/        điều khiển động cơ bằng PWM
│   ├── DistanceSensor/         đọc HC-SR04
│   └── RobotDisplay/           màn OLED
├── test/test_navigator/        test logic, chạy trên PC
├── docs/                       tài liệu nhóm
└── .github/workflows/ci.yml    tự động test mỗi khi đẩy code
```

## Quy tắc quan trọng nhất của repo này

**`lib/Navigator` tuyệt đối không được `#include <Arduino.h>`.**

Nó chỉ nhận vào một con số khoảng cách cùng mốc thời gian, rồi trả về một quyết định. Nhờ vậy:

- test được ngay trên máy tính, chạy xong trong vài phần nghìn giây
- không cần mô phỏng, không cần board, không cần chờ
- sau này bê thẳng sang firmware ESP-IDF, không sửa một dòng

Nếu bạn thấy mình muốn gọi `digitalWrite` hay `millis()` bên trong `Navigator`, nghĩa là đang đặt code nhầm chỗ. Truyền giá trị vào qua tham số thay vì đi lấy nó.

## Nhóm và chia việc

Nhóm 4 người, mỗi người sở hữu một mảng. Leader duyệt mọi pull request và phân công qua issue.

| Mảng | Thư mục | Làm gì |
|---|---|---|
| Thuật toán | `lib/Navigator`, `test/` | Cải tiến cách tránh vật cản, thoát kẹt góc, viết thêm test |
| Chuyển động | `lib/MotorController` | Tăng giảm ga mượt, bù lệch giữa hai bánh, quay theo góc |
| Cảm biến | `lib/DistanceSensor` | Lọc nhiễu, lấy trung vị nhiều lần đo, đọc không chặn |
| Giao diện | `lib/RobotDisplay`, `diagram.json` | Vẽ mặt biểu cảm, thêm linh kiện vào sơ đồ |

Mỗi mảng là một thư mục riêng nên hai người làm cùng lúc hiếm khi đụng file nhau. Chi tiết vai trò và nguyên tắc phối hợp xem `docs/phan-cong.md`, đề bài cụ thể xem `docs/bai-tap.md`.

Bài chia ba mức: cảm biến và màn hình là mức dễ, động cơ là mức vừa, thuật toán điều hướng là mức khó. Nhận bài theo sức mình.

## Quy ước làm việc chung

Xem `docs/gop-code.md`. Tóm tắt: nhánh đặt tên `ten-ban/viec-dang-lam`, mỗi pull request một việc, CI phải xanh trước khi merge, ai review thì để lại ít nhất một nhận xét thật.

## Tài liệu

| File | Nội dung |
|---|---|
| `docs/lo-trinh.md` | Năm giai đoạn phát triển, việc cụ thể và tiêu chí hoàn thành từng giai đoạn |
| `docs/kien-truc.md` | Vì sao chia tầng như vậy, và đường đi sang firmware thật |
| `docs/usecase-diagram.md` | Sơ đồ ca sử dụng — ai dùng robot để làm gì |
| `docs/class-diagram.md` | Sơ đồ lớp — tra cứu tên lớp, tên hàm khi làm bài |
| `docs/sequence-diagram.md` | Sơ đồ trình tự — khởi động, một nhịp chạy, chuỗi tránh vật cản |
| `docs/quyet-dinh.md` | Nhật ký quyết định kỹ thuật — chọn gì, vì sao, giá phải trả |
| `docs/phan-cong.md` | Vai trò bốn người, bốn mảng công việc, nguyên tắc phối hợp |
| `docs/linh-kien.md` | Danh sách linh kiện dự kiến và chi phí ước tính |
| `docs/phan-chan.md` | Bảng chân và những chân tuyệt đối không được dùng |
| `docs/bai-tap.md` | **Đề bài cho nhóm** — ba mức khó, từng TODO một |
| `docs/gop-code.md` | Quy trình git, chuẩn code, cấu hình GitHub cho nhóm |
| `CONTRIBUTING.md` | Bản tóm tắt quy trình, GitHub tự hiện khi mở pull request |

Đang ở **giai đoạn 0**. Xem `docs/lo-trinh.md` để biết còn gì phải làm.

## Vài chỗ có thể cần chỉnh khi chạy lần đầu

Sơ đồ `diagram.json` viết tay nên tên chân có thể lệch với phiên bản part của Wokwi. Nếu mô phỏng báo chân không tồn tại, chạy `wokwi-cli lint` để nó chỉ ra chỗ sai, hoặc mở sơ đồ trong trình chỉnh sửa Wokwi rồi kéo lại dây — nhanh hơn sửa tay.

Bước Wokwi trong CI cần secret `WOKWI_CLI_TOKEN`, lấy miễn phí tại trang CI dashboard của Wokwi. Chưa có token thì hai bước đầu (test và build) vẫn chạy bình thường.
