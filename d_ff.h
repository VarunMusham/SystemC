#include <systemc.h>

SC_MODULE(D_FF){
	sc_in<bool> d,clk,rst;
	sc_out<bool> out;
	
	void compute(){
		if (rst.read()==1)
			out.write(0);
		else
			out.write(d);
	}
	
	SC_CTOR(D_FF){
		SC_METHOD (compute);
		sensitive<<clk.pos()<<rst;
	}
};