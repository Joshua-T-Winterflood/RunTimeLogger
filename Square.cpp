#include "Square.h"

Square::Square(float sidelength){
    m_side_lenght = sidelength;
}

float Square::GetArea(){
    return pow(m_side_lenght, 2);
}

void Square::ExpensiveFunctionSimulator(){
    RunTimeLogger::StartTimer("Expensive FunctionCall");
    std::this_thread::sleep_for(std::chrono::seconds(15));
    RunTimeLogger::EndTimer("Expensive FunctionCall");

}