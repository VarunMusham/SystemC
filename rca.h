#include <systemc.h>
#include "fulladder.h"

SC_MODULE(RCA){
	sc_in<bool> a0,a1,a2,a3;
	sc_in<bool> b0,b1,b2,b3;
	sc_in<bool> cin;

	sc_out<bool> o0,o1,o2,o3,cout;

	sc_signal<bool> c0,c1,c2;

	FullAdder fa0,fa1,fa2,fa3;
	
	SC_CTOR (RCA):
		fa1("fa1"),
		fa2("fa2"),
		fa3("fa3"),
		fa0("fa0")
	{
		fa0.a(a0);fa0.b(b0);fa0.cin(cin);fa0.sum(o0);fa0.cout(c0);
		fa1.a(a1);fa1.b(b1);fa1.cin(c0);fa1.sum(o1);fa1.cout(c1);
		fa2.a(a2);fa2.b(b2);fa2.cin(c1);fa2.sum(o2);fa2.cout(c2);
		fa3.a(a3);fa3.b(b3);fa3.cin(c2);fa3.sum(o3);fa3.cout(cout);
	}
};