// ============================================================
// File: uart_rx.h
// ============================================================

#include <systemc.h>

SC_MODULE(UART_RX)
{
    // Inputs
    sc_in<bool> clk;
    sc_in<bool> rst;
    sc_in<bool> rx;

    // Outputs
    sc_out<bool> rx_done;
    sc_out<sc_uint<8>> rx_data;

    // FSM States
    enum State { IDLE, START, DATA, STOP };
    State current_state;

    // Internal registers
    sc_uint<8> data_reg;
    sc_uint<4> bit_index;
    sc_uint<4> bit_timer; // For bit period timing

    void uart_process()
    {
        if (rst.read() == 1)
        {
            current_state = IDLE;
            rx_done.write(0);
            data_reg = 0;
            bit_index = 0;
            bit_timer = 0;
        }
        else
        {
            switch (current_state)
            {
            case IDLE:
                rx_done.write(0);
                if (rx.read() == 0) // Start bit detected
                {
                    bit_timer = 0;
                    bit_index = 0;
                    data_reg = 0;
                    current_state = START;
                }
                break;
            case START:
                if (++bit_timer == 4) // Sample in the middle of start bit (assuming 8 cycles/bit)
                {
                    bit_timer = 0;
                    current_state = DATA;
                }
                break;
            case DATA:
                if (++bit_timer == 8)
                {
                    bit_timer = 0;
                    // Shift in LSB first
                    data_reg = data_reg | (rx.read() << bit_index);
                    if (bit_index == 7)
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
                if (++bit_timer == 12)
                {
                    bit_timer = 0;
                    rx_data.write(data_reg);
                    rx_done.write(1);
                    current_state = IDLE;
                }
                break;
            default:
                current_state = IDLE;
                break;
            }
            // De-assert rx_done after one cycle after STOP
            if (current_state != STOP && rx_done.read() == 1)
                rx_done.write(0);
        }
    }

    SC_CTOR(UART_RX)
    {
        SC_METHOD(uart_process);
        sensitive << clk.pos();
    }
};
