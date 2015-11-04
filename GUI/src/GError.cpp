//
// GError.cpp for gomoku in /home/rousse_3/Project/gomoku/GUI
// 
// Made by Roussel Rodolphe
// Login   <rousse_3@epitech.net>
// 
// Started on  Wed Nov  4 16:53:19 2015 Roussel Rodolphe
// Last update Wed Nov  4 17:12:39 2015 Roussel Rodolphe
//

#include		"GError.hh"

GError::GError(const std::string &what, const std::string &where) :
  std::exception(),
  _what(what.c_str()),
  _where(where.c_str())
{}

GError::~GError(void) throw() {}

const char		*GError::what(void) const throw() { return (_what); }

const char		*GError::where(void) const throw() { return (_where); }

GInitError::GInitError(const std::string &what, const std::string &where) :
  std::runtime_error(what),
  GError(what, where)
{}

GInitError::~GInitError(void) throw() {}
