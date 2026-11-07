# Class diagram

Cấu trúc lớp hiện tại của repo. Tên lớp và tên hàm khớp đúng với code, nên dùng sơ đồ này để tra cứu khi làm bài tập.

```mermaid
classDiagram
    direction TB

    class DriveCommand {
        <<enumeration>>
        Stop
        Forward
        Backward
        TurnLeft
        TurnRight
    }

    class NavDecision {
        +DriveCommand command
        +uint8_t speed
    }

    class NavConfig {
        +int stopDistanceCm
        +int slowDistanceCm
        +uint8_t cruiseSpeed
        +uint8_t slowSpeed
        +uint8_t manoeuvreSpeed
        +uint32_t backupMs
        +uint32_t turnMs
        +int stuckThreshold
        +uint32_t stuckWindowMs
    }

    class Navigator {
        <<no hardware>>
        -NavConfig cfg_
        -State state_
        -uint32_t phaseEndMs_
        -bool turnLeft_
        -int consecutiveBlocks_
        +start(uint32_t nowMs)
        +halt()
        +running() bool
        +state() State
        +stateName() const char*
        +update(int distanceCm, uint32_t nowMs) NavDecision
        -enter(State s, uint32_t nowMs, uint32_t durationMs)
        -registerBlock(uint32_t nowMs)
        -turnDuration() uint32_t
    }

    class MotorController {
        -int pinLF_
        -int pinLB_
        -int pinRF_
        -int pinRB_
        -int maxDuty_
        +begin(int lf, int lb, int rf, int rb, int freq, int res)
        +apply(NavDecision d)
        +forward(uint8_t speed)
        +backward(uint8_t speed)
        +turnLeft(uint8_t speed)
        +turnRight(uint8_t speed)
        +stop()
        -setSide(int pinFwd, int pinBwd, int signedSpeed)
        -writeDuty(int pin, uint8_t percent)
    }

    class DistanceSensor {
        -int trig_
        -int echo_
        -unsigned long timeoutUs_
        +begin(int trigPin, int echoPin, unsigned long timeoutUs)
        +readCm() int
    }

    class RobotDisplay {
        -bool ready_
        +begin(int sda, int scl, uint8_t addr) bool
        +show(const char* stateName, int distanceCm, bool running)
        +ready() bool
    }

    Navigator ..> NavDecision : tạo ra
    Navigator *-- NavConfig : chứa
    NavDecision ..> DriveCommand : dùng
    MotorController ..> NavDecision : nhận vào
```

## Hai nhóm lớp, khác nhau ở một điểm duy nhất

```mermaid
graph TB
    subgraph PURE["Thuần logic — không đụng phần cứng"]
        N["Navigator<br/>NavDecision · NavConfig"]
    end

    subgraph HW["Phụ thuộc Arduino.h"]
        M["MotorController"]
        D["DistanceSensor"]
        R["RobotDisplay"]
    end

    PURE -->|"test chạy trên PC<br/>vài phần nghìn giây"| T["pio test -e native"]
    HW -->|"chỉ chạy được<br/>trên chip hoặc Wokwi"| W["pio run -e esp32s3"]

    classDef pure fill:#E1F5EE,stroke:#0F6E56,color:#04342C
    classDef hw fill:#F1EFE8,stroke:#5F5E5A,color:#2C2C2A
    class N pure
    class M,D,R hw
```

Ranh giới này là quyết định kiến trúc quan trọng nhất của dự án, ghi ở `docs/quyet-dinh.md` mục QĐ-03.

`Navigator` không biết động cơ tồn tại. Nó nhận một con số và một mốc thời gian, trả về một quyết định. Nhờ vậy test chạy được trên máy tính, và sang giai đoạn 3 hai file này chép thẳng sang firmware ESP-IDF mà không sửa một ký tự.

## Quan hệ giữa các lớp

`Navigator` và `MotorController` không biết nhau. Chúng chỉ cùng biết kiểu `NavDecision`.

Đó là lý do hai người làm hai mảng này song song được: hợp đồng giữa họ là một struct nhỏ, đã khai báo sẵn trong header và không ai được tự ý đổi. Muốn đổi thì phải bàn với cả nhóm — xem `docs/phan-cong.md`.

`main.cpp` là nơi duy nhất biết cả bốn lớp. Nó giữ các đối tượng và nối chúng lại với nhau. Không lớp nào trong `lib/` được phép gọi sang lớp khác trong `lib/`.
