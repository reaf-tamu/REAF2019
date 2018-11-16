import random
good = ("yes")
ans = input("Wanna play?") 
if ans == good: #if they want to play
	print ("Yay!")
name = input("What's your name?")
print ("Howdy",name,"!") #cute AND redass
favnum = int(input("What is your favorite number?")) #reads input as an integer & not a string so that the if statement will work
a = 10
if favnum < a:
	printed = (random.randint(0,10))
	print("Here's your lucky number:",printed) #prints random number between 0-10
	if printed == favnum: #if they (luckily) get their favorite number...
		print("Yay! You got your lucky number! Congrats!")
else:
	printing = (random.randint(10,100))
	print("Here's your lucky number:",printing) #prints random number between 10-100