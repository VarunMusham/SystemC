#include "testbench_counter.h"
#include "counter.h"

int sc_main(int argc, char* argv[]){
	
	sc_signal<bool> rst,start,tin;
	sc_signal<sc_uint<2>> output;
	sc_clock clk("clk", 10, SC_NS, 0.5, 0, SC_NS, true);

	COUNTER c1("c1");
	c1.clk(clk);c1.rst(rst);c1.start(start);c1.output(output);c1.tin(tin);
	
	TESTBENCH_COUNTER tb("tb");
	tb.rst(rst);tb.start(start);tb.output(output);tb.tin(tin);

	sc_start();
	
	return 0;
}