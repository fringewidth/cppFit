#ifndef GEN_H

#define GEN_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <random>
#include <algorithm>
#include <chrono>
#include <memory>
#include "CSV_Writer.h"

class Gen {
    private:
        int start, end, inc;
        bool sorted;
        std::unique_ptr<CSV_Writer> op_CSV;
        int num_incs;


    public:
        Gen(std::string& csv_path, int start, int end, int inc, bool sorted=false) : 
        op_CSV(std::make_unique<CSV_Writer>(csv_path)), start(start), end(end), inc(inc), 
        sorted(sorted), num_incs((end-start)/inc + 1) {
            // validation
            if(start < 1) throw std::invalid_argument("Start must be positive and non zero");
            if(end <= start) throw std::invalid_argument("End must be greater than start");
            if(inc < 1) throw std::invalid_argument("Increment must be postive and non zero");
            if(inc >= end - start) throw std::invalid_argument("Increment must be lesser than the difference between end and start");          
        }

    private:
        void populate_arr(std::vector<long>& arr){
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<long> dis;
            for(auto& ele:arr){
                ele = dis(gen);
            }
            if(sorted) std::sort(arr.begin(), arr.end());            
        }

        void measure(std::vector<long>& running_times) {
            namespace time = std::chrono;
            for(int i = start; i < end; i+=inc){
                std::vector<long> array(i);
                populate_arr(array);
                auto time_start = time::high_resolution_clock::now();
                function(array.data(), array.size());
                auto time_end = time::high_resolution_clock::now();
                running_times[(i - start) / inc] = time::duration_cast<time::nanoseconds>(time_end - time_start).count();
            }

        }
    
    public:
        void gen_csv() {
            std::vector<long> running_times(num_incs);
            measure(running_times);
            op_CSV->define_header({"Size", "Running Time"});
            for(int i = 0; i < running_times.size(); i++)
                op_CSV->add_rows({std::to_string(i * inc + start), std::to_string(running_times[i])});
            
        }
};

#endif