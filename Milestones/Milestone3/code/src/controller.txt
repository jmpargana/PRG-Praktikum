#include "../include/controller.h"

Controller::Controller() {}

Controller::setTypology(unsigned x, unsigned y, unsigned z) {
    qgp_identifier = MultiLayerPerceptron qgp_identifier({x, y, z});
}

Controller::setSplit(unsigned train, unsigned test, std::string qgp_path, std::string nqgp_path) {
//    TODO loop until x and write to train; from x to end write to test
//    [[qgp train], [nqgp train], [qgp test], [nqgp test]]
    parse_directory(qgp_path, complete_list[0])
    parse_directory(nqgp_path, complete_list[1])
    parse_directory(qgp_path, complete_list[2])
    parse_directory(nqgp_path, complete_list[3])
}

Controller::startTraining() {
    try
    {
        // save all the data to two vectors (true and false)
        parse_directory("../../materials/dataset_new/qgp", complete_list[0]);
        parse_directory("../../materials/dataset_new/nqgp", complete_list[1]);

        if (argc != 4)
            throw std::runtime_error("Usage:\n\tfcnn <epochs> <epoch_size> <batch_size>");

        run_epoch();
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
}