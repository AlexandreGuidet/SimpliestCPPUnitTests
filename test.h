#ifndef TESTH
#define TESTH
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <typeinfo>

namespace tests
{
/**
* simple chronometer
*/
    class Chrono
    {
        private:
            std::chrono::high_resolution_clock::time_point startTime;
            std::chrono::high_resolution_clock::time_point stopTime;
        public:
	/**
	* start the measure
	*/
            void start(){
                startTime = std::chrono::high_resolution_clock::now();
            }
	/**
	* stop the measure
	*/
            void stop(){
                stopTime = std::chrono::high_resolution_clock::now();
            }
	/**
 	* compute time
	* @returns the time of measure, in milliseconds
	*/
            double time(){
                return std::chrono::nanoseconds(stopTime-startTime).count()/1000000.0;
            }
    };

    /**
     * Very simple class to make units tests in C++
     * To create a test case, you must inherit this class and overrides test_code
     * This class contains a lot of assert_xx methods to make tests
     * It computes the times taken for tests
     * All outputs are sent to an standard output stream (who may be std::cout but not only)
     * @author alexandre guidet
     * @version 1
     * @see https://github.com/AlexandreGuidet/SimpliestCPPUnitTests     
    */
    class Test
    {
        private:                       
            int failed; 
            int passed;
            std::ostream& output;
            Chrono chrono;
        public:
        /**
         * Initialize the test. 
         * @param output the stream to output the tests (default : the standard output)
        */
            Test(std::ostream& output=std::cout) : output(output), failed(0),passed(0){}
            virtual ~Test(){}
        /**
         * Runs the test and outputs the results on the stream
        */
            void run(){
                failed=0;
                passed=0;
                print_header();
                chrono.start();
                try{                    
                    test_code();                    
                }
                catch(...){
                    fail("*** exception occurs ***");
                    failed++;
                }                                
                chrono.stop();
                print_resume();                
            }

        private:
            void print_header(){
                output << "Start of unit tests.\r\n";
            }
            void print_resume(){
                output << "Tests ended. "<<passed<<" tests passed and "<<failed<<" failed.\r\n";
                output << "Total test time is "<<chrono.time()<< " ms.\r\n";
            }
            void print_result(std::string name, bool pass){
                output << "\ttest "<<name << ((pass)?" passed.\r\n":" failed ") ;
            }
            void newline(){
                output << "\r\n";
            }
        protected:
        /**
         * Contains the code of the test
        */
            virtual void test_code() = 0;

            template<typename T> void print_values(const T& expected, const T& computed)
            {
                output << expected<< " expected but "<<computed<<" gets.\r\n";
            }
        /**
         * Assert a value is true
         * @param value the value who must be true
         * @param name the name of the test (not mandatory)
        */
            void assert_true(bool value, std::string name="")
            {
                if(!value) failed++;
                else passed++;
                print_result(name,value);
                if(!value) print_values(true,false);
            }
        /**
         * Assert a value is false
         * @param value the value who must be false
         * @param name the name of the test (not mandatory)
        */
            void assert_false(bool value, std::string name="")
            {
                if(value) failed++;
                else passed++;
                print_result(name,!value);
                if(value) print_values(false,true);
            }
        /**
         * Failed the test
         *  @param name the name of the test (not mandatory)
        */
            void fail(std::string name="")
            {
                failed++;
                print_result(name,false);
                newline();
            }
        /**
         * Pass the test
         *  @param name the name of the test (not mandatory)
        */
            void pass(std::string name="")
            {
                passed++;
                print_result(name,true);
            }
        /**
         * Asserts two values are equal
         * @param expected the value expected
         * @param value the value computed by the test
         * @param name the name of the test (not mandatory)
         * @tparam T the type of values
        */
            template <typename T> 
            void assert_equal(const T& expected, const T& value,std::string name=""){
                bool pass=expected==value;
                if(!pass)
                    failed++;
                else passed++;
                print_result(name,pass);
                if(!pass) print_values(expected,value);
            }      
        /**
         * Asserts two float values are equal
         * @param expected the value expected
         * @param value the value computed by the test
         * @param precision the precision of the test 
         * @param name the name of the test (not mandatory)
        */      
            void assert_equal(const double& expected, const double& value, double precision, std::string name=""){
                double delta = std::abs(expected-value);
                bool pass = delta<precision;
                if(!pass) failed++; 
                else passed++;
                print_result(name,pass);
                if(!pass) print_values(expected,value);
            }

