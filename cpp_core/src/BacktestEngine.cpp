#include "BacktestEngine.h"
#include <fstream>
#include <iostream>

void BacktestEngine::run(
    const std::vector<Asset>& assets,
    Strategy& strategy,
    const std::string& output_csv
) {
    if (assets.empty()) {
        std::cerr << "No assets provided to BacktestEngine.\n";
        return;
    }

    size_t N = assets.size();
    size_t T = assets[0].prices.size();

    Portfolio portfolio(N);
    RiskManager risk;
    risk.max_leverage = 1.0;
    risk.target_volatility = 0.02;

    std::ofstream out(output_csv);
    if (!out.is_open()) {
        std::cerr << "Failed to open " << output_csv << " for writing.\n";
        return;
    }

    out << "day,portfolio_return\n";

    // Main loop
    for (size_t t = strategy.long_window; t < T; ++t) {
        // 1. Generate signals
        for (size_t i = 0; i < N; ++i) {
            portfolio.weights[i] = strategy.generate_signal(assets[i], t);
        }

        // 2. Apply volatility-adjusted risk management
        risk.enforce(const_cast<std::vector<Asset>&>(assets), portfolio);

        // 3. Compute daily PnL
        double daily_pnl = 0.0;
        for (size_t i = 0; i < N; ++i) {
            daily_pnl += portfolio.weights[i] * assets[i].returns[t];
        }

        out << t << "," << daily_pnl << "\n";
    }

    out.close();
    std::cout << "Backtest complete. Results written to " << output_csv << "\n";
}