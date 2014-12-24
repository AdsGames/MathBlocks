#include "calculator.h"

using namespace std;

Calculator::Calculator(){

}

Calculator::~Calculator(){
    
}

bool Calculator::Calculate(int number1,int number2,int method, int total){
     if(method==ADD){
          if((number1+number2)==total){
               return true;
          }
          else{
               return false;
          }
     
     }
     if(method==SUBTRACT){
          if((number1-number2)==total){
               return true;
          }
          else{
               return false;
          }
     
     }
     if(method==MULTIPLY){
          if((number1*number2)==total){
               return true;
          }
          else{
               return false;
          }
     
     }
     if(method==DIVIDE){
          if((number1+number2)==total){
               return true;
          }
          else{
               return false;
          }
     
     }
     else{
          return false;
     } 
}
