#include "argparse.h"
#include "stdio.h"


char* DEFAULT_MESSAGE = "Error default message. Please set something here";


result_parsed_argument_t parse_args(int argc, char *argv[])
{
    result_parsed_argument_t result;
    for (int i = 0; i < argc; ++i)
    {
        printf("%s\n", argv[i]);
    }
    return result;
}