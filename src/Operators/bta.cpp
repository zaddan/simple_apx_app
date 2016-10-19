#include <iostream>
#include <complex>
#include <vector>
#include "bta.h"
#include "globals.h"
#include "fp_helpers.h"
using namespace std;
#include <cstring>
#include <cassert>
#include <string>
extern int energy_value;


bta::bta(size_t Nt, size_t Nia, size_t msb, size_t lsb, bool table_gen) {
	this->Nt = Nt;
	this->Nia = Nia;
	this->msb = msb;
	this->lsb = lsb;

	if (table_gen) tbl_gen();

}

bta::~bta(void) {}
vector <float> add_long_long_energy_vals  {1.77, 1.7653 ,1.7620 ,1.7585, 1.7495, 1.7448, 1.7369,1.7321 ,1.7278 ,1.7240 ,1.7179,1.7135,1.7092,1.7052,1.6975,1.6945};
vector <float> add_long_int_energy_vals {1.63,1.6204 , 1.6091 , 1.6080 , 1.5979 ,  1.6019, 1.5879,1.5896 ,1.5785 ,1.5811 ,1.5667,1.5715,1.5566,1.5591,1.5450, 1.5469};
vector <float> add_int_int_energy_vals{.894, .8892198 , .8846183 , .8785046 , .8740424 , .8694106 ,  .8630022 ,.8601716 ,.8548939 ,.8502534 ,.8421492, .8393752 ,.8353899 ,.8289224 ,.8231492 ,.8175684};


void bta::update_energy(int n_apx_bits, string op1_type, string op2_type){
    /* 
    if (op1_type == "long" && op2_type == "long") {
        energy_value += add_long_long_energy_vals[n_apx_bits];
    }
    else if (op1_type=="int" && op2_type =="long") {
        energy_value += add_long_int_energy_vals[n_apx_bits];
    }
    else if (op1_type == "long" && op2_type == "int") {
        energy_value += add_long_int_energy_vals[n_apx_bits];
    }
    else if (op1_type == "int" && op2_type== "int") {
        energy_value += add_int_int_energy_vals[n_apx_bits];
    }
    else {
        cout<<"the energy value for this bta types is not defined"<<endl;
        exit(0);
    }
    */ 
    energy_value+= (32 - n_apx_bits) + 10;
}

size_t bta::get_ianum_bits(void) {
	return Nia;
}


double bta::calc(const double &a, const float &b) {
   update_energy(Nia, "float", "double"); 
   double b_out = b;
   calc(a, b_out);
}


double bta::calc(const float &a, const double &b) {
   update_energy(Nia, "float", "double"); 
   double a_out = a;
   calc(b, a_out);
}



int bta::calc(const long &a, const int &b) {
    // inaccurate part
    update_energy(Nia, "long", "int"); 

#ifdef VERBOSE 
    cout<<"=============long int version"<<endl; 
#endif  
    int weight = pow(2, Nia) - 1;
    int iap_a = weight&a;
#ifdef BT_RND
    int a_op = (iap_a >> (Nia - 1)) == 0x1 ? (a >> Nia) + 1 : (a >> Nia);
#else
    int a_op = (a >> Nia);
#endif
    int iap_b = weight&b;
#ifdef BT_RND
    int b_op = (iap_b >> (Nia - 1)) == 0x1 ? (b >> Nia) + 1 : (b >> Nia);
#else
    int b_op = (b >> Nia);
#endif

	return ((a_op) + (b_op)) << Nia;
}


int bta::calc(const long &a, const long &b) {
    // inaccurate part
    update_energy(Nia, "long", "long"); 

#ifdef VERBOSE 
    cout<<"=============long int version"<<endl; 
#endif  
    int weight = pow(2, Nia) - 1;
    int iap_a = weight&a;
#ifdef BT_RND
    int a_op = (iap_a >> (Nia - 1)) == 0x1 ? (a >> Nia) + 1 : (a >> Nia);
#else
    int a_op = (a >> Nia);
#endif
    int iap_b = weight&b;
#ifdef BT_RND
    int b_op = (iap_b >> (Nia - 1)) == 0x1 ? (b >> Nia) + 1 : (b >> Nia);
#else
    int b_op = (b >> Nia);
#endif

	return ((a_op) + (b_op)) << Nia;
}

