# DE-globalBest-CEC2014

A clean and efficient implementation of **Differential Evolution (DE)** with global-best guidance applied to the **CEC-2014 benchmark suite** (30 single-objective real-parameter functions).

## Algorithm Details
- **Strategy**: DE/rand/1/bin + occasional use of global best in mutation
- **Population size**: configurable (`Population_size` in header)
- **Mutation factor** `F = 0.8`
- **Crossover rate** `CR = 0.9`
- **Max FEs**: `MAX_FV` (e.g., 10,000 × dimension)
- **Runs per function**: `timesOfRun` (default 30)
- **Boost RNG** for high-quality randomness

## Benchmark
- CEC-2014 test suite (F1–F30)
- Shifted, rotated, composed functions
- Official C source (`CEC2010/Header.h` + data files required)

## Folder Structure
DE-globalBest-CEC2014/
├── CEC2010/               # Official CEC-2014 files (Header.h, data folder, etc.)
├── Self_Define_Functions.h
├── main.cpp               # Source code (this file)
├── Results/               # Auto-created, contains Fitness_result_for_function_X.txt
└── README.md

## How to Compile & Run (Windows / Linux)

### Prerequisites
- C++11 compiler (g++, clang++, MSVC)
- Boost libraries (`boost_random`)
- CEC-2014 data files placed correctly

### Windows (Visual Studio or MinGW)
```bash
g++ -O3 -std=c++11 main.cpp -o DE_CEC2014 -lboost_random
./DE_CEC2014.exe

Make sure the CEC2010/ folder with all .txt data files is in the same directory as the executable.
