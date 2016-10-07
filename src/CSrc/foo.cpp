#include <fstream>
#include "Operators.h"
#include "operatorFile_parser.h"
#include "setSubType.h"
#include "operandFile_parser.h"
#include "globals.h"
#include "foo.h"
extern hw_ac **myOp;   
//extern vector<int> inputVar;

int foo(int a, int b){
    int c = myOp[2]->calc(a,b); //AdditionOp
    return c;
}
