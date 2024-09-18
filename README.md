# Running a coffee shop project


Jacob Lu, 6/25/2024

This program provides a simulation of a day of orders in a cafe, displaying the order results and some statistics on the efficiency of baristas for the day.
This program serves practical applications for running a cafe and deciding how many baristas are necessary.
To compile: g++ -g -Wall Barista.o order.o shopQueue.o main.o -lm -o
To Run:./run_simulation  input_file.txt numB out_file.txt total_time
numB and total_time are both ints. numB is the number of baristas the user would like to test with. total_time is the total number of time steps the simulation will run for.
This project was independently completed.
