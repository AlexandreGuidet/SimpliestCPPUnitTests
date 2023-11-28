#include <iostream>
#include "test.h"

class bad_test : public tests::Test
{
    public:
    bad_test() : tests::Test(std::cout, 3000){

    }
    protected:
    void test_code() override {
        int i=0;
        while(true)
            i++; // loop test with no logic code
    }
};
int main()
{
    std::cout << "Tests with dog watch" << std::endl;
    bad_test test;
    test.run();

    return 0;
}