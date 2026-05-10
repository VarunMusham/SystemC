// ============================================================
// File: main_loopback.cpp
// ============================================================

#include <systemc.h>
#include "uart_tx.h"
#include "uart_rx.h"

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
    sc_signal<bool> rx_done_sig;
    sc_signal<sc_uint<8>> rx_data_sig;

    // DUTs
    UART_TX uart_tx("UART_TX");
    uart_tx.clk(clk);
    uart_tx.rst(rst_sig);
    uart_tx.tx_start(tx_start_sig);
    uart_tx.tx_data(tx_data_sig);
    uart_tx.tx(tx_sig);
    uart_tx.tx_done(tx_done_sig);

    UART_RX uart_rx("UART_RX");
    uart_rx.clk(clk);
    uart_rx.rst(rst_sig);
    uart_rx.rx(tx_sig); // Loopback connection
    uart_rx.rx_done(rx_done_sig);
    uart_rx.rx_data(rx_data_sig);

    // Testbench logic (inline)
    std::cout << "Simulation started" << std::endl;
    sc_trace_file *wf = sc_create_vcd_trace_file("uart_loopback_wave");
    sc_trace(wf, clk, "clk");
    sc_trace(wf, rst_sig, "rst");
    sc_trace(wf, tx_start_sig, "tx_start");
    sc_trace(wf, tx_data_sig, "tx_data");
    sc_trace(wf, tx_sig, "tx");
    sc_trace(wf, tx_done_sig, "tx_done");
    sc_trace(wf, rx_done_sig, "rx_done");
    sc_trace(wf, rx_data_sig, "rx_data");

    // Reset
    rst_sig.write(1);
    tx_start_sig.write(0);
    tx_data_sig.write(0);
    sc_start(2, SC_NS);
    rst_sig.write(0);
    sc_start(2, SC_NS);

    // Send first byte, then observe; send second byte after tx_done
    tx_data_sig.write(0x53);
    tx_start_sig.write(1);
    sc_start(1, SC_NS);
    tx_start_sig.write(0);

    bool second_sent = false;

    for (int i = 0; i < 400; ++i) {
        if (sc_end_of_simulation_invoked()) {
            break;
        }
        sc_start(1, SC_NS);
        // Send second byte once first transmission is done
        if (!second_sent && tx_done_sig.read()) {
            std::cout << "  >> TX done at " << sc_time_stamp() << ", data=0x" << std::hex << tx_data_sig.read() << std::dec << std::endl;
            second_sent = true;
            tx_data_sig.write(0xA5);
            tx_start_sig.write(1);
            sc_start(1, SC_NS);
            tx_start_sig.write(0);
        }
        if (tx_done_sig.read() && second_sent) {
            std::cout << "  >> TX done at " << sc_time_stamp() << ", data=0x" << std::hex << tx_data_sig.read() << std::dec << std::endl;
        }
        if (rx_done_sig.read()) {
            std::cout << "  >> RX done at " << sc_time_stamp() << ", rx_data=0x" << std::hex << rx_data_sig.read() << std::dec << " (" << rx_data_sig.read() << ")" << std::endl;
        }
    }

    sc_close_vcd_trace_file(wf);
    std::cout << "Simulation finished" << std::endl;
    return 0;
}
