#pragma once
/**********************************************************************************************************************
+======================================================= Observer ====================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| The Observer design pattern defines a one-to-many dependency between objects so that when one object changes state, |
| all its dependents (observers) are notified and updated automatically.                                              |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the Observer pattern when multiple objects need to react to changes in the state of another object, or when you |
| want to achieve a publish-subscribe mechanism to decouple subjects and observers.                                   |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

#include <list>
#include <string>

namespace observer
{
struct iobserver
{
    virtual ~iobserver() {}
    virtual void update(std::string) = 0;
    virtual std::string current() const = 0;
};

struct itarget
{
    virtual ~itarget() {}
    virtual void attach(iobserver&) = 0;
    virtual void detach(iobserver&) = 0;
    virtual void notify() = 0;
};

class target : public itarget
{
    public:
    target() : observers_(), message_() {}

    ~target() = default;

    virtual void attach(iobserver& observer) override
    {
        observers_.push_back(std::move(&observer));
    }

    virtual void detach(iobserver& observer) override
    {
        observers_.remove(&observer);
    }

    virtual void notify() override
    {
        for (const auto& observer : observers_)
        {
            observer->update(message_);
        }
    }

    void action(std::string in)
    {
        message_ = in;
        notify();
    }

    private:
    std::list<iobserver*> observers_;
    std::string message_;
};

class observer : public iobserver
{
    public:
    observer(target& t, std::size_t num) : target_(t), number_(num), message_()
    {
        target_.attach(*this);
    }

    virtual void update(std::string message) override
    {
        message_ = std::move(message);
    }

    virtual std::string current() const override
    {
        return message_;
    }

    void unsubscribe()
    {
        target_.detach(*this);
    }

    private:
    target& target_;
    std::size_t number_;
    std::string message_;
};
}  // namespace observer
