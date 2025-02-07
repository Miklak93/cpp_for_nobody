#pragma once
/**********************************************************************************************************************
+======================================================== singleton ==================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| The singleton design pattern ensures that a class has only one instance and provides a global access point to it.   |
| This is achieved by restricting direct instantiation and providing a static method to get the instance.             |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the singleton pattern when a single instance of a class must coordinate actions across a system,                |
| such as managing a shared resource, configuration settings, or logging.                                             |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

#include <memory>

namespace singleton
{
namespace detail
{
template <typename T>
struct singleton_traits
{
    using value_type = std::unique_ptr<T>;
};
}  // namespace detail

template <typename T>
class singleton
{
    public:
    /* singleton can't be copied but can be moved */
    singleton(const singleton<T>&) = delete;
    singleton(singleton<T>&&) = delete;

    singleton<T>& operator=(const singleton<T>&) = delete;
    singleton<T>& operator=(singleton<T>&&) = delete;

    template <typename... Args>
    static T& get(Args&&... args)
    {
        if (!instance)
        {
            if constexpr(sizeof...(Args) == 0)
            {
                instance = std::make_unique<T>();
            }
            else
            {
                instance = std::make_unique<T>((std::forward<Args>(args), ...));
            }
        }
        return *instance;
    }

    static void reset()
    {
        if (!instance)
        {
            return;
        }
        instance.reset();
    }

    private:
    singleton() = default;
    static typename detail::singleton_traits<T>::value_type instance;
};

/* Tricky way to initialize value in the header file */
template <typename T>
detail::singleton_traits<T>::value_type singleton<T>::instance = nullptr;
}  // namespace singleton
