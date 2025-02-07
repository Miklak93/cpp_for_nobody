#pragma once
/**********************************************************************************************************************
+======================================================== Builder ====================================================+
|                                                                                                                     |
| Description:                                                                                                        |
| The Builder design pattern separates the construction of a complex object from its representation, allowing the     |
| same construction process to create different representations. It focuses on step-by-step construction.             |
|                                                                                                                     |
| When to use:                                                                                                        |
| Use the Builder pattern when creating complex objects that require multiple steps or configurations. It is useful   |
| when the construction process should be independent of the parts that make up the object.                           |
|                                                                                                                     |
+=====================================================================================================================+
***********************************************************************************************************************/

#include <type_traits>
#include <vector>

namespace builder
{
using complex_product = std::vector<std::string>;

struct ibuilder
{
   virtual ~ibuilder() {};
   virtual const ibuilder& new_instance() const = 0;
   virtual const ibuilder& build_first_part(std::string) const = 0;
   virtual const ibuilder& build_second_part(std::string) const = 0;
   virtual const ibuilder& build_third_part(std::string) const = 0;
   virtual const complex_product& get() const = 0;
};

class builder_1 : public ibuilder
{
   public:
   builder_1() = default;

   virtual const builder_1& new_instance() const override
   {
      product.clear();
      return *this;
   }

   virtual const builder_1& build_first_part(std::string s) const override
   {
      product.push_back(prefix_ + std::move(s));
      return *this;
   }

   virtual const builder_1& build_second_part(std::string s) const override
   {
      product.push_back(prefix_ + std::move(s));
      return *this;
   }

   virtual const builder_1& build_third_part(std::string s) const override
   {
      product.push_back(prefix_ + std::move(s));
      return *this;
   }

   virtual const complex_product& get() const override
   {
      return product;
   }

   private:
   mutable complex_product product;
   static const inline std::string prefix_ = "1";
};

class builder_2 : public ibuilder
{
   public:
   builder_2() = default;

   virtual const builder_2& new_instance() const override
   {
      product.clear();
      return *this;
   }

   virtual const builder_2& build_first_part(std::string s) const override
   {
      product.push_back(std::move(s) + suffix_);
      return *this;
   }

   virtual const builder_2& build_second_part(std::string s) const override
   {
      product.push_back(std::move(s) + suffix_);
      return *this;
   }

   virtual const builder_2& build_third_part(std::string s) const override
   {
      product.push_back(std::move(s) + suffix_);
      return *this;
   }

   virtual const complex_product& get() const override
   {
      return product;
   }

   private:
   mutable complex_product product;
   static const inline std::string suffix_ = "2";
};

class director
{
public:
   director() = default;

   template <typename T, typename = std::enable_if_t<std::is_base_of_v<ibuilder, T>>>
   void set_builder()
   {
      builder_.reset();
      builder_ = std::make_unique<T>();
   }

   const ibuilder& new_instance()
   {
      if (!builder_)
      {
         throw std::runtime_error("No builder set!");
      }
      return *builder_;
   }

private:
   std::unique_ptr<ibuilder> builder_;
};
}  // namespace builder
