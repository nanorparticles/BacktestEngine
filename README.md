# Multi-Asset BacktestEngine

## Overview
This project implements a **multi-asset, event-driven backtest engine** in C++ for equities. It is designed to **demonstrate correctness, system thinking, and bias-aware simulation** — key signals for quant/trading interviews.

---

## Architecture
- **EventQueue**: Priority queue ordered by timestamps
- **Event Types**: Market, Order, Fill
- **Portfolio**: Tracks cash, positions, and applies fills
- **Strategy Interface**: Stateless per-event decision logic
- **BacktestEngine**: Main event loop handling market data, strategy decisions, execution simulation, and portfolio updates
- **Metrics**: Tracks Sharpe Ratio, Cumulative Return, Max Drawdown

---

## Event Model
- **MarketEvent**: OHLCV data
- **OrderEvent**: Quantity and price
- **FillEvent**: Execution info (price, quantity, fee)

Events are processed chronologically to avoid **lookahead bias**.

---

## Strategy
- **BuyAndHoldStrategy**:
    - Buys a fixed quantity of each symbol at the first market tick
    - Does not attempt to predict or optimize returns
    - Focuses on **correct integration with engine** rather than alpha

---

## Bias Mitigation
- **Lookahead Bias**: Engine only passes past events to the strategy  
- **Execution Bias**: Fills simulated with realistic latency and fees  
- **Survivorship Bias**: Limited by available historical data; documented in CSV loader  
- **Transaction Costs**: Fees included in FillEvent

---

## Metrics
- **Equity**: Cash + current market value of positions  
- **Cumulative Return**: Total return over period  
- **Max Drawdown**: Largest peak-to-trough loss  
- **Sharpe Ratio**: Risk-adjusted return

---

## Performance
- Deterministic event loop
- Minimal dynamic allocation in hot path
- Can be extended to higher-frequency or more assets

---

## Usage
```bash
mkdir build && cd build
cmake ..
make
./BacktestEngine