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


#include "../include/multi_layer_perceptron.hpp"
#include <regex>
#include <boost/filesystem.hpp>
#include <map>


//------------------------------------------------------------------------------


using fsd = boost::filesystem::directory_entry;


//------------------------------------------------------------------------------


/**
 * Global Variables
 */

// Neural network for qgp identification
MultiLayerPerceptron qgp_identifier({224000, 2, 1});

// random boolean generator
auto gen = std::bind(std::uniform_int_distribution<>(0,1),std::default_random_engine());

// two lists with all qgp events from dataset
// saved with boolean corresponding to their output
std::vector<std::vector<fsd>> complete_list(2, std::vector<fsd>(5000));


//------------------------------------------------------------------------------


/**
 * This method imports a given file and initializes the network with 
 * the given tipology 
 * @param file_name 
 * @param event contains the vector with 
 */
bnu::matrix<double> import_file(std::string file_name)
{
    std::ifstream ist {file_name};
    if (!ist) throw std::runtime_error("Couldn't open file");

    int temp;
    bnu::matrix<double> event(224000, 1);
    
    for (unsigned i_row=0; i_row<event.size1(); ++i_row){
	ist >> temp;
	event(i_row, 1) = temp;
    }

    return event;
}


//------------------------------------------------------------------------------


void batch_normalization(unsigned s_batch)
{
    std::map<double, bool> events;
    
    for (unsigned i=0; i<s_batch; ++i) {
	unsigned temp = gen();
	bnu::matrix<double> target(1, 1); target(1, 1) = temp;

	fsd event = complete_list[temp][complete_list.size() - 1];
	complete_list[temp].pop_back();

	qgp_identifier.forward_propagation(import_file(event.path().string()));
	events[qgp_identifier[qgp_identifier.size() - 1].m_output(1,1)] =
	    (bool)temp;
    }

    // perform batch normalization and use result for back propagation
    // qgp_indentifier.back_propagation(e);
}


//------------------------------------------------------------------------------


void run_epoch(unsigned n_epochs, unsigned s_batch)
{
    for (unsigned i_epoch=0; i_epoch<n_epochs; ++i_epoch) {
	batch_normalization(s_batch);
    }
}


//------------------------------------------------------------------------------


/**
 * Iterate throw the whole given directory and append all file names
 * to a given vector
 * @param input_dir folder name
 * @param other vector where it should be saved
 */
void parse_directory(const char* input_dir, std::vector<fsd>& other)
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
    // save all the data to two vectors (true and false)
    parse_directory("../../materials/dataset_new/qgp", complete_list[0]);
    parse_directory("../../materials/dataset_new/nqgp", complete_list[1]);

    if (argc != 3)
	throw std::runtime_error("Usage:\n\tfcnn <epochs> <batch_size>");
    
    run_epoch(atoi(argv[2]), atoi(argv[3])); // number of epochs & batch size
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
