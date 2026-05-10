#include <systemc.h>
#include "mux.h"

SC_MODULE(MUX_4X1){
	sc_in<bool> a,b,c,d,s1,s2;
	sc_out<bool> out;

	sc_signal<bool> o1,o2;
	
	mux m1,m2,m3;
	
	SC_CTOR(MUX_4X1):
		m1("l11"),
		m2("l12"),
		m3("l2"){
		m1.a(a);m1.b(b);m1.sel(s2);m1.y(o1);
		m2.a(c);m2.b(d);m2.sel(s2);m2.y(o2);
		m3.a(o1);m3.b(o2);m3.sel(s1);m3.y(out);
}	
};