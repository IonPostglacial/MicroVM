#pragma once

#include <stdint.h>
#include <stdio.h>

enum MVM_Opcode
{
    MVM_OP_LOAD_IMMEDIATE,
    MVM_OP_PUSH,
    MVM_OP_POP,
    MVM_OP_DUP,
    MVM_OP_SWAP,
    MVM_OP_LOAD_TOP,
    MVM_OP_OVER,
    MVM_OP_INC,
    MVM_OP_DEC,
    MVM_OP_ADD,
    MVM_OP_SUB,
    MVM_OP_MUL,
    MVM_OP_DIV,
    MVM_OP_EQ,
    MVM_OP_NEQ,
    MVM_OP_LT,
    MVM_OP_LTE,
    MVM_OP_GT,
    MVM_OP_GTE,
    MVM_OP_JMP,
    MVM_OP_NOT,
    MVM_OP_JMP_IF_ZERO,
    MVM_OP_JMP_IF_NOT_ZERO,
    MVM_OP_CALL,
    MVM_OP_RETURN,
};

union MVM_Instruction_Data
{
    int16_t immediate;
    int16_t address;
};

struct MVM_Instruction
{
    int8_t op;
    union MVM_Instruction_Data as;
};

struct MVM_Code
{
    int16_t count;
    int16_t capacity;
    struct MVM_Instruction *instructions;
};

void MVM_Code_ReadFromFile(struct MVM_Code *code, FILE *input);