TinyTest
========

TinyTest is a small unit test framework for C++. 

Its main features are:

* **Portability**. It consists of a single header file that uses Standard C++
  features only. It should work on every C++ compiler in any platform.
* **Ease of use**. Just include the header and write your tests using the 
provided macros.
* **User friendly output**. The colored output reports assertion failures, 
including filename, line number and failed condition in a friendly manner 
while ensuring maximum visibility. 

Example usage
-------------

    #include <iostream>
    #include "tinytest.h"
    
    std::string rosesAre() {
        return "red";
    }

    TINY_TEST(passingTest) {
        TINY_CHECK("Are roses red?", rosesAre() == "red");
    } 

    TINY_TEST(failingTest) {
        TINY_CHECK("Are roses blue?", rosesAre() == "blue");
    } 

    int main() {
        int r = RUN_TESTS();
        std::cout << r << " test(s) failed\n";
        return 0;
    }

Compile the program and run. The framework will run the tests defined and
produce the following output:

```diff
+ passingTest             passed
- failingTest             failed assertion in main.cpp on line 13 
                               Description: "Are roses blue?"
                                 Condition: [ rosesAre() == "blue" ]
```
