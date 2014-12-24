#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <allegro.h>

#include "datavalues.h"
#include "block.h"

using namespace std;

class Calculator{
      
public:
     Calculator();
     ~Calculator();
     
     bool Calculate(int number1,int number2,int method, int total);

private:

};

#endif
