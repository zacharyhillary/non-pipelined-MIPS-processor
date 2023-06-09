// nonpipelinedprocessor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include <fstream>
#include "Instructions.h"
#include <iostream>
#include<cmath>
#include <string>
using namespace std;
ofstream output;

void PrintNonZeroCellsReg(int array[], int arraysize, ostream& output) {
    for (int i = 0; i < arraysize; i++)if (array[i] != 0)output << "R" << i << " " << array[i] << endl;
}
void PrintNonZeroCellsMem(int array[], int arraysize, ostream& output) {
    for (int i = 0; i < arraysize; i++)if (array[i] != 0)output << i << " " << array[i] << endl;
}

void PrintNonZeroCellsReg(int array[], int arraysize, ofstream& output) {
    for (int i = 0;i < arraysize;i++)if (array[i] != 0)output << "R" << i << " " << array[i] << endl;
}
void PrintNonZeroCellsMem(int array[], int arraysize, ofstream& output) {
    for (int i = 0; i < arraysize; i++)if (array[i] != 0)output << i << " " << array[i] << endl;
}
bool ReadFromFile(string inputfile, int Registers[], int MEMORY[], Instruction* InstructionArray[]) {
    ifstream inputstream(inputfile);
    if (!inputstream) {
        cout << "Could Not Open File! Try Again!" << endl;
        return 0;
    }
    string trash;
    inputstream >> trash;//disregard first line of text
    string mode = "REGISTERS";
    while (1)
    {
        if (mode == "REGISTERS") {
            string registername;
            int registernumber;
            int registervalue;
            inputstream >> registername;
            if (registername == "MEMORY")// if it reads "MEMORY" then we switch to MEMORY mode
            {
                mode = "MEMORY";
                continue;
            }
            inputstream >> registervalue;
            registernumber = stoi(registername.erase(0, 1)); //"R1" -> 1  or "R22"->22
            Registers[registernumber] = registervalue;
        }
        if (mode == "MEMORY") {
            string memoryname;
            int memorynumber;
            int memoryvalue;
            inputstream >> memoryname;
            if (memoryname == "CODE")// if it reads "CODE" then we switch to CODE MODE
            {
                mode = "CODE";
                continue;
            }
            inputstream >> memoryvalue;
            memorynumber = stoi(memoryname); //string to int
            MEMORY[memorynumber] = memoryvalue;
        }
        if (mode == "CODE") {
            string machinecode;
            int i = 0;
            while (inputstream >> machinecode) { //untill end of file
                InstructionArray[i] = new Instruction(machinecode);// create new instruction and place it in the array
                i++;
            }
            break;
        }

    }

}
void PrintToScreen(int Registers[], int MEMORY[]) {
    cout << "REGISTERS" << endl;                                         // print register and memory
    PrintNonZeroCellsReg(Registers, 32, cout);
    cout << "MEMORY" << endl;
    PrintNonZeroCellsMem(MEMORY, 32, cout);
    cout << endl;
}
void WriteToFile(int Registers[],int MEMORY[], ofstream& output) {
    output << "REGISTERS" << endl;
    PrintNonZeroCellsReg(Registers, 32, output);
    output << "MEMORY" << endl;                      // print register and memory
    PrintNonZeroCellsMem(MEMORY, 250, output);
    output.close();
}
int main()
{

    string inputfile;// name of input file
    string outputfile;// name of output file
    int Registers[32];//32 registers 32 bit each
    int MEMORY[250];//250 memory cells 32 bit each
    Instruction* InstructionArray[30];//array of instructions. 30 is arbitrary value. cant handle more than 30 instructions.

    cout << "Welcome to our mips processor!" << endl;

    while (1) { // main loop
        for (int i = 0;i < 32; i++)Registers[i] = 0; //initalize registers to 0
        for (int i = 0;i < 250; i++)MEMORY[i] = 0; // initalize memory to 0
        cout << "Enter input file name:" << endl;
        cin >> inputfile;
        if (!ReadFromFile(inputfile, Registers, MEMORY, InstructionArray))continue;// this opens and reads from file. if it cant be opened it restarts the loop
        cout << "Enter output file name:" << endl;
        cin >> outputfile;
        cout << endl << endl;
        output.open(outputfile);

        cout <<  "-----BEFORE EXECUTION-----" << endl;
        PrintToScreen(Registers, MEMORY);

        int NumInstructions = InstructionArray[0]->ObjectCount;
        int PC = 0;//InstructionArray[0]->execute(Registers, MEMORY);//execute first instruction and update P

        do PC = InstructionArray[PC]->execute(Registers, MEMORY);//execute instruction and update PC 
        while (PC != NumInstructions);// while not the end of program.

        WriteToFile(Registers, MEMORY, output);
        cout << "-----AFTER EXECUTION-----" << endl;
        PrintToScreen(Registers, MEMORY);
        cout << "-----ASSEMBLY CODE-----" << endl;
        for (int i = 0;i < NumInstructions;i++)InstructionArray[i]->decode(); // this decodes every single instruction sequentially. just in case one was skipped during execution
        for (int i = 0;i < NumInstructions;i++)InstructionArray[i]->print(output);//print program in assembly

        //output << endl << endl << endl;
        cout << endl << "PROGRAM EXECUTED SUCCESFULLY " << endl << endl << endl;
        //reset object counter and PCAddress
        for (int i = 0; i < NumInstructions; i++)
        {
            InstructionArray[i]->reset();
        }

        
        cout << "Would you like to run another file?(y/n)"<<endl;
        char response;
        cin >> response;
        if (response != 'y' && response != 'Y') break;
    }
    
}