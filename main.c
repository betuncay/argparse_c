#include "argparse.h"

// example input arguments:
// program.exe compress --file somefile --algorithm lzh --strength 123
// program.exe decompress --file somefile


int main(int argc, char *argv[])
{
    
    result_parsed_argument_t parsed_args = parse_args(argc, argv);
    return 1;
}