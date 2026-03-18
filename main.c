#include "argparse.h"
#include "result.h"
#include <stdio.h>

// example input arguments:
// program.exe compress --file somefile --algorithm lzh --verbose
// program.exe decompress --file somefile


int main(int argc, char *argv[])
{
    
    result_parsed_argument_t result_parsed_args = parse_args(argc, argv);
    if (result_parsed_args.result_type == RESULT_ERROR) 
    {
        printf("%s\n", result_parsed_args.error_msg);
    }

    parsed_arguments_t parsed_args = result_parsed_args.parsed_args;

    return 1;
}