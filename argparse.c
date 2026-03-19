#include "argparse.h"
#include "result.h"
#include "stdio.h"
#include "string.h"

char* DEFAULT_MESSAGE = "Incorrect usage. To use this program do blablabla...";

// #TODO Assert that length of array == COMPRESSION_ALGORITHMS_MAX
char* compression_algorithm_string_map[] = {
    [RUN_LENGHT_ENCODING] = "run_length_encoded",
    [HUFFMAN_ENCODING] = "huffman_encoding",
    [LZH] = "lzh"
};


result_char_ptr_t get_compression_algorithm_string(compression_algorithm_t compression_algorithm) 
{
    result_char_ptr_t result;
    if (0 <= compression_algorithm && compression_algorithm < COMPRESSION_ALGORITHMS_MAX)
    {
        result.result_type = RESULT_OK;
        result.result = compression_algorithm_string_map[compression_algorithm];
    }
    else 
    {
        result.result_type = RESULT_ERROR;
        result.result = "Tried to get non existent compression algorithm";
    }
    
    return result;
}

// example input arguments:
// program.exe compress --file somefile --algorithm lzh --strength 123
// program.exe decompress --file somefile

// first idea to parse
// view args as a finite state machine -> accepting state = finished one argument
// then restart state machine / or if subcommands different start next state machine!
// example machine
// (s_0) --(--file)--> (s_1) --(any kind of string)--> ((s_2))


typedef enum {
    ARGS_STATE_START,
    ARGS_STATE_FILE,
    ARGS_STATE_ALGORITHM,
    ARGS_MAX_VALUE // sentinal state
} arg_state_e;
int state = 0;

arg_state_e arg_state = ARGS_STATE_START;
int arg_state_visited[ARGS_MAX_VALUE] = {0};


result_parsed_argument_t parse_args(int argc, char *argv[])
{
    result_parsed_argument_t result;
    for (int i = 1; i < argc; ++i)
    {
        char* token = argv[i];
        switch (state)
        {
            case ARGS_STATE_START:
            {
                // check possible transitions (e.g. --file, --strength, compress)
                if (strcmp(token, "--file") == 0)
                {
                    state = ARGS_STATE_FILE;
                }
                else if(strcmp(token, "--algorithm") == 0) 
                {
                    state = ARGS_STATE_ALGORITHM;
                }
                else if(strcmp(token, "--verbose") == 0) 
                {

                }
                else if(strcmp(token, "compress") == 0) 
                {
                    state = ARGS_STATE_START;
                    result.parsed_args.subcommand = COMMAND_COMPRESS; // TODO possible bug -> what if other subcommand has already been set? Simple fix -> Make state machine bigger (so that its impossible)
                }
                else if(strcmp(token, "decompress") == 0) 
                {
                    state = ARGS_STATE_START;
                    result.parsed_args.subcommand = COMMAND_DECOMPRESS; // TODO possible bug -> what if other subcommand has already been set?
                }
                else 
                {
                    result.result_type = RESULT_ERROR;
                    result.error_msg = DEFAULT_MESSAGE;
                    return result;
                }
                break;
            }

            case ARGS_STATE_FILE:
            {
                if (arg_state_visited[state] == 0)
                {
                    result.parsed_args.compression_command.file = token;
                    arg_state_visited[state]++;
                    state = ARGS_STATE_START;
                }
                else 
                {
                    result.result_type = RESULT_ERROR;
                    result.error_msg = "Argument --file can only be specified once.";
                    return result;
                }
                break;
            }

            case ARGS_STATE_ALGORITHM:
            {
                if (arg_state_visited[state] == 0)
                {
                    for (compression_algorithm_t algorithm = 0; algorithm < COMPRESSION_ALGORITHMS_MAX; algorithm++)
                    {
                        result_char_ptr_t algorithm_result = get_compression_algorithm_string(algorithm);
                        if (algorithm_result.result_type == RESULT_ERROR)
                        {
                            result.result_type = RESULT_ERROR;
                            result.error_msg = algorithm_result.error_msg;
                            return result;
                        }
                        else if (strcmp(algorithm_result.result, token))
                        {
                            result.parsed_args.compression_command.algorithm = algorithm;
                        }
                    }

                    arg_state_visited[state]++;
                    state = ARGS_STATE_START;
                    break;
                }
                else 
                {
                    result.result_type = RESULT_ERROR;
                    result.error_msg = "Argument --algorithm can only be specified once.";
                    return result;
                }
                break;
            }

        }
        printf("%s, (State: %d)\n", argv[i], state);
    }
    return result;
}