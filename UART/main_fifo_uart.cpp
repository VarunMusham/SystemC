// ============================================================
// File: main_fifo_uart.cpp
// ============================================================

#include <systemc.h>
#include "uart_tx.h"
#include "uart_rx.h"
#include "fifo.h"

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
    sc_signal<bool> fifo_wr_en_sig, fifo_rd_en_sig;
    sc_signal<sc_uint<8>> fifo_din_sig, fifo_dout_sig;
    sc_signal<bool> fifo_empty_sig, fifo_full_sig;

    // FIFO
    FIFO fifo("FIFO");
    fifo.clk(clk);
    fifo.rst(rst_sig);
    fifo.wr_en(fifo_wr_en_sig);
    fifo.rd_en(fifo_rd_en_sig);
    fifo.din(fifo_din_sig);
    fifo.dout(fifo_dout_sig);
    fifo.empty(fifo_empty_sig);
    fifo.full(fifo_full_sig);

    // UART TX
    UART_TX uart_tx("UART_TX");
    uart_tx.clk(clk);
    uart_tx.rst(rst_sig);
    uart_tx.tx_start(tx_start_sig);
    uart_tx.tx_data(tx_data_sig);
    uart_tx.tx(tx_sig);
    uart_tx.tx_done(tx_done_sig);

    // UART RX
    UART_RX uart_rx("UART_RX");
    uart_rx.clk(clk);
    uart_rx.rst(rst_sig);
    uart_rx.rx(tx_sig);
    uart_rx.rx_done(rx_done_sig);
    uart_rx.rx_data(rx_data_sig);

    // Testbench logic (inline)
    std::cout << "Simulation started" << std::endl;
    sc_trace_file *wf = sc_create_vcd_trace_file("fifo_uart_wave");
    sc_trace(wf, clk, "clk");
    sc_trace(wf, rst_sig, "rst");
    sc_trace(wf, tx_start_sig, "tx_start");
    sc_trace(wf, tx_data_sig, "tx_data");
    sc_trace(wf, tx_sig, "tx");
    sc_trace(wf, tx_done_sig, "tx_done");
    sc_trace(wf, rx_done_sig, "rx_done");
    sc_trace(wf, rx_data_sig, "rx_data");
    sc_trace(wf, fifo_wr_en_sig, "fifo_wr_en");
    sc_trace(wf, fifo_rd_en_sig, "fifo_rd_en");
    sc_trace(wf, fifo_din_sig, "fifo_din");
    sc_trace(wf, fifo_dout_sig, "fifo_dout");
    sc_trace(wf, fifo_empty_sig, "fifo_empty");
    sc_trace(wf, fifo_full_sig, "fifo_full");

    // Reset
    rst_sig.write(1);
    tx_start_sig.write(0);
    fifo_wr_en_sig.write(0);
    fifo_rd_en_sig.write(0);
    sc_start(2, SC_NS);
    rst_sig.write(0);
    sc_start(2, SC_NS);

    // Write two bytes to FIFO
    fifo_din_sig.write(0x53);
    fifo_wr_en_sig.write(1);
    sc_start(1, SC_NS);
    fifo_wr_en_sig.write(0);
    sc_start(1, SC_NS);
    fifo_din_sig.write(0xA5);
    fifo_wr_en_sig.write(1);
    sc_start(1, SC_NS);
    fifo_wr_en_sig.write(0);
    sc_start(1, SC_NS);

    // Read first byte from FIFO and send via UART
    fifo_rd_en_sig.write(1);
    sc_start(1, SC_NS);
    tx_data_sig.write(fifo_dout_sig.read());
    tx_start_sig.write(1);
    sc_start(1, SC_NS);
    tx_start_sig.write(0);
    fifo_rd_en_sig.write(0);

    bool second_sent = false;

    // Observe loop: send second byte from FIFO after tx_done, print on rx_done
    for (int i = 0; i < 400; ++i) {
        if (sc_end_of_simulation_invoked()) {
            break;
        }
        sc_start(1, SC_NS);
        // Send second byte from FIFO once first transmission is done
        if (!second_sent && tx_done_sig.read()) {
            std::cout << "  >> TX done at " << sc_time_stamp() << ", data=0x" << std::hex << tx_data_sig.read() << std::dec << std::endl;
            second_sent = true;
            fifo_rd_en_sig.write(1);
            sc_start(1, SC_NS);
            tx_data_sig.write(fifo_dout_sig.read());
            tx_start_sig.write(1);
            sc_start(1, SC_NS);
            tx_start_sig.write(0);
            fifo_rd_en_sig.write(0);
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
