#include "../include/controller.h"

#include <QDebug>

auto gennn = std::bind(std::uniform_int_distribution<>(0,1),std::default_random_engine());

Controller::Controller()
    : qgp_identifier({224000, 2, 1}),
      complete_list(2, std::vector<boost::filesystem::directory_entry>(5000))
{}

Controller::~Controller()
{

}

boost::numeric::ublas::matrix<double> Controller::import_file(std::string file_name)
{
    std::ifstream ist {file_name};
    if (!ist) throw std::runtime_error("Couldn't open file");

    int temp;
    boost::numeric::ublas::matrix<double> event(224000, 1);

    for (unsigned i_row=0; i_row<event.size1(); ++i_row){
        ist >> temp;
        event(i_row, 0) = temp;
    }

    return event;
}

void Controller::batch_normalization(unsigned s_batch, std::vector<std::vector<boost::filesystem::directory_entry>>& copied_list)
{
    std::map<double, double> events; boost::numeric::ublas::matrix<double> mean_inputs(224000, 1);

    for (unsigned i=0; i<s_batch; ++i) {
        unsigned temp = gennn();
        boost::numeric::ublas::matrix<double> target(1, 1); target(0, 0) = temp;

        boost::filesystem::directory_entry event = copied_list[temp][copied_list[temp].size() - 1];
        complete_list[temp].pop_back();

        boost::numeric::ublas::matrix<double> input(import_file(event.path().string()));
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

    boost::numeric::ublas::matrix<double> target(1,1); target(0, 0) = total_cost;
    qgp_identifier.back_propagation(std::move(target), std::move(mean_inputs));
}

void Controller::run_epoch(unsigned n_epochs, unsigned s_epoch, unsigned s_batch)
{
    if (s_epoch > 10000)
        throw std::runtime_error("Only 10000 events available");

    for (unsigned i_epoch=0; i_epoch<n_epochs; ++i_epoch) {
        std::vector<std::vector<boost::filesystem::directory_entry>> copied_list(2, std::vector<boost::filesystem::directory_entry>(s_epoch/2));

        for (unsigned i=0; i<s_epoch/2; ++i) {
            copied_list[0][i] = complete_list[0][i];
            copied_list[1][i] = complete_list[1][i];
        }

        batch_normalization(s_batch, copied_list);
    }
}

void Controller::parse_directory(const char* input_dir, std::vector<boost::filesystem::directory_entry>& other)
{
    unsigned i_file=0;
    for (auto& file : boost::filesystem::directory_iterator(input_dir)) {
        other[i_file] = file;
        ++i_file;
    }
}

void Controller::setTypology(const QVector<unsigned>& topology) {
    qDebug() << "new topology" << topology;
    qgp_identifier = MultiLayerPerceptron(topology.toStdVector());
}

void Controller::setSplit(unsigned train, unsigned test, std::string qgp_path, std::string nqgp_path) {
//    TODO loop until x and write to train; from x to end write to test
//    [[qgp train], [nqgp train], [qgp test], [nqgp test]]
//    parse_directory(qgp_path, complete_list[0])
//    parse_directory(nqgp_path, complete_list[1])
//    parse_directory(qgp_path, complete_list[2])
//    parse_directory(nqgp_path, complete_list[3])
    std::cout << "test" << std::endl;
}

int Controller::startTraining() {
    qDebug() << "starting training";
    try
    {
        // save all the data to two vectors (true and false)
//        parse_directory("../../materials/dataset_new/qgp", complete_list[0]);
//        parse_directory("../../materials/dataset_new/nqgp", complete_list[1]);

//        if (argc != 4)
//            throw std::runtime_error("Usage:\n\tfcnn <epochs> <epoch_size> <batch_size>");

        run_epoch(100, 100, 10);
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