int bta::calc(const int &a, const long &b) {
    // inaccurate part
    update_energy(Nia, "int", "long"); 
#ifdef VERBOSE 
    cout<<"=============int, long version"<<endl; 
#endif  
    int weight = pow(2, Nia) - 1;
    int iap_a = weight&a;
#ifdef BT_RND
    int a_op = (iap_a >> (Nia - 1)) == 0x1 ? (a >> Nia) + 1 : (a >> Nia);
#else
    int a_op = (a >> Nia);
#endif
    int iap_b = weight&b;
#ifdef BT_RND
    int b_op = (iap_b >> (Nia - 1)) == 0x1 ? (b >> Nia) + 1 : (b >> Nia);
#else
    int b_op = (b >> Nia);
#endif
	return ((a_op) + (b_op)) << Nia;
}




float bta::calc(const float &number1, const int &number2) {
    #ifdef VERBOSE 
    cout<<"=============insde half float"<<endl; 
    #endif 
    float numOut = number2; 
    calc(number1, numOut);
} 

float bta::calc(const int &number1, const float &number2) {
    cout<<"=============insde other half float"<<endl; 
    float numOut = number1; 
    calc(numOut, number2);
} 



float bta::calc(const float &number1, const float &number2) {
    update_energy(Nia, "float", "float"); 
    /*
    FILE* fp;
    fp = fopen("diff_file.txt", "ab+");
    
    if ( num1_inverse_converted+num2_inverse_converted != (number1+number2)){
        float diff_part_1 =  num1_inverse_converted+num2_inverse_converted;
        float diff_part_2 =  number1+number2;
        float diff = (diff_part_1 - diff_part_2);
        
        //--checking for under/over-flow 
        if (std::isinf(diff_part_1)) {
            fprintf(fp, "par_1_overflow\n");
        }
        if (std::isinf(diff_part_2)) {
            fprintf(fp, "par_2_overflow\n");
        }
        if ((diff_part_1 != diff_part_2) && (diff ==0)){
            fprintf(fp, "diff underflow\n");
        }

        fprintf(fp, "error   ");
        if ( diff > 1){
            fprintf(fp, "acc:%f apx: %f diff:%f\n",num1_inverse_converted+num2_inverse_converted ,number1+number2, diff);
        }
        fprintf(fp, "------\n");
    }
    
    fclose(fp);
    */ 
    
    
    /*
    int *num1_ptr = (int *)malloc(sizeof(int));
    memcpy(num1_ptr, &number1, sizeof(num1_ptr));
    int num1_mantisa =  *num1_ptr & ~(0xff800000);
    num1_mantisa = (num1_mantisa >> Nia) <<Nia;
    *num1_ptr &= (0xff800000);
    *num1_ptr |= num1_mantisa;
    
    int *num2_ptr = (int *)malloc(sizeof(int));
    memcpy(num2_ptr, &number2, sizeof(num2_ptr));
    int num2_mantisa =  *num2_ptr & ~(0xff800000);
    num2_mantisa = (num2_mantisa >> Nia) <<Nia;
    *num2_ptr &= (0xff800000);
    *num2_ptr |= num2_mantisa;
 */

     
    int num1_ptr ;
    memcpy(&num1_ptr, &number1, sizeof(num1_ptr));
    int num1_mantisa =  num1_ptr & ~(0xff800000);
    num1_mantisa = (num1_mantisa >> Nia) <<Nia;
    num1_ptr &= (0xff800000);
    num1_ptr |= num1_mantisa;
    
    int num2_ptr;
    memcpy(&num2_ptr, &number2, sizeof(num2_ptr));
    int num2_mantisa =  num2_ptr & ~(0xff800000);
    num2_mantisa = (num2_mantisa >> Nia) <<Nia;
    num2_ptr &= (0xff800000);
    num2_ptr |= num2_mantisa;
    

    float num2_restored, num1_restored; 
    memcpy(&num1_restored, &num1_ptr, sizeof(num1_restored));
    memcpy(&num2_restored, &num2_ptr, sizeof(num2_restored));
    

    #ifdef BT_RND
       printf("ERRR: rounding not defined for float float bta \n");
       exit(0);
    #endif

    return num2_restored + num1_restored;
   /*
    fpType num1;
    fpType num2;
    getFPComponents(number1, num1); //get the fp componenets
    getFPComponents(number2, num2); //get the fp components

    num1.Mantisa = ((num1.Mantisa)>> Nia) <<Nia;
    num2.Mantisa = ((num2.Mantisa)>> Nia) <<Nia;
    
    float num1_inverse_converted = convertFPCompToFP(num1);
    float num2_inverse_converted = convertFPCompToFP(num2);
    
    if (num1_inverse_converted != num1_restored){
        cout<<"sadf"<<endl; 
        cout<<"inverse: "<<num1_inverse_converted<< " num1_ptr: "<<num1_restored<<endl;
        exit(0); 
    }
    if (num2_inverse_converted != num2_restored){
        cout<<"inverse: "<<num2_inverse_converted<< " num2_ptr: "<<num2_restored<<endl;
        exit(0); 
    }
    return num1_inverse_converted + num2_inverse_converted;
     */
}

