/*
Given an integer (T) and a collection of integer (I), find a sub-collection (M) that the sum (S) of M's elements
is the largest among all subcollections of I and S <= T. I is not sorted, M is not required to be sorted.
Not required to find M with the least number of elements. I and M might contain repetitive elements.
If there�s no answer found set M to an empty vector and s to 0.

Signature of the interface :  void find_largest_sum(const uint32_t T, const std::vector<uint32_t> &I, vector<uint32_t>& M, uint32_t &S);

example
T: 11
I: 1 , 2, 3, 4, 5, 6,7

possible answers
M: 5,6
S:11

M: 4, 7
S: 11

You only need to find one answer if there are multiple subcollections meet the requirement.
Please don�t use the brute force way to solve this question. Don�t assume I is a small vector, it can contain like 10,000 numbers.
( tips: find the most appropriate technique, such as divide and conquer, dynamic programming, backtracking, etc.)

Your solution should be clean, clear, well commented, and thoroughly tested. (Create your own test cases for your solution.)
Please use cmake/make to setup your project for Linux OS.

*/

#include <iostream>
#include <stdint.h>
#include <vector>

void find_largest_sum(const uint32_t T,
                      const std::vector<uint32_t>& I,
                      std::vector<uint32_t>& M,
                      uint32_t& S);
void RunTests();


int main()
{
    RunTests();
    return 0;
}

/////////////////////////////////////////////////////////////
//                         ALGORITHM
////////////////////////////////////////////////////////////

// Time complexity is O(n)
void find_largest_sum(const uint32_t T,
                      const std::vector<uint32_t>& I,
                      std::vector<uint32_t>& M,
                      uint32_t& S)
{
    S = 0;
    M.clear();

    if(T == 0 || I.empty())
    {
        return;
    }

    uint32_t interval_sum = 0;

    //interval
    size_t start = 0, end = 0;

    // every sub-array starting from start index
    for(start; start < I.size(); start++)
    {
        // if current interval sum is less than the given sum,
        // then add elements to current interval from right
        while(interval_sum < T && end < I.size())
        {
            interval_sum += I[end];
            end++;
        }

        // if current interval sum is equal to the given sum
        if(interval_sum == T)
        {
            M = std::vector<uint32_t>(I.begin() + start, I.begin() + end);
            S = interval_sum;
            return;
        }

        // At this point the current interval sum is more than the given sum
        // remove current element (leftmost element) from the interval
        interval_sum -= I[start];
    }
}

/////////////////////////////////////////////////////////////
//                         TESTS
////////////////////////////////////////////////////////////

#define ARE_EQ( x, y) \
 if (x == y) std::cout << "Passed" <<std::endl; else { std::cout<< "Failed " <<std::endl;} 

void TestDummy()
{
    std::cout << "TestDummy: " << std::endl;
    ARE_EQ(5, 5);
    std::cout << "---------------------------------------- " << std::endl;
 }

void TestSingleSubcollectionSumLessThanTarget()
{
    std::cout << "TestSingleSubcollectionSumLessThanTarget: " << std::endl;

    const uint32_t T = 11;
    const std::vector<uint32_t>& I = { 1, 5 };
    std::vector<uint32_t> M = {};
    uint32_t S ={};
    find_largest_sum(T, I, M, S);

    std::vector<uint32_t> expected_m = {1, 5};
    uint32_t expected_s = 6;

    ARE_EQ(expected_m, M);
    ARE_EQ(expected_s, S);
    std::cout << "---------------------------------------- " << std::endl;
}

void TestSingleSubcollectionSumEqualsTarget()
{
    std::cout << "TestSingleSubcollectionSumEqualsTarget: " << std::endl;

    const uint32_t T = 11;
    const std::vector<uint32_t>& I = { 1, 5, 6 };
    std::vector<uint32_t> M = {};
    uint32_t S = {};
    find_largest_sum(T, I, M, S);

    std::vector<uint32_t> expected_m = { 5, 6 };
    uint32_t expected_s = 11;

    ARE_EQ(expected_m, M);
    ARE_EQ(expected_s, S);
    std::cout << "---------------------------------------- " << std::endl;
}


void TestSeveralSubcollectionSumEqualsTarget()
{
    std::cout << "TestSeveralSubcollectionSumEqualsTarget: " << std::endl;

    // there are several subarrays which sum equals to the target (T)
    // we should return the first in the input (I)
    const uint32_t T = 11;
    const std::vector<uint32_t>& I = { 4, 7, 5, 6 };
    std::vector<uint32_t> M = {};
    uint32_t S = {};
    find_largest_sum(T, I, M, S);

    std::vector<uint32_t> expected_m = {4, 7};
    uint32_t expected_s = 11;

    ARE_EQ(expected_m, M);
    ARE_EQ(expected_s, S);
    std::cout << "---------------------------------------- " << std::endl;
}

void TestNoSubarray()
{
    std::cout << "TestNoSubarray: " << std::endl;

    // Every element is bigger
    const uint32_t T = 11;
    const std::vector<uint32_t>& I = { 13, 15, 16 };
    std::vector<uint32_t> M = {};
    uint32_t S = {};
    find_largest_sum(T, I, M, S);

    std::vector<uint32_t> expected_m = {};
    uint32_t expected_s = 0;

    ARE_EQ(expected_m, M);
    ARE_EQ(expected_s, S);
    std::cout << "---------------------------------------- " << std::endl;
}

void TestNoSubarrayMNotEmpty()
{
    std::cout << "TestNoSubarrayMNotEmpty: " << std::endl;

    // If nothing was found, M and S should be set to 0
    const uint32_t T = 11;
    const std::vector<uint32_t>& I = { 13, 15, 16 };

    std::vector<uint32_t> M = {1, 2, 3};
    uint32_t S = 15;

    find_largest_sum(T, I, M, S);

    std::vector<uint32_t> expected_m = {};
    uint32_t expected_s = 0;

    ARE_EQ(expected_m, M);
    ARE_EQ(expected_s, S);
    std::cout << "---------------------------------------- " << std::endl;
}

void TestEmptyInput()
{
    std::cout << "TestEmptyInput: " << std::endl;

    const uint32_t T = 11;
    const std::vector<uint32_t>& I = {};
    std::vector<uint32_t> M = {};
    uint32_t S = {};
    find_largest_sum(T, I, M, S);

    std::vector<uint32_t> expected_m = {};
    uint32_t expected_s = 0;

    ARE_EQ(expected_m, M);
    ARE_EQ(expected_s, S);
    std::cout << "---------------------------------------- " << std::endl;
}

void RunTests()
{
    TestDummy();
    TestSingleSubcollectionSumLessThanTarget();
    TestSingleSubcollectionSumEqualsTarget();
    TestSeveralSubcollectionSumEqualsTarget();
    TestNoSubarray();
    TestNoSubarrayMNotEmpty();
    TestEmptyInput();
}