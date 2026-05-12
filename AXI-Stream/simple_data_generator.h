#ifndef SIMPLE_DATA_GENERATOR_H
#define SIMPLE_DATA_GENERATOR_H

#include <systemc.h>
#include "axi_stream_master.h"

class SimpleDataGenerator : public AXIStreamMaster {
public:
    SimpleDataGenerator(sc_module_name name, unsigned int data_width = 64)
        : AXIStreamMaster(name), WIDTH(data_width), counter(0) {}
    
    void set_data(const std::vector<unsigned char>& data_sequence) {
        data_queue = data_sequence;
        counter = 0;
    }
    
protected:
    void send_data() {
        wait();
        wait();
        
        if (data_queue.empty()) {
            for (unsigned int i = 0; i < 8; i++) {
                AXIStreamPayload payload(WIDTH);
                for (unsigned int j = 0; j < payload.data.size(); j++) {
                    payload.data[j] = (i * 10 + j) & 0xFF;
                }
                bool is_last = (i == 7);
                send_stream_transaction(payload, is_last);
                wait();
            }
        } else {
            for (unsigned int i = 0; i < data_queue.size(); i++) {
                AXIStreamPayload payload(WIDTH);
                payload.data[0] = data_queue[i];
                bool is_last = (i == (data_queue.size() - 1));
                send_stream_transaction(payload, is_last);
                wait();
            }
        }
        
        sc_stop();
    }
    
private:
    unsigned int WIDTH;
    unsigned int counter;
    std::vector<unsigned char> data_queue;
};

#endif
