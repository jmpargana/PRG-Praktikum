#ifndef PRG_PR_CONTROLLER_H
#define PRG_PR_CONTROLLER_H

#include "./multi_layer_perceptron.hpp"
#include <boost/filesystem.hpp>

#include <regex>
#include <map>
#include <algorithm>

//using fsd = boost::filesystem::directory_entry;
//namespace bnu = boost::numeric::ublas;

class Controller {

public:
    Controller();
    ~Controller();

    boost::numeric::ublas::matrix<double> import_file(std::string);
    void batch_normalization(unsigned, std::vector<std::vector<boost::filesystem::directory_entry>>&);
    void parse_directory(const char*, std::vector<boost::filesystem::directory_entry>&);
    void run_epoch(unsigned, unsigned, unsigned);

    void setTypology(unsigned, unsigned, unsigned);
    void setSplit(unsigned, unsigned, std::string, std::string);
    int startTraining();

private:
    MultiLayerPerceptron qgp_identifier;
//    [[qgp train], [nqgp train], [qgp test], [nqgp test]]
    std::vector<std::vector<boost::filesystem::directory_entry>> complete_list;
};

#endif //PRG_PR_CONTROLLER_H
