# AFRC Firmware

Real-time signal conditioning firmware for the ESP32-based AFRC board.

## Features

- 20 kHz analog sampling
- First-order high-pass filtering
- ADC calibration scaling
- DAC signal reconstruction
- Drift removal
- Runtime stability protection

## Hardware

| Function | GPIO |
|---|---|
| Analog Input | 34 |
| DAC Output | 25 |

## Filter

The firmware implements a recursive high-pass filter:

```math
y[n] = (u[n] - u[n-1]) + \alpha y[n-1]
```

Where:

```math
\alpha = e^{-2\pi f_c/f_s}
```

- Sampling frequency: `20 kHz`
- Cutoff frequency: `30 Hz`

## Signal Path

```text
ADC Input → Calibration → High-Pass Filter → DAC Output
```

## Notes

- ADC resolution: 12-bit
- DAC resolution: 8-bit
- Output centered at 1.65 V
- Invalid filter states are automatically reset

## Core DSP Line

```cpp
float y = (u - u_prev) + alpha * y_prev;
```
