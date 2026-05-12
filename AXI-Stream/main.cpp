#include <systemc.h>
#include "axi_stream.h"

class TestBench : public sc_module {
public:
    sc_clock clk{"clk", 10, SC_NS};
    sc_signal<bool> reset;
    
    AXIMaster* master;
    AXISlave* slave;
    
    SC_CTOR(TestBench) {
        master = new AXIMaster("master");
        slave = new AXISlave("slave");
        
        master->clk(clk);
        master->reset(reset);
        master->out(slave->in);
        
        slave->clk(clk);
        slave->reset(reset);
        
        SC_THREAD(run);
    }
    
    void run() {
        reset.write(1);
        wait(20, SC_NS);
        reset.write(0);
        wait(20, SC_NS);
        
        std::cout << "Sending data..." << std::endl;
        
        AXIPayload pkt1(64);
        pkt1.data[0] = 0x12;
        pkt1.data[1] = 0x34;
        pkt1.last = false;
        master->send(pkt1);
        
        wait(10, SC_NS);
        
        AXIPayload pkt2(64);
        pkt2.data[0] = 0x56;
        pkt2.data[1] = 0x78;
        pkt2.last = true;
        master->send(pkt2);
        
        wait(10, SC_NS);
        
        std::cout << "Received " << slave->count << " packets" << std::endl;
        std::cout << "Test PASSED" << std::endl;
        
        sc_stop();
    }
};

int sc_main(int argc, char* argv[]) {
    TestBench tb("tb");
    sc_start();
    return 0;
}
