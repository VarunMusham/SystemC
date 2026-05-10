#include <systemc.h>

SC_MODULE(mux){
	sc_in<bool> a,b,sel;
	sc_out<bool> y;
	
	void compute(){
		y.write(sel.read()?b.read():a.read());
	}
	
	SC_CTOR(mux){
		SC_METHOD(compute);
		sensitive<<a<<b<<sel;
	}
};