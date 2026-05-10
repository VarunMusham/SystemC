// ============================================================
// File: main_rx.cpp
// ============================================================

#include <systemc.h>
#include "uart_rx.h"
#include "testbench_rx.h"

int sc_main(int argc, char* argv[])
{
    // Clock
    sc_clock clk("clk", 1, SC_NS);

    // Signals
    sc_signal<bool> rst_sig;
    sc_signal<bool> rx_sig;
    sc_signal<bool> rx_done_sig;
    sc_signal<sc_uint<8>> rx_data_sig;

    // DUT
    UART_RX uart_rx("UART_RX");
    uart_rx.clk(clk);
    uart_rx.rst(rst_sig);
    uart_rx.rx(rx_sig);
    uart_rx.rx_done(rx_done_sig);
    uart_rx.rx_data(rx_data_sig);

    // Testbench
    Testbench_RX tb("Testbench");
    tb.rst(rst_sig);
    tb.rx(rx_sig);
    tb.rx_done(rx_done_sig);
    tb.rx_data(rx_data_sig);

    // Trace signals
    std::cout << "Simulation started" << std::endl;
    sc_trace_file *wf = sc_create_vcd_trace_file("uart_rx_wave");
    sc_trace(wf, clk, "clk");
    sc_trace(wf, rst_sig, "rst");
    sc_trace(wf, rx_sig, "rx");
    sc_trace(wf, rx_done_sig, "rx_done");
    sc_trace(wf, rx_data_sig, "rx_data");

    for (int i = 0; i < 200; ++i) {
        if (sc_end_of_simulation_invoked()) {
            break;
        }
        sc_start(1, SC_NS);
        if (rx_done_sig.read()) {
            std::cout << "[" << sc_time_stamp() << "] "
                      << "rx_data=0x" << std::hex << rx_data_sig.read() << std::dec << " (" << rx_data_sig.read() << ")"
                      << ", rx_done=" << rx_done_sig.read() << std::endl;
        }
    }

    sc_close_vcd_trace_file(wf);
    std::cout << "Simulation finished" << std::endl;
    return 0;
}
