#pragma once
/**********************************************************************************************************************
+======================================================== Memento ====================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| The Memento design pattern provides a way to capture and store an object's state so it can be restored later        |
| without violating encapsulation. It allows the object to manage its state externally while keeping details hidden.  |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the Memento pattern when you need to implement undo/redo functionality or save snapshots of an object's state   |
| to restore it later without exposing its internal structure.                                                        |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

#include <memory>
#include <vector>

namespace memento
{
struct imemento
{
    virtual ~imemento() {};
    virtual std::string name() const = 0;
    virtual std::string state() const = 0;
};

class memento : public imemento
{
    public:
    memento(std::string state) : state_(std::move(state)) {}

    virtual std::string name() const override
    {
        return "memento state: " + state_;
    }

    virtual std::string state() const override
    {
        return state_;
    }

    private:
    std::string state_;
};

class originator
{
    public:
    originator(std::string state = {}) : state_(std::move(state)) {}

    void action(std::string new_state)
    {
        state_ = new_state;
    }

    std::unique_ptr<imemento> save()
    {
        return std::make_unique<memento>(state_);
    }

    std::string state() const
    {
        return state_;
    }

    void restore(const imemento& memento)
    {
        state_ = memento.state();
    }

    private:
    std::string state_;
};

class caretaker
{
    public:
    caretaker(originator& orig) : originator_(orig) {}

    void backup()
    {
        mementos_.push_back(originator_.save());
    }

    void undo()
    {
        if (mementos_.empty())
        {
            return;
        }

        auto last = std::move(mementos_.back());
        mementos_.pop_back();

        try
        {
            originator_.restore(*last);
        }
        catch (...)
        {
            undo();
        }
    }

    std::vector<std::string> history() const
    {
        std::vector<std::string> out;
        for (const auto& memento_ : mementos_)
        {
            out.push_back(memento_->name());
        }
        return out;
    }

    private:
    std::vector<std::unique_ptr<imemento>> mementos_;
    originator& originator_;
};
}  // namespace memento
