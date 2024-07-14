#pragma once

#include <stdint.h>

typedef void (*MVM_Error_Writer)(char *buffer, size_t buffer_size);

enum MVM_Error_Kind
{
    MVM_ERR_DATA_STACK_OVERFLOW,
    MVM_ERR_DATA_STACK_UNDERFLOW,
    MVM_ERR_CALL_STACK_OVERFLOW,
    MVM_ERR_CALL_STACK_UNDERFLOW,
};

struct MVM_Error
{
    enum MVM_Error_Kind kind;
    MVM_Error_Writer write;
};

void MVM_Error_Write(char *buffer, size_t buffer_size, struct MVM_Error *err);
struct MVM_Error *MVM_Error_Data_Stack_Overflow();
struct MVM_Error *MVM_Error_Data_Stack_Underflow();
struct MVM_Error *MVM_Error_Call_Stack_Overflow();
struct MVM_Error *MVM_Error_Call_Stack_Underflow();