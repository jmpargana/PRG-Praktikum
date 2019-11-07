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

    class XBild {
    public:
        // constructor
        XBild();

        XBild(unsigned int, unsigned int);

        // destructor
        ~XBild();

        // methods
        void importFile(std::string file);

        void exportFile(std::string file);

    private:
        // image in matrix representation
        std::vector <std::vector<bool>> imageMx;
    };

    class NBild : public XBild {
    public:
        NBild();

        NBild(unsigned int x, unsigned int y);

        ~NBild();

    private:
    };

    class CBild : public XBild {
    public:
        CBild();

        CBild(unsigned int x, unsigned int y);

        ~CBild();

    private:
    };
}


#endif //PRG_PR_VIS_CRYPT_H
