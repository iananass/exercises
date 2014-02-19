#include <iostream>

class nullparam
{
};

template <class T, T Default>
class default_param
{
public:

    default_param(const nullparam&)
    : _value(Default)
    {
    }

    default_param(const T& val)
    : _value(val)
    {
    }

    default_param(T&& val)
    : _value(std::forward <T> (val))
    {
    }

    const T& get() const
    {
        return _value;
    }

private:
    T _value;
};

void foo(default_param<int, 10> p1, default_param <short, 22> p2, default_param <char, 'H'> p3)
{
    std::cout << p1.get() << ' ' << p2.get() << ' ' << p3.get() << std::endl;
}

int main()
{

    foo(nullparam(), nullparam(), 'G');
    foo(155, nullparam(), nullparam());
    foo(nullparam(), 122, nullparam());

    return 0;
}