
#include "Instructions.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
extern ofstream output;




int SignedBinaryStringToInt(string MyString, int BitWidth) {
    int myInt;
    myInt = stoi(MyString, NULL, 2);

    int bitWidth = 5;

    myInt |= myInt & (1 << (bitWidth - 1)) ? (-(1 << bitWidth)) : 0;
    return myInt;
}

Instruction::Instruction(string machinecode) {
    PCAddress = ObjectCount;// location in the PC. based on the order from input file
    ObjectCount++;//increment static variable
    this->machinecode = machinecode;// store argument in overloaded constructor in to the member variable "machinecode" 

}
void Instruction::print(ofstream& output) { //print out assembly code
    if (Type == 'R') cout << PCAddress << "         " << InstructionName << "  r" << rd << ", r" << rs << ", r" << rt << endl;

    else if (InstructionName == "beq" || InstructionName == "bne") cout << PCAddress << "         " << InstructionName << "  r" << rs << ", r" << rt << ", " << (intermediate + PCAddress + 1) << endl;

    else if (InstructionName == "lw" || InstructionName == "sw") cout << PCAddress << "         " << InstructionName << "   r" << rt << ", " << intermediate << "(r" << rs << ")" << endl;
    else if (InstructionName == "addi") cout << PCAddress << "         " << InstructionName << " r" << rt << ", r" << rs << ", " << intermediate << endl;
}
int Instruction::ObjectCount = 0;
int Instruction::iCount = 1;
int Instruction::cCount = 1;

