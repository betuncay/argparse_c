#ifndef ARGPARSE_H_
#define ARGPARSE_H_

#include "result.h"


typedef enum  {
    COMPRESS,
    DECOMPRESS
} command_e;

typedef enum  {
    RUN_LENGHT_ENCODING,
    HUFFMAN_ENCODING,
    LZH,
    COMPRESSION_ALGORITHMS_MAX
} compression_algorithm_t;

typedef struct {
    char file[256];
    char strength;
    compression_algorithm_t algorithm;
} compress_command_t;

typedef struct {
    char file[255];
    compression_algorithm_t algorithm;
} decompress_command_t;

typedef struct {
    command_e subcommand;
    union {
        compress_command_t compression_command;
        decompress_command_t decompression_command;
    } args;
} parsed_arguments_t;


typedef struct
{
    result_e result_type;
    union
    {
        parsed_arguments_t parsed_args;
        char* error_msg;
    } result;
} result_parsed_argument_t;


result_parsed_argument_t parse_args(int argc, char *argv[]);

#endif // ARGPARSE_H_