#ifndef RATIOH
#define RATIOH
#include <iostream>

/**
 * Divide by zero error
*/
class DivideByZero{};

/**
 * Simple ratio class
*/
class Ratio
{
    int num;
    int den;

 public:
 /**
  * Initialize the ratio
  * @param n the numerator
  * @param d the denominator (must not be null)
  * @throws DivideByZero if denominator is null
 */
    Ratio(int n=0, int d=1):num(n),den(d){
        if(d==0) throw DivideByZero();
    }

    /**
     * Converts to float value
     * @return the value 
    */
    double to_double() const {return (double)num/(double)den;}    
    int numerator() const {return num;}
    int denominator() const {return den;}
    /**
     * Add a ratio
     * @param r the other ratio to add
    */
    void operator+=(const Ratio& r)
    {
        num = num*r.den+r.num*den;
        den *= r.den;
    }
    /**
     * Ratio comparison
    */
    bool operator==(const Ratio& other) const{
        return num*other.den == other.num*den;
    }
    bool operator!=(const Ratio& other) const{
        return !operator==(other);
    }
};

/**
 * Add two ratios
 * @param r1 the first ratio
 * @param r2 the second ratio
 * @return r1+r2
*/
Ratio operator+(const Ratio& r1, const Ratio& r2)
{
    Ratio r(r1);
    r+=r2;
    return r;
}

/**
 * Sends ratio to a output stream
 * @param stream the output stream
 * @param r the ratio
 * @return the output stream
*/
std::ostream& operator<<(std::ostream& stream, const Ratio& r)
{
    stream<<r.numerator()<<"/"<<r.denominator();
    return stream;
}
#endif