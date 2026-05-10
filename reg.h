#include "d_ff.h"

SC_MODULE(REG){
	sc_in<bool> input,clk,rst;
	sc_out<sc_uint<4>> output;
	
	sc_signal<bool> t1,t2,t3,t4;
	
	D_FF d1,d2,d3,d4;
	
	void assign_output(){
		sc_uint<4> temp;
		temp[0]=t1;
		temp[1]=t2;
		temp[2]=t3;
		temp[3]=t4;
		
		output.write(temp);	
	}
		
	SC_CTOR(REG):
		 d1("d1"), d2("d2"), d3("d3"), d4("d4"){
			d1.d(input); d1.clk(clk); d1.rst(rst); d1.out(t1);
			d2.d(t1); d2.clk(clk); d2.rst(rst); d2.out(t2);
			d3.d(t2); d3.clk(clk); d3.rst(rst); d3.out(t3);
			d4.d(t3); d4.clk(clk); d4.rst(rst); d4.out(t4);
			SC_METHOD(assign_output);
			sensitive<<t1<<t2<<t3<<t4;
		}
};