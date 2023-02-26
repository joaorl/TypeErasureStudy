#ifndef __JSON_H__
#define __JSON_H__

#include "Any.h"

class Json
{
public:
    static std::string Serialize(Any& value);
    static Any Deserialize(const std::string& json);
private:
    static Any _Deserialize(stringstream& ss);
};

#endif // __JSON_H__