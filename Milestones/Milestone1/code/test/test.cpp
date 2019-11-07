/**
 * PRG-Praktikum
 * Author: Joao Pargana 6807391
 *
 * Unittests for this milestone's project using the catch2 framework
 *
 */

#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN

#include "../include/catch.hpp"
#include "../include/cellular_automaton.hpp"


//------------------------------------------------------------------------------


TEST_CASE("matrices can set and resized", "[matrix]"){
    // test matrix constructor and size getter
    
    Matrix m1, m2(40), m3(20,40);

    REQUIRE(m1.get_row_size() == 0);
    REQUIRE(m1.get_col_size() == 0);

    REQUIRE(m2.get_row_size() == 40);
    REQUIRE(m2.get_col_size() == 40);

    REQUIRE(m3.get_row_size() == 20);
    REQUIRE(m3.get_col_size() == 40);

}


#endif
