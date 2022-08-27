words = []
memory = []
quit = False


while quit == False:
    
    user_input = int(input(""" 
    Choose an option:
    (1) Insert text
    (2) Delete last word
    (3) Undo deletion
    (4) Quit 
    >>> """))

    if user_input == 1:
        user_text = input("Insert text here: ")
        for word in user_text.split():
            words.append(word)
    
    if user_input == 2:
        if len(words) > 0: # Make sure your stack is not empty
            removed_word = words.pop()
            memory.append(removed_word)
            print(f"You have removed the word '{removed_word}'")
        else:
            print("Sorry, you need to insert text first")
    
    if user_input == 3:
        restored_word = memory.pop()
        words.append(restored_word)
        print(f"Word: '{restored_word}' added again")
    
    if user_input == 4:
        quit = True

    print(f"""\n 
    ==================
    {' '.join(words)}
    ==================
    """)
    