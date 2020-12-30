import pandas as pd
import numpy as np
import yfinance as yf
import matplotlib.pyplot as plt
import datetime as dt
plt.style.use('ggplot');

#date format: year-month-day
start = input('write starting date in format (yyyy-mm-dd)_: ');
end   = input('write ending date in format (yyyy-mm-dd)___: ');
stock = input('write the stock-name to look at (AAPL)_____: ');

#looking to databases
price   = yf.download(stock, start, end);
returns = price.Close;


#plotting results
titlefig = stock+' close value';
plt.figure(1);
plt.title(titlefig);
plt.plot(returns);
plt.xlabel('time');
plt.ylabel('close [$]');
plt.grid(b=1);
plt.show();


