#include "rca.h"
#include "testbench_rca.h"

int sc_main(int argc, char* argv[]){
	sc_signal<bool> a0,a1,a2,a3;
	sc_signal<bool> b0,b1,b2,b3;
	sc_signal<bool> cin;

	sc_signal<bool> o0,o1,o2,o3,cout;
	
	RCA rca("rca");
	TESTBENCH_RCA tb("tb");
	
	rca.a0(a0);rca.a1(a1);rca.a2(a2);rca.a3(a3);
	rca.b0(b0);rca.b1(b1);rca.b2(b2);rca.b3(b3);
	rca.cin(cin);
	rca.o0(o0);rca.o1(o1);rca.o2(o2);rca.o3(o3);
	rca.cout(cout);

	tb.a0(a0);tb.a1(a1);tb.a2(a2);tb.a3(a3);
	tb.b0(b0);tb.b1(b1);tb.b2(b2);tb.b3(b3);
	tb.cin(cin);
	tb.o0(o0);tb.o1(o1);tb.o2(o2);tb.o3(o3);
	tb.cout(cout);

	sc_start();

	return 0;
}