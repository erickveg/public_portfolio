# Trees
## Table of Contents
* [Introduction](#introduction)
* [Binary Trees](#binary-trees)
* [Binary Search Trees](#binary-search-trees)
* [Balanced Binary Seach Trees](#balanced-binary-search-trees)
* [Recursion](#recursion)
* [Trees in Python](#trees-in-python)
* [Example](#example-insert-unique-values-function)
* [Problem to Solve](#problem-to-solve-create-tree-from-sorted-list)


## Introduction
A tree is a nonlinear data structure that unlike arrays, lists, linked lists, stacks or queues which are linear structures, can have multiple other nodes connected to the same node. The first node is always called the __root__, and all the nodes without a connection are called __leaves__. There is not circular connections or unconnected nodes. Every node that has other nodes under it is called __parent__ and each dependant is a __child__.

In this guide we will review the following types of trees: Binary Trees, Binary Search Tress and Balanced Binary Search Trees.

## Binary Trees
A Binary Tree is a type of tree that only allows at most two nodes connected to a single node. Those are often called __left child__ and __right child__. This type of trees are often used to implement binary search trees, and for efficient sorting or searching algorithms.
 
## Binary Search Trees
A binary search tree __(BST)__ is also known as an ordered or sorted binary tree because the place where new values are stored depends on whether they are larger or smaller than their parent node. The smallest values will be placed in the left child and the highest value will be placed in the right child. Having an structure like this is extremely efficient when it comes to sort a large collection of items. For example, let's insert the number 10 in the following tree.

![Binary Search Tree](Binary_search_tree.jpg)

To do it, we must follow the following steps:
1. Compare 10 and 50. Since 10 is less than 50 we keep looking at the left side of 50.
2. Compare 10 and 36. Since 10 is less than 36 we keep looking at the left side of 36.
3. Since there is an empty spot we can insert 10 at the left side of 36.

![Binary Search Tree Insert](Binary_search_tree_insert.jpg)

As you can see, a BST is extremely efficient because inserting and find a specific value in a BST is done by excluding [recursively](#recursion) a subtree, thus instead of performing a linear seach O(n) we reach an efficient of O(log n).

But notice that our three is balanced, in other words each side has almost the same __height__. 
>__The Height__ in a tree is defined by the maximum number of sub-levels existing in a tree.

If we would have the same values but inserted in this order: 

10, 36, 45, 50, 69, 73, 81

It would result in a tree like this:

![Unbalanced Binary Search Tree](unbalanced_binary_search_tree.jpg)

## Balanced Binary Search Trees

A Balanced Binary Search Tree is a BST which ensures that all the subtrees heights are almost the same. There are a variety of algorithms used to ensure this property in a BST.  

In the next example, you can see how a balanced binary search tree is created from an array taking the middle value of the array and setting it as the root and then continue doing the same with each remaining section.

![optimal binary search tree from sorted array](optimal-binary-search-tree-from-sorted-array.gif)

## Recursion

Recursion is a technique used in programming to call a function inside the same function. It is used for procesess that require to follow the same logic but with different inputs provided each time the function is called.

Recursion and trees are good friends. Since inserting and traversing a tree is a repetitive process of comparing and taking different paths, recursion is the best technique to accomplish this extenuating task. 

Let's analyze the following block of code:

```python
def  print_n_numbers(n):
    print(n)
    print_n_numbers(n-1)
```

The purpose of the function above is to print all the number from n to 0. We used recursion in the third line to call again the function `print_n_numbers()` and passed 'n-1' as the argument to decrease n by 1 every time the function call. Nevertheless we are missing some things that are important when using recursion. If we run this program, the result would look like this:

```
>>> print_n_numbers(10)
10
9
8
7
6
... 
-983
-984
-985

RecursionError: maximum recursion depth exceeded while calling a Python object
```

### Recursion Rules

When using recursion, if there isn't a stop sign, the program could run forever, well actually, as shown in the error above, Python will stop the recursive call when it reaches a maximum number of calls.

These rules will help us to implement recursion succesfully in our programs.

1. __Base Case__ - This is the stop sign for recursion. The base case is the condition that will stop recursion.

2. __Smaller Problem__ - We need to define a way for recursion to reach it's base case, or in other words, each time a function is called we need to alter its input in some way with a smaller problem.

Using `print_n_numbers()` let's implement a base case and a smaller problem.

 ```python
 def  print_n_numbers(n):
    if n < 0: # base case
        return
    else:
        print(n)
        print_n_numbers(n-1) # smaller problem
 ```

Notice that adding a simple if/else statement could be enought to stablish a base case for recursion to stop, in this case, if n is less than 0. We already have stablished a smaller problem because each time the function is called, n is reduced by 1 to reach the base case.

We will use recursion in the next examples to implement some functions that will help us understand how trees work in a deeper way.

## Trees in Python
There is a way to implement trees in Python using third-party libraries, but in this guide, we will implement trees using classes and functions for education purposes.

To implement a simple Binary Search Tree in Python we need to create a Node class first.

```python
class Node:
    def __init__(self, data):
        self.left = None
        self.right = None
        self.data = data
```

Once we have our Node class, we can initizalize a simple binary tree.

```
>>> root = Node(15)
# Tree Structure
#       15
#      /  \
#   None  None

>>> root.left = Node(7)
>>> root.right = Node(70)
# Tree Structure
#          15
#       /     \
#      7       70
#    /  \     /  \
# None None None None
```
We will see how to implement a Binary Search Tree and a Balanced Binary Search Tree in the Example later in this tutorial. But meanwhile, let's see the basic operations in a BST:

|Operation|Description|Performance|
|---------|-----------|-----------|
|insert(value)|Insert a value into the tree|O(log n)|
|remove(value)|Remove a value from the tree|O(log n)|
|height(node)|Get the height of a node in the tree|O(log n)|
|contains(value)|Check if certain value is in the tree|O(log n)|
|traverse()|Pass through all the nodes in a tree in certain order|O(log n)|

## Example: Insert Unique Values Function

In this example we will implement a Binary Search Tree and a function to insert a value in the tree. Remember that to insert a value in a BST (except for the root) we place the smallest values at the left and the biggest at the right. We need to make sure that only unique values can be inserted into the tree.

Let's implement a class to initialize a BST and an inner class for Nodes.

```python
class BST:

    class Node:

        def __init__(self, data):
            """Initialize a new node. Initially the links are set to None"""
            self.data = data
            self.right = None
            self.left = None

    def __init__(self):
        """Initialize an empty BST"""
        self.root = None        
```

Now that we have our base, let's implement our `insert()` function.
```python

    def insert(self, data):
        """"Insert a new node into the BST. If the BST is empty (the root is None), then set the new node as the root. Otherwise call _insert to find a spot to insert"""
        if self.root == None:
            self.root = BST.Node(data)
        else:
            self._insert(data, self.root) # Start at the root

    def _insert(self,data, node):
        """When this function is called we first check if the data to be inserted is unique. If it is unique, we compare the data to be inserted with the data of the current node, if the data to be inserted us greater we set a new node at the right node otherwise we use recursion to check again a new location. The same process with a data smaller than the current node data. """
        if data == node.data:
            pass

        elif data > node.data:
            # We find and empty spot to insert a new node 
            if node.right == None:
                node.right = BST.Node(data)
            # Otherwise, call _insert again
            else:
                self._insert(data, node.right)
        
        else:
            # We find and empty spot to insert a new node
            if node.left == None:
                node.left = BST.Node(data)
            # Otherwise, call _insert again
            else: 
                self._insert(data, node.left)    

```

## Problem to Solve: Create Tree From Sorted List

In this problem you will use what we have done above to create a function that is able to find the middle value from a sorted list and insert it in the BST. The same process wigit ll be repeated until all the elements in the sorted list are inserted in the BST.

You will be provided a template. Please, read carefully all the comments and documentation before to start.

Start here: [BST Template](bst_template.py)
> This template has been take and adapted from "09-prove_trees.py" CSE212 (c) BYU-Idaho - It is a violation of BYU-Idaho Honor Code to post or share this code with others or 
to post it online.  Storage into a personal and private repository (e.g. private
GitHub repository, unshared Google Drive folder) is acceptable.

You can check your code with the solution here: [BST Solution](bst_template_solution.py)
> The solution provided for the problem has been written by the author of this guide.

[Back to Welcome Page](0_Welcome.md)
