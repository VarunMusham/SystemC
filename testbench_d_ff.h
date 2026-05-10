#include <systemc.h>

SC_MODULE(TESTBENCH_D_FF){
	sc_out<bool> d,clk,rst;
	sc_in<bool> out;

	void run(){
		d.write(0);
		rst.write(1);
		wait(10,SC_NS);
		d.write(0);
		rst.write(0);
		wait(10,SC_NS);
	
		for (int i=0;i<5;i++){
			d.write(i%2);
			wait(10,SC_NS);
            		std::cout << "@" << sc_time_stamp() << " D=" << d.read()<< " Q=" << out.read()<< " rst=" << rst.read() << endl;
		}
		sc_stop();
	}

	void clk_gen(){
	   while(true){
		clk.write(0);
		wait(3,SC_NS);
		clk.write(1);
		wait(3,SC_NS);
	  }
	}

	SC_CTOR(TESTBENCH_D_FF){
		SC_THREAD(run);
		SC_THREAD(clk_gen);
	}
};