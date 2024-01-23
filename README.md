# CMap - C Implementation of a Map with Linked List

## Overview

Welcome to the `c_map` repository! This C program provides a simple implementation of a map (dictionary) using linked lists. It serves as an educational resource for understanding linked lists, memory management, and basic data structure implementation in the C programming language.

This project is designed to be beginner-friendly, offering junior developers a hands-on experience with fundamental concepts such as linked lists, memory allocation, and data structure implementation. The code is well-commented and structured, making it easy for junior developers to explore and learn.

### Introducing Iterators and Dot Notation

One interesting aspect of this script is the introduction of iterators, a concept widely used in programming languages like Python and Java. In C, iterators are implemented using function pointers and provide a way to iterate through data structures like maps.

Additionally, you'll notice the use of "->" notation in C, which is used instead of dot notation in Python (Example: `map.get(self, "example_key", -1)`). This notation is specific to C and is used to access members of a structure or a pointer to a structure. Understanding this syntax is essential for junior developers transitioning to C from languages that use dot notation for similar purposes.

This introduces junior developers to the idea of encapsulation and abstraction, even in languages that have different syntax conventions. It lays the foundation for a better understanding of language-specific nuances in programming.

## Table of Contents

- [Why Use This Script](#why-use-this-script)
- [Prerequisites](#prerequisites)
- [Languages and Utilities Used](#languages-and-utilities-used)
- [Environments Used](#environments-used)
- [Data Structures](#data-structures)
- [Functions](#functions)
- [Usage](#usage)

## Why Use This Script

As a junior developer, you might find this script beneficial for the following reasons:

- **Hands-on Learning:** This script provides a practical, hands-on approach to learning fundamental concepts in C programming. It is well-commented, making it accessible for junior developers who are eager to explore and understand how data structures, linked lists, and memory management work in a real-world scenario.

- **Structured Code:** The code is structured in a clear and organized manner, following best practices. Junior developers can navigate through different sections, functions, and data structures, gaining insights into writing clean and maintainable code.

- **Real-world Application:** The script implements a basic map (dictionary) functionality, a common data structure used in programming. By understanding this implementation, junior developers can apply similar concepts to real-world projects, enhancing their problem-solving skills.

- **Iterative Development:** The code includes an iterator, introducing the concept of iteration in data structures. Junior developers can learn how to iterate through a map, a crucial skill in programming.

- **Educational Resource:** This script is not just a piece of code; it's an educational resource. Junior developers can use it as a starting point to deepen their understanding of C programming and data structures.

## Prerequisites

Before using this C program, ensure that you have the following:

- A C compiler installed on your system.
- Basic understanding of C programming, including linked lists and memory allocation concepts.
- Review: [Python Dictionary Class Implementation in C](https://github.com/infinity-set/pydict)

## Languages and Utilities Used

- **C**
- **Visual Studio Code**

[<img  alt="C Logo Icon" width="45px" src="https://upload.wikimedia.org/wikipedia/commons/1/18/C_Programming_Language.svg" />][C]
[<img alt="Visual Code Icon" width="45px" src="https://upload.wikimedia.org/wikipedia/commons/9/9a/Visual_Studio_Code_1.35_icon.svg" />][vscode]

[C]: https://learn.microsoft.com/en-us/cpp/c-language/
[vscode]: https://code.visualstudio.com/

## Environments Used

- **Windows**

[<img align="left" alt="Microsoft Icon" width="35px" src="https://upload.wikimedia.org/wikipedia/commons/3/34/Windows_logo_-_2012_derivative.svg" />][windows]

[windows]: https://www.microsoft.com/

<br /><br />

## Data Structures

### Map Entry Structure (`MapEntry`)

- `char *key`: Pointer to the key string.
- `int value`: Value associated with the key.
- `struct MapEntry *__prev`: Pointer to the previous map entry.
- `struct MapEntry *__next`: Pointer to the next map entry.

### Map Iterator Structure (`MapIterator`)

- `MapEntry *__current`: Pointer to the current map entry.
- `MapEntry *(*next)(struct MapIterator *self)`: Function pointer for getting the next map entry.
- `void (*del)(struct MapIterator *self)`: Function pointer for deleting the map iterator.

### Map Structure (`Map`)

- `MapEntry *__head`: Head of the map entry linked list.
- `MapEntry *__tail`: Tail of the map entry linked list.
- `int __count`: Count of map entries.

## Functions

### `Map_new()`

- Creates a new empty map.
  - **C Syntax:**
    ```c
    Map *newMap = Map_new();
    ```
  - **Python Syntax:**
    ```python
    new_map = {}
    ```

### `__Map_put(Map *self, const char *key, int value)`

- Adds or updates a map entry in the map.
  - **C Syntax:**
    ```c
    self->put(self, "example_key", 42);
    ```
  - **Python Syntax:**
    ```python
    existing_map["example_key"] = 42
    ```

### `__Map_get(Map *self, const char *key, int default_value)`

- Gets the value associated with a key in the map.
  - **C Syntax:**
    ```c
    int result = self->get(self, "example_key", -1);
    ```
  - **Python Syntax:**
    ```python
    result = existing_map.get("example_key", -1)
    ```

### `__Map_find(MapEntry *self, const char *key)`

- Finds a map entry in the map based on the key.
  - **C Syntax:**
    ```c
    MapEntry *result = self->find(self->__head, "example_key");
    ```
  - **Python Syntax:**
    ```python
    if "example_key" in existing_map:
        # Node found
    ```

### `__Map_iter(Map *self)`

- Creates a new iterator for the map.
  - **C Syntax:**
    ```c
    MapIterator *iter = self->iter(self);
    ```
  - **Python Syntax:**
    ```python
    iter = iter(existing_map)
    ```

### `__MapIter_next(MapIterator *self)`

- Gets the next map entry using the iterator.
  - **C Syntax:**
    ```c
    MapEntry *current = iter->next(iter);
    ```
  - **Python Syntax:**
    ```python
    current = next(iter)
    ```

### `__MapIter_del(MapIterator *self)`

- Deletes the iterator.
  - **C Syntax:**
    ```c
    iter->del(iter);
    ```
  - **Python Syntax:**
    ```python
    del iter
    ```

### Usage

The `main` function in the provided C code demonstrates the creation, appending, printing, deletion, and iteration of the map (`Map`).

Feel free to explore and modify the code according to your needs.

 <div align="center">
<br/>
<img src="https://github.com/infinity-set/c_map/assets/142350896/cb42356a-987a-4c2d-81f7-aafae91789f7" height="100%" width="100%" alt="Main function code displayed in C"/>
<br />   
 </div>

 <div align="center">
<br/>
<img src="https://github.com/infinity-set/c_map/assets/142350896/65c19cd6-b14a-416c-8f2b-4528151f531d" height="100%" width="100%" alt="Output of the execution displayed."/>
<br />   
 </div>

<br />

Feel free to explore and modify the code according to your needs.

#

⬅️ **[Home](https://github.com/infinity-set)**
