# MSPM0 Examples

TI MSPM0 系列 MCU 例程与开发板资料合集，包含 L1306、G3507 各开发板例程及 AD9833 驱动、贪吃蛇游戏等。

## 项目列表

| 项目 | 说明 |
|------|------|
| L1306 | MSPM0L1306 基础例程合集（GPIO、UART、OLED、矩阵键盘等） |
| G3507-V2.0 | MSPM0G3507 V2.0 例程（LED、按键、OLED、IMU） |
| G3507-QiShiKeJi | 启石科技 MSPM0G3507 开发板资料 |
| G3507-TianMengXing | 天猛星 MSPM0G3507 开发板资料 |
| AD9833_drive | AD9833 DDS 信号发生器驱动 |
| greedysnake | OLED 显示的贪吃蛇游戏 |
| M0-FPGA | MSPM0G3507 + EP4CE6 FPGA 协同开发资料 |

## 硬件需求

- 主控芯片：MSPM0L1306 / MSPM0G3507
- 显示：0.96 寸 OLED（SPI/I2C）
- 外设：AD9833、矩阵键盘、IMU 等

## 软件环境

- IDE：Keil MDK-ARM / VS Code + Keil Assistant
- SDK：TI MSPM0 SDK

## 目录结构

```
MSPM0-Examples/
├── L1306/              # MSPM0L1306 例程
├── G3507-V2.0/         # MSPM0G3507 V2.0 例程
├── G3507-QiShiKeJi/    # 启石科技开发板
├── G3507-TianMengXing/ # 天猛星开发板
├── AD9833_drive/       # AD9833 DDS 驱动
├── greedysnake/        # 贪吃蛇游戏
├── M0-FPGA/            # M0+FPGA 协同
├── LICENSE
└── README.md
```

## 许可证

[CC BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/deed.zh-hans)

 
