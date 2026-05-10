#include "t_ff.h"
#include "testbench_t_ff.h"

int sc_main(int argc, char* argv[]){
	sc_signal<bool> t,rst,out;
	sc_clock clk("clk", 10,SC_NS,0.5,0,SC_NS,true);

	T_FF tf("tf");
	TESTBENCH_T_FF tb("tb");

	tf.t(t);tf.rst(rst);tf.out(out);tf.clk(clk);
	tb.t(t);tb.out(out);tb.rst(rst);

	sc_start();

	return 0;
}