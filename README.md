# Poisson Page Fault Detection
## Table of Contents
* [Overview](#overview)
* [Background](#background)
* [Random Number Generation](#random-number-generation)
* [Replacement Algorithms](#replacement-algorithms)
* [Results](#results)

# Overview
The program compares the effectiveness of page replacement algorithms and tallies up the number of faults generated. It uses Poisson distribution with λ = 10 to generate 1000 page numbers. This is ran through three different algorithms: FIFO, LRU, and Clock/Second Chance. A total of 1000 experiments is performed for each algorithm. Furthermore, each experiment will have each algorithm use a working set size from 2 to 20. The average number of faults is plotted using Microsoft Excel and will be shown in the results section.

## Background
Managing memory is a task that occurs in the background of all modern operating systems. Taking a closer look at the inner works of virtual memory management allows us to examine just how complex and involved the task actually is. This program aims to take a look at **memory paging** and how different algorithms can affect the effeciency of the OS. Memory paging is a memory management scheme in which secondary storage is used to store and retrieve data for later use in main memory. The OS retrieves data in equally-sized chunks known as pages. This allows programs to use secondary memory to exceed the amount of available physical memory. 

## Random Number Generation
The program generates a 1000 random numbers each time an experiment is performed. This random number generation is done using the built-in C++ Poisson distribution function with λ = 10. Poisson distribution is a discrete probability distribution that expresses the probability of a given number of events occurring in a fixed interval of time if these events occur with a known constant mean rate (10 in this case) and independently of the time since the last event. Here is an example of the distribution of 1,000,000 randomly generated numbers by the program:

<p align="center">
  <img src="https://user-images.githubusercontent.com/54548478/124325604-cdf5f800-db39-11eb-87ab-ba1d45d1e2d6.png" />
</p>

As you can see, the random numbers center around the variable λ regardless of how many are generated. This ensures that every time we perform our experiment, our 'randomness' will have some consistency.  

## Replacement Algorithms
Operating systems commonly use paging mechanisms for memory management. Various algorithms are used in dictating the logic/order of page replacement when virtual address space is full. Depending on the situation, some algorithms can be more effecient than others. The replacement algorithms used in the program are:-
* **FIFO**: The simplest page replacement algorithm. In this algorithm, the OS forms a queue in which the oldest page will always be in the front of the queue. When a page replacement is going to occur, the front of the queue is selected for removal.

* **LRU**: In this algorithm, the OS forms a queue that is similar to FIFO, but keeps track of which page has been recently used. The least recently used page is selected for removal when the queue is full.

* **Clock (or second chance)**: The most complex out of the three algorithms. It centers around using a ‘use bit’ in each frame (which can either be 0 or 1). It associates the use bit with each page depending on the state of use. This is used to determine whether a page will be replaced.

## Results
An example of the output of the average faults throughout the 1000 experiments after the data set has been graphed:

<p align="center">
  <img src="https://user-images.githubusercontent.com/54548478/124326567-7b1d4000-db3b-11eb-9393-104f9190cb19.png" width="500"/>
</p>

If you made it this far, I hope this was informative. I believe that this program can serve as a low-level look at memory management using paging. All 3 algorithms are very similar, yet small changes do make a huge difference in effeciency. I highly suggest you try to create a program centering around simulating memory management as I have learned a lot from this one. If you are interested in learning more, then I highly suggest checking out some of the links below.

https://www.geeksforgeeks.org/paging-in-operating-system/

https://www.geeksforgeeks.org/page-replacement-algorithms-in-operating-systems/

https://en.wikipedia.org/wiki/Cache_replacement_policies

http://www.mathcs.emory.edu/~cheung/Courses/355/Syllabus/9-virtual-mem/SC-replace.html
