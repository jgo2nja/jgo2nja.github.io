#!/bin/bash

# Creator: James O'Connell jgo2nja
# Last Updated: 15 March 2022

# Save the first two input lines as file name variables

read wordFile
read gridFile

# Find running times for 5 trials using variable expansion

RUNNING_TIME=`./a.out ${wordFile} ${gridFile} | tail -1`
RUNNING_TIME_2=`./a.out ${wordFile} ${gridFile} | tail -1`
RUNNING_TIME_3=`./a.out ${wordFile} ${gridFile} | tail -1`
RUNNING_TIME_4=`./a.out ${wordFile} ${gridFile} | tail -1`
RUNNING_TIME_5=`./a.out ${wordFile} ${gridFile} | tail -1`

# Find the average time

AVERAGE_TIME=$(((RUNNING_TIME+RUNNING_TIME_2+RUNNING_TIME_3+RUNNING_TIME_4+RUNNING_TIME_5)/5))

# Print to the console

echo ${AVERAGE_TIME} 
