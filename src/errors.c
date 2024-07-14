#include "errors.h"

void MVM_Error_Write(char *buffer, size_t buffer_size, struct MVM_Error *err)
{
    err->write(buffer, buffer_size);
}

void MVM_Error_Write_Data_Stack_Overflow(char *buffer, size_t buffer_size)
{

}

void MVM_Error_Write_Data_Stack_Underflow(char *buffer, size_t buffer_size)
{

}

void MVM_Error_Write_Call_Stack_Overflow(char *buffer, size_t buffer_size)
{

}

void MVM_Error_Write_Call_Stack_Underflow(char *buffer, size_t buffer_size)
{

}

static struct MVM_Error _MVM_Error_Data_Stack_Overflow = 
{ 
    .kind = MVM_ERR_DATA_STACK_OVERFLOW,
    .write = MVM_Error_Write_Data_Stack_Overflow,
};

static struct MVM_Error _MVM_Error_Data_Stack_Underflow = 
{
    .kind = MVM_ERR_DATA_STACK_UNDERFLOW,
    .write = MVM_Error_Write_Data_Stack_Underflow,
};

static struct MVM_Error _MVM_Error_Call_Stack_Overflow = 
{
    .kind = MVM_ERR_CALL_STACK_OVERFLOW,
    .write = MVM_Error_Write_Call_Stack_Overflow,
};

static struct MVM_Error _MVM_Error_Call_Stack_Underflow = 
{
    .kind = MVM_ERR_CALL_STACK_UNDERFLOW,
    .write = MVM_Error_Write_Call_Stack_Underflow,
};

struct MVM_Error *MVM_Error_Data_Stack_Overflow()
{
    return &_MVM_Error_Data_Stack_Overflow;
}

struct MVM_Error *MVM_Error_Data_Stack_Underflow()
{
    return &_MVM_Error_Data_Stack_Underflow;
}

struct MVM_Error *MVM_Error_Call_Stack_Overflow()
{
    return &_MVM_Error_Call_Stack_Overflow;
}

struct MVM_Error *MVM_Error_Call_Stack_Underflow()
{
    return &_MVM_Error_Call_Stack_Underflow;
}