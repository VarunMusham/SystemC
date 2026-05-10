#include<systemc.h>

SC_MODULE(T_FF){
	sc_in<bool> t,clk,rst;
	sc_out<bool> out;

	void toggle(){
		if (rst.read())
			out.write(0);
		else if (t.read())
			out.write(!(out.read()));
	}
	
	SC_CTOR(T_FF){
		SC_METHOD(toggle);
		sensitive<<clk.pos();
	}
};