#pragma once
/**********************************************************************************************************************
+======================================================== Proxy ======================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| The Proxy design pattern provides a placeholder or surrogate for another object to control access to it. It can be  |
| used to add an extra layer of control, such as lazy initialization, access control, or logging.                     |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the Proxy pattern when you need to control access to an object, add additional functionality like caching or    |
| logging, or when dealing with expensive objects that should be created on demand.                                   |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

namespace proxy
{
struct irequest
{
    virtual std::string send() const = 0;
};

struct request : irequest
{
    virtual std::string send() const override
    {
        return "request: send";
    }
};

class proxy : public irequest
{
    public:
    proxy(const irequest& request) : request_(request) {}

    virtual std::string send() const override
    {
        std::stringstream ss;
        ss << "proxy: " << is_connected() << " and " << is_logged() << " so " << request_.send();
        return ss.str();
    }

    private:
    std::string is_connected() const
    {
        return "is_connected";
    }

    std::string is_logged() const
    {
        return "is_logged";
    }

    const irequest& request_;
};
}  // namespace proxy
