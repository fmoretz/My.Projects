import pandas as pd
import numpy as np
import yfinance as yf
import matplotlib.pyplot as plt
import datetime as dt
plt.style.use('ggplot');

start = '2020-01-01';
end   = '2020-10-31';

price = yf.download('AAPL', start, end);
returns = price.Close;

plt.figure(1);
plt.plot(returns);
plt.xlabel('time [days]');
plt.ylabel('Prices');
plt.show();

