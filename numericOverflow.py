# -*- coding: utf-8 -*-
"""
Python Overflow/Underflow Testing Script

This script offers a set of tests to assess how well the Python system handles cases
of numerical overflow and underflow. It checks for the possibility of overflow or underflow
and has the capabilities to increase or decrease a beginning value incrementally. 

Author: Oluwaseun Akinola

Date: 2023-07-19
"""

# Importing the sys module to use sys.maxsize
import sys

# Function to add numbers and detect numeric overflow
def add_numbers(start, increment, steps):
    # The number from which the addition will start
    result = start

    # Loop to add increment to the result 'steps' times
    for i in range(steps):
        # Check if addition of 'increment' causes an overflow
        if sys.maxsize - result < increment:
            print("Numeric overflow detected!")
            # Return the result as soon as an overflow is detected
            return result
        # Add increment to the result
        result += increment

    # Return the final result after all additions
    return result

# Function to subtract numbers and detect numeric underflow
def subtract_numbers(start, decrement, steps):
    # The number from which the subtraction will start
    result = start

    # Loop to subtract decrement from the result 'steps' times
    for i in range(steps):
        # Check if subtraction of 'decrement' causes an underflow
        if -sys.maxsize - 1 > decrement - result:
            print("Numeric underflow detected!")
            # Return the result as soon as an underflow is detected
            return result
        # Subtract decrement from the result
        result -= decrement

    # Return the final result after all subtractions
    return result

# Function to test for numeric overflow
def test_overflow():
    # Set the number of steps, increment, and start value
    steps = 5
    increment = sys.maxsize // steps
    start = 0

    print("Overflow Test of Type =", type(start).__name__)

    overflow = False
    # Test addition without expected overflow
    print("\tAdding Numbers Without Overflow (", +start, ",", +increment, ",", steps, ") =", end=" ")
    result = add_numbers(start, increment, steps)
    # Check if the result of addition is less than the start value, indicating an overflow
    if result < start:
        overflow = True
    print(+result, ", Overflow Status:", overflow)

    overflow = False
    # Test addition with expected overflow
    print("\tAdding Numbers With Overflow (", +start, ",", +increment, ",", (steps + 1), ") =", end=" ")
    result = add_numbers(start, increment, steps + 1)
    # Check if the result of addition is less than the start value, indicating an overflow
    if result < start:
        overflow = True
    print(+result, ", Overflow Status:", overflow)

# Function to test for numeric underflow
def test_underflow():
    # Set the number of steps, decrement, and start value
    steps = 5
    decrement = sys.maxsize // steps
    start = sys.maxsize

    print("Underflow Test of Type =", type(start).__name__)

    underflow = False
    # Test subtraction without expected underflow
    print("\tSubtracting Numbers Without Overflow (", +start, ",", +decrement, ",", steps, ") =", end=" ")
    result = subtract_numbers(start, decrement, steps)
    # Check if the result of subtraction is greater than the start value, indicating an underflow
    if result > start:
        underflow = True
    print(+result, ", Underflow Status:", underflow)

    underflow = False
    # Test subtraction with expected underflow
    print("\tSubtracting Numbers With Underflow (", +start, ",", +decrement, ",", (steps + 1), ") =", end=" ")

# Function to run overflow tests
def do_overflow_tests(star_line):
    print()
    print(star_line)
    print("*** Running Overflow Tests ***")
    print(star_line)

    # Testing Python primitive types
    test_overflow()

# Function to run underflow tests
def do_underflow_tests(star_line):
    print()
    print(star_line)
    print("*** Running Underflow Tests ***")
    print(star_line)

    # Testing Python primitive types
    test_underflow()

# Main function to run all tests
def main():
    # Decorative line for separating different test outputs
    star_line = '*' * 50

    print("Starting Numeric Underflow / Overflow Tests!")

    # Run the overflow tests
    do_overflow_tests(star_line)

    # Run the underflow tests
    do_underflow_tests(star_line)

    print()
    print("All Numeric Underflow / Overflow Tests Complete!")

# Standard Python idiom to call the main function when the script is run as the main module
if __name__ == '__main__':
    main()
