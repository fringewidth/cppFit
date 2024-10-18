# cppFit

cppFit is a C++ project designed to generate and analyze running times of your array algorithm. The project includes a C++ executable and a Python script for analysis.

## Prerequisites

- A Linux system. (Windows users see [jFit](https://github.com/fringewidth/jfit2))
- CMake 3.22.1 or higher
- A C++14 compatible compiler
- Python 3

## Building the Project

1. Clone the repository:
    ```sh
    git clone https://github.com/fringewidth/cppFit.git
    cd cppFit
    ```

2. Make the `run.sh` script executable:
    ```sh
    chmod +x run.sh
    ```

## Usage
1. Replace the body of `function(long* arr, int size)` at `include/algs.h` with your own function.
2. Execute `run.sh`.

## Features
- Analysis of your algorithm in a single command.
- Fits to linear, logarithmic, linearithmic and polynomial time complexities.
- Measured data is preprocessed, which includes window based smoothing and outlier removal via IQR.
- Memory safe and storage safe.

### C++ Code

- `main.cpp`: The main entry point of the project. It generates running times and calls the Python script for analysis.
- `include/cppFit/Gen.h`: Contains the `Gen` class, which is responsible for generating arrays, measuring running times, and writing results to a CSV file.
- `include/cppFit/CSV_Writer.h`: A helper class for writing CSV files.
- `include/algs.h`: Your function here.

### Python Script

- `build/analyse.py`: A Python script that analyzes the generated CSV file.

## Usage

1. Run the `run.sh` script:
    ```sh
    ./run.sh
    ```

2. The script will:
    - Build the C++ project using CMake and Make.
    - Execute the `cppFit` executable, which generates running times and writes them to a CSV file.
    - Call the `analyse.py` Python script to analyze the CSV file.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any improvements or bug fixes.

## Contact

For any questions or suggestions, please open an issue.