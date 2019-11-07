//
// Created by Hendrik
//

#ifndef PRG_PR_VIS_CRYPT_H
#define PRG_PR_VIS_CRYPT_H

//#include "matrix.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// using namespace std;

namespace VCrypt {

//    <T>
    class XBild {
    public:
//        <T>
//        XBild();

        // constructor
        XBild(unsigned int, unsigned int);

        ~XBild();

        void importFile(std::string file);
        void exportFile(std::string file);
    private:
        std::vector<std::vector <bool>> imageMx;
    };

    class NBild : XBild {
    public:
        NBild(unsigned int, unsigned int);
        ~NBild();
    private:
    };

    class CBild : XBild {
    private:
        CBild(unsigned int, unsigned int);
        ~CBild();
    public:
    };
}



#endif //PRG_PR_VIS_CRYPT_H
