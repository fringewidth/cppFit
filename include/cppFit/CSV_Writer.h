#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

class CSV_Writer {
    private:
        std::string file_path;
        std::ofstream writer;
        int n_col{-1};
        bool is_open{false};

    public:
        CSV_Writer(const std::string& file_path) : file_path(file_path) {
            if(file_path.substr(file_path.size() - 4) != ".csv") throw std::invalid_argument("File must be a CSV");
            writer.open(file_path, std::ios::out | std::ios::app);
            if(!writer.is_open()) throw std::runtime_error("Error in opening file");
        }

        void define_header(const std::vector<std::string>& headers){
            if(headers.empty()) throw std::invalid_argument("Headers cannot be empty");
            if(writer.tellp() != 0) throw std::runtime_error("File already has rows defined.");
            n_col = headers.size();
            add_rows(headers);
        }

        void add_rows(const std::vector<std::string>& row){
            if(row.size() > n_col) throw std::invalid_argument("Rows exceed headers defined.");
            for(int i = 0; i < row.size() - 1; i++){
                writer << row[i] + ",";
            }
            writer << row[n_col - 1] << std::endl; // flush buffer.
        }

        ~CSV_Writer(){
            // close writer and delete file.
            writer.close();
            if(remove(file_path.c_str()) != 0) { // remove() returns exit code 0 on success.
                throw std::runtime_error("Failed to remove file. Please delete manually.");
            }
        }
};

#endif