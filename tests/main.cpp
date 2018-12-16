#include <iostream>
#include <string>
#include "../tinytest.h"

int addOne(int n) {
    return n+1;
}

std::string rosesAre() {
    return "red";
}

TINY_TEST(firstTest) {
    TINY_CHECK("Is 1+1=2?", addOne(1) == 2);
}

TINY_TEST(secondTest) {
    TINY_CHECK("Or is 1+1=1?", addOne(1) == 1);
}

TINY_TEST(thirdTest) {
    TINY_CHECK("Are roses red?", rosesAre() == "red");
}

TINY_TEST(fourthTest) {
    TINY_CHECK("Or are roses blue?", rosesAre() == "blue");
}

int main() {

    int r = RUN_TESTS();
    std::cout << r << " test(s) failed\n";
    return r;
}

