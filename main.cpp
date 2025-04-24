#include "RunTimeLogger.h"
#include "Square.h"
#include <iostream>

int main(){
    try{
        RunTimeLogger runtimelogger;
        std::thread thread(&RunTimeLogger::PrintTimerStats);
        thread.detach();

        RunTimeLogger::StartGlobalTimer();
        RunTimeLogger::StartTimer("Computation");
        float a = 10.0f;
        float b = 33.0f;
        float c = a + b;
        Square square(c);
        RunTimeLogger::EndTimer("Computation"); // String must be equal to StartTimer string

        RunTimeLogger::StartTimer("Area Computation");
        square.GetArea();
        RunTimeLogger::EndTimer("Area Computation");

        square.ExpensiveFunctionSimulator();
    }
    catch(std::invalid_argument exception){
        std::cout << exception.what() << std::endl;
    }
}