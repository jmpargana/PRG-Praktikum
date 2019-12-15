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

    void parse_directory(const char*, std::vector<boost::filesystem::directory_entry>);
    void run_epoch(unsigned, unsigned, unsigned);
    void batch_normalization(unsigned, std::vector<std::vector<boost::filesystem::directory_entry>>&)
    boost::numeric::ublas::matrix<double> import_file(std::string);

    void setTypology(unsigned, unsigned, unsigned);
    void setSplit(unsigned, unsigned);
    void startTraining();

private:
    MultiLayerPerceptron qgp_identifier({224000, 2, 1});
//    TODO: why 2 and why 5000?
//    [[qgp train], [nqgp train], [qgp test], [nqgp test]]
    std::vector<std::vector<boost::filesystem::directory_entry>> complete_list(2, std::vector<boost::filesystem::directory_entry>(5000));
};

#endif //PRG_PR_CONTROLLER_H
