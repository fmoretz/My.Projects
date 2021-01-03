import random


units = int(input('Enter the number of units___: '));
words = int(input('Enter the number of words___: '));

id_num=[];

def diceware(units):
    '''give the identifying number of a word
    from the diceware wordlist
    
    args:
        units = number of units you want to
        randomically find
        
    return:
        number that identify the word
    '''
    
    for i in range (0, units):
        dice = random.randint(1, units);
        id_num.append(dice);

    return 0;

for i in range(0, words):
    ''' repeat the process for 
    any words your password shall
    contain
    '''
    
    diceware(units);
    print(''.join(str(number) for number in id_num));
    id_num.clear();
    

    
    
    
