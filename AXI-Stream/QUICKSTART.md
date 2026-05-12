# Getting Started with AXI4-Stream TLM LT

## What You Get

This package contains a complete, beginner-friendly implementation of AXI4-Stream using SystemC TLM Loosely-Timed model. No prior knowledge of AXI or TLM required!

## Quick Setup (5 minutes)

### 1. Check Prerequisites

Make sure you have:
- SystemC 2.3.3 installed (or later)
- G++ compiler (MinGW on Windows)
- Git installed

To verify:
```powershell
g++ --version
git --version
```

### 2. Update SystemC Path

Edit `Makefile` and set the correct path to your SystemC installation:

```makefile
SYSTEMC_HOME = C:/systemc/systemc-2.3.3
```

Replace `C:/systemc/systemc-2.3.3` with your actual SystemC installation path.

### 3. Compile All Examples

```powershell
cd d:\Programming\SystemC\AXI-Stream
make all
```

This creates three executable files:
- `sim_basic.exe` - Simple starter example
- `sim_demo.exe` - Full demonstration
- `sim_advanced.exe` - Multiple transaction example

### 4. Run Your First Example

```powershell
make run_basic
```

You should see output like:
```
Starting AXI4-Stream Basic Example
@0 s Master sent transaction
Data bytes: 0x12 0x34 0x56 0x78
Slave received: SUCCESS
Simulation ended
```

## Understanding the Code Structure

### Folder Layout

```
AXI-Stream/
├── Core Headers (the TLM implementation)
│   ├── axi_stream_types.h          <- Data structures
│   ├── axi_stream_master.h         <- Transmitter
│   ├── axi_stream_slave.h          <- Receiver
│   └── axi_stream_interconnect.h   <- Connection logic
│
├── Helper Modules
│   └── simple_data_generator.h     <- Pre-built example master
│
├── Example Programs
│   ├── main_basic_example.cpp      <- Hello World level
│   ├── main_axi_stream.cpp         <- Shows monitoring
│   └── main_advanced_example.cpp   <- Multiple transactions
│
└── Build & Documentation
    ├── Makefile                    <- Compilation rules
    ├── README.md                   <- Full documentation
    ├── QUICKSTART.md               <- This file
    └── .gitignore                  <- Git configuration
```

## The Three Examples Explained

### Example 1: Basic Example
**File**: `main_basic_example.cpp`

Simplest possible use case:
1. Create a master and slave
2. Connect them with an interconnect
3. Send one transaction
4. Check if received

**Good for**: Understanding the minimum needed connections

### Example 2: Demo Example
**File**: `main_axi_stream.cpp`

Shows the full flow with data monitoring:
1. Reset sequence
2. Multiple transactions sent
3. Monitoring on slave side
4. Transaction counting

**Good for**: Seeing how signals work in practice

### Example 3: Advanced Example
**File**: `main_advanced_example.cpp`

Demonstrates multiple transactions with formatted output:
1. Sends 5 transactions
2. Pretty-prints each one
3. Shows LAST flag handling
4. Summary statistics

**Good for**: Learning multi-transaction sequences

## Creating Your Own Module

### Copy-Paste Template

```cpp
#include <systemc.h>
#include "axi_stream_master.h"
#include "axi_stream_slave.h"
#include "axi_stream_interconnect.h"

SC_MODULE(MyExample) {
    sc_clock clk{"clk", 10, SC_NS};
    sc_signal<bool> reset_n;
    
    AXIStreamMaster* source;
    AXIStreamSlave* sink;
    AXIStreamInterconnect* interconnect;
    
    SC_CTOR(MyExample) {
        source = new AXIStreamMaster("source");
        sink = new AXIStreamSlave("sink");
        interconnect = new AXIStreamInterconnect("interconnect");
        
        source->clk(clk);
        source->reset_n(reset_n);
        source->stream_socket(interconnect->master_port);
        
        interconnect->slave_port(sink->stream_socket);
        
        sink->clk(clk);
        sink->reset_n(reset_n);
        
        SC_THREAD(testbench);
    }
    
    void testbench() {
        reset_n.write(false);
        wait(20, SC_NS);
        reset_n.write(true);
        wait(50, SC_NS);
        
        // YOUR CODE HERE
        // Example: send data
        AXIStreamPayload pkt(64);
        pkt.data[0] = 0xAB;
        source->send_stream_transaction(pkt, false);
        
        wait(20, SC_NS);
        sc_stop();
    }
};

int sc_main(int argc, char* argv[]) {
    MyExample tb("my_test");
    sc_start();
    return 0;
}
```

### Steps to Use:

