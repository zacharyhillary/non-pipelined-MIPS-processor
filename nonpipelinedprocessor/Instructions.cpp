
#include "Instructions.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
extern ofstream output;


int SignedBinaryStringToInt(string MyString, int BitWidth) {//needed for immediate values
    int myInt;
    myInt = stoi(MyString, NULL, 2);
    myInt |= myInt & (1 << (BitWidth - 1)) ? (-(1 << BitWidth)) : 0;
    return myInt;
}
int UnSignedBinaryStringToInt(string MyString) {

    return stoi(MyString, NULL, 2);

}

Instruction::Instruction(string machinecode) {
    PCAddress = ObjectCount;// location in the PC. based on the order from input file
    ObjectCount++;//increment static variable
    this->machinecode = machinecode;// store argument in overloaded constructor in to the member variable "machinecode" 

}
void Instruction::print(ofstream& output) { //print out assembly code
    if (opcode == 0) cout << PCAddress << "         " << InstructionName << "  r" << rd << ", r" << rs << ", r" << rt << endl;

    else if (InstructionName == "beq" || InstructionName == "bne") cout << PCAddress << "         " << InstructionName << "  r" << rs << ", r" << rt << ", " << (immediate + PCAddress + 1) << endl;

    else if (InstructionName == "lw" || InstructionName == "sw") cout << PCAddress << "         " << InstructionName << "   r" << rt << ", " << immediate << "(r" << rs << ")" << endl;
    else if (InstructionName == "addi") cout << PCAddress << "         " << InstructionName << " r" << rt << ", r" << rs << ", " << immediate << endl;
}
int Instruction::ObjectCount = 0;
int Instruction::iCount = 1;
int Instruction::cCount = 1;

void Instruction::decode() {
    opcode = UnSignedBinaryStringToInt(machinecode.substr(0, 6));// convert first 6 characters from a binary string to a decimal integer
    if (opcode == 0) {// R TYPE
        rs = UnSignedBinaryStringToInt(machinecode.substr(6, 5));//// convert characters 6-10 from a binary string to a decimal integer
        rt = UnSignedBinaryStringToInt(machinecode.substr(11, 5));// convert characters 11-15 from a binary string to a decimal integer
        rd = UnSignedBinaryStringToInt(machinecode.substr(16, 5));// convert characters 16-20 from a binary string to a decimal integer
        shamt = UnSignedBinaryStringToInt(machinecode.substr(21, 5));// convert characters 21-25 from a binary string to a decimal integer
        funct = UnSignedBinaryStringToInt(machinecode.substr(26, 6));//converts characters 26-31 from a binary string to a decimal integer
        switch (funct) {  // we know that it is R-Type From the OPCODE so now we are trying to figure out its InstructionName by looking at the "funct" field.
            case 32:InstructionName = "add";break;
            case 34:InstructionName = "sub";break;
            case 42: InstructionName = "slt";break;

        }
    }
    else {//I TYPE
        rs = UnSignedBinaryStringToInt(machinecode.substr(6, 5));//// convert characters 6-10 from a binary string to a decimal integer
        rt = UnSignedBinaryStringToInt(machinecode.substr(11, 5));// convert characters 11-15 from a binary string to a decimal integer
        immediate = SignedBinaryStringToInt(machinecode.substr(16, 16), 16);//converts characters 16-31 from a binary string to a decimal integer
        switch (opcode) {
            case 4:InstructionName = "beq";break;
            case 5:InstructionName = "bne";break;
            case 8:InstructionName = "addi";break;
            case 35:InstructionName = "lw";break;
            case 43:InstructionName = "sw";break;

        }

    }
    output << "C#" << cCount << " I" << iCount << "-ID" << endl;//decode
    cCount++;
}
int Instruction::execute(int REGISTERS[], int MEMORY[]) {

    output << "C#" << cCount << " I" << iCount << "-IF" << endl;
    cCount++;
    decode();
    if (InstructionName == "add") {
        ALUResult = (REGISTERS[rs] + REGISTERS[rt]); // rd=rs+rt
        output << "C#" << cCount << " I" << iCount << "-EX" << endl;//execute
        cCount++;
        REGISTERS[rd] = ALUResult;
        output << "C#" << cCount << " I" << iCount << "-WB" << endl;//writeback
        cCount++;
        iCount++;
        return PCAddress + 1; // return address to next instruction
    }

    else if (InstructionName == "sub") {
        ALUResult = (REGISTERS[rs] - REGISTERS[rt]); // rd= rs-rt
        output << "C#" << cCount << " I" << iCount << "-EX" << endl;//ex
        cCount++;
        REGISTERS[rd] = ALUResult;
        output << "C#" << cCount << " I" << iCount << "-WB" << endl;//wb
        cCount++;
        iCount++;
        return PCAddress + 1; // return address to next instruction
    }

    else if (InstructionName == "slt") {
        if (REGISTERS[rs] < REGISTERS[rt])REGISTERS[rd] = 1;
        else REGISTERS[rd] = 0;
        output << "C#" << cCount << " I" << iCount << "-EX" << endl;//execute
        cCount++;
        output << "C#" << cCount << " I" << iCount << "-WB" << endl;//writeback
        cCount++;
        iCount++;
        return PCAddress + 1;
    }


    else if (InstructionName == "beq") {
        output << "C#" << cCount << " I" << iCount << "-EX" << endl;
        cCount++;
        iCount++;
        if (REGISTERS[rs] == REGISTERS[rt])return PCAddress + 1 + immediate;
        else return  PCAddress + 1;
    }
    else if (InstructionName == "bne"){
        output << "C#" << cCount << " I" << iCount << "-EX" << endl;
        cCount++;
        iCount++;
        if (REGISTERS[rs] == REGISTERS[rt])return PCAddress + 1;
        else return PCAddress + 1 + immediate;
    }
    
    else if (InstructionName == "addi") {
        ALUResult = REGISTERS[rs] + immediate;
        output << "C#" << cCount << " I" << iCount << "-EX" << endl;//execute
        cCount++;
        REGISTERS[rt] = ALUResult;
        output << "C#" << cCount << " I" << iCount << "-WB" << endl;//writeback
        cCount++;
        iCount++;
        return PCAddress + 1;
    }
    else if (InstructionName == "lw") {
        ALUResult = immediate + REGISTERS[rs];
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
    }
    else if (InstructionName == "sw") {
        ALUResult = immediate + REGISTERS[rs];
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