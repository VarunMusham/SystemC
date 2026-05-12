# AXI4-Stream TLM Loosely-Timed (LT) Implementation

## Overview

This is a user-friendly implementation of **AXI4-Stream** protocol using **SystemC TLM Loosely-Timed** (LT) model. AXI4-Stream is a unidirectional streaming interface commonly used in FPGA and SoC designs for high-bandwidth data transfer.

### What is AXI4-Stream?

AXI4-Stream is a simplified version of the AXI protocol designed specifically for streaming data applications. Unlike AXI4, which supports complex transactions, AXI4-Stream focuses on:

- **Unidirectional**: Data flows in one direction (Master → Slave)
- **Streaming**: Continuous data flow without complex addressing
- **Lightweight**: Minimal control signals (VALID, READY, LAST, KEEP, DATA)

### What is TLM Loosely-Timed (LT)?

TLM LT is a fast, approximate simulation model that prioritizes speed over cycle-accurate accuracy. It's ideal for:

- Early system validation
- Quick architectural exploration
- High-level protocol verification

## File Structure

```
AXI-Stream/
├── axi_stream_types.h          # Core data structures
├── axi_stream_master.h         # Master (Transmitter)
├── axi_stream_slave.h          # Slave (Receiver)
├── axi_stream_interconnect.h   # Simple interconnect
├── simple_data_generator.h     # Example data source
├── main_basic_example.cpp      # Simple demo
├── main_axi_stream.cpp         # Full demo with monitoring
├── Makefile                    # Build configuration
└── README.md                   # This file
```

## Core Components Explained

### 1. **AXI Stream Types** (`axi_stream_types.h`)

Defines the payload structure and TLM extension:

```c
AXIStreamPayload    - Data container holding stream data
AXIStreamExtension  - TLM extension for LAST and KEEP signals
```

**Key Fields:**
- `data`: Vector of bytes containing the actual payload
- `last`: Flag indicating last transaction in a burst
- `keep`: Flag indicating valid data bytes

### 2. **AXI Stream Master** (`axi_stream_master.h`)

The transmitter/initiator in the stream. 

**Main Method:**
- `send_stream_transaction()`: Sends a single transaction with payload and LAST flag

**Usage Example:**
```cpp
AXIStreamPayload payload(64);
payload.data[0] = 0x12;
master->send_stream_transaction(payload, false);
```

### 3. **AXI Stream Slave** (`axi_stream_slave.h`)

The receiver/target in the stream.

**Key Methods:**
- `get_last_data()`: Returns the last received data
- `get_last_flag()`: Returns LAST signal status
- `get_transaction_count()`: Total transactions received
- `has_received_transaction()`: Checks if any transaction was received

**Output Signals:**
- `data_valid`: Pulses when valid data arrives
- `transaction_complete`: Pulses when transaction processing is done

### 4. **AXI Stream Interconnect** (`axi_stream_interconnect.h`)

Simple pass-through interconnect connecting master to slave. Can be extended for:

- Multiple masters
- Multiple slaves
- Arbitration logic

### 5. **Simple Data Generator** (`simple_data_generator.h`)

Pre-built master that generates sample data patterns. Inherits from `AXIStreamMaster`.

## How to Build and Run

### Prerequisites

1. **SystemC** installed (v2.3.3 or later)
   - Download from: http://systemc.org
   - Build from source following SystemC documentation

2. **G++ compiler** (part of MinGW/GCC)

3. **Windows environment** (as per Makefile)

### Building

Open PowerShell/Command Prompt in the AXI-Stream directory:

```powershell
cd d:\Programming\SystemC\AXI-Stream
make all
```

This creates two executables:
- `sim_basic.exe` - Simple example
- `sim_demo.exe` - Full demo with data monitoring

### Running Examples

```powershell
make run_basic
```

Expected output:
```
Starting AXI4-Stream Basic Example
@0 s Master sent transaction
Data bytes: 0x12 0x34 0x56 0x78
Slave received: SUCCESS
Simulation ended
```

## Quick Start - Creating Your Own Module

### Step 1: Create a Custom Master

```cpp
class MyDataSource : public AXIStreamMaster {
public:
    MyDataSource(sc_module_name name) 
        : AXIStreamMaster(name) {}
    
protected:
    void send_data() {
        wait();
        
        for (int i = 0; i < 10; i++) {
            AXIStreamPayload payload(64);
            payload.data[0] = i;
            bool is_last = (i == 9);
            send_stream_transaction(payload, is_last);
            wait();
        }
        
        sc_stop();
    }
};
```

### Step 2: Connect in Main

