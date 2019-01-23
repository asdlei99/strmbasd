#ifndef BIGGER_TYPE_H_INCLUDED
#define BIGGER_TYPE_H_INCLUDED

#include <type_traits>

namespace compat
{
    template <typename T, typename U>
    struct BiggerType
    {
        using type = typename std::conditional <
            sizeof(T) >= sizeof(U),
            T,
            U
        >::type;
    };
}

#endif // BIGGER_TYPE_H_INCLUDED
