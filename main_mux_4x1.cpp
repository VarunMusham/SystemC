#include "mux_4x1.h"
#include "testbench_mux_4x1.h"

int sc_main(int argc, char* argv[]){
	sc_signal<bool> a,b,c,d,s1,s2,out;
	
	MUX_4X1 m1("mux_4x1");
	TESTBENCH_MUX_4X1 t1("tb");

	m1.a(a);m1.b(b);m1.c(c);m1.d(d);m1.s1(s1);m1.s2(s2);m1.out(out);
	t1.a(a);t1.b(b);t1.c(c);t1.d(d);t1.s1(s1);t1.s2(s2);t1.out(out);
	
	sc_start();

	return 0;
}