1. Save as `main_my_example.cpp`
2. Update Makefile:
   ```makefile
   SRC_MY = main_my_example.cpp
   run_my: sim_my.exe
   sim_my.exe: $(SRC_MY) $(INCLUDES) $(LIBS)
   ```
3. Compile: `g++ main_my_example.cpp -I... -L... -lsystemc`
4. Run: `./sim_my.exe`

## Key Concepts Simplified

### 1. Payload
A container for data being sent:
```cpp
AXIStreamPayload pkt(64);      // 64-bit width
pkt.data[0] = 0x12;            // First byte
pkt.data[1] = 0x34;            // Second byte
```

### 2. Master
The sender:
```cpp
master->send_stream_transaction(pkt, false);  // false = not last
master->send_stream_transaction(pkt, true);   // true = last packet
```

### 3. Slave
The receiver:
```cpp
if (sink->has_received_transaction()) {
    auto received_data = sink->get_last_data();
    bool is_last = sink->get_last_flag();
    int count = sink->get_transaction_count();
}
```

### 4. Reset Sequence
Always do this at start:
```cpp
reset_n.write(false);           // Assert reset
wait(20, SC_NS);
reset_n.write(true);            // De-assert reset
wait(50, SC_NS);                // Wait for settling
// NOW send data
```

## Common Patterns

### Pattern 1: Send Multiple Packets

```cpp
for (int i = 0; i < 10; i++) {
    AXIStreamPayload pkt(64);
    pkt.data[0] = i;
    bool is_last = (i == 9);
    
    master->send_stream_transaction(pkt, is_last);
    wait(10, SC_NS);
}
```

### Pattern 2: Check Reception

```cpp
if (sink->has_received_transaction()) {
    std::cout << "Received " << sink->get_transaction_count() << " packets" << std::endl;
}
```

### Pattern 3: Extract Data

```cpp
auto data = sink->get_last_data();
for (auto byte : data) {
    std::cout << "0x" << std::hex << (int)byte << " ";
}
```

## Timing Basics

Standard timing (10 ns clock):
```cpp
sc_clock clk{"clk", 10, SC_NS};    // 10 ns period = 100 MHz
```

Time operations:
```cpp
wait(10, SC_NS);                    // Wait 10 nanoseconds
wait(1, SC_US);                     // Wait 1 microsecond
wait(10);                           // Wait 10 clock cycles
```

## Troubleshooting

### Compilation Fails

**Error**: `undefined reference to 'sc_main'`
- Ensure your file has `int sc_main(int argc, char* argv[]) { ... }`

**Error**: `cannot find -lsystemc`
- Check SYSTEMC_HOME path in Makefile
- Verify SystemC is installed

### Simulation Doesn't Output Anything

- Check reset sequence (shown above)
- Verify connections are made
- Add debug prints in testbench

### "No transactions received"

- Check master.clk is connected to clock
- Verify reset_n sequence
- Ensure interconnect connections are correct
- Check slave is connected

## Next Steps

1. **Run all examples**: `make all` then `make run_basic`, `make run_demo`, `make run_advanced`
2. **Understand connections**: Look at how modules are connected in examples
3. **Create simple variant**: Copy template and modify for your use case
4. **Add features**: Extend with FIFO, error handling, etc. (see README.md)

## Files Overview

| File | Purpose | When to Use |
|------|---------|------------|
| axi_stream_types.h | Payload structure | Never modify (core) |
| axi_stream_master.h | Transmitter base | Inherit for custom sources |
| axi_stream_slave.h | Receiver base | Use directly or inherit |
| axi_stream_interconnect.h | Connection | Use directly (basic) |
| simple_data_generator.h | Example source | Inherit for data sources |
| main_*.cpp | Examples | Learn from, modify for your use |

## Tips & Tricks

1. **Print debug info**:
   ```cpp
   std::cout << "@" << sc_time_stamp() << " Some message" << std::endl;
   ```

2. **Check time in simulation**:
   ```cpp
   sc_time current_time = sc_time_stamp();
   ```

3. **Wait with event**:
   ```cpp
   wait(some_signal_change);
   ```

4. **Force simulation to stop**:
   ```cpp
   sc_stop();
   ```

## Resources

- **Detailed Info**: See README.md
- **SystemC Documentation**: http://systemc.org
- **TLM Guide**: Check SystemC installation docs
- **Examples**: main_basic_example.cpp, main_advanced_example.cpp

## Ready to Go!

You now have everything to:
- ✅ Run the examples
- ✅ Understand AXI4-Stream TLM LT
- ✅ Create your own testbenches
- ✅ Extend with custom features

Happy simulating!

---

**For detailed reference**: Open README.md  
**For API details**: Check header file comments  
**For help**: Review the example code in main_*.cpp files
