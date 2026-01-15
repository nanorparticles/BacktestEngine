import subprocess
import pandas as pd
import numpy as np
import os

# -----------------------------
# CSV file paths
# -----------------------------
csv_files = [
    "python_analysis/data/AAPL_av.csv",
    "python_analysis/data/GOOG_av.csv",
    "python_analysis/data/MSFT_av.csv"
]

# -----------------------------
# Backtester executable
# -----------------------------

# When running with cwd set to the build directory, use the local executable name
BACKTEST_EXE = "./BacktestEngine"

# Build command line: BacktestEngine currently accepts a single optional
# argument which is the output filename. Run the executable from its
# build directory so its internal relative paths resolve as expected.
# Pass the asset CSVs to the backtester (relative to repo root), run from build dir
asset_paths = [
    "../../python_analysis/data/AAPL_av.csv",
    "../../python_analysis/data/GOOG_av.csv",
    "../../python_analysis/data/MSFT_av.csv",
]
cmd = [BACKTEST_EXE] + asset_paths

print("Running backtester...")
# Run from the build dir so main.cpp's relative data paths are correct
result = subprocess.run(cmd, capture_output=True, text=True, cwd="../cpp_core/build")

if result.returncode != 0:
    print("Backtester failed!")
    print(result.stderr)
    exit(1)

print(result.stdout)

# -----------------------------
# Load results.csv
# -----------------------------
results_csv = "../cpp_core/build/results.csv"
if not os.path.exists(results_csv):
    print("results.csv not found! Expected at:", os.path.abspath(results_csv))
    exit(1)

df = pd.read_csv(results_csv)

if 'portfolio_return' in df.columns:
    returns = df['portfolio_return'].values
else:
    # Backtester currently exports a trade log (symbol,price,quantity).
    # Fall back: if we have price & quantity, synthesize a per-trade
    # return series as trade P/L divided by initial capital (approx).
    if set(['price', 'quantity']).issubset(df.columns):
        print("portfolio_return column missing; synthesizing returns from trade log.")
        initial_cash = 100000.0
        # trade P/L approximation: -price * quantity (buy reduces cash) normalized
        returns = (-(df['price'] * df['quantity'])) / initial_cash
        returns = returns.values
    else:
        print("portfolio_return column missing and cannot synthesize returns from results.csv")
        exit(1)

# guard: no returns -> nothing to compute
if returns.size == 0:
    print("No returns found in results.csv; exiting.")
    exit(0)

# -----------------------------
# Metrics
# -----------------------------
def sharpe_ratio(returns, annualization=252):
    excess = returns
    mean_ret = np.mean(excess)
    # ddof=1 is sample standard deviation; when there's only one sample use ddof=0
    ddof = 1 if excess.size > 1 else 0
    vol = np.std(excess, ddof=ddof)
    if vol == 0 or np.isnan(vol):
        return 0.0
    return mean_ret / vol * np.sqrt(annualization)

def cumulative_return(returns):
    return np.prod(1 + returns) - 1

def max_drawdown(returns):
    equity = np.cumprod(1 + returns)
    peak = np.maximum.accumulate(equity)
    drawdown = (peak - equity) / peak
    return np.max(drawdown)

# -----------------------------
# Compute metrics
# -----------------------------
sharpe = sharpe_ratio(returns)
cum_ret = cumulative_return(returns)
mdd = max_drawdown(returns)

print(f"\nPortfolio Metrics:")
print(f"Sharpe Ratio: {sharpe:.4f}")
print(f"Cumulative Return: {cum_ret*100:.2f}%")
print(f"Max Drawdown: {mdd*100:.2f}%")

# -----------------------------
# Sanity checks
# -----------------------------
if cum_ret < -1.0:
    print("WARNING: Portfolio lost more than 100% capital!")
if mdd > 0.5:
    print("NOTICE: Max drawdown exceeds 50%")
if abs(sharpe) > 5:
    print("NOTICE: Extremely high Sharpe, check calculations")