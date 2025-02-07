#pragma once
/**********************************************************************************************************************
+======================================================== Adapter ====================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| The Adapter design pattern allows incompatible interfaces to work together by converting the interface of one class |
| into an interface that the client expects. It acts as a bridge between two incompatible components.                 |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the Adapter pattern when you need to integrate a class with an incompatible interface into your system or       |
| when you want to reuse existing classes without modifying their source code.                                        |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

#include <string>
#include <vector>

namespace adapter
{
struct target
{
    virtual std::string request() const
    {
        return "request";
    }
};

struct to_be_adapted
{
    std::vector<char> do_request()
    {
        return std::vector<char>{'r', 'e', 'q', 'u', 'e', 's', 't', ' ', '1', '0', '0', '0'};
    }
};

class adapter : public target
{
    public:
    adapter(to_be_adapted item) : item_(std::move(item)) {}

    virtual std::string request() const override
    {
        const auto result = item_.do_request();
        return std::string{result.begin(), result.end()};
    }

    private:
    mutable to_be_adapted item_;
};
}  // namespace adapter
