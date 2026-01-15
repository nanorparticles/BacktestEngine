from alpha_vantage.timeseries import TimeSeries
import pandas as pd
import time
import os 

API_KEY = os.environ.get("ALPHAVANTAGE_KEY")

symbols = ["AAPL", "MSFT", "GOOG"]
ts = TimeSeries(key=API_KEY, output_format='pandas')

for symbol in symbols:
    # Fetch daily historical data
    data, meta = ts.get_daily(symbol=symbol, outputsize='compact')
    data.to_csv(f"{symbol}_av.csv")
    print(f"Saved {symbol}_av.csv")
    time.sleep(15)  # Alpha Vantage free tier: 5 calls/min