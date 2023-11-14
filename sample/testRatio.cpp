#include "ratio.h"
#include "test.h"
#include <sstream>
#include <vector>
#include <list>

using namespace tests;

/**
 * Sample of unit test framework
*/
class TestRatio : public Test{
    private:
        void test_create(){
            Ratio r(1,2);
            assert_equal(0.5,r.to_double(),1e-7,"create");    
            assert_throws<DivideByZero>( [](){
                Ratio z(1,0);
            },"exception divide 0");

        }
        void test_add(){
            Ratio r1(1,2);
            Ratio r2(3,5);
            Ratio r3 = r1+r2; // 1/2+3/5 = 5/10+6/10=11/10
            Ratio test(11,10);
            assert_equal(11.0/10.0, r3.to_double(), 1e-7,"add");
            assert_equal(test,r3,"equals after add");
        }
        void test_tostring(){
             Ratio r2(3,5);
            std::ostringstream str;
            str << r2;
            assert_equal(std::string("3/5"),str.str(),"output to stream");  
        }
        void test_collections(){
            std::vector<Ratio> ratios;        
            Ratio r1(1,2);
            Ratio r2(3,5);
            Ratio r3;
            ratios.push_back(r1); 
            ratios.push_back(r2);
            assert_contains(ratios.begin(), ratios.end(), r1, "value in vector");
            assert_not_contains(ratios.begin(),ratios.end(),r3,"value not in vector");
            std::list<Ratio> ratios2;
            ratios2.push_back(r1);
            ratios2.push_back(r2);
            assert_contains(ratios2.begin(), ratios2.end(), r1, "value in list");
            assert_collection_equals(ratios.begin(), ratios.end(), ratios2.begin(), ratios2.end(),"vector and list");
        }

        void test_pointers(){
            Ratio *r1 = nullptr;
            Ratio *r2 = new Ratio(1,2);
            assert_null(r1,"pointer is null");
            assert_not_null(r2,"pointer is not null");
            delete r2;
        }

        void test_type(){
            Ratio r1(1,2);
            Ratio r2(3,5);
            assert_same_type(r1,r2,"type comparison");
            assert_not_same_type(r1,1/2,"types differents");
        }
    protected:
        void test_code() override{
            test_create();
            test_add();
            test_tostring();
            test_collections();       
            test_pointers();
            test_type();
        }
    public:
        TestRatio(std::ostream& stream):Test(stream){}
};

int main()
{
    TestRatio tests(std::cout);
    tests.run();
    return 0;
}