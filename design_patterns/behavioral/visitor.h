#pragma once
/**********************************************************************************************************************
+======================================================== Visitor ====================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| The Visitor design pattern allows you to add new operations to existing object structures without modifying their   |
| classes. It achieves this by separating the operation logic into a separate visitor object.                         |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the Visitor pattern when you need to perform many unrelated operations on an object structure and want to keep  |
| these operations separate from the objects themselves. It is especially useful when the object structure is stable. |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

namespace visitor
{
struct component_1;
struct component_2;

struct ivisitor
{
    virtual ~ivisitor() {}
    virtual std::string visit(const component_1& component) const = 0;
    virtual std::string visit(const component_2& component) const = 0;
};

struct icomponent
{
    virtual ~icomponent() {}
    virtual std::string accept(const ivisitor& visitor) const = 0;
};

struct component_1 : icomponent
{
    /* The most important function */
    virtual std::string accept(const ivisitor& visitor) const override
    {
        return visitor.visit(*this);
    }

    /* Specific method of the component_1 */
    std::string name_1() const
    {
        return "component_1";
    }
};

struct component_2 : icomponent
{
    /* The most important function */
    virtual std::string accept(const ivisitor& visitor) const override
    {
        return visitor.visit(*this);
    }

    /* Specific method of the component_2 */
    std::string name_2() const
    {
        return "component_2";
    }
};

struct visitor_1 : ivisitor
{
    virtual std::string visit(const component_1& component) const override
    {
        return component.name_1() + " visited by visitor_1";
    }

    virtual std::string visit(const component_2& component) const override
    {
        return component.name_2() + " visited by visitor_1";
    }
};

struct visitor_2 : ivisitor
{
    virtual std::string visit(const component_1& component) const
    {
        return component.name_1() + " visited by visitor_2";
    }

    virtual std::string visit(const component_2& component) const
    {
        return component.name_2() + " visited by visitor_2";
    }
};
}  // namespace visitor
