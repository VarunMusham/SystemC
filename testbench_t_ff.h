#include<systemc.h>

SC_MODULE(TESTBENCH_T_FF){
	sc_out<bool> t,rst;
	sc_in<bool> out;

	void run(){
		rst.write(1);wait(10,SC_NS);
		rst.write(0);wait(10,SC_NS);

		for (int i=0;i<10;i++){
			t.write(i%2);wait(10,SC_NS);
			std::cout<<"@"<<sc_time_stamp()<<" T: "<<t<<" out: "<<out<<endl;
		}
	sc_stop();
	}
	
	SC_CTOR(TESTBENCH_T_FF){
		SC_THREAD(run);
	}
};