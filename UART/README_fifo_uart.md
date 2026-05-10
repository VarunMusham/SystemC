# FIFO + UART System

## Overview
This simulation integrates a synchronous FIFO buffer with the UART TX and RX modules. Data is first written into the FIFO, then read out and transmitted over UART. The TX output is looped back to the RX input, allowing the full pipeline — FIFO → TX → RX — to be verified.

## Files
| File | Description |
|------|-------------|
| `fifo.h` | Synchronous FIFO buffer module |
| `UART_tx.h` | UART TX FSM module |
| `UART_rx.h` | UART RX FSM module |
| `main_fifo_uart.cpp` | Top-level FIFO+UART simulation |

## System Architecture
```
           +-------+   dout   +----------+   tx   +----------+
din -----> | FIFO  | -------> | UART_TX  | -----> | UART_RX  | ---> rx_data
wr_en ---> |       |          |          |        |          | ---> rx_done
rd_en ---> |       |          |          |        +----------+
           +-------+          +----------+
```

## FIFO Interface
| Signal | Direction | Type | Description |
|--------|-----------|------|-------------|
| `clk` | Input | `bool` | Clock |
| `rst` | Input | `bool` | Active-high synchronous reset |
| `wr_en` | Input | `bool` | Write enable |
| `rd_en` | Input | `bool` | Read enable |
| `din` | Input | `sc_uint<8>` | Data in |
| `dout` | Output | `sc_uint<8>` | Data out |
| `empty` | Output | `bool` | FIFO is empty |
| `full` | Output | `bool` | FIFO is full (depth = 16) |

## FIFO Specifications
- **Depth:** 16 entries
- **Width:** 8 bits
- **Type:** Synchronous, single-clock
- **Behavior:** Simultaneous read/write supported

## Test Sequence
1. Reset all modules
2. Write `0x53` and `0xA5` into the FIFO
3. Read first byte from FIFO, send via UART TX
4. Wait for `tx_done`, read second byte from FIFO, send via UART TX
5. Print timestamps when `tx_done` and `rx_done` are asserted

## Building & Running
```bash
g++ main_fifo_uart.cpp -IC:/systemc/systemc-2.3.3/src -LC:/systemc/systemc-2.3.3/build/src/.libs -lsystemc -o sim_fifo.exe
./sim_fifo.exe
```

## Example Output
```
Simulation started
  >> RX done at 88 ns, rx_data=0x053 (83)
  >> TX done at 90 ns, data=0x053
  >> RX done at 170 ns, rx_data=0x0a5 (165)
  >> TX done at 172 ns, data=0x0a5
Simulation finished
```
