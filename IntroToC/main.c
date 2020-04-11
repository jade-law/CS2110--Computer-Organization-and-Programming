/**
 * @file main.c
 * @author YOUR TAs!
 * @date 2020-03-06
 * 
 * DO NOT MODIFY THIS FILE.
 */
#include "hw7.h"

/**
 * @brief Main method, responsible for parsing command line argument and populating expression structs in the global arr
 * 
 * Note: This function/file is provided as the entry point of the program. 
 * All it does is to call your my_main function in hw7.c with the command line arguments.
 * 
 * In any C program, there would be only one true "main" function, however, 
 * this is due to the way the local autograder is setup.
 * 
 * Run "make hw7" to get the hw7 object file and then run the program like:
 * ./hw7 "3+0x40-7+5" "0xA6+5000-45"
 * ./hw7 -d "3+0x40-7+5" "0xA6+5000-45"
 * 
 * @param argc argument count
 * @param argv argument vector (it's an array of strings)
 * @return int status code of the program termination
 */
int main(int argc, char const *argv[])
{
    return my_main(argc, argv);
}
