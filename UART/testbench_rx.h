// ============================================================
// File: testbench_rx.h
// ============================================================

#include <systemc.h>

SC_MODULE(Testbench_RX)
{
    // Outputs to DUT
    sc_out<bool> rst;
    sc_out<bool> rx;

    // Inputs from DUT
    sc_in<bool> rx_done;
    sc_in<sc_uint<8>> rx_data;

    void run()
    {
        // Reset
        rst.write(1);
        rx.write(1); // Idle
        wait(2, SC_NS);
        rst.write(0);
        wait(2, SC_NS);


        // Send Start Bit (hold for 8 clocks)
        rx.write(0);
        wait(8, SC_NS);
        // Send 8 Data Bits (0x53), each held for 8 clocks
        sc_uint<8> data = 0x53;
        for (int i = 0; i < 8; ++i) {
            rx.write((data >> i) & 1);
            wait(8, SC_NS);
        }
        // Send Stop Bit (hold for 8 clocks)
        rx.write(1);
        wait(8, SC_NS);

        // Wait for rx_done
        wait(16, SC_NS);

        // Send another byte (0xA5)
        rx.write(0);
        wait(8, SC_NS);
        data = 0xA5;
        for (int i = 0; i < 8; ++i) {
            rx.write((data >> i) & 1);
            wait(8, SC_NS);
        }
        rx.write(1);
        wait(8, SC_NS);
        wait(16, SC_NS);

        sc_stop();
    }

    SC_CTOR(Testbench_RX)
    {
        SC_THREAD(run);
    }
};
