# SimpliestCPPUnitTests
A **very simple** framework to make unit tests in C++. 

This project is a simple unit testing framework for C++. It is build in **pure C++**, and can be used with any compiler on any systems who complains to C++ 11 standard.

## Install the framework
Simply copy file `test.h` and include it : it's done. The whole framework is on this file.

## Use the framework
To use the framework, you must create a class who inherits from `tests::Test` and override the `test_code()` function.
All the test case in include into this function.
The code of the test may use one of the protected members (all this functions have a `name` string parameter, not mandatory, who can identified the test)  :

* `assert_true(value,name)` asserts value passed is true. The test fails otherwise.
* `assert_false(value,name)` asserts value passed is false. The test fails otherwise.
* `fail(name)` fails the test
* `pass(name)` passes the test
* `assert_equal(x,y,name)` asserts that x==y, fails otherwise
* `assert_equal(x,y,p,name)` do the same thing but with floating-point numbers, with a parameter p which is the precision (1e-7, for exemple)
* `assert_not_equal(x,y,name)` asserts values are not equal
* `assert_null(ptr,name)` asserts a pointer is equal to nullptr
* `assert_not_null(ptr,name)` asserts a pointer is not equal to nullptr
* `assert_throws<exception>( function, name)` asserts that the function passed (may be a lambda expression) throws an exception of type exception (template parameter)
* `assert_contains(first, last, value, name)` asserts that value exists in the collection between first and last (two iterators)
* `assert_not_contains(first,last,value,name)` assert that value not exists in the collection between first and last
* `assert_collection_equals(first1, last1, first2, last2,name)` asserts that collection between first1 and last1 and collection between first2 ans last2 (all iterators) contains the same values
* `assert_same_type(val1, val2, name)` asserts that val1 and val2 have identical type
* `assert_not_same_type(val1, val2, name)` asserts that val1 and val2 does not have the same type

To run the test, you must create an instance of your test class and call its `run()` operation. The results of the test are outputed on the standard output (`std::cout`) but you can change it : the constructor of `Test` may receive an optional `std::ostream&` parameter, who is the output of the test framework.
The time of the whote test is computed and shown.

## Sample
In the sample folder you will find a `Ratio` class and a simple test who use the framework. You juste have to build and run to show the test.

## New in version 2
A timeout is added (default: 30s) and tests are cancelled if their time is over. Prevents for loop tests. 
If you want to make long tests (more than 30s in total) you must specify a longer timeout, or infinite timeout)
