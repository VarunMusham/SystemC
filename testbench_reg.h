#include <systemc.h>

SC_MODULE(TESTBENCH_REG){
	sc_out<bool> input,rst;
	sc_in<sc_uint<4>> output;
	// sc_clock clk;
	
	void run(){
		rst.write(1);wait(10,SC_NS);
		rst.write(0);wait(10,SC_NS);
		for (int i=0;i<10;i++){
			input.write(i%2);
			wait(10,SC_NS);
			std::cout<< "@" << sc_time_stamp()<<"output: "<<output.read()<<std::endl;
		}
		sc_stop();
	}
	
	
	SC_CTOR(TESTBENCH_REG)
	// : clk("clk", 10, SC_NS, 0.5, 0, SC_NS, true) // initializer list
	{
		SC_THREAD(run);
		// SC_THREAD(clk_gen);
	}
};