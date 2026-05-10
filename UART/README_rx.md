# UART RX Module

## Overview
This module implements a UART Receiver in SystemC. It deserializes a standard UART frame (1 start bit, 8 data bits, 1 stop bit) into an 8-bit data word, sampling each bit in the middle of its bit period.

## Files
| File | Description |
|------|-------------|
| `UART_rx.h` | UART RX FSM module |
| `testbench_rx.h` | Testbench for UART RX |
| `main_rx.cpp` | Top-level simulation file |

## UART Frame Format
```
IDLE | START | D0 | D1 | D2 | D3 | D4 | D5 | D6 | D7 | STOP | IDLE
  1  |   0   |                   8 data bits               |  1  |  1
```

## Module Interface
| Signal | Direction | Type | Description |
|--------|-----------|------|-------------|
| `clk` | Input | `bool` | Clock (rising edge triggered) |
| `rst` | Input | `bool` | Active-high synchronous reset |
| `rx` | Input | `bool` | Serial data input line |
| `rx_done` | Output | `bool` | Pulses high for 1 cycle when a byte is received |
| `rx_data` | Output | `sc_uint<8>` | Received byte |

## FSM States
| State | Description |
|-------|-------------|
| `IDLE` | Waits for start bit (line going low) |
| `START` | Waits 4 clocks to align to middle of start bit |
| `DATA` | Samples each data bit every 8 clocks (LSB first) |
| `STOP` | Waits 8 clocks, latches `rx_data`, asserts `rx_done` |

## Timing
- Each bit is sampled every **8 clock cycles**
- The start bit is sampled after **4 clocks** (mid-bit alignment)
- Full frame: approximately **80+ clock cycles**

## Testbench
The testbench drives two UART frames onto the `rx` line:
- `0x53` (83 decimal)
- `0xA5` (165 decimal)

Each bit is held for **8 clock cycles** to match the receiver's sampling rate.

## Building & Running
```bash
g++ main_rx.cpp -IC:/systemc/systemc-2.3.3/src -LC:/systemc/systemc-2.3.3/build/src/.libs -lsystemc -o sim.exe
./sim.exe
```

## Example Output
```
Simulation started
[81 ns] rx_data=0x053 (83), rx_done=1
[177 ns] rx_data=0x0a5 (165), rx_done=1
Simulation finished
```
