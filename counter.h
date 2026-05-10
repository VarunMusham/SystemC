#include "t_ff.h"

SC_MODULE(COUNTER){
	sc_in<bool> start,clk,rst;
	sc_out<sc_uint<2>> output;
	sc_inout<bool> tin;
	
	sc_signal<bool> o1,o2;

	T_FF t1,t2;

	void assign_output(){
		//tin.write(1);
		sc_uint<2> temp;
		temp[0]=o1;
		temp[1]=o2;
		if (start)
			output.write(temp);
	}

	SC_CTOR(COUNTER):
	t1("t1"),t2("t2"){
		t1.t(tin);t1.rst(rst);t1.clk(clk);t1.out(o1);
		t2.t(tin);t2.rst(rst);t2.clk(o1);t2.out(o2);

		SC_METHOD(assign_output);
		sensitive<<clk;
	}
};