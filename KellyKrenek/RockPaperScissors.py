import random
def main():
    winner = False
    while(winner == False):
        #prompt user to choose R, P, or S
        userChoice = input("[R]ock, [P]aper, or [S]cissors")
        #will choose 0 as rock, 1 as paper, and 2 as scissors
        computerChoice = random.randint(0,2)
        
        if(userChoice == 'r' or userChoice == 'R'):
            if(computerChoice == 0):
                print("Both of you chose rock, no winner, try again")
            elif(computerChoice == 1):
                print("Computer chose paper, you chose rock, you lose")
                winner = True
            elif(computerChoice == 2):
                print("Computer chose scissors, you chose rock, you win")
                winner = True
        elif(userChoice == 's' or userChoice == 'S'):
            if(computerChoice == 0):
                print("Computer chose rock, you chose scissors, you lose")
                winner = True
            elif(computerChoice == 1):
                print("Computer chose paper, you chose scissors, you win")
                winner = True
            elif(computerChoice == 2):
                print("You both chose scissors, no winner, try again")          
        elif(userChoice == 'p' or userChoice == 'P'):
            if(computerChoice == 0):
                print("Computer chose rock, you chose paper, you win")
                winner = True
            elif(computerChoice == 1):
                print("You both chose paper, no winner, try again")
            elif(computerChoice == 2):
                print("Computer chose scissors, you chose paper, you lose")
                winner = True
        
        
        
    
    
main()