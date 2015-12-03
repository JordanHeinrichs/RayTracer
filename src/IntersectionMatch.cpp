#include "IntersectionMatch.h"

IntersectionMatch::IntersectionMatch()
: matchSuccessful_(false)
, object_(0)
, t_(0.0)
{
}

IntersectionMatch::IntersectionMatch(
    bool matchSuccessful, const I_Object* const object, const double t)
: matchSuccessful_(matchSuccessful)
, object_(object)
, t_(t)
{
}

IntersectionMatch::~IntersectionMatch()
{
}


bool IntersectionMatch::matchSuccessful() const
{
    return matchSuccessful_;
}

const I_Object* const IntersectionMatch::object() const
{
    return object_;
}

double IntersectionMatch::t() const
{
    return t_;
}

IntersectionMatch::operator bool() const
{
    return matchSuccessful_;
}

bool IntersectionMatch::operator <(const IntersectionMatch& other) const
{
    if (!other.matchSuccessful())
    {
        return true;
    }
    else if (!matchSuccessful_)
    {
        return false;
    }
    else
    {
        return t_ < other.t();
    }
}

IntersectionMatch& IntersectionMatch::operator=(const IntersectionMatch& other)
{
    matchSuccessful_ = other.matchSuccessful_;
    object_ = other.object_;
    t_ = other.t_;
    return *this;
}
