#include "reg.h"
#include "testbench_reg.h"

int sc_main(int argc, char* argv[]){
	sc_signal<bool> input,rst;
	sc_signal<sc_uint<4>> output;
	sc_clock clk("clk", 10, SC_NS, 0.5, 0, SC_NS, true);
	REG reg("reg");
	TESTBENCH_REG tb("tb");

	reg.input(input);reg.clk(clk);reg.rst(rst);reg.output(output);
	tb.input(input);tb.rst(rst);tb.output(output);
	sc_start();
	return 0;
}