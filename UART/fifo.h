// ============================================================
// File: fifo.h
// ============================================================

#include <systemc.h>

SC_MODULE(FIFO)
{
    sc_in<bool> clk;
    sc_in<bool> rst;
    sc_in<bool> wr_en;
    sc_in<bool> rd_en;
    sc_in<sc_uint<8>> din;
    sc_out<sc_uint<8>> dout;
    sc_out<bool> empty;
    sc_out<bool> full;

    sc_uint<8> mem[16];
    sc_uint<4> wptr, rptr, count;

    void fifo_process()
    {
        if (rst.read() == 1) {
            wptr = rptr = count = 0;
            empty.write(1);
            full.write(0);
        } else {
            if (wr_en.read() && !full.read()) {
                mem[wptr] = din.read();
                wptr = (wptr + 1) % 16;
                count++;
            }
            if (rd_en.read() && !empty.read()) {
                dout.write(mem[rptr]);
                rptr = (rptr + 1) % 16;
                count--;
            }
            empty.write(count == 0);
            full.write(count == 16);
        }
    }

    SC_CTOR(FIFO)
    {
        SC_METHOD(fifo_process);
        sensitive << clk.pos();
    }
};
