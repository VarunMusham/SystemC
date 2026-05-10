#include <systemc.h>

SC_MODULE(TESTBENCH_COUNTER){
	sc_out<bool> start,rst,tin;
	sc_in<sc_uint<2>> output;

	void run(){
		tin.write(1);
		start.write(0); rst.write(1);wait(10,SC_NS);
		start.write(1); rst.write(1);wait(10,SC_NS);
		for (int i=0;i<10;i++){
			start.write(1); rst.write(0);wait(10,SC_NS);
		
			std::cout<<"@ "<<sc_time_stamp()<<" output = "<<output<<" t "<<tin<<std::endl;
		}
		sc_stop();
	}

	SC_CTOR(TESTBENCH_COUNTER){
		SC_THREAD(run);
	}
};