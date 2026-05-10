#include "testbench_fsm.h"
#include "fsm.h"

int sc_main(int argc, char* argv[]){
	sc_signal<bool> red,yellow,green,rst;
	sc_clock clk("clk", 10, SC_NS, 0.5, 0, SC_NS, true);

	FSM f1("f1");
	f1.red(red);f1.yellow(yellow);f1.green(green);f1.rst(rst);f1.clk(clk);
	
	TESTBENCH_FSM tb("tb");
	tb.red(red);tb.yellow(yellow);tb.green(green);tb.rst(rst);
	
	sc_start();
	return 0;
}