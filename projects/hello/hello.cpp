#include <cmath>
#include <iostream>
#include <variables.h>
#include <sstream>

using namespace std;

const char *getVersion()
{
    std::stringstream sstr;
    sstr << PROGRAM_VERSION_MAJOR \
        << "." << PROGRAM_VERSION_MINOR \
        << "." << PROGRAM_VERSION_PATCH;
    return sstr.str().c_str();
}

int main(int argc, char *argv[])
{
    cout << TITLE_STRING << " v " << getVersion() << "\n";
    double const inputValue = std::stod(argv[1]);
    double const outputValue = sqrt(inputValue);
    cout << "√(" << inputValue << ") = " << outputValue << "\n";

    return 0;
}