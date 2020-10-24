# Subway Problem

## Introduction

There is currently a Guinness World Record for the fastest time to visit each subway station. The path used by the latest record was created by hand, but we hope to best that record by exploring various **Time Dependent Traveling Salesman (TDTSP)** heuristics to arrive at better solutions. Fortunately, new stations have been added since the last record, so anything we could attempt would technically qualify. However, we are hoping to best **24 hours** in our program. The current best is just over 26 hours.

## Repository Structure

This is the primary repository for the project. Written in C++, it has a source folder for each functionality of the overall program. There is also a folder called gtfs which contains the gtfs files and associated data for the initial creation of the cost matrix. The different functionalities of the program are as follows:

 * create - creates the cost matrix in one of two ways: (1) uses all 472 nodes, and (2) using a selection of 231 nodes that will encompass all solutions
 * read - just a test to see if the matrix loading function works. If adding a new heuristic, use this code as a template
 * ant - a rough implementation of the **Ant Colony Optimization (ACO)** algorithm. It requires extensive parameter fiddling.

## Instructions

Before doing anything else, you must create the cost matrix. This takes a while, but the 231-node matrix takes about half the time that the 472-node matrix does. I believe the 472-node matrix takes about 45 minutes to build. You can change which one you use by following the intructions in create/main.cpp at line 21. Start by navigating to the create directory from the repository home:

`$ cd create`

And running the appropriate make command:

`$ make run`

This will start the process of matrix creation.

Next, you can use the ACO algorithm. In ant/main.cpp, go to `main()` and change the file name at line 23 to the appropriate matrix file. _**WARNING:**_ You must adjust `constexpr int NUM_NODES` in ant/constants.hpp to either 231 or 472 depending on which matrix you use.

To run it, navigate to the ant directory:

`$ cd ant`

And run the appropriate make command:

`$ make run`

It will run the ACO algorithm, and depending on the parameters defined constants.cpp, it will work or not. As I mentioned, the ACO algorithm is very dependent on parameters. Anyways, that's all!