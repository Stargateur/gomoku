//
// IStandard.cpp for IStandard in /home/plasko_a/projet/cplusplus/cpp_spider
// 
// Made by Antoine Plaskowski
// Login   <antoine.plaskowski@epitech.eu>
// 
// Started on  Fri Nov 20 06:01:14 2015 Antoine Plaskowski
// Last update Thu Dec 10 16:27:34 2015 Antoine Plaskowski
//

#include	"IStandard.hpp"

IStandard::~IStandard(void)
{
}

IStandard_exception::IStandard_exception(void) noexcept
{
}

IStandard_exception::IStandard_exception(IStandard_exception const &) noexcept :
ISocket_exception()
{
}

IStandard_exception::IStandard_exception::~IStandard_exception(void) noexcept
{
}

IStandard_exception &IStandard_exception::operator=(IStandard_exception const &) noexcept
{
  return (*this);
}
