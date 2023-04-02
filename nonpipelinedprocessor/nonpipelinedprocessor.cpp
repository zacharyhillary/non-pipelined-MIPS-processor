// nonpipelinedprocessor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include <fstream>
#include "Instructions.h"
#include <iostream>
#include<cmath>
#include <string>
using namespace std;

void PrintNonZeroCells(int array[],int arraysize) {
    for (int i = 0;i < arraysize;i++)if (array[i] != 0)cout << "R" << i << " " << array[i] << endl;       
}
bool ReadFromFile(string inputfile, int Registers[], int MEMORY[], Instruction* InstructionArray[]) {
    ifstream inputstream(inputfile);
    if (!inputstream) {
        cout << "Could Not Open File! Try Again!" << endl;
        return 0;
    }
    string trash;
    string mode = "REGISTERS";
    inputstream >> trash;
    while (1) 
    {
        if (mode == "REGISTERS") {
            string registername;
            int registernumber;
            int registervalue;
            inputstream >> registername;
            //cout << "Register Name: " << registername << endl;
            if (registername == "MEMORY")// if it reads "MEMORY" then we switch modes so that we can write to memory instead of registers
            {
                mode = "MEMORY";
                continue;
            }
            inputstream >> registervalue;
            registernumber = stoi(registername.erase(0, 1)); //"R1" -> 1  or "R22"->22
            //cout << "Register Number: " << registernumber << endl;
            //cout << "Register Value: " << registervalue << endl;
            Registers[registernumber] = registervalue;
       }
        if (mode == "MEMORY") {
            string memoryname;
            int memorynumber;
            int memoryvalue;
            inputstream >> memoryname;// must scan string to search for next section "CODE"
            //cout << "MEMORY NAME: " << memoryname << endl;
            if (memoryname == "CODE")// if it reads "MEMORY" then we switch modes so that we can write to memory instead of registers
            {
                mode = "CODE";
                continue;
            }
            inputstream >> memoryvalue;
            memorynumber = stoi(memoryname); //string to int
            //cout << "MEMORY NUMBER: " << memorynumber << endl;
            //cout << "MEMORY VALUE: " << memoryvalue << endl;
            MEMORY[memorynumber] = memoryvalue;
        }
        if (mode == "CODE") {
            string machinecode;
            int i = 0;
            while (inputstream >> machinecode) { //untill end of file
                InstructionArray[i] = new Instruction(machinecode);
                //cout << "Machine Code: " << machinecode << endl;
                i++;
            }
            break;
        }
        
    }

}

int main()
    {

    string inputfile;// name of input file
    string outputfile;// name of output file
    int Registers[32];//32 registers 32 bit each
    int MEMORY[250];//250 memory cells 32 bit each
    Instruction* InstructionArray[30];//array of instructions. 30 is arbitrary value. cant handle more than 30 instructions.
    for (int i = 0;i < 32; i++)Registers[i] = 0; //initalize registers to 0
    for (int i = 0;i < 250; i++)MEMORY[i] = 0; // initalize memory to 0

    while (1) { // main loop
        cout << "Welcome to our mips processor!" << endl;
        cout << "enter input file name" << endl;
        cin >> inputfile;
        if (!ReadFromFile(inputfile, Registers, MEMORY, InstructionArray))continue;// this opens and reads from file. if it cant be opened it restarts the loop
        cout << "enter output file name" << endl;
        cin >> outputfile;
        

    


    InstructionArray[0]->print();
    InstructionArray[1]->print();  //print program in assembly
    InstructionArray[2]->print();
    InstructionArray[3]->print();
    InstructionArray[4]->print();
    InstructionArray[5]->print();

    


    cout << endl << endl << endl << "-----BEFORE EXECUTION-----"<<endl;
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
    cout << "PROGRAM SUCCESSFULY RAN!!!" << endl << endl << endl;
    }
}