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
    myfile << ("k_runtime1, missingV1, k_runtime2, missingV3, k_runtime3, missingV3, k_runtime4, missingV4, k_runtime5, missingV5, numpoints, numtrials, dimension, avgWeight, totaltime \n");
    myfile.close();

    int numpoints[11] = {128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072};

    for (int dimension = 0; dimension < 5; dimension++){
        if (dimension == 1){
            continue;
        }

        for (int i = 0; i < 10; i++) {
            int n = numpoints[i];
            std::string line = "./randmst 0 ";
            line += to_string(n);
            line += " 5 ";
            line += to_string(dimension);
            std::system(line.c_str());
        }
    }

    return 0;
}