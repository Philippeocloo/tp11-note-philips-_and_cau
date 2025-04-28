#include <iostream>
#include "main.h"

#ifndef UNIT_TESTS
int main()
{
    std::cout << "Hello world" << std::endl;
}
#endif

int oneplusone() {
    return 1 + 1;
}