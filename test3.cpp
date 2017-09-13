
#include <iostream>
#include "list.hpp"

using namespace List;

struct I
{
    typedef int Args;
    int i;   
    I(int i) : i(i) {}
    
    friend std::ostream& operator << (std::ostream& s, I& i)
    {
        s << i.i;
        return s;
    };
};

int main()
{
    List<I, char, int> l(0,49,2);
    std::cout << l << std::endl;
};
