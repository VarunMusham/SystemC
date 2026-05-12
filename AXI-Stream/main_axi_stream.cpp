#include <systemc.h>
#include <iomanip>
#include "axi_stream_master.h"
#include "axi_stream_slave.h"
#include "simple_data_generator.h"
#include "axi_stream_interconnect.h"

class AXIStreamTestbench {
public:
    static void print_data(const std::string& label, const std::vector<unsigned char>& data) {
        std::cout << label;
        for (unsigned char byte : data) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') 
                     << (unsigned int)byte << " ";
        }
        std::cout << std::dec << std::endl;
    }
    
    static void print_transaction_info(unsigned int trans_num, 
                                      const std::vector<unsigned char>& data, 
                                      bool is_last, bool keep) {
        std::cout << "\n--- Transaction " << trans_num << " ---" << std::endl;
        print_data("Data: 0x", data);
        std::cout << "LAST: " << (is_last ? "Yes" : "No") << std::endl;
        std::cout << "KEEP: " << (keep ? "Yes" : "No") << std::endl;
    }
};

SC_MODULE(DemoTestbench) {
    sc_clock clk{"clk", 10, SC_NS, 0.5, 0, SC_NS, true};
    sc_signal<bool> reset_n;
    
    SimpleDataGenerator* generator;
    AXIStreamSlave* receiver;
    AXIStreamInterconnect* interconnect;
    
    SC_CTOR(DemoTestbench) {
        generator = new SimpleDataGenerator("generator", 64);
        receiver = new AXIStreamSlave("receiver");
        interconnect = new AXIStreamInterconnect("interconnect");
        
        generator->clk(clk);
        generator->reset_n(reset_n);
        generator->stream_socket(interconnect->master_port);
        
        interconnect->slave_port(receiver->stream_socket);
        
        receiver->clk(clk);
        receiver->reset_n(reset_n);
        
        SC_THREAD(testbench_process);
    }
    
    void testbench_process() {
        reset_n.write(false);
        wait(20, SC_NS);
        reset_n.write(true);
        wait(200, SC_NS);
        
        std::cout << "\n===== AXI4-Stream Transmission Log =====" << std::endl;
        
        wait(200, SC_NS);
        
        if (receiver->has_received_transaction()) {
            std::cout << "\nTotal Transactions Received: " 
                     << receiver->get_transaction_count() << std::endl;
        }
        
        sc_stop();
    }
};

int sc_main(int argc, char* argv[]) {
    DemoTestbench tb("testbench");
    
    std::cout << "\n=== AXI4-Stream TLM LT Simulation ===" << std::endl;
    std::cout << "Data Width: 64 bits" << std::endl;
    std::cout << "Clock Period: 10 ns" << std::endl;
    std::cout << "================================\n" << std::endl;
    
    sc_start();
    
    std::cout << "\n=== Simulation Complete ===" << std::endl;
    
    return 0;
}
