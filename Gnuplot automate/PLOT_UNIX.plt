# GNUPLOT TEMPLATE FILE(c) - Federico Moretta
#!/usr/bin/env/gnuplot

# TAKE FILE NAME AND PATH FROM COMMAND LINE
# to take a file from the command line, use the following command:
# $ gnuplot -e "filename='filename.dat'" PLOT.plt
reset
if ( !exists("filename") ) quit("No file name given")

# SET TERMINAL TYPE FOR VECTORIAL IMAGES
set terminal svg enhanced size 1000,700
set output filename.'.svg'

# to save it in png, switch these two terminals
# set terminal pngcairo enhanced size 1000,1000
# set output 'gnuplot_figure.png'

stats filename skip 1
max_col = STATS_columns
print "Number of Columns = ", max_col

round(x) = real(sprintf("%.0E", x));

if (max_col == 1){
  ROWS = 1
  COLS = 1
  print "ROWS = ", ROWS, " COLS = ", COLS 
}
if (max_col == 2) {
  ROWS = 1
  COLS = 2
  print "ROWS = ", ROWS, " COLS = ", COLS 
}
if (max_col == 3) {
  ROWS = 1
  COLS = 3
  print "ROWS = ", ROWS, " COLS = ", COLS 
}
if (max_col == 4) {
  ROWS = 2
  COLS = 2
  print "ROWS = ", ROWS, " COLS = ", COLS 
}
if (max_col == 5) {
  ROWS = 2
  COLS = 3
  print "ROWS = ", ROWS, " COLS = ", COLS 
}
if (max_col == 6) {
  ROWS = 2
  COLS = 3
  print "ROWS = ", ROWS, " COLS = ", COLS 
}
if (max_col == 7) {
  ROWS = 3
  COLS = 3
  print "ROWS = ", ROWS, " COLS = ", COLS 
}
if (max_col == 8) {
  ROWS = 3
  COLS = 4
  print "ROWS = ", ROWS, " COLS = ", COLS 
}
if (max_col > 8) {
  ROWS = 3
  COLS = int(round((max_col-1)/ROWS))
  print "ROWS = ", ROWS, " COLS = ", COLS
}

set multiplot layout ROWS,COLS

index = 1

do for [i=1:ROWS] {

  do for [j=1:COLS] {
        # PLOTTING PARAMETERS
        set autoscale                                   # scale axes automatically
        set size square                                 # make the plot square

        unset log                                       # remove any log-scaling
        unset label                                     # remove any previous labels
        unset key                                       # remove any previous key
        
        set xtic auto                                   # set xtics automatically
        set ytic auto                                   # set ytics automatically
        
        set grid                                        # ENABLE GRID
        
        firstrow = system('head -1 '.filename)          # GET FIRST ROW OF DATA FILE
        set xlabel word(firstrow, 1)                 # SET X LABEL
        set ylabel word(firstrow, index+1)              # SET Y LABEL
  
        index = index + 1                               # Autoincrement index
        if ( index > max_col ) {                        # stop increment when limit is reached
          break
        }

        print "plot n. ", index-1                          # check visaully all the plots where done

        plot filename using (column(1)):(column(index)) \
        w lp pt index lc index
    }
}               
unset multiplot