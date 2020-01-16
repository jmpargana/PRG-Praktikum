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
#include "../lib/filesystem.hpp"
#include <regex>
#include <map>
#include <algorithm>


//------------------------------------------------------------------------------


using fsd = boost::filesystem::directory_entry;


//------------------------------------------------------------------------------


/**
 * Global Variables
 */

// Neural network for qgp identification
MultiLayerPerceptron qgp_identifier({224000, 2, 1});

// random boolean generator
auto genn = std::bind(std::uniform_int_distribution<>(0,1),std::default_random_engine());

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
	event(i_row, 0) = temp;
    }

    return event;
}


//------------------------------------------------------------------------------


/** 
 * This function iterates s_batch times and performs the
 * forward propagation in the neural network with the input
 * read from a randomly selected event file
 * It later calculates the batch mean and calls the back propagation
 * method with it to update the weights 
 * @param s_batch is the number of times it should iterate
 */
void batch_normalization(unsigned s_batch,
			 std::vector<std::vector<fsd>>& copied_list)
{
    std::map<double, double> events; bnu::matrix<double> mean_inputs(224000, 1);
    
    for (unsigned i=0; i<s_batch; ++i) {
        unsigned temp = genn();
        bnu::matrix<double> target(1, 1); target(0, 0) = temp;

        fsd event = copied_list[temp][copied_list[temp].size() - 1];
        complete_list[temp].pop_back();

        bnu::matrix<double> input(import_file(event.path().string()));
        mean_inputs += input;

    	qgp_identifier.forward_propagation(std::move(input));
    	events[qgp_identifier[qgp_identifier.size() - 1].m_output(0,0)] = temp;
    }

    std::transform(mean_inputs.begin1(), mean_inputs.end1(), mean_inputs.begin1(),
		  [&](double val) {
		      return val / s_batch;
		  });
    
    // perform batch normalization and use result for back propagation
    double total_cost = 0.0; 
    std::for_each(events.begin(), events.end(),
		  [&total_cost](std::pair<double, double> p) {
		      total_cost += std::abs(p.second - p.first);
		  });
    
    bnu::matrix<double> target(1,1); target(0, 0) = total_cost;    
    qgp_identifier.back_propagation(std::move(target), std::move(mean_inputs));
}


//------------------------------------------------------------------------------


/**
 * This function runs n epoches with the given s_epoch and s_batch
 * number, where s_epoch means the amount of events to be loaded
 * and s_batch the amount of events before each back propagation
 * @param n_epochs number of epoches
 * @param s_epoch amount of events
 * @param s_batch number of feed forward without back propagation
 * 
 */
void run_epoch(unsigned n_epochs, unsigned s_epoch, unsigned s_batch)
{
    if (s_epoch > 10000)
	    throw std::runtime_error("Only 10000 events available");

    for (unsigned i_epoch=0; i_epoch<n_epochs; ++i_epoch) {
	    std::vector<std::vector<fsd>> copied_list(2, std::vector<fsd>(s_epoch/2));

	    for (unsigned i=0; i<s_epoch/2; ++i) {
            copied_list[0][i] = complete_list[0][i];
            copied_list[1][i] = complete_list[1][i];
        }
	
        batch_normalization(s_batch, copied_list);
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
    parse_directory("../materials/dataset_new/qgp", complete_list[0]);
    parse_directory("../materials/dataset_new/nqgp", complete_list[1]);

    if (argc != 4)
    	throw std::runtime_error("Usage:\n\tfcnn <epochs> <epoch_size> <batch_size>");

    run_epoch(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
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
