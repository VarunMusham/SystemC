#include <systemc.h>

SC_MODULE(TESTBENCH_FSM){
	sc_out<bool> rst;
	sc_in<bool> red, yellow, green;

	void run(){
		rst.write(1); wait(10,SC_NS);
		for (int i=0;i<10;i++){
			rst.write(0); wait(10,SC_NS);
			std::cout<<"@"<<sc_time_stamp()<<" Red: "<<red<<" YELLOW: "<<yellow<<" GREEN: "<<green<<std::endl;
		}
		sc_stop();
	}

	SC_CTOR(TESTBENCH_FSM){
		SC_THREAD(run);
	}
};