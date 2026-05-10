#include "fulladder.h"
#include "testbench_fa.h"

int sc_main(int argc, char* argv[]){
    sc_signal<bool> a,b,cin,sum,cout;

    TestbenchFA tb("tb");
    FullAdder fa("fa");

    tb.a(a);tb.b(b);tb.cin(cin);tb.sum(sum);tb.cout(cout);
    fa.a(a);fa.b(b);fa.cin(cin);fa.sum(sum);fa.cout(cout);

    sc_start();
    return 0;
}