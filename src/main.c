#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "vm.h"
#include "errors.h"

int main(int argc, const char **argv)
{
    struct MVM_Machine vm;
    struct MVM_Code code;
    struct MVM_Error *err;
    code.count = 0;
    code.capacity = 512;
    code.instructions = calloc(code.capacity, sizeof(struct MVM_Instruction));
    if (argc > 1) {
        FILE *input;
        errno_t err = fopen_s(&input, argv[1], "r");
        if (err != 0) {
            printf("could not open file: %s\n", argv[1]);
            return 1;
        }
        MVM_Code_ReadFromFile(&code, input);
        fclose(input);
    }
    printf("code count: %hd\n", code.count);
    for (int i = 0; i < code.count; i++) {
        printf("instruction: %hu\n", code.instructions[i].op);
    }
    MVM_Machine_Init(&vm);
    MVM_Machine_RunCode(&vm, code, &err);
    printf("acc: %d\n", vm.acc);
    printf("sp: %zu\n", vm.sp);
    for (int i = 0; i < vm.sp; i++) {
        printf("cell %d: %d\n", i, vm.stack[i]);
    }
}