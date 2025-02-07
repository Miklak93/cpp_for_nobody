#pragma once
/**********************************************************************************************************************
+======================================================== Mediator ===================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| The Mediator design pattern defines an object that encapsulates how a set of objects interact. It promotes loose    |
| coupling by preventing objects from referring to each other explicitly and allowing their communication through a   |
| central mediator.                                                                                                   |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the Mediator pattern when you want to reduce the complexity of communication between multiple objects in a      |
| system. It is useful when you have many objects that need to interact, but direct interactions would lead to        |
| tightly coupled components.                                                                                         |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

namespace mediator
{
struct imediator;

struct icomponent
{
    virtual void set_mediator(const imediator& mediator) = 0;
};

struct imediator
{
    virtual std::string notify(std::string event) const = 0;
};

class component_1 : public icomponent
{
    public:
    component_1() : mediator_(nullptr) {}

    virtual void set_mediator(const imediator& mediator) override
    {
        mediator_ = &mediator;
    }

    std::string action_1() const
    {
        if (!mediator_)
        {
            return "component_1: action_1";
        }
        std::string procedure = "component_1: action_1 trigerred ";
        std::string notification = mediator_->notify("action_1");
        return procedure + notification;
    }

    std::string handle_1() const
    {
        return "component_1: handle_1";
    }

    private:
    const imediator* mediator_;
};

class component_2 : public icomponent
{
    public:
    component_2() : mediator_(nullptr) {}

    virtual void set_mediator(const imediator& mediator) override
    {
        mediator_ = &mediator;
    }

    std::string action_2() const
    {
        if (!mediator_)
        {
            return "component_2: action_2";
        }
        std::string procedure = "component_2: action_2 trigerred ";
        std::string notification = mediator_->notify("action_2");
        return procedure + notification;
    }

    std::string handle_2() const
    {
        return "component_2: handle_2";
    }

    private:
    const imediator* mediator_;
};

class mediator : public imediator
{
    public:
    mediator(component_1& component1, component_2& component2) : component1_(component1), component2_(component2)
    {
        component1_.set_mediator(*this);
        component2_.set_mediator(*this);
    }

    virtual std::string notify(std::string event) const override
    {
        if (event == "action_1")
        {
            return "mediator which triggered " + component2_.handle_2();
        }
        if (event == "action_2")
        {
            return "mediator which triggered " + component1_.handle_1();
        }
        return {};
    }

    private:
    component_1& component1_;
    component_2& component2_;
};
}  // namespace mediator
