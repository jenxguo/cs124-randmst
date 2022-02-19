#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

/* 
How to use: 
- "make"
- "g++ -Wall -o runtests ./runtests.cpp"
- "./runtests"
*/

int main() {
    ofstream myfile;
    myfile.open ("data.txt");
    myfile << ("numpoints, numtrials, dimension, avgWeight\n");
    myfile.close();

    for (int dimension = 0; dimension < 5; dimension++){
        if (dimension == 1){
            continue;
        }

        for (int numpoints = 5; numpoints <= 20; numpoints += 5){
                std::string line = "./randmst 0 ";
                line += to_string(numpoints);
                line += " 3 ";
                line += to_string(dimension);
                std::system(line.c_str());
        }
    }

    return 0;
}