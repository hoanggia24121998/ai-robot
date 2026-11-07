## Thay đổi gì

<!-- Một đến hai câu. Viết cho người chưa biết bạn đang làm việc gì. -->

## Vì sao

<!-- Lý do, hoặc link tới issue. -->

## Đã thử thế nào

<!-- Chạy test nào, thử trên mô phỏng ra sao. Nếu đổi hành vi robot thì quay màn hình đính kèm. -->

## Mảng

- [ ] Thuật toán điều hướng (`lib/Navigator`)
- [ ] Chuyển động (`lib/MotorController`)
- [ ] Cảm biến (`lib/DistanceSensor`)
- [ ] Giao diện và mạch ảo (`lib/RobotDisplay`, `diagram.json`)
- [ ] Tài liệu
- [ ] Khác

## Tự kiểm trước khi gửi

- [ ] `pio test -e native` chạy xanh trên máy tôi
- [ ] `Navigator` không `#include <Arduino.h>` (nếu có sửa thư mục này)
- [ ] Thay đổi hành vi đã có test đi kèm
- [ ] Số liệu điều chỉnh được đã đưa vào `NavConfig`, không viết thẳng trong thân hàm
- [ ] Không sửa file thuộc mảng người khác, hoặc đã báo trước
