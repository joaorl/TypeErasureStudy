
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include "Json.h"

using namespace std;

string Json::Serialize(Any& value)
{
    stringstream ss;

    if (value.Type() == typeid(int))
    {
        ss << value.Get<int>();
    }
    else if (value.Type() == typeid(double))
    {
        ss << value.Get<double>();
    }
    else if (value.Type() == typeid(string))
    {
        ss << "\"" << value.Get<string>() << "\"";
    }
    else if (value.Type() == typeid(map<string, Any>))
    {
        ss << "{";
        map<string, Any> data = value.Get<map<string, Any>>();
        for (auto it = data.begin(); it != data.end(); ++it)
        {
            if (it != data.begin())
            {
                ss << ",";
            }
            ss << "\"" << it->first << "\":" << Serialize(it->second);
        }
        ss << "}";
    }
    else if (value.Type() == typeid(vector<Any>))
    {
        ss << "[";
        vector<Any> list = value.Get<vector<Any>>();
        for (int i = 0; i < list.size(); i++)
        {
            if (i > 0)
            {
                ss << ",";
            }
            ss << Serialize(list[i]);
        }
        ss << "]";
    }

    return ss.str();
}

Any Json::Deserialize(const string& json)
{
    stringstream ss(json);

    char c = ss.get();
    if (c == '\"')
    {
        c = ss.get();

        string value;
        while (c != '\"' && ss)
        {
            if (c != '\\')
            {
                value += c;
            }
            c = ss.get();
        }
        if (c != '\"')
        {
            throw invalid_argument("Invalid JSON string");
        }
        return value;
    }

    if (c == '{')
    {
        map<string, Any> map;
        while (ss && (c = ss.get()) != '}')
        {
            if (c != '\"')
            {
                throw invalid_argument("Invalid JSON object");
            }

            c = ss.get();

            string key;
            while (c != '\"' && ss)
            {
                if (c != '\\')
                {
                    key += c;
                }
                c = ss.get();
            }

            if (c != '\"' || ss.get() != ':')
            {
                throw invalid_argument("Invalid JSON object");
            }

            map[key] = _Deserialize(ss);

            c = ss.get();
            if (c == ',')
            {
                continue;
            }
            if (c == '}')
            {
                break;
            }
            else
            {
                throw invalid_argument("Invalid JSON object");
            }
        }
        return map;
    }

    if (c == '[')
    {
        vector<Any> lst;
        while (ss && (c = ss.get()) != ']')
        {
            ss.unget();
            lst.push_back(_Deserialize(ss));

            c = ss.get();
            if (c == ',')
            {
                continue;
            }
            if (c == ']')
            {
                break;
            }
            else
            {
                throw invalid_argument("Invalid JSON array");
            }
        }
        return lst;
    }

    string value;
    while (ss && (isdigit(c) || c == '.' || c == '-' || c == '+'))
    {
        value += c;
        c = ss.get();
    }

    try
    {
        if (value.find('.') != string::npos)
        {
            return stod(value);
        }
        return stoi(value);
    }
    catch (const exception&)
    {
        throw invalid_argument("Invalid JSON value");
    }
}

Any Json::_Deserialize(stringstream& ss)
{
    char next;
    ss >> next;

    if (next == '{')
    {
        map<string, Any> mapValue;

        while (ss.peek() != '}')
        {
            string key;
            ss >> key;
            key = key.substr(1, key.length() - 3);

            ss >> next;
            mapValue[key] = _Deserialize(ss);

            ss >> next;
        }

        return Any(mapValue);
    }
    else if (next == '[')
    {
        vector<Any> listValue;

        while (ss.peek() != ']')
        {
            listValue.push_back(_Deserialize(ss));

            if (ss.peek() == ',')
            {
                ss.ignore();
            }
        }

        ss.get();

        return Any(listValue);
    }
    else if (next == '"')
    {
        string strValue;
        getline(ss, strValue, '"');
        return Any(strValue);
    }
    else
    {
        ss.unget();

        int intValue;
        ss >> intValue;

        if (ss.fail())
        {
            bool boolValue;
            ss >> boolalpha >> boolValue;
            return Any(boolValue);
        }

        return Any(intValue);
    }
}
