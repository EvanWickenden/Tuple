
#include <iostream>

#include "type.hpp"
#include "tuple.hpp"
#include "list.hpp"

using namespace List;
using namespace Tuple;
using namespace Type;

using std::cout;
using std::endl;

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
    List<int, int> l2(0,1);
    List<int, int, int> l3(3,2,1);
    List<int, int, int, int> l4(4,3,2,1);
    cout << l2 << "  " << l3 << "  " << l4 << endl;
};
