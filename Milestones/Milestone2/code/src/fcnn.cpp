/**
 * PRG-Praktikum WS19/20
 * 
 * author: Joao Pargana
 * Gruppe: 3
 * 
 * main.cpp this source file contains a short script to read/write files
 * and train batches using the neural network
 * 
 */


#include "../include/network.hpp"
#include <regex>


//------------------------------------------------------------------------------


std::string menu = "\n\
Neural Network\n\n\
Usage:\n\
\tfcnn <command> [<args>]\n\n\
Command:\n\
\ttrain [<args>] <data>\n\
\tpredict <data>\n\n\
args:\n\
\ttopology <sizes>\n\n\
data: multiple file names\n\
\texample1.dat example2.dat ...\n\n\
size: layer size seperated by commas\n\
\t7,6,5,6,7,2\n";


//------------------------------------------------------------------------------


/**
 * This main function will execute a script with the users defined values
 * it can read batches from a given file or from multiple
 * 
 */
int main(int argc, const char** argv)

try
{
    std::regex re_sizes{R"(\d|(\d,\d)*)"};
    std::regex re_commands{R"(train|predict)"};

    if (argc < 3 || std::regex_match(argv[2], re_commands))
	throw std::runtime_error(menu);

    
    
    return 0;
}

catch(std::exception& e)
{
    std::cout << e.what() << std::endl;
    return 1;
}

catch(...)
{
    std::cout << "Something went wrong..." << std::endl;
    return 2;
}
