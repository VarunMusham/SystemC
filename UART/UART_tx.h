// ============================================================
// File: uart_tx.h
// ============================================================

#include <systemc.h>

SC_MODULE(UART_TX)
{
    // Inputs
    sc_in<bool> clk;
    sc_in<bool> rst;

    sc_in<bool> tx_start;
    sc_in<sc_uint<8>> tx_data;

    // Outputs
    sc_out<bool> tx;
    sc_out<bool> tx_done;

    // FSM States
    enum State
    {
        IDLE,
        START,
        DATA,
        STOP
    };

    State current_state;

    // Internal registers
    sc_uint<8> data_reg;
    sc_uint<4> bit_index;
    sc_uint<4> bit_timer; // For bit period timing

    // -------------------------------------------------
    // UART FSM
    // -------------------------------------------------
    void uart_process()
    {
        // Reset
        if(rst.read() == 1)
        {
            current_state = IDLE;
            tx.write(1);
            tx_done.write(0);
            data_reg = 0;
            bit_index = 0;
            bit_timer = 0;
        }
        else
        {
            switch(current_state)
            {
                case IDLE:
                    tx.write(1);
                    tx_done.write(0);
                    bit_timer = 0;
                    if(tx_start.read() == 1)
                    {
                        data_reg = tx_data.read();
                        bit_index = 0;
                        current_state = START;
                    }
                    break;
                case START:
                    tx.write(0);
                    if (++bit_timer == 8) {
                        bit_timer = 0;
                        current_state = DATA;
                    }
                    break;
                case DATA:
                    tx.write(data_reg[bit_index]);
                    if (++bit_timer == 8) {
                        bit_timer = 0;
                        if(bit_index == 7)
                        {
                            current_state = STOP;
                        }
                        else
                        {
                            bit_index++;
                        }
                    }
                    break;
                case STOP:
                    tx.write(1);
                    if (++bit_timer == 8) {
                        bit_timer = 0;
                        tx_done.write(1);
                        current_state = IDLE;
                    }
                    break;
                default:
                    current_state = IDLE;
                    break;
            }
        }
    }

    // Constructor
    SC_CTOR(UART_TX)
    {
        SC_METHOD(uart_process);

        sensitive << clk.pos();
    }
};
