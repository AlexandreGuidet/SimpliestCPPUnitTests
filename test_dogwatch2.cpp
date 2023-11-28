#include <iostream>
#include "test.h"

class bad_test : public tests::Test
{
    public:
    bad_test() : tests::Test(std::cout, 3000){

    }
    protected:
    void test_code() override {
        assert_true(true,"first fake test");
        int i=0;
        while(true)
            i++; // loop test with no logic code
        assert_false(true,"last fake test");
    }
};

class good_test : public tests::Test
{
    protected:
    void test_code() override{
        assert_true(true,"Good test");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        assert_equal(1,1,"another good test");
    }
};
int main()
{
    std::cout << "Tests with dog watch" << std::endl;

    std::cout << "Test good one" << std::endl;
    good_test test1;
    test1.run();

    std::cout << "Test bad one "<<std::endl;
    bad_test test2;
    test2.run(); 

    return 0;
}