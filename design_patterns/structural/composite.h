#pragma once
/**********************************************************************************************************************
+======================================================= Composite ===================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| The Composite design pattern allows you to compose objects into tree structures to represent part-whole hierarchies.|
| It lets clients treat individual objects and compositions of objects uniformly.                                     |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the Composite pattern when you need to represent a tree-like structure of objects, where individual objects and |
| their compositions should be treated in the same way (e.g., directories and files in a filesystem).                 |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

#include <list>
#include <sstream>

namespace composite
{
class component
{
    public:
    virtual ~component() {}

    virtual std::string operation() const
    {
        return "";
    }

    virtual void add(component&) {}

    virtual void remove(component&) {}

    void set_parent(const component* parent)
    {
        parent_ = parent;
    }

    const component* get_parent() const
    {
        return parent_;
    }

    virtual bool is_composite() const
    {
        return false;
    }

    protected:
    const component* parent_;
};

struct leaf : component
{
    virtual std::string operation() const override
    {
        return "{leaf operation}";
    }
};

class composite : public component
{
    public:
    virtual void add(component& item) override
    {
        children_.push_back(&item);
        item.set_parent(this);
    }

    virtual void remove(component& item) override
    {
        children_.remove(&item);
        item.set_parent(nullptr);
    }

    virtual bool is_composite() const override
    {
        return true;
    }

    std::string operation() const override
    {
        std::stringstream ss;
        ss << "branch->{";
        std::for_each(children_.begin(), children_.end(), [&](const auto& ptr) { ss << ptr->operation(); });
        ss << "}. ";
        return ss.str();
    }

    protected:
    std::list<component*> children_;
};

/* Some helper functions */
std::unique_ptr<component> make_leaf()
{
    return std::make_unique<leaf>();
}

std::unique_ptr<component> make_branch()
{
    return std::make_unique<composite>();
}

std::unique_ptr<component> make_tree()
{
    return std::make_unique<composite>();
}
}  // namespace composite
