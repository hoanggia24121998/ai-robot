# Sequence diagram

Ba kịch bản quan trọng nhất, vẽ theo trình tự thời gian.

## 1. Khởi động

```mermaid
sequenceDiagram
    autonumber
    participant MCU as ESP32 runtime
    participant Main as main.cpp
    participant Mot as MotorController
    participant Sen as DistanceSensor
    participant Disp as RobotDisplay

    MCU->>Main: setup()
    Main->>Main: Serial.begin(115200)
    Main->>Main: pinMode(PIN_BUTTON, INPUT_PULLUP)

    Main->>Mot: begin(4 chân, 20kHz, 8 bit)
    Mot->>Mot: cấu hình LEDC trên 4 chân
    Mot->>Mot: stop()
    Note over Mot: dừng ngay từ đầu để<br/>động cơ không tự chạy

    Main->>Sen: begin(TRIG=15, ECHO=16)
    Sen->>Sen: pinMode và kéo TRIG xuống LOW

    Main->>Disp: begin(SDA=8, SCL=9)
    alt Tìm thấy màn hình
        Disp-->>Main: true
    else Không có màn hình
        Disp-->>Main: false
        Main->>Main: in cảnh báo rồi chạy tiếp
    end

    Main->>Main: in "ROBOT READY"
    Note over Main: CI chờ đúng dòng này
```

Điểm đáng chú ý: thiếu màn hình thì chương trình vẫn chạy tiếp, chỉ in một dòng cảnh báo. Thiết bị phụ không được phép làm chết cả hệ thống.

## 2. Một nhịp chạy bình thường

```mermaid
sequenceDiagram
    autonumber
    participant MCU as ESP32 runtime
    participant Main as main.cpp
    participant Sen as DistanceSensor
    participant Nav as Navigator
    participant Mot as MotorController
    participant Disp as RobotDisplay

    MCU->>Main: loop()
    Main->>Main: now = millis()
    Main->>Main: pollButton(now)

    alt Chưa tới 50ms kể từ nhịp trước
        Main-->>MCU: return ngay
    else Đã tới nhịp
        Main->>Main: nextTickMs = now + 50

        Main->>Sen: readCm()
        Sen->>Sen: bắn xung TRIG 10µs
        Sen->>Sen: pulseIn(ECHO) đo thời gian dội
        Sen-->>Main: 85 (cm)

        Main->>Nav: update(85, now)
        Nav->>Nav: đường thông, giữ trạng thái Cruise
        Nav-->>Main: { Forward, 70 }

        Main->>Mot: apply({ Forward, 70 })
        Mot->>Mot: setSide(trái, +70)
        Mot->>Mot: setSide(phải, +70)

        Main->>Disp: show("CRUISE", 85, true)

        opt Mỗi 500ms
            Main->>Main: in dòng log ra serial
        end
    end
```

Nhịp 50ms không phải con số tuỳ tiện. Nhanh hơn thì cảm biến siêu âm chưa kịp nghe tiếng dội của lần đo trước, số đo sẽ loạn. Chậm hơn thì robot phản ứng không kịp ở tốc độ di chuyển thường gặp.

## 3. Gặp vật cản — chuỗi lùi và quay

```mermaid
sequenceDiagram
    autonumber
    participant Main as main.cpp
    participant Sen as DistanceSensor
    participant Nav as Navigator
    participant Mot as MotorController

    Note over Main,Mot: t = 100ms — phát hiện vật cản

    Main->>Sen: readCm()
    Sen-->>Main: 12 (cm, dưới ngưỡng 20)
    Main->>Nav: update(12, 100)
    Nav->>Nav: registerBlock(100)
    Nav->>Nav: enter(Backup, 100, 400ms)
    Nav-->>Main: { Backward, 60 }
    Main->>Mot: apply({ Backward, 60 })

    Note over Main,Mot: t = 150 … 450ms — đang lùi

    loop Mỗi 50ms
        Main->>Nav: update(d, now)
        Nav->>Nav: now < phaseEndMs_, giữ nguyên
        Nav-->>Main: { Backward, 60 }
    end

    Note over Main,Mot: t = 500ms — hết thời gian lùi

    Main->>Nav: update(d, 500)
    Nav->>Nav: enter(Turn, 500, turnDuration())
    Nav-->>Main: { TurnLeft, 60 }
    Main->>Mot: apply({ TurnLeft, 60 })

    Note over Main,Mot: t = 550 … 800ms — đang quay

    Note over Main,Mot: t = 850ms — hết thời gian quay

    Main->>Nav: update(d, 850)
    Nav->>Nav: turnLeft_ = false (lần sau quay phải)
    Nav->>Nav: enter(Cruise, 850, 0)
    Nav-->>Main: { Forward, 70 }
    Main->>Mot: apply({ Forward, 70 })
```

Hai chi tiết quyết định chất lượng thuật toán nằm ở sơ đồ này.

Thứ nhất, `turnLeft_` đảo chiều sau mỗi lần quay. Không đảo thì robot gặp góc tường sẽ quay trái mãi và xoay vòng tròn không thoát ra được.

Thứ hai, `registerBlock` đếm số lần vướng liên tiếp. Nếu vướng ba lần trong vòng ba giây thì `turnDuration()` trả về thời gian dài gấp ba, để robot quay hẳn ra thay vì loay hoay tại chỗ.

## 4. Giai đoạn 3 — hai đường xử lý song song

Sơ đồ này mô tả kiến trúc sẽ có sau khi ghép AI, chưa áp dụng cho repo hiện tại.

```mermaid
sequenceDiagram
    autonumber
    participant Sen as DistanceSensor
    participant Guard as Phản xạ cục bộ
    participant Mot as MotorController
    participant MCP as MCP server
    participant AI as Xiaozhi cloud

    Sen->>Guard: 12cm, quá gần
    Guard->>Mot: dừng và lùi
    Note over Guard,Mot: 50ms — robot đã an toàn

    par Song song, chậm hơn nhiều
        Guard->>MCP: sự kiện: gặp vật cản
        MCP->>AI: gửi sự kiện lên
        AI-->>MCP: "Ôi, có gì chặn mình rồi!"
        MCP->>Mot: (tuỳ nội dung trả về)
        Note over MCP,AI: 1–2 giây
    end
```

Đây là lý do tránh vật cản không được đi qua AI. Vòng AI mất một đến hai giây; robot chạy 20cm mỗi giây thì trong hai giây đã đâm vào tường và đẩy thêm 20cm nữa.

Phản xạ giữ cho robot không va chạm. AI làm cho nó dễ thương. Hai việc khác nhau, chạy ở hai tốc độ khác nhau, và không được trộn vào nhau.
