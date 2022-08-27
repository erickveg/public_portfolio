# STACKS

## Table of Contents

* [Introduction](#introduction)
* [Stacks in Python](#stacks-in-python)
* [Performance](#performance)
* [Example](#example-undo-property-in-a-simple-text-editor)
* [Problem to Solve](#problem-to-solve-pyramid-volume)

## Introduction

A stack is a linear data structure which means that each element exists next to the other in memory (contiguous memory). The main feature of a stack is that new components can be added or removed only from one end also known as Last In First Out (LIFO) structure, while other data structures like [Queues](https://dbader.org/blog/queues-in-python) remove items from one end and added to the opposite end. Stacks are used to implementing functions and are used in a variety of ways in computer science because are useful to process nested functions.

## Stacks in Python

The built-in List data structure in Python can be used to implement a stack. To add a new component in the stack we use the function `append()` and to remove any element from the end `pop()` is used, but it must be used carefully because it won't work if the list is empty.

```python
# How to use Python's list as a LIFO stack:

stack = list()

# Add elements to the stack
stack.append('bananas')
stack.append('apples')
stack.append('mangos')
```
```python
>>> stack
['bananas','apples','mangos']
```
```python
# Remove items from the stack
>>> stack.pop()
'mangos'
>>> stack.pop()
'apples'
>>> stack.pop()
'bananas'
>>> stack.pop()
ERROR  # You can't remove any item because the stack is empty
```
## Performance
As you can notice because we add or remove a stack component only from one end of the structure the performance of those operations will always be O(1). 

## Example: Undo Property in a Simple Text Editor
Have you ever been writing an important document and suddenly you press a key and everything disappears? You get desperate but remember that "Ctrl + Z" is there to undo your mistake. How does the computer know what to put back when you use the Undo property? In this example, we will implement a simple text editor with the capacity to undo any deletion. 

```python
# Create a stack to store the text inserted by the user
text = []
# Create a stack to store the words deleted
memory = []

quit = False

while quit == False:
    
    user_input = int(input(""" 
    Choose an option:
    (1) Insert text
    (2) Delete last word
    (3) Undo deletion
    (4) Quit 
    """))

    if user_input == 1:
        user_text = input("Insert text here: ")
        for word in user_text.split():
            text.append(word)
    
    if user_input == 2:
        if len(text) > 0: # Make sure your text stack is not empty
            removed_word = text.pop()
            memory.append(removed_word)
            print(f"You have removed the word {removed_word}")
        else:
            print("Sorry, you need to insert text first")
    
    if user_input == 3:
        if len(memory) > 0 # Make sure your memory stack is not empty
            
            restore_word = text.append(memory.pop())
            print(f"Word: {restore_word} added again")
        else:
            print("No words in 'memory'")
    
    # Exit the program if the user enters 4
    if user_input == 4:
        quit = True

    print(f"""\n 
    ==================
    {' '.join(text)}
    ==================
    """)
```
OUTPUT:
```
Choose an option:
    (1) Insert text
    (2) Delete last word
    (3) Undo deletion
    (4) Quit 
    
>>> 1

Insert text here: My name is Erick

==================
My name is Erick
==================

Choose an option:
    (1) Insert text
    (2) Delete last word
    (3) Undo deletion
    (4) Quit 

>>> 2 
You have removed the word 'Erick'

==================
My name is
==================

Choose an option:
    (1) Insert text
    (2) Delete last word
    (3) Undo deletion
    (4) Quit 

>>> 3

Word: 'Erick' added again

==================
My name is Erick
==================

... # Menu removed for simplicity

>>> 3    # 'is' removed
>>> 3    # 'name' removed
>>> 3    # 'My' removed
>>> 3
No words in memory

>>> 2    # 'My' added to text
==================
My 
==================
```


## Problem to Solve: Pyramid Volume
Now, you will have the opportunity to implement a program that will help you understand why stacks are useful handling functions in programming.

You will implement a simple pyramid volume calculator which accepts thee parameters: 

* l : base length
* w : base width
* h : pyramid height 

The formula to calculate the volume of a pyramid is the following:

_V = (lwh) / 3_

The _l_, _w_ and _h_ values will be given in centimeters and your program must be able to convert centimeters to inches for the final result. Your program should have at least three functions, one to calculate the actual volume, one to calculate the pyramid base, and another to convert _cm_ to _in_.

### Test
Try your solution with the following values. The input values are l, w, and h, in that order.

```
>>> calculate_pyramid_volume(3,5,10)

The pyramid volume in inches is: 19.685
```

You can check your code with the solution here: [Pyramid Volume Solution](pyramid_volume_solution.py)

### Analysis
You are probably wondering what does this program has to be with stacks? Well, what you just did is a perfect example of how stacks are used to solve multiple function calls from the same program. How do computers know what to solve first?

Compilers basically use stacks to store all the function calls while running a program and always warranty to solve the last call before proceed with the previous call.

In our case, the compiler call functions in the following order:

1. `calculate_pyramid_volume()`
2. `calculate_base_area()`
3. `convert_cm_to_in()`

But, here is the key feature of stacks. What would happen if we try to solve our program in that order? It would simply fail, because `calculate_pyramid_volume()` couldn't calculate the volume without knowing the pyramid base first. The stacks are very useful to solve nested functions, it helps the compiler to go backward from the last recent function call to the very first call. Our program was solved in the following order:

1. `calculate_base_area()`
2. `convert_cm_to_in()`
3. `calculate_pyramid_volume()`


[Back to Welcome Page](0_Welcome.md)

