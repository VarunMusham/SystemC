#include "halfadder.h"
#include "testbench.h"

int sc_main(int argc, char* argv[]){
    sc_signal<bool> a,b,sum,carry;

    Testbench tb("tb");
    HalfAdder ha("ha");

    tb.a(a);tb.b(b);tb.sum(sum);tb.carry(carry);
    ha.a(a);ha.b(b);ha.sum(sum);ha.carry(carry);

    sc_start();
    return 0;
}