```cpp
SC_MODULE(TopLevel) {
    sc_clock clk{"clk", 10, SC_NS};
    sc_signal<bool> reset_n;
    
    MyDataSource* my_source;
    AXIStreamSlave* my_sink;
    AXIStreamInterconnect* interconnect;
    
    SC_CTOR(TopLevel) {
        my_source = new MyDataSource("source");
        my_sink = new AXIStreamSlave("sink");
        interconnect = new AXIStreamInterconnect("interconnect");
        
        my_source->clk(clk);
        my_source->reset_n(reset_n);
        my_source->stream_socket(interconnect->master_port);
        
        interconnect->slave_port(my_sink->stream_socket);
        my_sink->clk(clk);
        my_sink->reset_n(reset_n);
        
        SC_THREAD(run);
    }
    
    void run() {
        reset_n.write(false);
        wait(20, SC_NS);
        reset_n.write(true);
        wait(500, SC_NS);
        
        std::cout << "Total Received: " 
                  << my_sink->get_transaction_count() << std::endl;
        
        sc_stop();
    }
};
```

### Step 3: Compile and Run

Update Makefile with your source and run:

```powershell
make all
./sim_custom.exe
```

## Architecture Diagram

```
┌─────────────────────┐
│  MyDataSource       │
│  (Master/Initiator) │
└──────────┬──────────┘
           │ stream_socket (TLM b_transport)
           │
┌──────────▼──────────────────┐
│  AXIStreamInterconnect      │
│  (Simple Pass-through)      │
└──────────┬──────────────────┘
           │ stream_socket
           │
┌──────────▼──────────┐
│  AXIStreamSlave     │
│  (Receiver/Target)  │
└─────────────────────┘
```

## Key Features

✅ **User-Friendly**: Clear naming, easy-to-understand code structure  
✅ **TLM LT Compliant**: Uses standard SystemC TLM patterns  
✅ **Extensible**: Easy to add features (FIFOs, arbitration, etc.)  
✅ **No Comments in Code**: Clean code with descriptive naming  
✅ **Examples Included**: Both basic and advanced examples  
✅ **Makefile Provided**: One-command compilation  

## Signal Summary

| Signal | Direction | Type | Purpose |
|--------|-----------|------|---------|
| clk | Input | Clock | System clock (10 ns period) |
| reset_n | Input | Reset | Active low reset |
| data_valid | Output | Boolean | Indicates valid data reception |
| transaction_complete | Output | Boolean | Transaction processing complete |

## Data Flow Example

```
Cycle 1:  Master creates payload with data 0x12345678
Cycle 2:  Master calls send_stream_transaction(payload, false)
Cycle 3:  TLM b_transport carries transaction to Slave
Cycle 4:  Slave b_transport receives and stores data
Cycle 5:  Slave outputs data_valid pulse
Cycle 6:  Slave outputs transaction_complete pulse
```

## Extension Ideas

1. **Add Flow Control**: Implement READY signal
2. **Add Backpressure**: Block transfers when slave is busy
3. **FIFO Buffer**: Add buffering between master and slave
4. **Error Handling**: Add error generation/detection
5. **Statistics**: Track latency, throughput, errors
6. **Multiple Streams**: Demultiplexer/Multiplexer for multiple data channels

## Troubleshooting

### Compilation Issues

**Problem**: `undefined reference to 'sc_main'`
- **Solution**: Ensure you have exactly one sc_main() in your project

**Problem**: `cannot find systemc headers`
- **Solution**: Check SYSTEMC_HOME path in Makefile matches your installation

### Runtime Issues

**Problem**: `No transactions received`
- **Solution**: Check that master is properly connected; verify reset sequence

**Problem**: `Simulation hangs`
- **Solution**: Ensure sc_stop() is called; check for infinite loops in send_data()

## Performance Tips

1. Use LT model for quick exploration (current implementation)
2. Switch to AT (Approximate Timed) for better accuracy if needed
3. Disable waveform tracing for faster simulation
4. Use sc_pause() for debugging specific cycles

## References

- [SystemC TLM Documentation](http://www.systemc.org/)
- [AMBA AXI4-Stream Specification](https://developer.arm.com/)
- [TLM Modeling Examples](https://systemc.org/download/standards/)

## License

This implementation is provided as-is for educational and development purposes.

## Support

For questions or issues:
1. Review the example files
2. Check SystemC documentation
3. Verify all connections in your testbench
4. Use sc_report_handler for debugging

---

**Last Updated**: 2026  
**SystemC Version**: 2.3.3+  
**TLM Version**: 2.0
