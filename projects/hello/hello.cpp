#include <cmath>
#include <iostream>
#include <variables.h>
#include <sstream>

using namespace std;

const char *concat(int nparts, string parts[])
{
    std::stringstream result;

    for (int i = 0; i < nparts; ++i)
    {
        result << parts[i];
    }
    return result.str().c_str();
}

const char *getVersion()
{
    string components[] = {PROGRAM_VERSION_MAJOR,
                           ".", PROGRAM_VERSION_MINOR,
                           ".", PROGRAM_VERSION_PATCH};
    return concat(5, components);
}

void printCalculus(double number, double root)
{
    cout << "√(" << number << ") = " << root << "\n";
}

int main(int argc, char *argv[])
{
    cout << TITLE_STRING << " v " << getVersion() << "\n";
    double const inputValue = std::stod(argv[1]);
    double const outputValue = sqrt(inputValue);
    printCalculus(inputValue, outputValue);

    return 0;
}