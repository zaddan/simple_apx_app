/**
* @file RecME.cpp
* @author Muhammad Usman Karim Khan
* Group: Prof. Joerg Henkel at Chair for Embedded Systems (CES), KIT
* @brief This file contains the computational adaptation for both number
* of threads and the frequency of the cores.
*/

#include <fstream>
#include "assert.h"
#include "Operators.h"
#include "operatorFile_parser.h"
#include "setSubType.h"
#include "operandFile_parser.h"
#include "globals.h"
#include "foo.h"

using namespace std;
extern hw_ac **myOp;   
//extern vector<int> inputVar;

//int notMain(){ //uncomment when you want to run the run_unit_tests
int main(int argc, char* argv[]){
    string resultFolderName; 
    string resultFileName; 
    string operatorFileName;
    //string operandFileName;
    if (argc < 4) {
        cout<< "provide the name of the file that you want the result to be written to"<<endl;
        cout<< "Example: resultFolderName.txt resultFile.txt operatorFile.txt"<<endl; 
        return 0; 
    }else{
        resultFolderName= argv[1]; 
        resultFileName = argv[2]; 
        operatorFileName = argv[3]; 
    }
    assign_global_variables(resultFolderName, operatorFileName);
    string resultFileNameCompleteAddress = resultFileName;
    ofstream resultFile;
    resultFile.open(resultFileNameCompleteAddress.c_str(), ios_base::app);
    resultFile<<"*****************start******"<<endl; 
    //keep the above part of the main file intact for various files 
    //writing the result 
     //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
    //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
//    const int inputSize = 0; 
//    int inputVar[inputSize] = {}; 
//    assert(argc == inputSize + 4);
//    for (int i =0 ; i < 4; i++) {
//        inputVar[i] = atoi(argv[4 + i]);
//    }
    
    int in1 = 10;
    int in2 = 20;
    int in3 = 30;
    int a = myOp[0]->calc(in1,in2); //MultiplicationOp
    int b = foo(a, in3); 
    int c = myOp[1]->calc(b,a); //MultiplicationOp
    int overAllOutput = c; 
    cout <<overAllOutput<<endl;
    resultFile<< overAllOutput <<endl;
    resultFile<<"*****************end******"<<endl; 
    resultFile.close();
    return 0;
}    

