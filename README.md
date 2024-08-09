# Generic Sorters 🔢

Sorting algorithm consists of a set of predefined procedures whose main purpose is, as the name suggests, to sort a collection of objects based on some arbitrarily defined criteria. This repository was created for mainly educational purposes, where my primary objective is to study, understand and broadly exercise sorting algorithms in C language. Exploring new approaches and methodologies for different scenarios will allow me to sophisticate my understanding of different data structures and the indispensability of performative code, further consolidating my programming skills. 

All — or almost all — of the ordering functions presented here are perfectly applicable in real project contexts. I also emphasize that this is a learning repository, where each code here represents my own version of the sorting algorithm, which means that not all of them will be implemented in their most efficient version. However, I ensure that each one has been properly tested and implemented to the best of my ability within my current level of understanding.

The test codes used for each sorting algorithm will be placed in the "Tests" folder of this repository.

Below is a table to illustrate the different functions currently available:

<div align="center">

## Algorithmic Complexity in Big O Notation for the functions:

| Function                |                  | Time Complexity    |                  | Space Complexity | Stable? |
|:-----------------------:|:----------------:|:------------------:|:----------------:|:----------------:|:-------:|
|                         | **Best Case**    | **Average Case**   | **Worst Case**   | **Worst Case**   |         |
| Binary Insertion Sort   | $Ω(n*log(n))$      | $Θ(n²)$              | $O(n²)$            | $O(1)$             | Yes     |
| Bubble Sort             | $Ω(n)$             | $Θ(n²)$              | $O(n²)$            | $O(1)$             | Yes     |
| Comb Sort               | $Ω(n*log(n))$      | $Θ(n$<sup>1.2</sup>$)$         | $O(n²)$            | $O(1)$             | No      |
| Double Selection Sort   | $Ω(n²)$            | $Θ(n²)$              | $O(n²)$            | $O(1)$             | No      |
| Insertion Sort          | $Ω(n)$             | $Θ(n²)$              | $O(n²)$            | $O(1)$             | Yes     |
| Heap Sort               | $Ω(n*log(n))$        | $Θ(n*log(n))$        | $O(n*log(n))$      | $O(1)$             | No      |
| Merge Sort              | $Ω(n*log(n))$      | $Θ(n*log(n))$        | $O(n*log(n))$      | $O(n)$             | Yes     |
| Radix LSD Sort          | $Ω(n*k)$           | $Θ(n*k)$             | $O(n*k)$           | $O(n*k)$           | Yes     |
| Selection Sort          | $Ω(n²)$            | $Θ(n²)$              | $O(n²)$            | $O(1)$             | No      |
| Shaker Sort             | $Ω(n)$             | $Θ(n²)$              | $O(n²)$            | $O(1)$             | Yes     |
| Shell Sort              | $Ω(n*log(n))$      | $Θ(n$<sup>1.2</sup>$)$         | $O(n$<sup>1.5</sup>$)$       | $O(1)$             | No      |
| Quick Sort              | $Ω(n*log(n))$      | $Θ(n*log(n))$        | $O(n²)$            | $O(log(n))$        | No      |


## Algorithmic Complexity in Big O Notation for the best sorting functions EVER:
| Function                |                  | Time Complexity    |                  | Space Complexity | Stable?  |
|:-----------------------:|:----------------:|:------------------:|:----------------:|:----------------:|:--------:|
|                         | **Best Case**    | **Average Case**   | **Worst Case**   | **Worst Case**   |          |
| Bogo Sort 🤹            | $Ω(1)$             | $Θ(n*n!)$            | $O(ꝏ)$            | $O(1)$             | Maybe...? |
| Good Enough Sort 💤     | $Ω(1)$             | $Θ(1)$               | $O(1)$             | $O(1)$             | For Sure! |
| Sleep Sort 🛏️           | $Ω(M)$             | $Θ(M)$               | $O(M)$             | $O(n)$             | I dunno... |
| Stooge Sort 🪼          | $Ω(n$<sup>2.7095...</sup>$)$ | $Θ(n$<sup>2.7095...</sup>$)$   | $O(n$<sup>2.7095...</sup>$)$ | $O(n)$             | Nope!     |
| Surprise Sort 🎉        | $Ω(?)$             | $Θ(?)$               | $O(?)$             | $O(?)$             | Who Knows?|

</div>
