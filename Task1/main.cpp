/*1. Use bit operator(s) to calculate the sum of two integers, 
check overflow with bit operator too. Throw an exception in case of overflow. 
Comparison operators are allowed.
Signature of the interface :	int add(int a, int b);
*/
#include <iostream>

int add(int a, int b)
{
    try
    {
        int a_0(a),b_0(b);
        while (b != 0)
        {
            //helper contains common set bits of a and b
            int helper = a & b;
            //on sum must be at least on of the bits isn't set
            a = a ^ b;
            //shift to x for adding it to a, what gives the required sum
            b = helper << 1;
        }
        if (a_0 > 0 && b_0 > 0 && a < 0)
        {
            throw a;
        }
        if (a_0 < 0 && b_0 < 0 && a > 0)
        {
            throw a;
        }
        return a;
    }
    catch (int a)
    {
        std::cerr << "Result of addition: "<< a << " is overflowed" << '\n';
    }
}

int main()
{
    int a, b;
    std::cin >> a;
    std::cin >> b;

    std::cout << std::endl
              << add(a, b);
    return 0;
}