        /**
         * Asserts two values are not equal
         * @param not_expected the value expected to be different
         * @param value the value computed by the test
         * @param name the name of the test (not mandatory)
         * @tparam T the type of values
        */            
            template <typename T> 
            void assert_not_equal(const T& not_expected, const T& value, std::string name=""){
                bool pass=not_expected!=value;
                if(!pass) failed++;
                else passed++;
                print_result(name,pass);
            }
        /**
         * Asserts two float values are not equal
         * @param not_expected the value expected
         * @param value the value computed by the test
         * @param precision the precision of the test 
         * @param name the name of the test (not mandatory)
        */             
            void assert_not_equal(const double& not_expected, const double& value, double precision, std::string name=""){                
                double delta = std::abs(not_expected-value);
                bool pass = delta > precision;
                if(!pass) failed++;
                else passed++;
                print_result(name,pass);
            }
        /**
         * Assert an expression throws an exception
         * @param function a functionnal object (ie lambda expression) with code who can throw except
         * @param name the name of the test (not mandatory)
         * @tparam except the exception type
        */
            template <typename except> void assert_throws( void function(), std::string name="")
            {
                try
                {
                    function();
                    fail(name);
                }
                catch(const except& e)
                {
                    pass(name);
                }
                catch(...)
                {
                    fail(name);
                }
                
            }
            
        /**
         * Asserts a collection contains a value
         * @param begin the first element of collection
         * @param end the invalid element of collection (after last)
         * @param value the value to find
         * @param name the name of the test (not mandatory)
         * @tparam iterator the type of iterator
         * @tparam T the type of the value
        */
            template <typename iterator, typename T>
            void assert_contains(iterator begin, iterator end, const T& value, std::string name="")
            {
                bool pass=std::find(begin,end,value)!=end;
                                
                if(pass)
                    passed++;
                else
                    failed++;
                print_result(name,pass);
                if(!pass) output << "element not founded\r\n";
            }
        /**
         * Asserts a collection not contains a value
         * @param begin the first element of collection
         * @param end the invalid element of collection (after last)
         * @param value the value to find
         * @param name the name of the test (not mandatory)
         * @tparam iterator the type of iterator
         * @tparam T the type of the value
        */            
            template <typename iterator, typename T>
            void assert_not_contains(iterator begin, iterator end, const T& value, std::string name="")
            {
                bool pass=std::find(begin,end,value)==end;
                                
                if(pass)
                    passed++;
                else
                    failed++;
                print_result(name,pass);
                if(!pass) output << "element founded\r\n";
            }
        /**
         * Asserts two collections are identical (same elements in same order)
         * collections may be differents (list and vector) but elements type must be identical
         * @tparam iter1 type of iterator of the first collection
         * @tparam iter2 type of iterator of the second collection
         * @param first1 begin of the first collection
         * @param last1 end of the first collection
         * @param first2 begin of the second collection
         * @param last2 end of the second collection
         * @param name the name of the test (not mandatory)
        */
            template <typename iter1, typename iter2>
            void assert_collection_equals(iter1 first1, iter1 last1, iter2 first2, iter2 last2,std::string name="")
            {
                bool pass=true;
                iter1 i1 = first1;
                iter2 i2 = first2;
                bool end=false;
                while(!end){
                    if(i1==last1 || i2==last2)
                    {
                        end=true;
                        if(i1!=last1 || i2!=last2)
                            pass=false;
                    }
                    else{
                        if(*i1 != *i2){
                            pass=false;
                            end=true;
                        }
                        else{
                            ++i1;
                            ++i2;
                        }
                    }
                }
                if(pass) passed++;
                else failed++;
                print_result(name,pass);
                if(!pass) newline();
            }

        /**
         * Asserts a pointer is null
         * @tparam T type of pointer
         * @param pointer the pointer to test
         * @param name name of the test (not mandatory)
        */
            template <typename T>
            void assert_null(const T* pointer,std::string name="")
            {
                bool pass = pointer==nullptr;
                print_result(name,pass);
                if(!pass) output << "pointer is not null !\r\n";
            }
        /**
         * Asserts a pointer is not null
         * @tparam T type of pointer
         * @param pointer the pointer to test
         * @param name name of the test (not mandatory)
        */
            template <typename T>
            void assert_not_null(const T* pointer, std::string name=""){
                bool pass = pointer!=nullptr;
                print_result(name,pass);
                if(!pass) output << "pointer is null !\r\n";
            }

        /**
         * Asserts two values have the same type
         * @tparam T1 the type of value 1
         * @tparam T2 the type of value 2
         * @param value1 the first value
         * @param value2 the second value
         * @param name name of the test (not mandatory)
        */
            template <typename T1, typename T2>
            void assert_same_type(const T1& value1, const T2& value2, std::string name=""){
                bool pass = typeid(value1)==typeid(value2);
                print_result(name,pass);
                if(!pass) output << "not the same type !\r\n";
            }

        /**
         * Asserts two values have differents types
         * @tparam T1 the type of value 1
         * @tparam T2 the type of value 2
         * @param value1 the first value
         * @param value2 the second value
         * @param name name of the test (not mandatory)
        */            
            template <typename T1, typename T2>
            void assert_not_same_type(const T1& value1, const T2& value2, std::string name=""){
                bool pass = typeid(value1)!=typeid(value2);
                print_result(name,pass);
                if(!pass) output << "the same type !\r\n";
            }
    };
}

#endif
