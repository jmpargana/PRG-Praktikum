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
#include <boost/filesystem.hpp>


//------------------------------------------------------------------------------


// only needed for script version of this program
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


void parse_directory(const char* input_dir,
		     std::vector<boost::filesystem::directory_entry>& other)
{
    unsigned i_file=0;
    for (auto& file : boost::filesystem::directory_iterator(input_dir)) {
	other[i_file] = file;
	++i_file;
    }
}


//------------------------------------------------------------------------------


/**
 * This main function will execute a script with the users defined values
 * it can read batches from a given file or from multiple
 * 
 */
int main(int argc, const char** argv)

try
{
    // read all files from both folders in the dataset
    std::vector<boost::filesystem::directory_entry> nqgp(5000);
    std::vector<boost::filesystem::directory_entry> qgp(5000);

    // save all the data to two vectors (true and false)
    parse_directory("../../materials/dataset_new/qgp", qgp);
    parse_directory("../../materials/dataset_new/nqgp", nqgp);

    // select 20 events randomly and perform the batches until
    // there are no files left for the training
    
    
    
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
