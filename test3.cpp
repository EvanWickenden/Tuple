
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
    List<> l0;
    List<int, int> l2(0,1);
    List<int, int, int> l3(3,2,1);
    List<int, int, int, int> l4(4,3,2,1);

    int a = 2, b = 3;
    List<int&, int&> l5(a, b);

    cout << l0 << endl;

    cout << l2 << "  " << l3 << "  " << l4 << endl;

    cout << l5 << endl;
    a++;
    cout << l5 << endl;

    cout << l3.three << endl;
};
