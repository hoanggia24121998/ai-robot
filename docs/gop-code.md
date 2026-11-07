# Cách cùng làm trên repo này

## Quy trình một thay đổi

```bash
git switch main
git pull
git switch -c ten-ban/viec-dang-lam

# ... sửa code ...

pio test -e native        # bắt buộc chạy trước khi đẩy
git add -A
git commit -m "navigator: thêm trạng thái quét trước khi quay"
git push -u origin ten-ban/viec-dang-lam
```

Rồi mở pull request trên GitHub. Chờ CI xanh. Chờ một người review. Rồi merge.

Không đẩy thẳng lên `main`. Kể cả sửa một dòng.

## Đặt tên nhánh

`ten-ban/viec-dang-lam`, ví dụ `minh/loc-nhieu-cam-bien`, `lan/mat-bieu-cam`. Nhìn danh sách nhánh là biết ai đang làm gì, tránh hai người cùng sửa một chỗ.

## Viết commit

Dạng `phần: việc đã làm`, viết thường, động từ trước.

Tốt: `navigator: quay lâu hơn khi kẹt góc ba lần liên tiếp`
Chưa tốt: `update`, `fix bug`, `sửa lại`

Lý do không phải hình thức: ba tháng nữa tìm lại xem ai đổi cái gì, bạn sẽ cảm ơn chính mình.

## Pull request

Mỗi PR một việc. Hai việc không liên quan thì tách hai PR, dù tiện tay làm cùng lúc.

Phần mô tả nói rõ ba điều: thay đổi cái gì, vì sao, và đã thử thế nào. Nếu là thay đổi về hành vi robot, quay màn hình mô phỏng rồi đính kèm.

## Review

Ai review để lại ít nhất một nhận xét thật. "LGTM" không phải review.

Những điều đáng soi: Navigator có lỡ `#include <Arduino.h>` không, thay đổi hành vi đã có test chưa, có số lạ nào nằm thẳng trong code mà đáng lẽ phải vào `NavConfig` không.

Nhận xét thì nói về code, không nói về người. Viết "chỗ này chia cho 0 khi khoảng cách bằng 0" thay vì "bạn viết ẩu".

## Chuẩn code

Thụt lề 4 dấu cách, không dùng tab.

Tên class viết hoa chữ đầu mỗi từ, tên hàm chữ thường trước rồi hoa, hằng số có tiền tố `k` hoặc viết hoa toàn bộ, biến thành viên của class kết thúc bằng dấu gạch dưới.

Chú thích trong code viết tiếng Anh. Lý do: tránh hẳn lỗi mã hoá khi hiển thị trên serial monitor và trên máy cài đặt vùng khác nhau, đồng thời là thói quen tốt cho repo công khai. Tài liệu markdown trong `docs/` thì viết tiếng Việt có dấu bình thường.

Số liệu điều chỉnh được thì đưa vào `NavConfig`, đừng viết thẳng vào thân hàm. Người sau muốn thử giá trị khác sẽ không phải đi lục.

## Khi bí

Mở issue mô tả rõ: định làm gì, đã thử gì, kết quả ra sao. Dán cả log serial nếu có.

Hỏi sớm tốt hơn tự xoay ba ngày.

---

## Cấu hình GitHub cho nhóm (leader làm một lần)

### Khoá nhánh main

`Settings → Branches → Add branch ruleset`, áp cho `main`:

- Bật **Require a pull request before merging**, số approval tối thiểu là **1**
- Bật **Require review from Code Owners** — file `.github/CODEOWNERS` đã trỏ mọi đường dẫn về leader, nên mọi PR sẽ tự động mời leader review
- Bật **Require status checks to pass**, chọn job `kiem-tra` của CI
- Bật **Dismiss stale pull request approvals when new commits are pushed** — tránh chuyện đã duyệt rồi lại đẩy thêm code khác vào

Leader cũng không đẩy thẳng lên `main`. Để ngoại lệ cho mình là cách nhanh nhất làm cả quy trình mất giá trị.

### Mời thành viên

`Settings → Collaborators → Add people`, quyền **Write**. Quyền Write cho phép đẩy nhánh và mở PR, nhưng không cho phép merge vào `main` khi đã khoá nhánh — đúng cái ta muốn.

### Thêm secret cho CI

`Settings → Secrets and variables → Actions → New repository secret`, tên `WOKWI_CLI_TOKEN`, lấy token miễn phí ở trang CI dashboard của Wokwi.

### Dùng issue để giao việc

Leader tạo issue cho từng việc, gán người, gắn nhãn theo mảng (`thuat-toan`, `chuyen-dong`, `cam-bien`, `giao-dien`). Thành viên nhận việc từ danh sách issue.

Trong phần mô tả PR, viết `Closes #12` để issue tự đóng khi merge.

Nếu muốn nhìn tổng thể, bật `Projects` dạng bảng với ba cột: cần làm, đang làm, xong.
