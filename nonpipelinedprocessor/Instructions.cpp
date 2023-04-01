
#include "Instructions.h"
#include <iostream>

Instruction::Instruction(string machinecode) {
    PCAddress = ObjectCount;// location in the PC. based on the order from input file
    ObjectCount++;//increment static variable

	this->machinecode = machinecode;// store argument in overloaded constructor in to the member variable "machinecode"
    opcode = stoi(machinecode.substr(0, 6),0,2);// convert first 6 characters from a binary string to a decimal integer
    rs = stoi(machinecode.substr(6, 5), 0, 2);//// convert characters 6-10 from a binary string to a decimal integer
    rt = stoi(machinecode.substr(11, 5), 0, 2);// convert characters 11-15 from a binary string to a decimal integer
    rd = stoi(machinecode.substr(16, 5), 0, 2);// convert characters 16-20 from a binary string to a decimal integer
    shamt = stoi(machinecode.substr(21, 5), 0, 2);// convert characters 21-25 from a binary string to a decimal integer
    funct = stoi(machinecode.substr(26, 6), 0, 2);//converts characters 26-31 from a binary string to a decimal integer
    intermediate = stoi(machinecode.substr(16, 16), 0, 2);//converts characters 16-31 from a binary string to a decimal integer
    target = stoi(machinecode.substr(6, 26), 0, 2);// converts cjaracters 11-31 from a binary string to a decimal integer

    NextInstructionPC = PCAddress++;// by default NextPC = PC + 1 unless jump instruction

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

    else if (InstructionName == "beq" || InstructionName == "bne") cout << InstructionName << "     r" << rs << ", r" << rt << ", " << (intermediate  + PCAddress ) << endl; 

    else if (InstructionName == "lw" || InstructionName == "sw") cout << InstructionName << "      r" << rt << ", " << intermediate << "(r" << rs << ")" << endl;
    else if (InstructionName == "addi") cout << InstructionName << "    r" << rt << ", r" << rs << ", " << intermediate << endl;
}
int Instruction::ObjectCount = 0;
int Instruction::execute(int REGISTERS[], int MEMORY[]) {
    if (InstructionName == "add") {
        REGISTERS[rd] = (REGISTERS[rs] + REGISTERS[rt]); // rd=rs+rt
        return NextInstructionPC; // return address to next instruction
    }
    else if (InstructionName == "sub") {
        REGISTERS[rd] = (REGISTERS[rs] - REGISTERS[rt]); // rd= rs-rt
        return NextInstructionPC; // return address to next instruction
    }

    // ***********************************FINISH THIS I ONLY CREATED EXECUTION FOR 2 INSTRUCTIONS (ADD AND SUB)***********************************************
}