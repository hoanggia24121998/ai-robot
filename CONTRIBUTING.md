# Đóng góp vào AI Robot

GitHub tự hiện file này khi ai đó mở issue hoặc pull request, nên đây chỉ là bản tóm tắt. Nội dung đầy đủ nằm trong `docs/`.

## Trước khi bắt đầu

Đọc `docs/bai-tap.md` để nhận bài theo mức độ, và `docs/phan-cong.md` để biết mình phụ trách thư mục nào.

## Quy trình một thay đổi

```bash
git switch main && git pull
git switch -c ten-ban/viec-dang-lam

# ... sửa code ...

pio test -e native        # bắt buộc chạy trước khi đẩy
git add -A
git commit -m "navigator: thêm trạng thái quét trước khi quay"
git push -u origin ten-ban/viec-dang-lam
```

Rồi mở pull request. Chờ CI xanh, chờ một người review, rồi merge. Không đẩy thẳng lên `main`.

## Ba luật không được phá

**`lib/Navigator` không được `#include <Arduino.h>`.** Không gọi `millis()`, không gọi `digitalWrite()`. Lý do ở `docs/kien-truc.md`.

**Không sửa file ngoài mảng của mình mà không báo trước.** Mở issue hoặc nhắn nhóm.

**`NavDecision` và `NavConfig` là hợp đồng chung.** Đổi chúng phải bàn với cả nhóm.

## Chuẩn code

Chú thích viết tiếng Anh, thụt lề 4 dấu cách. File `.editorconfig` và `.clang-format` đã cấu hình sẵn, editor sẽ tự theo.

Chi tiết: `docs/gop-code.md`.

## Tài liệu

| File | Nội dung |
|---|---|
| `docs/bai-tap.md` | Đề bài ba mức, hướng dẫn viết test |
| `docs/phan-cong.md` | Vai trò và bốn mảng công việc |
| `docs/gop-code.md` | Quy trình git đầy đủ, chuẩn code |
| `docs/kien-truc.md` | Vì sao chia tầng như vậy |
| `docs/class-diagram.md` | Tra cứu tên lớp và tên hàm |
| `docs/sequence-diagram.md` | Luồng chạy theo thời gian |