double bta::calc(const double &number1, const double &number2) {
    update_energy(Nia, "double", "double"); 
    /*
    FILE* fp;
    fp = fopen("diff_file.txt", "ab+");
    
    if ( num1_inverse_converted+num2_inverse_converted != (number1+number2)){
        float diff_part_1 =  num1_inverse_converted+num2_inverse_converted;
        float diff_part_2 =  number1+number2;
        float diff = (diff_part_1 - diff_part_2);
        
        //--checking for under/over-flow 
        if (std::isinf(diff_part_1)) {
            fprintf(fp, "par_1_overflow\n");
        }
        if (std::isinf(diff_part_2)) {
            fprintf(fp, "par_2_overflow\n");
        }
        if ((diff_part_1 != diff_part_2) && (diff ==0)){
            fprintf(fp, "diff underflow\n");
        }

        fprintf(fp, "error   ");
        if ( diff > 1){
            fprintf(fp, "acc:%f apx: %f diff:%f\n",num1_inverse_converted+num2_inverse_converted ,number1+number2, diff);
        }
        fprintf(fp, "------\n");
    }
    
    fclose(fp);
    */ 
    
    
    /*
    int *num1_ptr = (int *)malloc(sizeof(int));
    memcpy(num1_ptr, &number1, sizeof(num1_ptr));
    int num1_mantisa =  *num1_ptr & ~(0xff800000);
    num1_mantisa = (num1_mantisa >> Nia) <<Nia;
    *num1_ptr &= (0xff800000);
    *num1_ptr |= num1_mantisa;
    
    int *num2_ptr = (int *)malloc(sizeof(int));
    memcpy(num2_ptr, &number2, sizeof(num2_ptr));
    int num2_mantisa =  *num2_ptr & ~(0xff800000);
    num2_mantisa = (num2_mantisa >> Nia) <<Nia;
    *num2_ptr &= (0xff800000);
    *num2_ptr |= num2_mantisa;
 */

     
    long num1_ptr ;
    memcpy(&num1_ptr, &number1, sizeof(num1_ptr));
    long num1_mantisa =  num1_ptr & ~(0xfff0000000000000);
    num1_mantisa = (num1_mantisa >> Nia) <<Nia;
    num1_ptr &= 0xfff0000000000000;
    num1_ptr |= num1_mantisa;
    
    long num2_ptr;
    memcpy(&num2_ptr, &number2, sizeof(num2_ptr));
    long num2_mantisa =  num2_ptr & ~(0xfff0000000000000);
    num2_mantisa = (num2_mantisa >> Nia) <<Nia;
    num2_ptr &= 0xfff0000000000000;
    num2_ptr |= num2_mantisa;
    

    double num2_restored, num1_restored; 
    memcpy(&num1_restored, &num1_ptr, sizeof(num1_restored));
    memcpy(&num2_restored, &num2_ptr, sizeof(num2_restored));
    

    #ifdef BT_RND
       printf("ERRR: rounding not defined for float float bta \n");
       exit(0);
    #endif

    return num2_restored + num1_restored;
   


}
int bta::calc(const int &a, const int &b) {
    update_energy(Nia, "int", "int"); 
    // inaccurate part
#ifdef VERBOSE 
    cout<<"=============in int version"<<endl; 
    #endif  
    int weight = pow(2, Nia) - 1;
	int iap_a = weight&a;
#ifdef BT_RND
    int a_op = (iap_a >> (Nia - 1)) == 0x1 ? (a >> Nia) + 1 : (a >> Nia);
#else
	int a_op = (a >> Nia);
#endif
	int iap_b = weight&b;
#ifdef BT_RND
	int b_op = (iap_b >> (Nia - 1)) == 0x1 ? (b >> Nia) + 1 : (b >> Nia);
#else
	int b_op = (b >> Nia);
#endif

	// accurate part
	return ((a_op) + (b_op)) << Nia;
}
//
//


