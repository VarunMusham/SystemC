#ifndef AXI_STREAM_INTERCONNECT_H
#define AXI_STREAM_INTERCONNECT_H

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

class AXIStreamInterconnect : public sc_module {
public:
    tlm_utils::simple_target_socket<AXIStreamInterconnect, 32> master_port;
    tlm_utils::simple_initiator_socket<AXIStreamInterconnect, 32> slave_port;
    
    AXIStreamInterconnect(sc_module_name name) 
        : sc_module(name), master_port("master_port"), slave_port("slave_port") {
        master_port.register_b_transport(this, &AXIStreamInterconnect::b_transport);
    }
    
    void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay) {
        slave_port->b_transport(trans, delay);
    }
};

#endif
