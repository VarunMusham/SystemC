#include<systemc.h>

SC_MODULE(Testbench){
    sc_out<bool> a,b;
    sc_in<bool> sum, carry;

    void run(){
        a.write(0);b.write(0);wait(10, SC_NS);
        std::cout << "A: " << a.read() << " B: " << b.read() << " Sum: " << sum.read() << " Carry: " << carry.read() << std::endl;
        a.write(0);b.write(1);wait(10, SC_NS);
        std::cout << "A: " << a.read() << " B: " << b.read() << " Sum: " << sum.read() << " Carry: " << carry.read() << std::endl;
        a.write(1);b.write(0);wait(10, SC_NS);
        std::cout << "A: " << a.read() << " B: " << b.read() << " Sum: " << sum.read() << " Carry: " << carry.read() << std::endl;
        a.write(1);b.write(1);wait(10, SC_NS);
        std::cout << "A: " << a.read() << " B: " << b.read() << " Sum: " << sum.read() << " Carry: " << carry.read() << std::endl;
        sc_stop();
    }
    SC_CTOR(Testbench){
        SC_THREAD(run);
    }   
};