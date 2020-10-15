#include <systemc.h>
#include <string>
#include <vector>

// NB = total number of bits
// NI = number of integer bits
// The notation is Q<NI>.<NB-NI>
// Change to include NF if necessary
#define NB 8
#define NI 1

// People don't recommend 'using namespaces', but this is meant to be minimal
// and used 'as is', no work should derive from this particular code
using namespace std;

// The lowest value a Q<NI>.<NB-NI> signed fixed point can represent
const double const_fx_unit = 1/pow(2,NB-NI);

// Auxiliary functions
template<int nb_t, int ni_t> sc_fixed_fast<nb_t, ni_t> uint2fixedfast(sc_uint<nb_t> uint_num){
    const double const_fx_unit = 1/pow(2,nb_t-ni_t);
    sc_fixed_fast<nb_t, ni_t> fx_fst_num;
    if(uint_num < pow(2,nb_t-1)){
        return uint_num*const_fx_unit;
    }
    else{
        return - (pow(2,NB)-uint_num)*const_fx_unit;
    }
}

template<int nb_t, int ni_t> sc_uint<nb_t> fixedfast2uint(sc_fixed_fast<nb_t, ni_t> fx_fst_num){
    std::string bin_string;
    bin_string = fx_fst_num.to_bin();
    bin_string.replace(2+ni_t,1,"");

    sc_uint<nb_t> uint_num(sc_uint<nb_t>(bin_string.c_str()));
    
    return uint_num;
}

// Make your own operations
// Multiplication:
template<int nb_t, int ni_t> sc_uint<nb_t> mult(sc_uint<nb_t> op1, sc_uint<nb_t> op2){
    sc_fixed_fast<nb_t, ni_t, SC_RND, SC_SAT> op1_fx, op2_fx, ans_fx;
    sc_uint<nb_t> ans_uint;

    op1_fx = uint2fixedfast<nb_t, ni_t>(op1);
    op2_fx = uint2fixedfast<nb_t, ni_t>(op2);

    ans_fx = op1_fx*op2_fx;

    ans_uint = fixedfast2uint<nb_t, ni_t>(ans_fx);
    
    return ans_uint;
}



// Main routine
int sc_main(int argc, char** argv){
    // In signed Q1.7 notation, 64 = 0.5
    // The expected result of a multiplication is
    // 32 = 0.25
    sc_fixed_fast<NB, NI> a_fx = 0.5;
    sc_fixed_fast<NB, NI> x_fx = 0.5;
    sc_uint<NB> a = 64;
    sc_uint<NB> x = 64;
    cout<<"Automatic fixed-point multiplication:\t\t"<<a_fx*x_fx<<endl
        <<"Multiplication with integers as starting points: "<<mult<NB, NI>(a, x)<<endl<<endl;



    // Calculations directly from unsigned integer representation
    cout<<"More operations with integers: "<<endl;

    sc_uint<NB> b = 200, c = 128;
    sc_uint<NB> y = 244, z = 82;
    // Directly
    cout<<"Res. frac.: "<<uint2fixedfast<NB, NI>(mult<NB, NI>(b, y))<<endl
        <<"Res. deci.: "<<mult<NB, NI>(b, y)<<endl<<endl;


    // With intermediary variable
    sc_uint<NB> res;
    res = mult<NB, NI>(c, z);
    cout<<"Res. frac.: "<<uint2fixedfast<NB, NI>(res)<<endl
        <<"Res. deci.: "<<res<<endl;
    
    return 0;
}