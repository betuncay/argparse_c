
#ifndef RESULT_H_
#define RESULT_H_


typedef enum
{
    RESULT_OK,
    RESULT_ERROR
} result_e;

typedef struct
{
    result_e result_type;
    union
    {
        short result;
        char* error_msg;
    };
} result_int_t;

typedef struct
{
    result_e result_type;
    union
    {
        char* result;
        char* error_msg;
    };
} result_char_ptr_t;


#endif // RESULT_H_