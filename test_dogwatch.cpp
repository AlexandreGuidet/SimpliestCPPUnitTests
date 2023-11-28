#include <iostream>
#include "test.h"

int main()
{
    std::cout << "Simple test of dogwatch"<<std::endl;
    bool end=false;
    tests::DogWatch watch(3000);
    // watch.start([&](){std::cout << "Dog watch !"; end=true;} ); // test 1 : with a function
    watch.start(); // test 2 with an exception
              
    while(!end)
    {
        std::cout << "Do you want to end ?" << std::endl;
        std::string response;
        std::cin >> response;
        if(response=="yes") 
        {
            watch.cancel();
            end=true;
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(3000)); // wait if dog watch is not cancelled !

    std::cout << "good bye" << std::endl;
}