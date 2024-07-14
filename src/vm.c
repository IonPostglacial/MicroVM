#include "vm.h"
#include "errors.h"
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

int32_t MVM_Machine_Stack_Pop(struct MVM_Machine *machine, struct MVM_Error **err)
{
    if (machine->sp < 0) {
        *err = MVM_Error_Data_Stack_Underflow();
    }
    return machine->stack[--machine->sp];
}

void MVM_Machine_Stack_Push(struct MVM_Machine *machine, int32_t value, struct MVM_Error **err)
{
    if (machine->sp >= MVM_STACK_SIZE) {
        *err = MVM_Error_Data_Stack_Overflow();
    }
    machine->stack[machine->sp++] = value;
}

void MVM_Machine_ExecuteInstruction(struct MVM_Machine *machine, struct MVM_Instruction instruction, struct MVM_Error **err)
{
    switch (instruction.op) {
    case MVM_OP_LOAD_IMMEDIATE:
        machine->acc = instruction.as.immediate;
        break;
    case MVM_OP_PUSH:
        MVM_Machine_Stack_Push(machine, machine->acc, err);
        break;
    case MVM_OP_POP:
        machine->acc = MVM_Machine_Stack_Pop(machine, err);
        break;
    case MVM_OP_DUP:
        if (machine->sp < 0) {
            exit(1);
        }
        MVM_Machine_Stack_Push(machine, machine->stack[machine->sp], err);
        break;
    case MVM_OP_SWAP:
        if (machine->sp < 1) {
            exit(1);
        }
        int32_t tmp = machine->stack[machine->sp];
        machine->stack[machine->sp] = machine->stack[machine->sp - 1];
        machine->stack[machine->sp - 1] = tmp;
        break;
    case MVM_OP_LOAD_TOP:
        if (machine->sp < 0) {
            exit(1);
        }
        machine->acc = machine->stack[machine->sp];
        break;
    case MVM_OP_OVER:
        if (machine->sp < 1) {
            exit(1);
        }
        machine->acc = machine->stack[machine->sp - 1];
        break;
    case MVM_OP_INC:
        machine->acc++;
        break;
    case MVM_OP_DEC:
        machine->acc--;
        break;
    case MVM_OP_ADD:
        machine->acc += MVM_Machine_Stack_Pop(machine, err);
        break;
    case MVM_OP_SUB:
        machine->acc -= MVM_Machine_Stack_Pop(machine, err);
        break;
    case MVM_OP_MUL:
        machine->acc *= MVM_Machine_Stack_Pop(machine, err);
        break;
    case MVM_OP_DIV:
        machine->acc /= MVM_Machine_Stack_Pop(machine, err);
        break;
    case MVM_OP_EQ:
        machine->acc = machine->acc == MVM_Machine_Stack_Pop(machine, err);
        break;
    case MVM_OP_NEQ:
        machine->acc = machine->acc != MVM_Machine_Stack_Pop(machine, err);
        break;
    case MVM_OP_LT:
        machine->acc = machine->acc < MVM_Machine_Stack_Pop(machine, err);
        break;
    case MVM_OP_LTE:
        machine->acc = machine->acc <= MVM_Machine_Stack_Pop(machine, err);
        break;
    case MVM_OP_GT:
        machine->acc = machine->acc > MVM_Machine_Stack_Pop(machine, err);
        break;
    case MVM_OP_GTE:
        machine->acc = machine->acc >= MVM_Machine_Stack_Pop(machine, err);
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

void MVM_Machine_RunCode(struct MVM_Machine *machine, struct MVM_Code code, struct MVM_Error **err)
{
    while (machine->pc < code.count) {
        MVM_Machine_ExecuteInstruction(machine, code.instructions[machine->pc], err);
    }
}