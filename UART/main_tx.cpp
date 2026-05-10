// ============================================================
// File: main.cpp
// ============================================================

#include <systemc.h>

#include "uart_tx.h"
#include "testbench_tx.h"

int sc_main(int argc, char* argv[])
{
    // Clock
    sc_clock clk("clk", 1, SC_NS);

    // Signals
    sc_signal<bool> rst_sig;

    sc_signal<bool> tx_start_sig;

    sc_signal<sc_uint<8>> tx_data_sig;

    sc_signal<bool> tx_sig;
    sc_signal<bool> tx_done_sig;

    // DUT
    UART_TX uart("UART_TX");

    uart.clk(clk);
    uart.rst(rst_sig);

    uart.tx_start(tx_start_sig);
    uart.tx_data(tx_data_sig);

    uart.tx(tx_sig);
    uart.tx_done(tx_done_sig);

    // Testbench
    Testbench_TX tb("Testbench");

    tb.rst(rst_sig);

    tb.tx_start(tx_start_sig);
    tb.tx_data(tx_data_sig);

    tb.tx(tx_sig);
    tb.tx_done(tx_done_sig);


    // Trace signals during simulation
    std::cout << "Simulation started" << std::endl;

    // Add a trace file for waveform viewing (optional)
    sc_trace_file *wf = sc_create_vcd_trace_file("uart_tx_wave");
    sc_trace(wf, clk, "clk");
    sc_trace(wf, rst_sig, "rst");
    sc_trace(wf, tx_start_sig, "tx_start");
    sc_trace(wf, tx_data_sig, "tx_data");
    sc_trace(wf, tx_sig, "tx");
    sc_trace(wf, tx_done_sig, "tx_done");

    // Run simulation in steps to print signal values
    for (int i = 0; i < 40; ++i) {
        sc_start(1, SC_NS);
        std::cout << "[" << sc_time_stamp() << "] "
                  << "rst=" << rst_sig.read() << ", "
                  << "tx_start=" << tx_start_sig.read() << ", "
                  << "tx_data=0x" << std::hex << tx_data_sig.read() << std::dec << ", "
                  << "tx=" << tx_sig.read() << ", "
                  << "tx_done=" << tx_done_sig.read() << std::endl;
        if (tx_done_sig.read()) {
            std::cout << "  >> TX done at " << sc_time_stamp() << ", data=0x" << std::hex << tx_data_sig.read() << std::dec << std::endl;
        }
    }

    sc_close_vcd_trace_file(wf);
    std::cout << "Simulation finished" << std::endl;
    return 0;
}