/*NumericOverflows.cpp : This file contains the 'main' function.Program execution begins and ends there.
Modified by: Oluwaseun Akinola
Overview: 
This code provides a template-based approach to test numeric overflows and underflows for various types.
It provides the ability to check the result of adding or subtracting a value multiple times, and if the
operation would cause an overflow or underflow, it throws a runtime error */

#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits
#include <stdexcept>    // std::runtime_error
#include <typeinfo>     // typeid()


// Core function that performs operations with overflow/underflow detection.
template <typename T>
T perform_operation(T const& start, T const& change, unsigned long int const& steps, bool isAddition)
{
    T result = start;

    for (unsigned long int i = 0; i < steps; ++i)
    {
        if(isAddition)
        {
            if (std::numeric_limits<T>::max() - result < change)
                throw std::runtime_error("Numeric overflow detected!");
            result += change;
        }
        else
        {
            if (std::numeric_limits<T>::min() + result > change)
                throw std::runtime_error("Numeric underflow detected!");
            result -= change;
        }
    }

    return result;
}

// Function to test overflow by trying out the operation and catching exceptions.
// The rest of the main function can remain the same.

template <typename T>
void test_overflow()
{
    // ... rest of the code ...

    try
    {
        result = perform_operation<T>(start, increment, steps, true);
        std::cout << +result << std::endl;
    }
    catch(const std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
    }

    // ... rest of the code ...

    try
    {
        result = perform_operation<T>(start, increment, steps + 1, true);
        std::cout << +result << std::endl;
    }
    catch(const std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
    }
}

//Function to test underflow by trying out the operation and catching exceptions.
template <typename T>
void test_underflow()
{
    // ... rest of the code ...

    try
    {
        result = perform_operation<T>(start, decrement, steps, false);
        std::cout << +result << std::endl;
    }
    catch(const std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
    }

    // ... rest of the code ...

    try
    {
        result = perform_operation<T>(start, decrement, steps + 1, false);
        std::cout << +result << std::endl;
    }
    catch(const std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
    }
}

// The rest of the main function may remain the same.
