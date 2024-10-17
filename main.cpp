#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <array>
#include <memory>

#include "include/algs.h"
#include "include/cppFit/CSV_Writer.h"
#include "include/cppFit/Gen.h"

int start = 1;
int end = 10000;
int increment = 100;
bool sorted = true;

std::string csvPath = "runningTimes.csv"; 

std::string call_py(std::string path, std::vector<std::string> argv){
    std::string command = "python3 " + path;
    for(auto arg:argv) command += " " + arg;

    std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose); // pclose shares pipe
    char buffer[128];
    std::string py_output;

    while(fgets(buffer, 128, pipe.get())){
        py_output += buffer;
    }

    return py_output;

}

int main() {
    std::cout << "Creating CSV File..." << std::endl;
    Gen gen(csvPath, start, end, increment, sorted);
    std::cout << "Generating running times..." << std::endl;
    gen.gen_csv();
    std::cout << "Calling Python script..." << std::endl;
    std::string py_op = call_py("analyse.py", {csvPath});
    std::cout << py_op;
}