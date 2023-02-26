#ifndef __ANY_H__
#define __ANY_H__

#include <memory>
#include "TypeHolder.h"

class Any
{
public:
    Any() {}

    template <typename T>
    Any(const T& value) : _holder(new Holder<T>(value)) {}

    Any(const Any& other) : _holder(other._holder->Clone()) {}

    Any& operator=(const Any& other)
    {
        _holder.reset(other._holder->Clone());

        return *this;
    }

    const std::type_info& Type() const
    {
        if (_holder)
        {
            return _holder->Type();
        }

        return typeid(void);
    }

    template <typename T>
    T& Get()
    {
        if (typeid(T) != _holder->Type())
        {
            throw std::bad_cast();
        }

        return static_cast<Holder<T>*>(_holder.get())->GetValue();
    }

private:
    std::unique_ptr<HolderBase> _holder;
};

#endif // __ANY_H__
