
#include "Instructions.h"
#include <iostream>

int SignedBinaryStringToInt(string MyString, int BitWidth) {
    int myInt;
    myInt = std::stoi(MyString, NULL, 2);

    int bitWidth = 5;

    myInt |= myInt & (1 << (bitWidth - 1)) ? (-(1 << bitWidth)) : 0;
    return myInt;
}

Instruction::Instruction(string machinecode) {
    PCAddress = ObjectCount;// location in the PC. based on the order from input file
    ObjectCount++;//increment static variable

	this->machinecode = machinecode;// store argument in overloaded constructor in to the member variable "machinecode"
    opcode = SignedBinaryStringToInt(machinecode.substr(0, 6),6);// convert first 6 characters from a binary string to a decimal integer
    rs = SignedBinaryStringToInt(machinecode.substr(6, 5),5);//// convert characters 6-10 from a binary string to a decimal integer
    rt = SignedBinaryStringToInt(machinecode.substr(11, 5), 5);// convert characters 11-15 from a binary string to a decimal integer
    rd = SignedBinaryStringToInt(machinecode.substr(16, 5), 5);// convert characters 16-20 from a binary string to a decimal integer
    shamt = SignedBinaryStringToInt(machinecode.substr(21, 5), 5);// convert characters 21-25 from a binary string to a decimal integer
    funct = SignedBinaryStringToInt(machinecode.substr(26, 6), 6);//converts characters 26-31 from a binary string to a decimal integer
    intermediate = SignedBinaryStringToInt(machinecode.substr(16, 16),16);//converts characters 16-31 from a binary string to a decimal integer
    //target = SignedBinaryStringToInt(machinecode.substr(6, 26), 24);// converts cjaracters 11-31 from a binary string to a decimal integer


    switch (opcode) {// By looking at the opcode we can tell what type of instruction it is.
    case 0://R-Type OPCODE = 000000 = 0
        Type = 'R';
            switch (funct) {  // we know that it is R-Type From the OPCODE so now we are trying to figure out its InstructionName by looking at the "funct" field.
            case 32://add funct = 100000=32
                InstructionName = "add";
                break;
            case 34: //sub funct = 100010=34
                InstructionName = "sub";
                break;
            case 42: //slt funct = 101010=42
                InstructionName = "slt";
                break;
             }
         break;
    case 4://beq OPCODE = 000100=4
        Type = 'I';
        InstructionName = "beq";
        break;
    case 5://bne OPCODE = 000101=5
        Type = 'I';
        InstructionName = "bne";
        break;
    case 8://addi OPCODE = 001000=8
        Type = 'I';
        InstructionName = "addi";
        break;
    case 35://lw OPCODE = 100011=lw
        Type = 'I';
        InstructionName = "lw";
        break;
    case 43://sw OPCODE = 101011=sw
        Type = 'I';
        InstructionName = "sw";
     break;
    }

}
void Instruction::print() { //print out assembly code
    if (Type == 'R') cout << InstructionName << "     r" << rd << ", r" << rs << ", r" << rt << endl;

    else if (InstructionName == "beq" || InstructionName == "bne") cout << InstructionName << "     r" << rs << ", r" << rt << ", " << (intermediate  + PCAddress +1 ) << endl; 

    else if (InstructionName == "lw" || InstructionName == "sw") cout << InstructionName << "      r" << rt << ", " << intermediate << "(r" << rs << ")" << endl;
    else if (InstructionName == "addi") cout << InstructionName << "    r" << rt << ", r" << rs << ", " << intermediate << endl;
}
int Instruction::ObjectCount = 0;
int Instruction::execute(int REGISTERS[], int MEMORY[]) {
    if (InstructionName == "add") {
        REGISTERS[rd] = (REGISTERS[rs] + REGISTERS[rt]); // rd=rs+rt
        return PCAddress + 1; // return address to next instruction
    }
    else if (InstructionName == "sub") {
        REGISTERS[rd] = (REGISTERS[rs] - REGISTERS[rt]); // rd= rs-rt
        return PCAddress + 1; // return address to next instruction
    }
    else if (InstructionName == "addi") {
        REGISTERS[rt] = REGISTERS[rs] + intermediate;
        return PCAddress + 1;
    }
    else if (InstructionName == "lw") {
        REGISTERS[rt] = MEMORY[intermediate + REGISTERS[rs]];
        return PCAddress + 1;
    }
    else if (InstructionName == "sw") {
        MEMORY[intermediate + REGISTERS[rs]] = REGISTERS[rt];
        return PCAddress + 1;
    }
    else if (InstructionName == "bne") {
        if (REGISTERS[rs] == REGISTERS[rt])return PCAddress + 1;
        else return PCAddress + 1 + intermediate;

    }
    else if (InstructionName == "beq") {
        if (REGISTERS[rs] == REGISTERS[rt])return PCAddress + 1 + intermediate;
        else return  PCAddress + 1;
    }
    else if (InstructionName == "slt") {
        if (REGISTERS[rs] < REGISTERS[rt])REGISTERS[rd] = 1;
        else REGISTERS[rd] = 0;
        return PCAddress + 1;
    }
}