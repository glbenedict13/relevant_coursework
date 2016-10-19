#Garrett Benedict
#Intro to Python
#Hangman game
#9/26/2016

import random

###draws hangman###
def hangman(wrong_ans):
    if wrong_ans == 0:
        print(' __')
        print('|')
        print('|')
        print('|')
    elif wrong_ans == 1:
        print(' __')
        print('|  O')
        print('|')
        print('|')
    elif wrong_ans == 2:
        print(' __')
        print('|  O')
        print('|  |')
        print('|')
    elif wrong_ans == 3:
        print(' __')
        print('|  O')
        print('| /|')
        print('|')
    elif wrong_ans == 4:
        torso = '| /|' + r'\ '
        print(' __')
        print('|  O')
        print(torso)
        print('|')
    elif wrong_ans == 5:
        torso = '| /|' + r'\ '
        print(' __')
        print('|  O')
        print(torso)
        print('| /')
    elif wrong_ans == 6:
        torso = '| /|' + r'\ '
        legs = '| / ' + r'\ '
        print(' __')
        print('|  O')
        print(torso)
        print(legs)
        game_on = 0
        wrong_ans = 0
        flag = 0
    return

###prints array lists###
def printList(word):
    for i in range(0, len(word), 1):
        print(word[i], end='')
    print('')
    return

###game play function###
def gamePlay(hang_word, guessed_word, missed_guess):
    flag = 1 #determines when to end game play
    while flag:

        ###Game play###    
        letter = input('Please guess a letter: ')
        #stupid proof letter input
        invalid = 1
        while invalid:
            if not letter.isalpha():
                letter = input('No numbers please: ')
            if not len(letter) == 1:
                letter = input('Only one letter please: ')
            else: invalid = 0
            
        letter = letter.lower()
        letter_repetition = 0
        letter_location = []

        #Check to see if letter is in hang_word
        for i in range(0, len(hang_word), 1):
            if letter == hang_word[i]:
                letter_location.append(i)
                letter_repetition += 1

        if letter_repetition > 0:
            for i in range(0, letter_repetition, 1):
                guessed_word[letter_location[i]] = letter
        else: missed_guess += 1
    
        hangman(missed_guess) #print hangman
        printList(guessed_word)
        #Game Over Logic
        if missed_guess >= 6:
            flag = 0
            print('Game Over')
        #Winner Logic
        if '-' not in guessed_word:
            flag = 0
            print('Winner!')
    return

###The 'main' method###
game_on = 1
while game_on:
    #Player selection#
    players = input('How many players? (1 or 2): ')
    invalid = 1
    while invalid:
        if players.isdigit() == False: #makes sure a number is selected
            players = input('Please type either "1" or "2": ')
        elif (2 < int(players)) or (int(players) < 1): #makes sure it is a 1 or a 2
            players = input('Please type either "1" or "2": ')
        else: invalid = 0

    ###Player 1 logic###
    if players == '1':
        word_list = ['cowboy', 'python', 'triggered', 'koala', 'onomatopoeia']
        word_index = random.randint(0, len(word_list)-1)
        hang_word = word_list[word_index] #select hang_word from word_list
        guessed_word = []
        #initialize guessed_word to '----'
        for i in range(0, len(hang_word), 1):
            guessed_word.append('-')
            
        missed_guess = 0 #count of missed guesses
        hangman(missed_guess) #print hangman
        printList(guessed_word) #print guessed_word

        gamePlay(hang_word, guessed_word, missed_guess)

    ###Player 2 logic###            
    elif players == '2':
        hang_word = input('Player 1, type in a word: ')
        #stupid proof hang_word
        invalid = 1
        while invalid:
            if not hang_word.isalpha():
                hang_word = input('Please type in a word without numbers or spaces: ')
            else: invalid = 0
        hang_word = hang_word.lower()

        guessed_word = []
        #initialize guessed_word to '----'
        for i in range(0, len(hang_word), 1):
            guessed_word.append('-')
            
        missed_guess = 0 #count of missed guesses
        hangman(missed_guess) #print hangman
        printList(guessed_word) #print guessed_word

        gamePlay(hang_word, guessed_word, missed_guess)  
        
    #Post game; New game or nah    
    print('The word was:', hang_word)
    play = input('Play again? (Y/N): ')
    play = play.lower()
    if play == 'y': game_on = 1
    else: game_on = 0
     
        
        
        
        
    
    
