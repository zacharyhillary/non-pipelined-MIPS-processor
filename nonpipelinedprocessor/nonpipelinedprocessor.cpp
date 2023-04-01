// nonpipelinedprocessor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//




#include "Instructions.h"
#include <iostream>
#include<cmath>
#include <string>
using namespace std;


int main()
    {
    int Registers[32];//32 registers 32 bit each
    int MEMORY[250];//250 memorys 32 bit each

    Instruction first("00000010111100110100000000100010");// create instruction sub r8,r23,r19  
    
    Registers[8] = 69;// set initial registersw
    Registers[23] = 17;
    Registers[19] = 7;


    cout << "Initial Registers r8: " << Registers[8] << "  r23: " << Registers[23] << "  r19: " << Registers[19] << endl;//print registers before executing  instruction
    first.print(); //translate machine code into assembly
    first.execute(Registers, MEMORY);// execute instruction
    cout << "Final Registers r8: " << Registers[8] << "  r23: " << Registers[23] << "  r19: " << Registers[19] << endl;// print registers after executing instruction

        
        
    }
