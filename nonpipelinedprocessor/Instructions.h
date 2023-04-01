#ifndef Instructions_H
#define Instructions_H
#include <string>
using namespace std;
class Instruction {
private:
    int PCAddress;// first instruction is 0 then 1,2,3,4....
    string machinecode;// 32 bit machine code
    int opcode;//6 bit
    int rs; //5 bit
    int rt;//5 bit
    int rd; // 5 bit
    int shamt;//5 bit
    int funct;// 6 bit
    int intermediate;
    int target;//26 bit
    int Type;// 'R' 'I' 'J'
    string InstructionName;//"add, lw,addi....."
    static int ObjectCount;
    int NextInstructionPC;// PC address of the next instruction.. usually PCAddress+1 unless jump instruction
public:
    Instruction(string machinecode);
    void print();
    int execute(int REGISTERS[], int MEMORY[]);// RETURNS PC ADDRESS OF NEXT INSTRUCTON
};

#endif