#include <typeinfo> 

using namespace std; 

class HolderBase
{
public:
    virtual ~HolderBase() {}
    virtual HolderBase* Clone() const = 0;
    virtual const std::type_info& Type() const = 0;
};

template <typename T>
class Holder : public HolderBase
{
public:
    Holder(const T& value) : _value(value) {}

    const std::type_info& Type() const override
    {
        return typeid(T);
    }

    HolderBase* Clone() const override
    {
        return new Holder(_value);
    }

    void SetValue(T value)
    {
        _value = value;
    }

    T& GetValue()
    {
        return _value;
    }

private:
    T _value;
};
