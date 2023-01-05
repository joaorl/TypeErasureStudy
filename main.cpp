#include "Any.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int main()
{
    Any a = 1;
    Any b = string("hello");
    Any c = vector<int>{1, 2, 3};
    Any d = map<string, Any> { 
            {string("a"), 1}, 
            {string("b"), string("hello")} 
        };

    cout << a.Get<int>() << endl;
    cout << b.Get<string>() << endl;
    cout << c.Get<vector<int>>().size() << endl;

    for (auto& x : c.Get<vector<int>>())
    { 
        cout << x << " "; 
    } 
    cout << endl;

    for (auto& [key, value] : d.Get<map<string, Any>>())
    {
        try
        {
            auto v = value.Get<int>();
            cout << key << ": " << v << endl; 
        }
        catch (std::bad_cast& e)
        {
            auto v = value.Get<string>();
            cout << key << ": " << v << endl; 
        }
    }

    return 0;
}
