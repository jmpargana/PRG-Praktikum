/**
 * PRG-Praktikum
 * Author: Joao Pargana 6807391
 *
 * Main file to run game of life in console
 *
 */


#include "../include/cellular_automaton.hpp"


//------------------------------------------------------------------------------


std::string menu =		// menu to be shown to user
    "Game Of Life!\n\n\
Menu:\n\
\t1 -> \tImport from file\n\
\t2 -> \tExport to file\n\
\t3 -> \tNext Life\n\
\t4 -> \tRead cell\n\
\t5 -> \tChange cell\n\
\t6 -> \tRandom start\n\
\t0 -> \tExit Game\n\
";

char key;			// read input from user
CellularAutomaton ca;		// global variable with cellular automaton


//------------------------------------------------------------------------------


void import_file()
// read cellular automaton matrix from given file name as input
{
    std::string file_name;
    std::cout << "Enter input file name:" << std::endl;
    std::cin >> file_name;

    std::ifstream ist {file_name}; // instatiate input file stream with fiven string
    if (!ist) throw std::runtime_error("File not found"); // test if file can be opened

    ist >> ca; 			// input file to cellular automaton
    std::cout << "Successfully read file \"" << file_name << '\"' << std::endl;
}


//------------------------------------------------------------------------------


void export_file()
// save current state of cellular automaton to given file name
{
    std::string file_name;
    std::cout << "Enter output file name:" << std::endl;
    std::cin >> file_name;

    std::ofstream ost {file_name}; // check if output file stream can be opened
    if (!ost) throw std::runtime_error("Couldn't open file"); // error detection

    ost << ca;
    std::cout << "Successfully wrote to file \"" << file_name << '\"' << std::endl;
}



//------------------------------------------------------------------------------


void read_cell()
// after testing user's input read value in given cell
{
    unsigned row = 30000, col = 30000;		// initialize with impossible value

    // avoid invalid input
    while (row >= ca.get_rows() || col >= ca.get_cols()) {
	std::cout << "Give a row and column value:" << std::endl;
	std::cin >> row >> col;
    }

    std::cout << "The value in " << row << ' ' << col << " is:" << std::endl;
    std::cout << ca[row][col] << std::endl;
}


//------------------------------------------------------------------------------


void change_cell()
// change cell value by overriding matrix value via subscripting
{
    unsigned new_value = 2, row = 30000, col = 30000;

    while (new_value > 1) {
	std::cout << "Give new value (1 for true or 0 for false)" << std::endl;
	std::cin >> new_value;
    }

    while (row >= ca.get_rows() || col >= ca.get_cols()) {
	std::cout << "Give a row and column value:" << std::endl;
	std::cin >> row >> col;
    }

    ca[row][col] = (new_value);
    std::cout << "Value successfully updated to " << new_value << " in "
	      << row << ' ' << col << std::endl;
}


//------------------------------------------------------------------------------


void random_start()
// initiate or override cellular automaton with random true or false values
{
    for (int row=0; row<ca.get_rows(); ++row) {
	for (int col=0; col<ca.get_cols(); ++col) {
	    ca[row][col] = random();
	}
    }
    std::cout << ca << std::endl;
}


//------------------------------------------------------------------------------


int main(int argc, const char** argv)
// main function runs console game presenting the user a simple menu
// the user is prompted some numbers and manipulates the game using them
// including functionalities are importing and exporting of files
// showing next phase of cellular automaton, reading and writing specific cell
// initiate game with random values and exit at any time
try
{
    // run until case '0' has been selected
    while (true) {
	std::cout << menu << std::endl;
	std::cin >> key;
	
	switch (key) {
	case '1': import_file();
	case '2': export_file();
	case '3': ++ca; std::cout << ca << std::endl;
	case '4': read_cell();
	case '5': change_cell();
	case '6': random_start();
	case '0': exit(0);
	default: continue;	// ignore invalid input
	}
    }
	
    return 0;
}

catch (std::exception& e)
{
    std::cout << e.what() << std::endl;
    return 1;
}

catch (...)
{
    std::cerr << "Something failed" << std::endl;
    return 2;
}
    
