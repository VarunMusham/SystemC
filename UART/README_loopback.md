# UART Loopback (TX → RX)

## Overview
This simulation connects the UART TX output directly to the UART RX input, forming a loopback. A byte transmitted by the TX module is immediately received by the RX module. This verifies that both modules operate correctly together with matched timing.

## Files
| File | Description |
|------|-------------|
| `UART_tx.h` | UART TX FSM module |
| `UART_rx.h` | UART RX FSM module |
| `main_loopback.cpp` | Top-level loopback simulation |

## System Architecture
```
             +----------+    tx    +----------+
tx_data ---> | UART_TX  | -------> | UART_RX  | ---> rx_data
tx_start --> |          |          |          | ---> rx_done
             +----------+          +----------+
```

## Signal List
| Signal | Type | Description |
|--------|------|-------------|
| `clk` | `bool` | System clock (1 ns period) |
| `rst` | `bool` | Active-high synchronous reset |
| `tx_start` | `bool` | Initiates TX transmission |
| `tx_data` | `sc_uint<8>` | Data to transmit |
| `tx` | `bool` | Serial line connecting TX to RX |
| `tx_done` | `bool` | TX signals frame complete |
| `rx_done` | `bool` | RX signals byte received |
| `rx_data` | `sc_uint<8>` | Received byte |

## Timing
- Each bit is held for **8 clock cycles**
- Full frame: **80 clock cycles** per byte
- Second byte is sent after `tx_done` is asserted from the first byte

## Test Sequence
1. Reset both modules
2. Transmit `0x53` via UART TX
3. Wait for `tx_done`, then transmit `0xA5`
4. Print timestamps when `tx_done` and `rx_done` are asserted

## Building & Running
```bash
g++ main_loopback.cpp -IC:/systemc/systemc-2.3.3/src -LC:/systemc/systemc-2.3.3/build/src/.libs -lsystemc -o sim_loopback.exe
./sim_loopback.exe
```

## Example Output
```
Simulation started
  >> RX done at 83 ns, rx_data=0x053 (83)
  >> TX done at 85 ns, data=0x053
  >> RX done at 164 ns, rx_data=0x0a5 (165)
  >> TX done at 166 ns, data=0x0a5
Simulation finished
```
