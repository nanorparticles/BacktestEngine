#include "engine.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    BacktestEngine engine(100000.0); // $100k starting cash
    // Binary runs from cpp_core/build — adjust relative path to repository root
    engine.loadHistoricalData("../../python_analysis/data/AAPL_av.csv");
    engine.runStrategy();
    // Default output: write to the repository's python_analysis folder when run from build/
    std::string output = "../../python_analysis/results.csv";
    if (argc > 1) output = argv[1];


    std::cout << "Writing results to: " << output << std::endl;

    engine.exportResults(output);   
    std::cout << "Backtest complete. Results exported.\n";
    return 0;
}