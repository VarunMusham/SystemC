# SystemC UART Project

## Overview
This project implements a complete UART communication system in SystemC, consisting of a Transmitter (TX), Receiver (RX), Loopback test, and a FIFO-buffered UART system.

## Project Structure
```
UART/
├── UART_tx.h           # UART TX FSM
├── UART_rx.h           # UART RX FSM
├── fifo.h              # Synchronous FIFO buffer
├── testbench_tx.h      # Testbench for TX
├── testbench_rx.h      # Testbench for RX
├── main_tx.cpp         # TX-only simulation
├── main_rx.cpp         # RX-only simulation
├── main_loopback.cpp   # TX→RX loopback simulation
├── main_fifo_uart.cpp  # FIFO+UART simulation
├── Makefile
├── README.md           # This file
├── README_tx.md        # UART TX documentation
├── README_rx.md        # UART RX documentation
├── README_loopback.md  # Loopback documentation
└── README_fifo_uart.md # FIFO+UART documentation
```

## Modules

### UART TX (`UART_tx.h`)
Serializes an 8-bit word into a UART frame (start + 8 data + stop bit), LSB first.
Each bit is held for **8 clock cycles**.

### UART RX (`UART_rx.h`)
Deserializes a UART frame into an 8-bit word. Samples each bit every **8 clock cycles**, with mid-bit alignment for the start bit.

### FIFO (`fifo.h`)
16-deep, 8-bit wide synchronous FIFO with `full` and `empty` flags.

## UART Frame Format
```
Line: 1 1 1 | 0 | D0 D1 D2 D3 D4 D5 D6 D7 | 1 | 1 1 1
            IDLE START        DATA          STOP  IDLE
```

## Timing

| Parameter | Value |
|-----------|-------|
| Clock period | 1 ns |
| Bits per clock | 1 bit per 8 clocks |
| Frame duration | 80 clocks (80 ns) |

### Why does `tx_done` fire at ~85 ns?

Simulation setup consumes 5 ns before the frame starts:

| Action | Time |
|--------|------|
| `rst=1`, run 2 clocks | t = 0 → 2 ns |
| `rst=0`, run 2 clocks | t = 2 → 4 ns |
| `tx_start=1`, run 1 clock — TX enters START | t = 4 → **5 ns** |

The TX FSM then runs its full 80-clock frame:

| State | Clocks | Ends at |
|-------|--------|---------|
| START | 8 | 13 ns |
| DATA (8 bits × 8 clocks) | 64 | 77 ns |
| STOP (`tx_done` fires on 8th clock) | 8 | **85 ns** |

$$5\text{ ns setup} + 8 + 64 + 8 = \mathbf{85\text{ ns}}$$

### Why is `rx_done` only 2 ns after `tx_done`?

TX and RX process the same frame **in parallel** — `rx_done` is not waiting for `tx_done`. The 2 ns gap comes from two 1-clock offsets:

**1. Signal propagation delay (1 clock)**  
When TX drives `tx=0` (start bit) at t=5 ns, the signal only becomes visible to the RX module at the next rising clock edge (t=6 ns) due to SystemC delta-cycle semantics. RX is always 1 clock behind TX in detecting the start bit.

**2. Mid-bit alignment compensation (1 clock)**  
The RX START state waits only 4 clocks (instead of 8) to land at mid-bit, saving 4 clocks early. To compensate, the STOP state waits 12 clocks (instead of 8), adding 4 clocks late. The net active time is the same 80 clocks, but the residual +4/−4 split leaves 1 extra clock at the end.

| Module | START | DATA | STOP | Total active | Fires at |
|--------|-------|------|------|-------------|---------|
| TX | 8 | 64 | 8 | 80 clocks | **85 ns** |
| RX | 4 | 64 | 12 | 80 clocks (from t=6) | **87 ns** |

$$\underbrace{1}_{\text{detection delay}} + \underbrace{1}_{\text{STOP residual}} = \mathbf{2\text{ ns gap}}$$

This ordering is physically correct: a receiver always confirms the stop bit slightly *after* the transmitter finishes driving it.

## Simulations

| Simulation | Source File | Output Binary | Description |
|------------|------------|---------------|-------------|
| TX only | `main_tx.cpp` | `sim.exe` | Transmit test, prints all signals every cycle |
| RX only | `main_rx.cpp` | `sim.exe` | Receive test, prints on `rx_done` |
| Loopback | `main_loopback.cpp` | `sim_loopback.exe` | TX wired to RX, prints TX and RX events |
| FIFO+UART | `main_fifo_uart.cpp` | `sim_fifo.exe` | FIFO feeds TX, looped to RX |

## Building

The default Makefile builds the TX simulation:
```bash
make
./sim.exe
```

To build others manually:
```bash
# RX
g++ main_rx.cpp -IC:/systemc/systemc-2.3.3/src -LC:/systemc/systemc-2.3.3/build/src/.libs -lsystemc -o sim.exe

# Loopback
g++ main_loopback.cpp -IC:/systemc/systemc-2.3.3/src -LC:/systemc/systemc-2.3.3/build/src/.libs -lsystemc -o sim_loopback.exe

# FIFO+UART
g++ main_fifo_uart.cpp -IC:/systemc/systemc-2.3.3/src -LC:/systemc/systemc-2.3.3/build/src/.libs -lsystemc -o sim_fifo.exe
```

## Dependencies
- [SystemC 2.3.3](https://www.accellera.org/downloads/standards/systemc)
- g++ compiler

## Expected Output (Loopback / FIFO+UART)
```
Simulation started
  >> RX done at 83 ns, rx_data=0x053 (83)
  >> TX done at 85 ns, data=0x053
  >> RX done at 164 ns, rx_data=0x0a5 (165)
  >> TX done at 166 ns, data=0x0a5
Simulation finished
```
