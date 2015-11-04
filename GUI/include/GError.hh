/*
** GError.hh for gomoku in /home/rousse_3/Project/gomoku/GUI
** 
** Made by Roussel Rodolphe
** Login   <rousse_3@epitech.net>
** 
** Started on  Wed Nov  4 16:42:28 2015 Roussel Rodolphe
// Last update Wed Nov  4 17:12:19 2015 Roussel Rodolphe
*/

#ifndef			GERROR_HH_
# define		GERROR_HH_

# include		<stdexcept>

class			GError : public std::exception
{
public:
  GError(const std::string &what, const std::string &where);
  ~GError(void) throw();
  virtual const char	*what(void) const throw();
  virtual const char	*where(void) const throw();
protected:
  const char		*_what;
  const char		*_where;
};

class			GInitError : public std::runtime_error, public GError
{
public:
  GInitError(const std::string &what, const std::string &where);
  ~GInitError(void) throw();
};

#endif
