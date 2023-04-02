// nonpipelinedprocessor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//




#include "Instructions.h"
#include <iostream>
#include<cmath>
#include <string>
using namespace std;

void PrintNonZeroCells(int array[],int arraysize) {
    for (int i = 0;i < arraysize;i++)if (array[i] != 0)cout << "R" << i << " " << array[i] << endl;       
}


int main()
    {



    



    int Registers[32];//32 registers 32 bit each
    int MEMORY[250];//250 memorys 32 bit each
    for (int i = 0;i < 32; i++)Registers[i] = 0; //initalize registers to 0
    for (int i = 0;i < 250; i++)MEMORY[i] = 0; // initalize memory to 0

    string machinecode[6] = { "10001100001000100000000000000000","00000000010000110010000000100000","10101100001001000000000000000000","00010100000001000000000000000001","00100000010000011111111111110111","00000000001000110000100000100000" };

    Instruction* InstructionArray[6];
    for (int i = 0;i < 6;i++) {                 //load Instructions into array
        InstructionArray[i] = new Instruction(machinecode[i]);
    }

    InstructionArray[0]->print();
    InstructionArray[1]->print();  //print program in assembly
    InstructionArray[2]->print();
    InstructionArray[3]->print();
    InstructionArray[4]->print();
    InstructionArray[5]->print();

    Registers[1] = 16; //initalize registers and memory  *********instead of manually doing it make it read from file*****
    Registers[3] = 42;
    Registers[5] = 8;
    MEMORY[8] = 40;
    MEMORY[16] = 60;


    cout << "-----BEFORE EXECUTION-----"<<endl;
    cout << "REGISTERS" << endl;
    PrintNonZeroCells(Registers,32);
    cout << "MEMORY" << endl;
    PrintNonZeroCells(MEMORY, 32);
    cout << endl << endl << endl;

    int NumInstructions = InstructionArray[0]->ObjectCount;
    int PC = InstructionArray[0]->execute(Registers, MEMORY);//execute first instruction
    while (PC != NumInstructions) {        // while not the end of program.
        PC = InstructionArray[PC]->execute(Registers, MEMORY);//execute instruction and update PC
    }



    cout << "-----AFTER EXECUTION-----" << endl;
    cout << "REGISTERS" << endl;
    PrintNonZeroCells(Registers, 32);
    cout << "MEMORY" << endl;
    PrintNonZeroCells(MEMORY, 32);
    cout << endl << endl << endl;
    }
