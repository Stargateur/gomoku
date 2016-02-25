#include	"ISelect.hpp"

ISelect::~ISelect(void)
{
}

ISelect_exception::ISelect_exception(void) noexcept
{
}

ISelect_exception::ISelect_exception(ISelect_exception const &) noexcept
{
}

ISelect_exception::~ISelect_exception(void) noexcept
{
}

ISelect_exception &ISelect_exception::operator=(ISelect_exception const &) noexcept
{
    return (*this);
}

