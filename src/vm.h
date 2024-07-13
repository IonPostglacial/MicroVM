#include <stdint.h>
#include "bytecode.h"

#define MVM_STACK_SIZE 16000
#define MVM_CALLSTACK_SIZE 100

struct MVM_Machine
{
    size_t pc;
    size_t sp;
    size_t fp;
    int32_t acc;
    int32_t stack[MVM_STACK_SIZE];
    size_t callstack[MVM_CALLSTACK_SIZE];
};

void MVM_Machine_Init(struct MVM_Machine *machine);
void MVM_Machine_RunCode(struct MVM_Machine *machine, struct MVM_Code code);