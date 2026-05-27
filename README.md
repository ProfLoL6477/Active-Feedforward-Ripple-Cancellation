# Active Feedforward Ripple Cancellation (AFRC)

AFRC is an isolated mixed-signal ripple cancellation system using real-time DSP on ESP32.

The system senses ripple on a power rail, extracts the unwanted AC component, generates an inverted compensation signal, and reinjects it back into the rail to reduce ripple through destructive interference.

## Architecture

```text
Power Rail
    ↓
Voltage Divider + Filter
    ↓
AMC1200 Isolation
    ↓
ESP32 ADC
    ↓
DSP Ripple Extraction
    ↓
ESP32 DAC
    ↓
AMC1200 Isolation
    ↓
Compensation Injection
    ↓
Ripple-Reduced Output
```

## Features

- Real-time ripple cancellation
- Feedforward compensation architecture
- Isolated sensing and injection
- ESP32 ADC + DAC processing
- Recursive DSP filtering
- Simulation + hardware implementation

## DSP Core

```math
y[n] = (u[n] - u[n-1]) + \alpha y[n-1]
```

The filtered ripple component is inverted and reinjected into the power rail for active cancellation.

## Status

- Firmware working
- Simulations validated
- Hardware testing in progress
