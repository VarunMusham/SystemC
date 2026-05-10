// ============================================================
// File: testbench.h
// ============================================================

#include <systemc.h>

SC_MODULE(Testbench_TX)
{
    // Outputs to DUT
    sc_out<bool> rst;

    sc_out<bool> tx_start;
    sc_out<sc_uint<8>> tx_data;

    // Inputs from DUT
    sc_in<bool> tx;
    sc_in<bool> tx_done;

    // -------------------------------------------------
    // Test Process
    // -------------------------------------------------
    void run()
    {
        // Reset
        rst.write(1);

        tx_start.write(0);

        wait(2, SC_NS);

        rst.write(0);

        wait(2, SC_NS);

        // -----------------------------------------
        // Send First Byte
        // -----------------------------------------
        tx_data.write(0x53);

        tx_start.write(1);

        wait(1, SC_NS);

        tx_start.write(0);

        // Wait until transmission completes
        wait(15, SC_NS);

        // -----------------------------------------
        // Send Second Byte
        // -----------------------------------------
        tx_data.write(0xA5);

        tx_start.write(1);

        wait(1, SC_NS);

        tx_start.write(0);

        wait(15, SC_NS);

        sc_stop();
    }

    // Constructor
    SC_CTOR(Testbench_TX)
    {
        SC_THREAD(run);
    }
};
