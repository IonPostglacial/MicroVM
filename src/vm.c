#include "vm.h"
#include <memory.h>
#include <stdlib.h>

void MVM_Machine_Init(struct MVM_Machine *machine)
{
    machine->pc = 0;
    machine->sp = 0;
    machine->fp = 0;
    machine->acc = 0;
    memset(machine->stack, 0, sizeof machine->stack);
}

int32_t MVM_Machine_Stack_Pop(struct MVM_Machine *machine)
{
    if (machine->sp < 0) {
        exit(1);
    }
    return machine->stack[--machine->sp];
}

void MVM_Machine_ExecuteInstruction(struct MVM_Machine *machine, struct MVM_Instruction instruction)
{
    switch (instruction.op) {
    case MVM_OP_LOAD_IMMEDIATE:
        machine->acc = instruction.as.immediate;
        break;
    case MVM_OP_PUSH:
        if (machine->sp >= MVM_STACK_SIZE) {
            exit(1);
        }
        machine->stack[machine->sp++] = machine->acc;
        break;
    case MVM_OP_POP:
        machine->acc = MVM_Machine_Stack_Pop(machine);
        break;
    case MVM_OP_INC:
        machine->acc++;
        break;
    case MVM_OP_DEC:
        machine->acc--;
        break;
    case MVM_OP_ADD:
        machine->acc += MVM_Machine_Stack_Pop(machine);
        break;
    case MVM_OP_SUB:
        machine->acc -= MVM_Machine_Stack_Pop(machine);
        break;
    case MVM_OP_MUL:
        machine->acc *= MVM_Machine_Stack_Pop(machine);
        break;
    case MVM_OP_DIV:
        machine->acc /= MVM_Machine_Stack_Pop(machine);
        break;
    case MVM_OP_EQ:
        machine->acc = machine->acc == MVM_Machine_Stack_Pop(machine);
        break;
    case MVM_OP_NEQ:
        machine->acc = machine->acc != MVM_Machine_Stack_Pop(machine);
        break;
    case MVM_OP_LT:
        machine->acc = machine->acc < MVM_Machine_Stack_Pop(machine);
        break;
    case MVM_OP_LTE:
        machine->acc = machine->acc <= MVM_Machine_Stack_Pop(machine);
        break;
    case MVM_OP_GT:
        machine->acc = machine->acc > MVM_Machine_Stack_Pop(machine);
        break;
    case MVM_OP_GTE:
        machine->acc = machine->acc >= MVM_Machine_Stack_Pop(machine);
        break;
    case MVM_OP_JMP:
        machine->pc = instruction.as.address;
        return;
    case MVM_OP_NOT:
        machine->acc = !machine->acc;
        break;
    case MVM_OP_JMP_IF_ZERO:
        if (machine->acc == 0) {
            machine->pc = instruction.as.address;
        }
        return;
    case MVM_OP_JMP_IF_NOT_ZERO:
        if (machine->acc != 0) {
            machine->pc = instruction.as.address;
        }
        return;
    case MVM_OP_CALL:
        if (machine->fp >= MVM_CALLSTACK_SIZE) {
            exit(1);
        }
        machine->callstack[machine->fp++] = machine->pc;
        machine->pc = instruction.as.address;
        return;
    case MVM_OP_RETURN:
        if (machine->fp < 0) {
            exit(1);
        }
        machine->pc = machine->callstack[--machine->fp];
        break;
    }
    machine->pc++;
}

void MVM_Machine_RunCode(struct MVM_Machine *machine, struct MVM_Code code)
{
    while (machine->pc < code.count) {
        MVM_Machine_ExecuteInstruction(machine, code.instructions[machine->pc]);
    }
}