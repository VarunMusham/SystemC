#include <systemc.h>

SC_MODULE(TESTBENCH_RCA){
	sc_out<bool> a0,a1,a2,a3;
	sc_out<bool> b0,b1,b2,b3;
	sc_out<bool> cin;

	sc_in<bool> o0,o1,o2,o3,cout;

	void run(){
		for (int a=0;a<16;a++){
			a0.write((a>>0)&1);
			a1.write((a>>1)&1);
			a2.write((a>>2)&1);
			a3.write((a>>3)&1);
			for (int b=0;b<16;b++){
				b0.write((b>>0)&1);
				b1.write((b>>1)&1);
				b2.write((b>>2)&1);
				b3.write((b>>3)&1);
				for (int c=0;c<2;c++){
					cin.write((c>>0)&1);
					wait(10,SC_NS);
					std::cout<<"a: "<<a0.read()<<a1.read()<<a2.read()<<a3.read()<<" b: "<<b0.read()<<b1.read()<<b2.read()<<b3.read()<<" cin: "<<cin.read()<<" o: "<<o0.read()<<o1.read()<<o2.read()<<o3.read()<<" cout: "<<cout.read()<<std::endl;
				}
			}
		}
		sc_stop();
	}
	SC_CTOR(TESTBENCH_RCA){
		SC_THREAD(run);
	}
};