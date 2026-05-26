# MSPM0 L1306 Examples

TI MSPM0L1306 基础例程合集，涵盖 GPIO、UART、OLED、矩阵键盘、Flash、定时器等外设。

## 硬件需求

- 主控芯片：MSPM0L1306
- 显示：0.96 寸 OLED（SPI 接口）
- 按键：独立按键 / 矩阵键盘

## 软件环境

- IDE：Keil MDK-ARM / VS Code + Keil Assistant
- SDK：TI MSPM0 SDK

## 例程列表

| 例程 | 说明 |
|------|------|
| ADDA | ADC/DAC 采样实验 |
| BUTTON | 按键检测 |
| Breath / Breathing | LED 呼吸灯 |
| ButtonDebounce | 按键消抖 |
| CLK | 时钟配置 |
| CreativeProject | 创意项目 |
| FlashSave / FlashSaver | Flash 读写 |
| GPIO_EXP | GPIO 扩展实验 |
| INT_GPIO | GPIO 中断 |
| MCU_DigitalClock | 数字钟 |
| MatrixKeyboard | 矩阵键盘 |
| OLED | OLED 显示驱动 |
| RunningLed | 跑马灯 |
| TIM / TIMEREXAMPLE | 定时器实验 |
| UART / UART1 | 串口通信 |
| WaterFloat / Wavekey | 其他实验 |

## 目录结构

```
MSPM0-L1306-Examples/
├── L1306/
│   ├── ADDA/            # ADC/DAC 例程
│   ├── BUTTON/          # 按键例程
│   ├── OLED/            # OLED 例程
│   ├── UART/            # 串口例程
│   ├── MatrixKeyboard/  # 矩阵键盘例程
│   ├── Driver/          # TI SDK 驱动库
│   └── ...
├── LICENSE
└── .gitignore
```

## 许可证

[CC BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/deed.zh-hans)
