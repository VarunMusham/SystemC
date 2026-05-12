#ifndef AXI_STREAM_H
#define AXI_STREAM_H

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>
#include <vector>

struct AXIPayload {
    std::vector<unsigned char> data;
    bool last;
    
    AXIPayload(int size = 64) : data(size/8, 0), last(false) {}
};

class AXIMaster : public sc_module {
public:
    tlm_utils::simple_initiator_socket<AXIMaster, 32> out;
    sc_in<bool> clk;
    sc_in<bool> reset;
    
    SC_HAS_PROCESS(AXIMaster);
    AXIMaster(sc_module_name name) : sc_module(name), out("out") {
        SC_THREAD(run);
    }
    
    void send(const AXIPayload& pkt) {
        tlm::tlm_generic_payload trans;
        trans.set_write();
        trans.set_data_ptr(const_cast<unsigned char*>(pkt.data.data()));
        trans.set_data_length(pkt.data.size());
        
        sc_time delay = SC_ZERO_TIME;
        out->b_transport(trans, delay);
    }
    
    virtual void run() { wait(); }
};

class AXISlave : public sc_module {
public:
    tlm_utils::simple_target_socket<AXISlave, 32> in;
    sc_in<bool> clk;
    sc_in<bool> reset;
    
    int count;
    
    AXISlave(sc_module_name name) : sc_module(name), in("in"), count(0) {
        in.register_b_transport(this, &AXISlave::receive);
    }
    
    void receive(tlm::tlm_generic_payload& trans, sc_time& delay) {
        count++;
        trans.set_response_status(tlm::TLM_OK_RESPONSE);
        delay = SC_ZERO_TIME;
    }
};

#endif
