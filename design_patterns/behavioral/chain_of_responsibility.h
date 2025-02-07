#pragma once
/**********************************************************************************************************************
+========================================= Chain of Responsibility ===================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| The Chain of Responsibility design pattern allows a request to pass through a chain of handlers until one of them   |
| handles it. Each handler decides whether to process the request or pass it to the next handler in the chain.        |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the Chain of Responsibility pattern when multiple objects may handle a request, and the handler isn't known     |
| beforehand. It is useful for reducing coupling between senders and receivers and for implementing flexible          |
| workflows where steps can be modified dynamically.                                                                  |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

#include <string>

namespace chain_of_responsiblity
{
struct ihandler
{
   virtual ihandler& set_next(ihandler& halder) = 0;
   virtual std::string action(std::string request) const = 0;
};

class handler : public ihandler
{
   public:
      handler(): next_(nullptr)
      {
      }

      virtual ihandler& set_next(ihandler& next) override
      {
         next_ = &next;
         return next;
      }

      virtual std::string action(std::string request) const override
      {
         if (next_)
         {
            return next_->action(std::move(request));
         }
         return request + " not handled!";
      }

   private:
      const ihandler* next_;
};

struct handler_1 : handler
{
   virtual std::string action(std::string request) const override
   {
      if (request == "request_1")
      {
         return "request_1 handled by handler_1";
      }
      return handler::action(std::move(request));
   }
};

struct handler_2 : handler
{
   virtual std::string action(std::string request) const override
   {
      if (request == "request_2")
      {
         return "request_2 handled by handler_2";
      }
      return handler::action(std::move(request));
   }
};

struct handler_3 : handler
{
   virtual std::string action(std::string request) const override
   {
      if (request == "request_3")
      {
         return "request_3 handled by handler_3";
      }
      return handler::action(std::move(request));
   }
};
}  // namespace chain_of_responsibility
