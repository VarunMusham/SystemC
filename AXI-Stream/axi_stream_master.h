#ifndef AXI_STREAM_MASTER_H
#define AXI_STREAM_MASTER_H

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/tlm_quantumkeeper.h>
#include "axi_stream_types.h"
#include <tlm_utils/simple_initiator_socket.h>

class AXIStreamMaster : public sc_module {
public:
    tlm_utils::simple_initiator_socket<AXIStreamMaster, 32> stream_socket;
    
    sc_in<bool> clk;
    sc_in<bool> reset_n;
    
    AXIStreamMaster(sc_module_name name) 
        : sc_module(name), stream_socket("stream_socket"), quantum() {
        SC_HAS_PROCESS(AXIStreamMaster); SC_THREAD(send_data);
        sensitive << clk.pos();
    }
    
    void send_stream_transaction(const AXIStreamPayload& payload, bool is_last) {
        tlm::tlm_generic_payload trans;
        
        unsigned char* data_ptr = new unsigned char[payload.data.size()];
        std::copy(payload.data.begin(), payload.data.end(), data_ptr);
        
        trans.set_write();
        trans.set_address(0);
        trans.set_data_ptr(data_ptr);
        trans.set_data_length(payload.data.size());
        trans.set_streaming_width(payload.data.size());
        
        AXIStreamExtension* ext = new AXIStreamExtension();
        ext->last = is_last;
        ext->keep = payload.keep;
        trans.set_extension(ext);
        
        sc_time delay = SC_ZERO_TIME;
        stream_socket->b_transport(trans, delay);
        
        wait(delay);
        
        delete[] data_ptr;
    }
    
    virtual void send_data() {
        wait();
    }
    
protected:
    tlm_utils::tlm_quantumkeeper quantum;
};

#endif
