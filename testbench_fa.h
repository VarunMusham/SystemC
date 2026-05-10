#include <systemc.h>

SC_MODULE(TestbenchFA){
    sc_out<bool> a,b,cin;
    sc_in<bool> sum, cout;

    void run(){
        a.write(0);b.write(0);cin.write(0);wait(10, SC_NS);
        std::cout << "A: " << a.read() << " B: " << b.read() << " Cin: " << cin.read() << " Sum: " << sum.read() << " Cout: " << cout.read() << std::endl;
        a.write(0);b.write(0);cin.write(1);wait(10, SC_NS);
        std::cout << "A: " << a.read() << " B: " << b.read() << " Cin: " << cin.read() << " Sum: " << sum.read() << " Cout: " << cout.read() << std::endl;
        a.write(0);b.write(1);cin.write(0);wait(10, SC_NS);
        std::cout << "A: " << a.read() << " B: " << b.read() << " Cin: " << cin.read() << " Sum: " << sum.read() << " Cout: " << cout.read() << std::endl;
        a.write(0);b.write(1);cin.write(1);wait(10, SC_NS);
        std::cout << "A: " << a.read() << " B: " << b.read() << " Cin: " << cin.read() << " Sum: " << sum.read() << " Cout: " << cout.read() << std::endl;
        a.write(1);b.write(0);cin.write(0);wait(10, SC_NS);
        std::cout << "A: " << a.read() << " B: " << b.read() << " Cin: " << cin.read() << " Sum: " << sum.read() << " Cout: " << cout.read() << std::endl;
        a.write(1);b.write(0);cin.write(1);wait(10, SC_NS);
        std::cout << "A: " << a.read() << " B: " << b.read() << " Cin: " << cin.read() << " Sum: " << sum.read() << " Cout: " << cout.read() << std::endl;
        a.write(1);b.write(1);cin.write(0);wait(10, SC_NS);
        std::cout << "A: " << a.read() << " B: " << b.read() << " Cin: " << cin.read() << " Sum: " << sum.read() << " Cout: " << cout.read() << std::endl;
        a.write(1);b.write(1);cin.write(1);wait(10, SC_NS);
        std::cout << "A: " << a.read() << " B: " << b.read() << " Cin: " << cin.read() << " Sum: " << sum.read() << " Cout: " << cout.read() << std::endl;      
        sc_stop();
    }
    SC_CTOR(TestbenchFA){
        SC_THREAD(run);
    }
};