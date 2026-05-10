#include <systemc.h>

SC_MODULE(TESTBENCH_MUX_4X1){
	sc_out<bool> a,b,c,d,s1,s2;
	sc_in<bool> out;
	
	void run(){
		for (int data=0;data<16;data++){
			a.write((data>>3)&1);
			b.write((data>>2)&1);
			c.write((data>>1)&1);
			d.write((data>>0)&1);
			
			for (int sel=0;sel<4;sel++){
				s1.write((sel>>1)&1);
				s2.write((sel>>0)&1);
				wait(10,SC_NS);
				std::cout<<"s1: "<<s1.read()<<" s2: "<<s2.read()<<" a: "<<a.read()<<" b: "<<b.read()<<" c: "<<c.read()<<" d: "<<d.read()<<" out: "<<out.read()<<std::endl;
			}
		}
		sc_stop();
	}
	SC_CTOR(TESTBENCH_MUX_4X1){
		SC_THREAD(run);
	}	
};