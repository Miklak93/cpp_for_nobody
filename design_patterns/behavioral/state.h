#pragma once
/**********************************************************************************************************************
+======================================================== State ======================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| The State design pattern allows an object to change its behavior when its internal state changes. It achieves this  |
| by encapsulating state-specific behavior in separate classes and delegating state transitions to these classes.     |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the State pattern when an object's behavior depends on its state, and it must change its behavior dynamically   |
| at runtime. It is particularly useful when you have complex state-dependent behavior that would otherwise result in |
| large and complex conditional statements.                                                                           |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

#include <memory>

namespace state
{
struct istate;

struct icontext
{
    virtual ~icontext() {}
    virtual void change_state(istate& state) = 0;
    virtual std::string request_1() = 0;
    virtual std::string request_2() = 0;
};

struct istate
{
    virtual ~istate() {}
    virtual std::string action_1() = 0;
    virtual std::string action_2() = 0;
};

class state_2 : public istate
{
    public:
    state_2(icontext& context) : context_(&context) {}

    virtual std::string action_1() override
    {
        return "state_2: action_1";
    }

    virtual std::string action_2() override
    {
        return "state_2: action_2";
    }

    private:
    icontext* context_;
};



class state_1 : public istate
{
    public:
    state_1(icontext& context) : context_(&context), next_state_(std::make_unique<state_2>(context)) {}

    virtual std::string action_1() override
    {
        return "state_1: action_1";
    }

    virtual std::string action_2() override
    {
        context_->change_state(*next_state_);
        return "state_1: action_2 -> transition to state_2";
    }

    private:
    icontext* context_;
    std::unique_ptr<istate> next_state_;
};

class context : public icontext
{
    public:
    context() : current_state_(nullptr) {}

    virtual void change_state(istate& state) override
    {
        current_state_ = &state;
    }

    virtual std::string request_1() override
    {
        return current_state_->action_1();
    }

    virtual std::string request_2() override
    {
        return current_state_->action_2();
    }

    private:
    istate* current_state_;
};
}  // namespace state
