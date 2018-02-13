//
//  main.cpp
//  Homework3 #2 linear recursive
//
//  Created by Jie-Yun Cheng on 2/13/18.
//  Copyright © 2018 Jie-Yun Cheng. All rights reserved.
//

#include <iostream>
#include <cassert>

// TODO: only declare somePredicate, but don't implement it when turning it in
// A function that takes a double and returns true if a particular property of that double is true, and false otherwise. (Such a function is called a predicate.)
bool somePredicate(double x)
{
    return x > 0;
}

///////////////////////////
// 5 Recursive Functions //
///////////////////////////

// The first four take an array of doubles and the number of doubles to examine in the array; the last takes two arrays of doubles and the number of doubles to examine in each:

// 1. Return false if the somePredicate function returns false for at least one of the array elements; return true otherwise.
bool allTrue(const double a[], int n)
{
    if (n == 0)
        return true;
    if (n<=0)
        return false;
    if (n == 1)
        return somePredicate(a[0]); // reached base case and no numbers have failed somePredicate
    return (allTrue(a+1, n-1) && somePredicate(*a)); // why must this be *a and can't be a[n]?
}

// 2. Return the number of elements in the array for which the somePredicate function returns false.
int countFalse(const double a[], int n)
{
    if (n <= 0)
        return 0;
    else if (somePredicate(a[0]) == false)
        return (countFalse(a+1, n-1) + 1); // increment if somePredicate function returns false and keep checking the next element
    return countFalse(a+1, n-1); // if (somePredicate(a[0]) == true), just keep che-cking the next element
    
    // Professor Nachenberg's Lecture 8 slide 52 code also works:
    /*
    if (n <= 0)
        return 0;
     
    int total;
    total = countFalse(a+1, n-1);
    if (somePredicate(a[0]) == false)
        total++;
    return total;
    */
}

// 3. Return the subscript of the first element in the array for which the somePredicate function returns false.  If there is no such element, return -1.
int firstFalse(const double a[], int n)
{
    if (n <= 0)
        return -1;
    if (somePredicate(a[0]) == false)
        return 0;
    else if (firstFalse(a+1, n-1) == -1)
        return -1;
    else // if (somePredicate(a[0]) == true)
        return (firstFalse(a+1, n-1) + 1); // increment the index
}

// 4. Return the subscript of the smallest double in the array (i.e., the one whose value is <= the value of all elements).  If more than one element has the same smallest value, return the smallest subscript of such an element.  If the array has no elements to examine, return -1.
int indexOfMin(const double a[], int n)
{
    return -999;  // This is incorrect.
}

// 5. If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2)
{
    return false;  // This is not always correct.
}


// You will not receive full credit if the allTrue, countFalse, or firstFalse functions cause each value somePredicate returns to be examined more than once. Consider all operations that a function performs that compares two doubles (e.g. <=, ==, etc.). You will not receive full credit if for nonnegative n, the indexOfMin function causes operations like these to be performed more than n times, or the includes function causes them to be performed more than n1 times.


int main()
{
    double var1[] = {1, -2, 3, -4, 5, -6}; // last neg, 3 neg
    double var2[] = {1, 2, -3, -4, 5, 6}; // 2 neg
    double var3[] = {-1, -2, 3, -4, 5, 6}; // first neg, 3 neg
    double var4[] = {30, 9, 76, 22, 4, 1}; // all pos
    double var5[] = {1}; // all pos, 1 element
    double var6[] = {}; // empty array

    int size = 6;
    int size5 = 1;
    int size6 = 0;
    
    ////////////////
    // test cases //
    ////////////////
    
    // function 1
    assert(allTrue(var1, size) == false && allTrue(var2, size) == false && allTrue(var3, size) == false);
    assert(allTrue(var4, size) == true && allTrue(var5, size5) == true);
    assert(allTrue(var6, size6) == true);

    // function 2
    assert(countFalse(var1, size) == 3 && countFalse(var2, size) == 2 && countFalse(var3, size) == 3);
    assert(countFalse(var4, size) == 0 && countFalse(var5, size5) == 0 && countFalse(var6, size6) == 0);
    
    // function 3
    assert(firstFalse(var1, size) == 1 && firstFalse(var2, size) == 2 && firstFalse(var3, size) == 0);
    assert(firstFalse(var4, size) == -1 && firstFalse(var5, size5) == -1 && firstFalse(var6, size6) == -1);

}

