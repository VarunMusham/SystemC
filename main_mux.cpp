#include "testbench_mux.cpp"
#include "mux.h"

int sc_main(int argc, char* argv[])
{
	sc_signal<bool> a,b,sel,y;
	
	mux m1("my_mux");
	TESTBENCH_MUX tb("test");
	
	m1.a(a);m1.b(b);m1.sel(sel);m1.y(y);
	
	tb.a(a);tb.b(b);tb.sel(sel);tb.y(y);
	
	sc_start();

	return 0;
}