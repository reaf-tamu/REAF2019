import random

##rolling dice

print("Do you want to roll the dice")

## input answer
s = str(input("yes or no: "))

if  s == 'yes' :

    ## generate random number
    ## assign it to variable
    random_Num = random.randint(1,6)
    
    ## print the variable
    print( random_Num )



