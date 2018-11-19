from time import *
from sys import *

def control_room(inventory):
    """Creates room 1 called the 'Control Room'"""
    print("1.) Hack into the system" + '\n' + '2.) Sit in chair' + '\n' + '3.) Drink leftover coffee'+'\n'+
          '4.) Open secret door'+'\n'+'5.) Go back to main entrance'+'\n')
    sleep(2)
    choice = input("Pick a choice: ")
    if choice == '1':
        sleep(2)
        print('\n'+"Hacked into system. Now the government is looking for you >:)")
        mainhall(inventory)
    elif choice == '2':
        sleep(2)
        print('\n'+"The chair has fallen and you have been impaled. You are dead."+'\n'+'\n'+'GAME OVER')
    elif choice == '3':
        sleep(2)
        print('\n'+'You have drank the coffee, now you have to pee'+'\n'+'BUT...'+
              'You have found launching codes at the bottom of the cup. It\'s been added to your inventory'+'\n')
        inventory.append('codes')   #add 'codes' to inventory
        mainhall(inventory)

    elif choice == '4':
        sleep(2)
        for i in inventory:
            if i == 'acid':
                secret_room(inventory)
            else:
                continue
        print("You can\'t open the door yet. You have been booted back to the main hallway.")
        mainhall(inventory)
    else:
        mainhall(inventory)

def laboratory(inventory):
    """"Creates room 2 called the laboratory"""
    print("1.) Mix chemicals"+'\n'+'2.) Drink H2O2 to give you magical powers'+'\n'+'3.) Go back to main entrance'+'\n')
    sleep(2)
    choice = input("Pick a choice: ")
    if choice == '1':
        sleep(2)
        print('\n'+"You have created a corrosive acid. It's been added to your inventory.")
        inventory.append('acid')   #adds 'acid' to inventory
        mainhall(inventory)
    elif choice == '2':
        sleep(2)
        print('\n'+"You have died. Not very smart on your part. This is not a comic."+'\n'+'\n'+'GAME OVER')
    elif choice == '3':
        mainhall(inventory)

def secret_room(inventory):
    """Creates room 4 called the Secret Room"""
    print("You have opened the door with your corrosive acid."+'\n'+'You walk to the launch pad box. '
                                                                    'There is a key required- do you have it?')
    sleep(2)
    for i in inventory:
        if i == 'key':  #checks to see if player has the key in inventory
            sleep(2)
            print("You have the key. There is a place to put the launch codes. Do you have the launch codes?")
            for i in inventory:
                if i == 'codes':   #checks to see if player has codes in inventory
                    sleep(3)
                    print("You do have the codes. You type them in..."+'\n'+'\n'+'The Russians have succeeded >:)'+
                          '\n'+'GAME WON')
                    exit()  #breaks from rest of code
                else:
                    continue
        else:
            continue
    sleep(2)
    print("You do not have the key/codes. Come back later.")
    mainhall(inventory)


def kitchen(inventory):
    """Creates room 3 called Kitchen"""
    print("1.) Make a waffle"+'\n'+'2.) Eat a pie'+'\n'+'3.) Hide in pantry'+'\n'+'4.) Go back to the main hall'+'\n')
    sleep(2)
    choice  = input("Pick a choice: ")
    if choice == '1':
        sleep(2)
        print('\n'+'You have found a key inside of the waffle maker. It has been added to your inventory.')
        inventory.append('key')   #adds 'key' to inventory
        mainhall(inventory)
    elif choice == '2':
        sleep(2)
        print("You have eaten a pie it was very good. Now you have been guided back to the main hall.")
        mainhall(inventory)
    elif choice == '3':
        sleep(2)
        print("The cook has found you and is actually a zombie so you have been eaten."+'\n'+'GAME OVER')
    else:
        mainhall(inventory)


def mainhall(inventory):
    """Creates default room with listing of all the rooms possible"""
    sleep(2)
    print("You have been booted to the main hall."+'\n')

    print("1.) The Control Room" + '\n' + "2.) The Laboratory" + '\n' + "3.) The Kitchen"+'\n')

    direction = input("Enter room number to enter: ")
    steps = 0
    if direction == ('1' or '1.' or '1.)'):
        control_room(inventory)
    elif direction == ('2' or '2.' or '2.)'):
        laboratory(inventory)
    elif direction == '3':
        kitchen(inventory)



inventory = []    #create empty list for inventory
mainhall(inventory)   #directs player to mainhall room and carries inventory with them


