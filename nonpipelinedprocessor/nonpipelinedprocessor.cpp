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
    for (int i = 0;i < 32; i++)Registers[i] = 0; //initalize registers to 0
    for (int i = 0;i < 250; i++)MEMORY[i] = 0; // initalize memory to 0

    ///////////////////////////////////////////////////////////////////////
    cout << "----------------------TEST 1----------------------" << endl;
    string machinecode[6] ={"10001100001000100000000000000000","00000000010000110010000000100000","10101100001001000000000000000000","00010100000001000000000000000001","00100000010000011111111111110111","00000000001000110000100000100000"};
   
    Instruction* InstructionArray[6];
    for (int i = 0;i < 6;i++) {                 //load Instructions into array
        InstructionArray[i] = new Instruction(machinecode[i]);
 }
   
    InstructionArray[0]->print();
    InstructionArray[1]->print();
    InstructionArray[2]->print();
    InstructionArray[3]->print();
    InstructionArray[4]->print();
    InstructionArray[5]->print();
    cout << "--------------------------------------------------" << endl<<endl<<endl<<endl;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////



    ///////////////////////////////////////////////////////////////////////////////////////////////////

    cout << "----------------------TEST 2----------------------" << endl;
    Instruction first("00000010111100110100000000100010");// create instruction sub r8,r23,r19  
    
    Registers[8] = 69;// set initial registers
    Registers[23] = 17;
    Registers[19] = 7;


    cout << "Initial Registers r8: " << Registers[8] << "  r23: " << Registers[23] << "  r19: " << Registers[19] << endl;//print registers before executing  instruction
    first.print(); //prints the assembly code to display
    first.execute(Registers, MEMORY);// execute instruction
    cout << "Final Registers r8: " << Registers[8] << "  r23: " << Registers[23] << "  r19: " << Registers[19] << endl;// print registers after executing instruction
    cout << "--------------------------------------------------" << endl << endl << endl << endl;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
    }
