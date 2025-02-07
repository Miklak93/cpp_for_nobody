#pragma once
/**********************************************************************************************************************
+======================================================= Strategy ====================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| The Strategy design pattern defines a family of algorithms, encapsulates each one, and makes them interchangeable.  |
| It allows the algorithm to vary independently from the clients that use it, promoting flexibility and reuse.        |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the Strategy pattern when you need to define multiple algorithms for a task and want to switch between them     |
| dynamically at runtime, or when you want to eliminate conditional statements by encapsulating algorithm logic.      |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

namespace strategy
{
struct istrategy
{
    virtual ~istrategy() {}
    virtual std::string action() const = 0;
};

class target
{
    public:
    target() : strategy_(nullptr) {}

    void set_strategy(const istrategy& strategy)
    {
        strategy_ = &strategy;
    }

    std::string request() const
    {
        return strategy_->action();
    }

    private:
    const istrategy* strategy_;
};

struct strategy_1 : istrategy
{
    virtual std::string action() const override
    {
        return "strategy_1: action";
    }
};

struct strategy_2 : istrategy
{
    virtual std::string action() const override
    {
        return "strategy_2: action";
    }
};
}  // namespace strategy
