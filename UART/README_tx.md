# UART TX Module

## Overview
This module implements a UART Transmitter in SystemC. It serializes an 8-bit data word into a standard UART frame (1 start bit, 8 data bits, 1 stop bit), transmitting LSB first.

## Files
| File | Description |
|------|-------------|
| `UART_tx.h` | UART TX FSM module |
| `testbench_tx.h` | Testbench for UART TX |
| `main_tx.cpp` | Top-level simulation file |

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
| `tx_start` | Input | `bool` | Pulse high for 1 cycle to begin transmission |
| `tx_data` | Input | `sc_uint<8>` | Byte to transmit |
| `tx` | Output | `bool` | Serial data output line |
| `tx_done` | Output | `bool` | Pulses high for 1 cycle when transmission completes |

## FSM States
| State | Description |
|-------|-------------|
| `IDLE` | Line held high, waits for `tx_start` |
| `START` | Drives line low for 8 clock cycles (start bit) |
| `DATA` | Shifts out each bit (LSB first), 8 clocks per bit |
| `STOP` | Drives line high for 8 clock cycles (stop bit), asserts `tx_done` |

## Timing
- Each bit is held for **8 clock cycles**
- Full frame: 10 bits × 8 clocks = **80 clock cycles**

## Testbench
The testbench sends two bytes sequentially:
- `0x53` (83 decimal)
- `0xA5` (165 decimal)

## Building & Running
```bash
make
./sim.exe
```

## Example Output
```
Simulation started
[1 ns] rst=1, tx_start=0, tx_data=0x000, tx=1, tx_done=0
...
  >> TX done at 85 ns, data=0x053
  >> TX done at 166 ns, data=0x0a5
Simulation finished
```
