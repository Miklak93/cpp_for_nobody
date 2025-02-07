#pragma once
/**********************************************************************************************************************
+======================================================== Bridge =====================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| The Bridge design pattern separates an abstraction from its implementation, allowing them to vary independently.    |
| It uses composition to bridge the gap between the abstraction and its implementation.                               |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the Bridge pattern when you want to decouple abstractions and implementations so they can evolve independently, |
| or when you need to avoid a permanent binding between an abstraction and its implementation.                        |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

#include <string>
#include <type_traits>

namespace bridge
{
struct iimplementation
{
    virtual ~iimplementation() {};

    virtual std::string action() const = 0;
};

struct implementation_1 : iimplementation
{
    virtual std::string action() const override
    {
        return "implementation_1: action";
    }
};

struct implementation_2 : iimplementation
{
    virtual std::string action() const override
    {
        return "implementation_2: action";
    }
};

struct implementation_3 : iimplementation
{
    virtual std::string action() const override
    {
        return "implementation_3: action";
    }
};

struct iabstraction
{
    virtual std::string trigger_action() const = 0;
};

class abstraction : public iabstraction
{
    public:
    abstraction(const iimplementation& implementation) : implementation_(implementation) {}

    virtual std::string trigger_action() const override
    {
        return std::string{"abstraction with "} + implementation_.action();
    }

    private:
    const iimplementation& implementation_;
};
}  // namespace bridge
