#pragma once
/**********************************************************************************************************************
+==================================================== Template Method ================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| The Template Method design pattern defines the skeleton of an algorithm in a base class, allowing subclasses to     |
| override specific steps without changing the overall structure of the algorithm.                                    |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the Template Method pattern when multiple classes share the same algorithm structure but require customization  |
| in certain steps, or when you want to enforce a consistent sequence of operations while allowing some flexibility.  |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

#include <sstream>

namespace template_method
{
class itemplate_method
{
public:
    virtual std::string perform_all() const
    {
        std::stringstream ss;
        ss << impl_action_1() << " " << impl_action_2() << " " << to_impl_action_1() << " " << to_impl_action_2();
        return ss.str();
    }

protected:
    virtual std::string impl_action_1() const
    {
        return "itemplate_method: impl_action_1";
    }

    virtual std::string impl_action_2() const
    {
        return "itemplate_method: impl_action_2";
    }

    virtual std::string to_impl_action_1() const = 0;
    virtual std::string to_impl_action_2() const = 0;
};

class template_method_1 : public itemplate_method
{
protected:
    virtual std::string to_impl_action_1() const override
    {
        return "template_method_1: action_1";
    }

    virtual std::string to_impl_action_2() const override
    {
        return "template_method_1: action_2";
    }
};

class template_method_2 : public itemplate_method
{
protected:
    virtual std::string to_impl_action_1() const override
    {
        return "template_method_2: action_1";
    }

    virtual std::string to_impl_action_2() const override
    {
        return "template_method_2: action_2";
    }
};
}  // namespace template_method
