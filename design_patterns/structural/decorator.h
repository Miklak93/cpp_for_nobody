#pragma once
/**********************************************************************************************************************
+======================================================= Decorator ===================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| The Decorator design pattern allows behavior to be added to individual objects dynamically, without affecting the   |
| behavior of other objects from the same class. It provides a flexible alternative to subclassing for extending      |
| functionality.                                                                                                      |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the Decorator pattern when you need to add or modify functionality of objects at runtime, and when extending    |
| functionality through inheritance would result in an explosion of subclasses.                                       |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

#include <memory>
#include <type_traits>
namespace decorator
{
struct icomponent
{
    virtual ~icomponent() {};
    virtual std::string operation() const = 0;
};

struct component_1 : icomponent
{
    virtual std::string operation() const override
    {
        return "component_1: operation";
    }
};

struct component_2 : icomponent
{
    virtual std::string operation() const override
    {
        return "component_2: operation";
    }
};

/* Notice that decorator extends icomponent */
class decorator : icomponent
{
    public:
    decorator(const icomponent& component) : component_(component) {}

    virtual std::string operation() const override
    {
        return "decorated{" + component_.operation() + "}";
    }

    private:
    const icomponent& component_;
};
}  // namespace decorator
