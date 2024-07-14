#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include "bytecode.h"

#define MVM_MAX_FILE_SIZE 5000000

const char *delimiters = " \r\n";

void MVM_Code_ReadLine(struct MVM_Code *code, char *src)
{
    char *tok;
    char *next_token;
    tok = strtok_s(src, delimiters, &next_token);
    while (tok) {
        if (tok == NULL) {
            break;
        }
        if (strcmp(tok, "load") == 0) {
            code->instructions[code->count].op = MVM_OP_LOAD_IMMEDIATE;
            if ((tok = strtok_s(NULL, delimiters, &next_token))) {
                code->instructions[code->count].as.immediate = atoi(tok);
            }
        } else if (strcmp(tok, "push") == 0) {
            code->instructions[code->count].op = MVM_OP_PUSH;
        } else if (strcmp(tok, "pop") == 0) {
            code->instructions[code->count].op = MVM_OP_POP;
        } else if (strcmp(tok, "dup") == 0) {
            code->instructions[code->count].op = MVM_OP_DUP;
        } else if (strcmp(tok, "swap") == 0) {
            code->instructions[code->count].op = MVM_OP_SWAP;
        } else if (strcmp(tok, "ldt") == 0) {
            code->instructions[code->count].op = MVM_OP_LOAD_TOP;
        } else if (strcmp(tok, "over") == 0) {
            code->instructions[code->count].op = MVM_OP_OVER;
        } else if (strcmp(tok, "inc") == 0) {
            code->instructions[code->count].op = MVM_OP_INC;
        } else if (strcmp(tok, "dec") == 0) {
            code->instructions[code->count].op = MVM_OP_DEC;
        } else if (strcmp(tok, "add") == 0) {
            code->instructions[code->count].op = MVM_OP_ADD;
        } else if (strcmp(tok, "sub") == 0) {
            code->instructions[code->count].op = MVM_OP_SUB;
        } else if (strcmp(tok, "mul") == 0) {
            code->instructions[code->count].op = MVM_OP_MUL;
        } else if (strcmp(tok, "div") == 0) {
            code->instructions[code->count].op = MVM_OP_DIV;
        } else if (strcmp(tok, "eq") == 0) {
            code->instructions[code->count].op = MVM_OP_EQ;
        } else if (strcmp(tok, "neq") == 0) {
            code->instructions[code->count].op = MVM_OP_NEQ;
        } else if (strcmp(tok, "lt") == 0) {
            code->instructions[code->count].op = MVM_OP_LT;
        } else if (strcmp(tok, "lte") == 0) {
            code->instructions[code->count].op = MVM_OP_LTE;
        } else if (strcmp(tok, "gt") == 0) {
            code->instructions[code->count].op = MVM_OP_GT;
        } else if (strcmp(tok, "gte") == 0) {
            code->instructions[code->count].op = MVM_OP_GTE;
        } else if (strcmp(tok, "jmp") == 0) {
            code->instructions[code->count].op = MVM_OP_JMP;
            if ((tok = strtok_s(NULL, delimiters, &next_token))) {
                code->instructions[code->count].as.address = atoi(tok);
            }
        } else if (strcmp(tok, "not") == 0) {
            code->instructions[code->count].op = MVM_OP_NOT;
        } else if (strcmp(tok, "jz") == 0) {
            code->instructions[code->count].op = MVM_OP_JMP_IF_ZERO;
            if ((tok = strtok_s(NULL, delimiters, &next_token))) {
                code->instructions[code->count].as.address = atoi(tok);
            }
        } else if (strcmp(tok, "jnz") == 0) {
            code->instructions[code->count].op = MVM_OP_JMP_IF_NOT_ZERO;
            if ((tok = strtok_s(NULL, delimiters, &next_token))) {
                code->instructions[code->count].as.address = atoi(tok);
            }
        } else if (strcmp(tok, "call") == 0) {
            code->instructions[code->count].op = MVM_OP_CALL;
            if ((tok = strtok_s(NULL, delimiters, &next_token))) {
                code->instructions[code->count].as.address = atoi(tok);
            }
        } else if (strcmp(tok, "ret") == 0) {
            code->instructions[code->count].op = MVM_OP_RETURN;
        }
        code->count++;
        tok = strtok_s(NULL, delimiters, &next_token);
    }
}

void MVM_Code_ReadFromFile(struct MVM_Code *code, FILE *input)
{
    code->count = 0;
    char *buffer = malloc(MVM_MAX_FILE_SIZE + 1);

    while (fgets(buffer, MVM_MAX_FILE_SIZE, input) != NULL) {
        MVM_Code_ReadLine(code, buffer);
    }
}