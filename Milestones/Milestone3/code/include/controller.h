#ifndef PRG_PR_CONTROLLER_H
#define PRG_PR_CONTROLLER_H

#include "./multi_layer_perceptron.hpp"
#include <boost/filesystem.hpp>

#include <regex>
#include <map>
#include <algorithm>
#include <QObject>

#include <iostream>
#include <ctime>

//using fsd = boost::filesystem::directory_entry;
//namespace bnu = boost::numeric::ublas;

class Controller : public QObject {
    Q_OBJECT

public:
    Controller();
    ~Controller();

public slots:
    boost::numeric::ublas::matrix<double> import_file(std::string);
    double batch_normalization(unsigned, std::vector<std::vector<boost::filesystem::directory_entry>>&);
    void parse_directory(const char*, std::vector<boost::filesystem::directory_entry>&);
    void run_epoch(unsigned, unsigned, unsigned);

    void setTrainingDataDirectory(const QString& path);
    void setTypology(const QVector<unsigned> &topology);
    void setSplit(unsigned percentageTest);
    void setEpochNo(int epochNo);
    int startTraining();

signals:
    // used for listening to events and passing the information to other objects
    void epochTrained(int epochNumber);
    void newDataPoint(QString plotName, double xvalue, double yvalue);

private:
    MultiLayerPerceptron qgp_identifier;
//    [[qgp train], [nqgp train], [qgp test], [nqgp test]]
    unsigned m_percentageTest;
    int m_epochNo;
    QString m_trainingDataPath;
    std::vector<std::vector<boost::filesystem::directory_entry>> complete_list;
};

#endif //PRG_PR_CONTROLLER_H
