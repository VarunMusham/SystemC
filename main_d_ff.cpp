#include "d_ff.h"
#include "testbench_d_ff.h"

int sc_main(int argc, char* argv[]){
	sc_signal<bool> d,clk,rst,out;
	D_FF d_ff("d_ff");
	TESTBENCH_D_FF tb("tb");

	d_ff.d(d);d_ff.clk(clk);d_ff.rst(rst);d_ff.out(out);
	tb.d(d);tb.clk(clk);tb.rst(rst);tb.out(out);
	sc_start();
	return 0;
}