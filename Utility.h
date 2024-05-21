#ifndef SEARCH_AND_SORT_UTILITY_H
#define SEARCH_AND_SORT_UTILITY_H

// All libraries are included in the Utility header file for avoiding multiple includes and conflicts
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib> // For system()
#include <iomanip>

enum Error_code {
    success,
    fail,
    utility_range_error,
    range_error,
    overflow,
};

using std::cout;
using std::cin;
using std::exit;
using std::endl;
using std::flush;
using std::vector;
using std::setw;
using std::setfill;
using std::left;
using std::stringstream;
using std::getline;
using std::string;
using std::ifstream;
using std::ofstream;
using std::istream;

bool user_says_yes();
void print_menu();

#endif //SEARCH_AND_SORT_UTILITY_H