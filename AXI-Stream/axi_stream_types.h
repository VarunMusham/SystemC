#ifndef AXI_STREAM_TYPES_H
#define AXI_STREAM_TYPES_H

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/tlm_quantumkeeper.h>
#include <vector>

struct AXIStreamPayload {
    std::vector<unsigned char> data;
    unsigned int data_width;
    bool last;
    bool keep;
    
    AXIStreamPayload(unsigned int width = 64) : data_width(width), last(false), keep(true) {
        data.resize(width / 8, 0);
    }
    
    void reset() {
        std::fill(data.begin(), data.end(), 0);
        last = false;
        keep = true;
    }
};

struct AXIStreamExtension : public tlm::tlm_extension<AXIStreamExtension> {
    bool last;
    bool keep;
    
    AXIStreamExtension() : last(false), keep(true) {}
    
    virtual tlm::tlm_extension_base* clone() const {
        AXIStreamExtension* ext = new AXIStreamExtension();
        ext->last = this->last;
        ext->keep = this->keep;
        return ext;
    }
    
    virtual void copy_from(const tlm::tlm_extension_base& from) {
        const AXIStreamExtension& ext = dynamic_cast<const AXIStreamExtension&>(from);
        this->last = ext.last;
        this->keep = ext.keep;
    }
};

#endif
