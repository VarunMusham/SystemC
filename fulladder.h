#include "halfadder.h"

SC_MODULE(FullAdder){
    sc_in<bool>a,b,cin;
    sc_out<bool>sum,cout;

    sc_signal<bool> s1,c1,c2;

    HalfAdder ha1,ha2;

    void carry(){
        cout.write(c1.read() | c2.read());
    }
    SC_CTOR(FullAdder):
        ha1("HalfAdder1"),
        ha2("HalfAdder2"){
            ha1.a(a);ha1.b(b);ha1.sum(s1);ha1.carry(c1);
            ha2.a(s1);ha2.b(cin);ha2.sum(sum);ha2.carry(c2);
            SC_METHOD(carry);
            sensitive << c1 << c2;
        }
};