#ifndef ARGPARSE_H_
#define ARGPARSE_H_

#include "result.h"
#include "stdbool.h"

typedef enum  {
    COMMAND_COMPRESS,
    COMMAND_DECOMPRESS
} command_e;

typedef enum  {
    RUN_LENGHT_ENCODING,
    HUFFMAN_ENCODING,
    LZH,
    COMPRESSION_ALGORITHMS_MAX
} compression_algorithm_t;

typedef struct {
    char* file;
    bool verbose;
    compression_algorithm_t algorithm;
} compress_command_t;

typedef struct {
    char* file;
    compression_algorithm_t algorithm;
} decompress_command_t;

typedef struct {
    command_e subcommand;
    union {
        compress_command_t compression_command;
        decompress_command_t decompression_command;
    };
} parsed_arguments_t;
// maybe consider simplifying to flat structure for now


typedef struct
{
    result_e result_type;
    union
    {
        parsed_arguments_t parsed_args;
        char* error_msg;
    };
} result_parsed_argument_t;

result_parsed_argument_t parse_args(int argc, char *argv[]);

#endif // ARGPARSE_H_