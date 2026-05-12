#include <systemc.h>
#include "axi_stream_master.h"
#include "axi_stream_slave.h"
#include "axi_stream_interconnect.h"

SC_MODULE(BasicExample) {
    sc_clock clk{"clk", 10, SC_NS};
    sc_signal<bool> reset_n;
    
    AXIStreamMaster* master;
    AXIStreamSlave* slave;
    AXIStreamInterconnect* interconnect;
    
    SC_CTOR(BasicExample) {
        master = new AXIStreamMaster("master");
        slave = new AXIStreamSlave("slave");
        interconnect = new AXIStreamInterconnect("interconnect");
        
        master->clk(clk);
        master->reset_n(reset_n);
        master->stream_socket(interconnect->master_port);
        
        interconnect->slave_port(slave->stream_socket);
        
        slave->clk(clk);
        slave->reset_n(reset_n);
        
        SC_THREAD(run);
    }
    
    void run() {
        reset_n.write(false);
        wait(20, SC_NS);
        reset_n.write(true);
        wait(50, SC_NS);
        
        AXIStreamPayload payload(64);
        payload.data[0] = 0x12;
        payload.data[1] = 0x34;
        payload.data[2] = 0x56;
        payload.data[3] = 0x78;
        
        master->send_stream_transaction(payload, false);
        wait(10, SC_NS);
        
        std::cout << "@" << sc_time_stamp() << " Master sent transaction" << std::endl;
        std::cout << "Data bytes: 0x12 0x34 0x56 0x78" << std::endl;
        
        if (slave->has_received_transaction()) {
            std::cout << "Slave received: SUCCESS" << std::endl;
        }
        
        wait(20, SC_NS);
        sc_stop();
    }
};

int sc_main(int argc, char* argv[]) {
    BasicExample basic("basic_example");
    
    std::cout << "Starting AXI4-Stream Basic Example" << std::endl;
    sc_start();
    std::cout << "Simulation ended" << std::endl;
    
    return 0;
}
