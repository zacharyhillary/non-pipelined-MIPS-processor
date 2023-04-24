#ifndef Instructions_H
#define Instructions_H
#include <string>
#include <vector>
using namespace std;
extern ofstream output;

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
    long int immediate;
    int target;//26 bit
    int Type;// 'R' 'I' 'J'
    string InstructionName;//"add", "lw","addi".....
    int ALUResult;
    int temp;
    static int cCount;
    static int iCount;



public:
    Instruction(string machinecode);
    void print(ofstream& output);
    int execute(int REGISTERS[], int MEMORY[]);// RETURNS PC ADDRESS(int) OF NEXT INSTRUCTON
    void reset();
    static int ObjectCount;
    void decode();

};

#endif