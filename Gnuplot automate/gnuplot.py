from checkOS import *
import os

def gnuplot(filename = None):
    
    f = filename + '.dat'
    
    file = open(f,'r')
    
    gen_command = """gnuplot -e "filename='""" + file.name + """'" PLOT_"""

    if checkOS == 'Windows':
        comp_command = gen_command + 'Windows.plt'
        
        print('\ncommand: ', comp_command)
        print(f'\nPlotting {filename} on Windows...')
        
        os.system(comp_command)
        
    elif checkOS == 'Linux':
        comp_command = gen_command + 'UNIX.plt'
        
        print('\ncommand: ', comp_command)
        print(f'\nPlotting {filename} on Linux...')
        
        os.system(comp_command)
        
    elif checkOS == 'Darwin':
        comp_command = gen_command + 'UNIX.plt'
        
        print('\ncommand: ', comp_command)
        print(f'\nPlotting {filename} on Mac OS...')
        
        os.system(comp_command)