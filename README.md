# BacktestEngine

## Overview
A quantitative backtesting engine for simulating trading strategies.
- Core: C++ (high-performance)
- Analysis: Python (PnL, Sharpe, visualization)
- Strategy example: 5-day SMA crossover

## Setup

### Build C++ Engine
```bash
cd cpp_core
mkdir build && cd build
cmake ..
cmake --build .