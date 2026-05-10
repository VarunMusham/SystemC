#include <systemc.h>

SC_MODULE(TESTBENCH_MUX){
	sc_out<bool> a,b,sel;
	sc_in<bool> y;

	void run(){
		sel.write(0);
		a.write(0);b.write(0);wait(10,SC_NS);
		std::cout<<"sel: "<<sel.read()<<" a: "<<a.read()<<" b: "<<b.read()<<" y: "<<y.read()<<std::endl;
		a.write(0);b.write(1);wait(10,SC_NS);
		std::cout<<"sel: "<<sel.read()<<" a: "<<a.read()<<" b: "<<b.read()<<" y: "<<y.read()<<std::endl;
		a.write(1);b.write(0);wait(10,SC_NS);
		std::cout<<"sel: "<<sel.read()<<" a: "<<a.read()<<" b: "<<b.read()<<" y: "<<y.read()<<std::endl;
		a.write(1);b.write(1);wait(10,SC_NS);
		std::cout<<"sel: "<<sel.read()<<" a: "<<a.read()<<" b: "<<b.read()<<" y: "<<y.read()<<std::endl;

		sel.write(1);
		a.write(0);b.write(0);wait(10,SC_NS);
		std::cout<<"sel: "<<sel.read()<<" a: "<<a.read()<<" b: "<<b.read()<<" y: "<<y.read()<<std::endl;
		a.write(0);b.write(1);wait(10,SC_NS);
		std::cout<<"sel: "<<sel.read()<<" a: "<<a.read()<<" b: "<<b.read()<<" y: "<<y.read()<<std::endl;
		a.write(1);b.write(0);wait(10,SC_NS);
		std::cout<<"sel: "<<sel.read()<<" a: "<<a.read()<<" b: "<<b.read()<<" y: "<<y.read()<<std::endl;
		a.write(1);b.write(1);wait(10,SC_NS);
		std::cout<<"sel: "<<sel.read()<<" a: "<<a.read()<<" b: "<<b.read()<<" y: "<<y.read()<<std::endl;

		sc_stop();
	}

	SC_CTOR(TESTBENCH_MUX){
		SC_THREAD(run);
	}
};