unsigned int bta::calc(const unsigned int &a, const unsigned int &b) {
    update_energy(Nia, "int", "int"); 
    #ifdef BT_RND
       printf("ERRR: rounding not defined for unsigned int unsigned int bta \n");
       exit(0);
    #endif
 

    
    // inaccurate part
    #ifdef VERBOSE 
    cout<<"=============in unsigned unsigned int version"<<endl; 
    #endif  
    unsigned int weight = pow(2, Nia) - 1;
	unsigned int iap_a = weight&a;
#ifdef BT_RND
	unsigned int a_op = (iap_a >> (Nia - 1)) == 0x1 ? (a >> Nia) + 1 : (a >> Nia);
#else
	unsigned int a_op = (a >> Nia);
#endif
	unsigned int iap_b = weight&b;
#ifdef BT_RND
	unsigned int b_op = (iap_b >> (Nia - 1)) == 0x1 ? (b >> Nia) + 1 : (b >> Nia);
#else
	unsigned int b_op = (b >> Nia);
#endif

	// accurate part
	return ((a_op) + (b_op)) << Nia;
}

int bta::calc(const unsigned int &a_unsigned, const int &b) {
    
    update_energy(Nia, "int", "int"); 
    
    #ifdef BT_RND
       printf("ERRR: rounding not defined for unsigned int, int bta \n");
       exit(0);
    #endif
    // inaccurate part
    #ifdef VERBOSE 
    cout<<"=============in unsigned unsigned int version"<<endl; 
    #endif  
    int a = (int)a_unsigned; 
    int weight = pow(2, Nia) - 1;
	int iap_a = weight&(int)a;
#ifdef BT_RND
	int a_op = (iap_a >> (Nia - 1)) == 0x1 ? (a >> Nia) + 1 : (a >> Nia);
#else
	int a_op = ((int)a >> Nia);
#endif
	int iap_b = weight&b;
#ifdef BT_RND
	int b_op = (iap_b >> (Nia - 1)) == 0x1 ? (b >> Nia) + 1 : (b >> Nia);
#else
	int b_op = (b >> Nia);
#endif

	// accurate part
	return ((a_op) + (b_op)) << Nia;
}

int bta::calc(const int &a, const unsigned int &b_unsigned) {
    update_energy(Nia, "int", "int"); 
    // inaccurate part
    
    #ifdef BT_RND
       printf("ERRR: rounding not defined for int, unsigned int bta \n");
       exit(0);
    #endif

#ifdef VERBOSE 
    cout<<"=============in unsigned unsigned int version"<<endl; 
    #endif  
    int b = (int)b_unsigned; 
    int weight = pow(2, Nia) - 1;
	int iap_a = weight&(int)a;
#ifdef BT_RND
	int a_op = (iap_a >> (Nia - 1)) == 0x1 ? (a >> Nia) + 1 : (a >> Nia);
#else
	int a_op = ((int)a >> Nia);
#endif
	int iap_b = weight&b;
#ifdef BT_RND
	int b_op = (iap_b >> (Nia - 1)) == 0x1 ? (b >> Nia) + 1 : (b >> Nia);
#else
	int b_op = (b >> Nia);
#endif

	// accurate part
	return ((a_op) + (b_op)) << Nia;
}




int bta::calc_ref(const int &a, const int &b) {
	// this is adder
    update_energy(Nia, "int", "int"); 
    return a + b;
}

void bta::tbl_gen() {
	int i,j;
	int i_w, j_w;
	int calc_tmp1;
	int calc_tmp2;
	for (i=0; i<pow(2,msb-lsb+1); i++) {
		for (j=0; j<pow(2,msb-lsb+1); j++) {
			i_w = i<<lsb;
			j_w = j<<lsb;
			calc_tmp1 = calc(i_w, j_w);
			calc_tmp2 = calc_ref(i_w, j_w);

			//cout << "sglee: " << i_w << "," << j_w << ", apr: " << calc_tmp1 << ", ori: " << calc_tmp2 << endl;
			if (calc_tmp1 != calc_tmp2) {
				err_tbl.push_back(make_pair(make_pair(i_w,j_w), make_pair(make_pair(0,0),calc_tmp2-calc_tmp1)));
			}
		}
	}
}
