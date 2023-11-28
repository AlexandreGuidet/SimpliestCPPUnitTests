#include <iostream>
#include "test.h"

int main()
{
    std::cout << "Simple test of dogwatch"<<std::endl;
    bool end=false;
    tests::WatchDog watch(3000);
    watch.start([&](){std::cout << "Dog watch !" << std::endl; end=true;} ); 
              
    std::cout << "Waiting";
    while(!end)
    {
        std::cout << ".";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    

    watch.start([](){std::cout<<"This dog watch never throws";});
    std::cout << "Waiting again...";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); 
    watch.cancel();
    std::cout << "cancelled."<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // wait if dog watch is not cancelled !
    std::cout << "good bye" << std::endl;
}