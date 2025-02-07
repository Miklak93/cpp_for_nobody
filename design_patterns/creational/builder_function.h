#pragma once
/**********************************************************************************************************************
+======================================================== Builder ====================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| Acts like regular builder but is simplified by using lambda functions.                                              |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the Builder pattern when creating complex objects that require multiple steps or configurations. It is useful   |
| when the construction process should be independent of the parts that make up the object.                           |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

#include <functional>
#include <string>
#include <vector>
#include <type_traits>

namespace builder_function
{
using complex_product = std::vector<std::string>;

template <typename T, typename = std::enable_if_t<std::is_default_constructible_v<T>>>
complex_product builder(std::function<void(T&)> setter)
{
    T t{};
    setter(t);
    return t;
}
}  // namespace builder_function
