#ifndef AXI_STREAM_SLAVE_H
#define AXI_STREAM_SLAVE_H

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_target_socket.h>
#include "axi_stream_types.h"

class AXIStreamSlave : public sc_module {
public:
    tlm_utils::simple_target_socket<AXIStreamSlave, 32> stream_socket;
    
    sc_in<bool> clk;
    sc_in<bool> reset_n;
    
    AXIStreamSlave(sc_module_name name) 
        : sc_module(name), stream_socket("stream_socket"),
          total_transactions(0), last_transaction_received(false) {
        
        stream_socket.register_b_transport(this, &AXIStreamSlave::b_transport);
    }
    
    void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay) {
        if (trans.is_write()) {
            unsigned char* data = trans.get_data_ptr();
            unsigned int length = trans.get_data_length();
            
            if (data != NULL && length > 0) {
                last_received_data.clear();
                last_received_data.insert(last_received_data.end(), data, data + length);
            }
            
            AXIStreamExtension* ext = NULL;
            trans.get_extension(ext);
            
            if (ext != NULL) {
                last_is_last = ext->last;
                last_keep = ext->keep;
            } else {
                last_is_last = false;
                last_keep = true;
            }
            
            total_transactions++;
            last_transaction_received = true;
        }
        
        trans.set_response_status(tlm::TLM_OK_RESPONSE);
        delay = SC_ZERO_TIME;
    }
    
    std::vector<unsigned char> get_last_data() const {
        return last_received_data;
    }
    
    bool get_last_flag() const {
        return last_is_last;
    }
    
    bool get_keep_flag() const {
        return last_keep;
    }
    
    unsigned int get_transaction_count() const {
        return total_transactions;
    }
    
    bool has_received_transaction() const {
        return last_transaction_received;
    }
    
private:
    std::vector<unsigned char> last_received_data;
    bool last_is_last;
    bool last_keep;
    unsigned int total_transactions;
    bool last_transaction_received;
};

#endif
