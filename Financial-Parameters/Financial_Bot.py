import pandas as pd
import numpy as np
import yfinance as yf
import matplotlib.pyplot as plt
import datetime as dt
import time
from datetime import date
plt.style.use('classic');

#date format: year-month-day
start = input('write starting date in format (yyyy-mm-dd)___________________: ');
end   = input('write ending date in same format (today for current value)___: ');
stock = input('write the stock-name to look at (AAPL)_______________________: ');
mov_av= input('Display moving average trend? [y/n]__________________________: ');

if mov_av == 'y':
    n = int(input('Please, input the averaging periods (f.i. 3): '));

#looking to databases
price   = yf.download(stock, start, end);
returns = price.Close;


#define moving average
if mov_av == 'y':
    returns_list = list(returns);
    ma_trend = pd.Series(returns_list).rolling(window=n).mean().iloc[n-1:].values

#plotting results
plt.figure(1);


if end == start:
    plt.scatter(end, returns);
    titlefig = 'Today '+stock+' current value: '+str("{0:.2f}".format(returns[-1]))+' $'
    plt.title(titlefig);
    print(titlefig);
else:
    if mov_av == 'y':
        titlefig = stock+' close value';
        plt.title(titlefig);
        plt.subplot(211);
        plt.plot(returns, label='real');
        plt.grid(b=1); plt.legend(loc='best');
        plt.ylabel('close [$]');
        
        plt.subplot(212);
        plt.plot(ma_trend, label='average');
        plt.xlabel('time-index');

        
    elif mov_av == 'n' and end != start:
        titlefig = stock+' close value';
        plt.title(titlefig);
        plt.plot(returns);
        plt.xlabel('time');


plt.ylabel('close [$]');
plt.grid(b=1);
plt.legend(loc='best');
plt.show();

