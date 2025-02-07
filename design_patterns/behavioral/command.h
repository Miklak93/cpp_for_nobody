#pragma once
/**********************************************************************************************************************
+======================================================= Command =====================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| The Command design pattern encapsulates a request as an object, allowing you to parameterize objects with requests, |
| delay or queue the execution of a request, and support undoable operations.                                         |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the Command pattern when you need to decouple the sender and receiver of a request, support undo/redo           |
| functionality, or when you need to queue or log requests. It is particularly useful in task scheduling systems.     |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

namespace command
{
struct icommand
{
    virtual ~icommand() {}
    virtual std::string execute() const = 0;
};


class invoker
{
    public:
    void set_on_start(const icommand& on_start)
    {
        on_start_ = &on_start;
    }

    void set_on_finish(const icommand& on_finish)
    {
        on_finish_ = &on_finish;
    }

    std::string invoke() const
    {
        std::stringstream ss;
        if (on_start_)
        {
            ss << on_start_->execute() << " ";
        }

        ss << "invoker: invoke";

        if (on_finish_)
        {
            ss << " " << on_finish_->execute();
        }
        return ss.str();
    }

    private:
    const icommand* on_start_;
    const icommand* on_finish_;
};

class simple_command : public icommand
{
    public:
    simple_command(std::string data) : data_(std::move(data)) {}

    virtual std::string execute() const override
    {
        return "simple_command: execute: " + data_;
    }

    private:
    std::string data_;
};

class complex_command : public icommand
{
    private:
    struct receiver
    {
        std::string action_1(std::string action) const
        {
            return "receiver: action_1: " + action;
        }

        std::string action_2(std::string action) const
        {
            return "receiver: action_2: " + action;
        }
    };

    public:
    complex_command(std::string value1, std::string value2) : receiver_(), value1_(std::move(value1)), value2_(std::move(value2)) {}

    virtual std::string execute() const override
    {
        return receiver_.action_1(value1_) + " " + receiver_.action_2(value2_);
    }

    private:
    receiver receiver_;
    std::string value1_;
    std::string value2_;
};
}  // namespace command
