#pragma once
#include <bitset>

template <typename TENUM>
class FlagSet
{

    using TUNDER = typename std::underlying_type<TENUM>::type;
    std::bitset<std::numeric_limits<TUNDER>::max()> m_flags;

public:
    FlagSet() = default;

    template <typename... ARGS>
    FlagSet(TENUM f, ARGS... args)
        : FlagSet(args...)
    {
        set(f);
    }
    FlagSet& set(TENUM f)
    {
        m_flags.set(static_cast<TUNDER>(f));
        return *this;
    }
    bool test(TENUM f) const
    {
        return m_flags.test(static_cast<TUNDER>(f));
    }
    FlagSet& operator|=(TENUM f)
    {
        return set(f);
    }

    bool operator&(TENUM rhs) const 
    {
        return test(rhs); 
    }
};