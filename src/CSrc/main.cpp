//copy paste the following lines: start here
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
//end here


//copy past the following lines: start here
int mainSIMPLE(int argc, char* argv[]){
    string resultFolderName; 
    string resultFileName; 
    string operatorFileName;
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
    //end here

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

