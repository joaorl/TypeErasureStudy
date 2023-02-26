#include "Any.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Json.h"

using namespace std;

int main()
{
    Any a = 1;
    Any b = string("hello");
    Any c = vector<int>{1, 2, 3};
    Any d = map<string, Any> { 
            {string("a"), 1}, 
            {string("b"), string("hello")}, 
            {string("c"), vector<Any>{1, 2, 3}} 
        };

    cout << a.Get<int>() << endl;
    cout << b.Get<string>() << endl;
    cout << c.Get<vector<int>>().size() << endl;

    for (auto& x : c.Get<vector<int>>())
    { 
        cout << x << " "; 
    } 
    cout << endl;

    // Json format serialization and deserialization example.
    d = Json::Deserialize(Json::Serialize(d));
    for (auto& [key, value] : d.Get<map<string, Any>>())
    {
        try
        {
            auto v = value.Get<int>();
            cout << key << ": " << v << endl;
            continue;
        }
        catch (std::bad_cast& e)
        {
        }

        try
        {
            auto v = value.Get<string>();
            cout << key << ": " << v << endl;
            continue;
        }
        catch (std::bad_cast& e)
        {
        }

        try
        {
            auto v = value.Get<vector<Any>>();
            for (auto& i : v)
                cout << key << ": " << i.Get<int>() << endl;
            continue;
        }
        catch (std::bad_cast& e)
        {
        }
    }

    return 0;
}
