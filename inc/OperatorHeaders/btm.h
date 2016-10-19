#ifndef _BTM
#define _BTM

#include <string>
#include <cstring>
#include <iostream>
#include <complex>
#include <vector>

#include "hw_ac.h"
#include "ac_types.h"
#include "sim_config.h"

using namespace std;

// broken array multiplier
class btm : public hw_ac {

private:
    size_t hbl; // the number of bits row nulling
    size_t vbl; // the number of bits column nulling

public:
    // constructor 
    btm();

    btm(size_t Nt, size_t Nia, bool table_gen);

    virtual ~btm();

//void update_energy(int n_apx_b);
void update_energy(int n_apx_b, string a, string b);
virtual int calc(const int &a, const int &b);

virtual int calc(const int &a, const unsigned int &b);
virtual int calc(const unsigned int &a, const int &b);
virtual unsigned int calc(const unsigned int &a, const unsigned int &b);

virtual int calc(const long &a, const int &b);
virtual int calc(const int &a, const long &b);
virtual int calc(const long &a, const long &b);

virtual float calc(const float &number1, const int &number2);
virtual float calc(const int &number1, const float &number2);
virtual float calc(const float &a, const float &b);

virtual double calc(const double &a, const double &b);
virtual double calc(const double &a, const float &b);
virtual double calc(const float &a, const double &b);


virtual int calc_ref(const int &a, const int &b);
    
        virtual size_t get_ianum_bits(void);
size_t get_hbl_bits(void);
    size_t get_vbl_bits(void);

    virtual void tbl_gen();

};

#endif
