#pragma once
class I_Object;

class IntersectionMatch
{
public:
    IntersectionMatch();
    IntersectionMatch(bool matchSuccessful, const I_Object* const object, const double t);
    virtual ~IntersectionMatch();

    bool matchSuccessful() const;
    const I_Object* const object() const;
    double t() const;

    explicit operator bool() const;
    bool operator <(const IntersectionMatch& other) const;
    IntersectionMatch& operator =(const IntersectionMatch& other);

private:
    bool matchSuccessful_;
    const I_Object* object_;
    double t_;
};