int Instruction::execute(int REGISTERS[], int MEMORY[]) {

    output << "C#" << cCount << " I" << iCount << "-IF" << endl;
    cCount++;
    opcode = SignedBinaryStringToInt(machinecode.substr(0, 6), 6);// convert first 6 characters from a binary string to a decimal integer
    switch (opcode) {// By looking at the opcode we can tell which instruction it is
    case 0://R-Type OPCODE = 000000 = 0
        rs = SignedBinaryStringToInt(machinecode.substr(6, 5), 5);//// convert characters 6-10 from a binary string to a decimal integer
        rt = SignedBinaryStringToInt(machinecode.substr(11, 5), 5);// convert characters 11-15 from a binary string to a decimal integer
        rd = SignedBinaryStringToInt(machinecode.substr(16, 5), 5);// convert characters 16-20 from a binary string to a decimal integer
        shamt = SignedBinaryStringToInt(machinecode.substr(21, 5), 5);// convert characters 21-25 from a binary string to a decimal integer
        funct = SignedBinaryStringToInt(machinecode.substr(26, 6), 6);//converts characters 26-31 from a binary string to a decimal integer
        output << "C#" << cCount << " I" << iCount << "-ID" << endl;
        cCount++;
        switch (funct) {  // we know that it is R-Type From the OPCODE so now we are trying to figure out its InstructionName by looking at the "funct" field.
        case 32://add funct = 100000=32
            InstructionName = "add";
            ALUResult = (REGISTERS[rs] + REGISTERS[rt]); // rd=rs+rt
            output << "C#" << cCount << " I" << iCount << "-EX" << endl;//execute
            cCount++;
            REGISTERS[rd] = ALUResult;
            output << "C#" << cCount << " I" << iCount << "-WB" << endl;//writeback
            cCount++;
            iCount++;
            return PCAddress + 1; // return address to next instruction

        case 34: //sub funct = 100010=34
            InstructionName = "sub";
            ALUResult = (REGISTERS[rs] - REGISTERS[rt]); // rd= rs-rt
            output << "C#" << cCount << " I" << iCount << "-EX" << endl;//ex
            cCount++;
            REGISTERS[rd] = ALUResult;
            output << "C#" << cCount << " I" << iCount << "-WB" << endl;//wb
            cCount++;
            iCount++;
            return PCAddress + 1; // return address to next instruction

        case 42: //slt funct = 101010=42
            InstructionName = "slt";
            if (REGISTERS[rs] < REGISTERS[rt])REGISTERS[rd] = 1;
            else REGISTERS[rd] = 0;
            output << "C#" << cCount << " I" << iCount << "-EX" << endl;//execute
            cCount++;
            output << "C#" << cCount << " I" << iCount << "-WB" << endl;//writeback
            cCount++;
            iCount++;
            return PCAddress + 1;
        }

    case 4://beq OPCODE = 000100=4
        rs = SignedBinaryStringToInt(machinecode.substr(6, 5), 5);//// convert characters 6-10 from a binary string to a decimal integer
        rt = SignedBinaryStringToInt(machinecode.substr(11, 5), 5);// convert characters 11-15 from a binary string to a decimal integer
        intermediate = SignedBinaryStringToInt(machinecode.substr(16, 16), 16);//converts characters 16-31 from a binary string to a decimal integer
        output << "C#" << cCount << " I" << iCount << "-ID" << endl;//decode
        cCount++;
        InstructionName = "beq";
        output << "C#" << cCount << " I" << iCount << "-EX" << endl;
        cCount++;
        iCount++;
        //list.push_back("EX"); // instruction executed
        if (REGISTERS[rs] == REGISTERS[rt])return PCAddress + 1 + intermediate;
        else return  PCAddress + 1;

    case 5://bne OPCODE = 000101=5
        rs = SignedBinaryStringToInt(machinecode.substr(6, 5), 5);//// convert characters 6-10 from a binary string to a decimal integer
        rt = SignedBinaryStringToInt(machinecode.substr(11, 5), 5);// convert characters 11-15 from a binary string to a decimal integer
        intermediate = SignedBinaryStringToInt(machinecode.substr(16, 16), 16);//converts characters 16-31 from a binary string to a decimal integer
        output << "C#" << cCount << " I" << iCount << "-ID" << endl;//decode
        cCount++;
        InstructionName = "bne";
        output << "C#" << cCount << " I" << iCount << "-EX" << endl;
        cCount++;
        iCount++;
        if (REGISTERS[rs] == REGISTERS[rt])return PCAddress + 1;
        else return PCAddress + 1 + intermediate;

    case 8://addi OPCODE = 001000=8
        InstructionName = "addi";
        rs = SignedBinaryStringToInt(machinecode.substr(6, 5), 5);//// convert characters 6-10 from a binary string to a decimal integer
        rt = SignedBinaryStringToInt(machinecode.substr(11, 5), 5);// convert characters 11-15 from a binary string to a decimal integer
        intermediate = SignedBinaryStringToInt(machinecode.substr(16, 16), 16);//converts characters 16-31 from a binary string to a decimal integer
        output << "C#" << cCount << " I" << iCount << "-ID" << endl;//decode
        cCount++;
        ALUResult = REGISTERS[rs] + intermediate;
        output << "C#" << cCount << " I" << iCount << "-EX" << endl;//execute
        cCount++;
        REGISTERS[rt] = ALUResult;
        output << "C#" << cCount << " I" << iCount << "-WB" << endl;//writeback
        cCount++;
        iCount++;
        return PCAddress + 1;
    case 35://lw OPCODE = 100011=lw
        InstructionName = "lw";
        rs = SignedBinaryStringToInt(machinecode.substr(6, 5), 5);//// convert characters 6-10 from a binary string to a decimal integer
        rt = SignedBinaryStringToInt(machinecode.substr(11, 5), 5);// convert characters 11-15 from a binary string to a decimal integer
        intermediate = SignedBinaryStringToInt(machinecode.substr(16, 16), 16);//converts characters 16-31 from a binary string to a decimal integer
        output << "C#" << cCount << " I" << iCount << "-ID" << endl;//decode
        cCount++;
        ALUResult = intermediate + REGISTERS[rs];
        output << "C#" << cCount << " I" << iCount << "-EX" << endl; // execute
        cCount++;
        temp = MEMORY[ALUResult];
        output << "C#" << cCount << " I" << iCount << "-MEM" << endl; //memory access
        cCount++;
        REGISTERS[rt] = temp;
        output << "C#" << cCount << " I" << iCount << "-WB" << endl; //write back
        cCount++;
        iCount++;
        return PCAddress + 1;

    case 43://sw OPCODE = 101011=sw
        rs = SignedBinaryStringToInt(machinecode.substr(6, 5), 5);//// convert characters 6-10 from a binary string to a decimal integer
        rt = SignedBinaryStringToInt(machinecode.substr(11, 5), 5);// convert characters 11-15 from a binary string to a decimal integer
        intermediate = SignedBinaryStringToInt(machinecode.substr(16, 16), 16);//converts characters 16-31 from a binary string to a decimal integer
        output << "C#" << cCount << " I" << iCount << "-ID" << endl;//decode
        cCount++;
        InstructionName = "sw";
        ALUResult = intermediate + REGISTERS[rs];
        output << "C#" << cCount << " I" << iCount << "-EX" << endl;
        cCount++;
        MEMORY[ALUResult] = REGISTERS[rt];
        output << "C#" << cCount << " I" << iCount << "-MEM" << endl;
        cCount++;
        iCount++;
        return PCAddress + 1;

    }
}

void Instruction::reset() {
    ObjectCount = 0;
    PCAddress = 0;
    iCount = 1;
    cCount = 1;
}