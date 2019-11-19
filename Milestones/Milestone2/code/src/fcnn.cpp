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


// variable will be updated as soon as files are
// read and topology is given
Network neural_network({224000, 200, 100, 50, 1});


//------------------------------------------------------------------------------


/**
 * Iterate throw the whole given directory and append all file names
 * to a given vector
 * @param input_dir folder name
 * @param other vector where it should be saved
 */
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
 * This method imports a given file and initializes the network with 
 * the given tipology 
 * @param file_name 
 */
void import_file(std::string file_name)
{
    
}


//------------------------------------------------------------------------------


void run_batch(boost::filesystem::directory_entry event)
{
    import_file(event.path().string());
    
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
    // random generator for nqgp or qgp file
    auto gen = std::bind(std::uniform_int_distribution<>(0,1),std::default_random_engine());

    // read all files from both folders in the dataset
    std::vector<std::vector<boost::filesystem::directory_entry>>
	complete_list(2, std::vector<boost::filesystem::directory_entry>(5000));

    // save all the data to two vectors (true and false)
    parse_directory("../../materials/dataset_new/qgp", complete_list[0]);
    parse_directory("../../materials/dataset_new/nqgp", complete_list[1]);

    // select 20 events randomly and perform the batches until
    // there are no files left for the training
    while (!complete_list[0].empty() && !complete_list[1].empty()) {
	
	for (unsigned i=0; i<20; ++i) {
	    unsigned temp = gen();
	    // train file
	    boost::filesystem::directory_entry event = complete_list[temp][complete_list.size() - 1];
	    complete_list[temp].pop_back();
	    run_batch(event);
	}
	// after the whole batch is done perform back propagation
	neural_network.back_propagation();
    }
    // after the traning
    
    
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
