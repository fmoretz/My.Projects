# GNUPLOT TEMPLATE FILE(c) - Federico Moretta
#!/usr/bin/env/gnuplot

# TAKE FILE NAME AND PATH FROM COMMAND LINE
# to take a file from the command line, use the following command:
# $ gnuplot -e "filename='file.dat'" PLOT.plt
reset
if ( !exists("filename") ) quit("No file name given")

# SET TERMINAL TYPE FOR VECTORIAL IMAGES
set terminal svg enhanced size 1000,1000
set output filename.'.svg'

# set terminal pngcairo enhanced size 1000,1000
# set output 'gnuplot_figure.png'

stats filename skip 1
max_col = STATS_columns
print "max_col = ", max_col

round(x) = real(sprintf("%.0E", x));

ROWS = 4
COLS = round(max_col/ROWS+1)
print "COLS = ", COLS
index = 1

set multiplot layout ROWS,COLS

do for [i=1:ROWS] {

  do for [j=1:COLS] {

        print index

        # PLOTTING PARAMETERS
        set autoscale                                   # scale axes automatically
        
        unset log                                       # remove any log-scaling
        unset label                                     # remove any previous labels
        unset key                                       # remove any previous key
        
        set xtic auto                                   # set xtics automatically
        set ytic auto                                   # set ytics automatically
        
        set grid                                        # ENABLE GRID
        
        firstrow = system('head -1 '.filename)          # GET FIRST ROW OF DATA FILE
        set xlabel word(firstrow, 1)                    # SET X LABEL
        set ylabel word(firstrow, index+1)         # SET Y LABEL

        index = index + 1
        if ( index > max_col ) {
          break
        }

        plot filename using (column(1)):(column(index)) \
        w lp pt index lc index
    }
}               
