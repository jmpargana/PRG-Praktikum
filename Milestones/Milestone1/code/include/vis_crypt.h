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
#include <stdio.h>
#include <iostream>
#include <sstream>

//using namespace std;

//namespace VCrypt {

class XBild {
public:
    // constructor
    XBild();

    XBild(unsigned int, unsigned int);

    // assignment operator
    XBild &operator=(const XBild &);

    // move constructor and move operator
    XBild &operator=(XBild &&) noexcept;

    // read & write
    std::vector<bool> &operator[](unsigned);

    // read only
    const std::vector<bool> &operator[](unsigned) const;

    // destructor
    ~XBild();

    void printImage();

    unsigned get_x_size() const;

    unsigned get_y_size() const;

    // methods
    void importFile(std::string);

    void exportFile(std::string);

private:
    // image in matrix representation
    std::vector <std::vector<bool>> imageMx;
    unsigned xLen, yLen;
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
//} // namespace VCrypt

#endif //PRG_PR_VIS_CRYPT_H
