#include <systemc.h>
#include <iomanip>
#include "axi_stream_master.h"
#include "axi_stream_slave.h"
#include "axi_stream_interconnect.h"

SC_MODULE(AdvancedExample) {
    sc_clock clk{"clk", 10, SC_NS};
    sc_signal<bool> reset_n;
    
    AXIStreamMaster* master;
    AXIStreamSlave* slave;
    AXIStreamInterconnect* interconnect;
    
    SC_CTOR(AdvancedExample) {
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
    
    void print_transaction(unsigned int num, 
                          const std::vector<unsigned char>& data,
                          bool is_last) {
        std::cout << "\nTransaction #" << num << std::endl;
        std::cout << "Data (hex): ";
        for (unsigned int i = 0; i < std::min((size_t)4, data.size()); i++) {
            std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0')
                     << (unsigned int)data[i] << " ";
        }
        std::cout << std::dec << std::endl;
        std::cout << "LAST flag: " << (is_last ? "YES" : "NO") << std::endl;
    }
    
    void run() {
        reset_n.write(false);
        wait(20, SC_NS);
        reset_n.write(true);
        wait(50, SC_NS);
        
        std::cout << "\n===== AXI4-Stream Advanced Example =====" << std::endl;
        std::cout << "Sending 5 transactions..." << std::endl;
        
        for (int i = 0; i < 5; i++) {
            AXIStreamPayload payload(64);
            
            for (unsigned int j = 0; j < 4; j++) {
                payload.data[j] = (i * 0x11 + j * 0x22) & 0xFF;
            }
            
            bool is_last = (i == 4);
            
            master->send_stream_transaction(payload, is_last);
            wait(10, SC_NS);
            
            print_transaction(i, slave->get_last_data(), slave->get_last_flag());
        }
        
        wait(20, SC_NS);
        
        std::cout << "\n===== Summary =====" << std::endl;
        std::cout << "Total transactions sent: 5" << std::endl;
        std::cout << "Total transactions received: " 
                 << slave->get_transaction_count() << std::endl;
        std::cout << "Status: " << (slave->get_transaction_count() == 5 
                                     ? "SUCCESS" : "FAILED") << std::endl;
        
        sc_stop();
    }
};

int sc_main(int argc, char* argv[]) {
    AdvancedExample advanced("advanced_example");
    
    std::cout << "\n=== AXI4-Stream TLM LT - Advanced Example ===" << std::endl;
    std::cout << "Clock: 10 ns | Data Width: 64 bits" << std::endl;
    
    sc_start();
    
    std::cout << "\n=== Simulation Finished ===" << std::endl;
    
    return 0;
}
