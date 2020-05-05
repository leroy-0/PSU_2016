/*
** Parser.hpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/include/Parser.hpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Fri Jun 23 13:31:27 2017 Sebastien Bruere
** Last update Fri Jun 23 13:31:27 2017 Sebastien Bruere
*/

#pragma			once

#include		<vector>
#include		<string>
#include "MessageList.hpp"

namespace		ZappyAI {

  class			Parser {

    typedef struct	s_ptrfunc
    {
      bool		(*ptr)(ZappyAI::Parser *, char **, int );
      char			arg;
    }			t_ptrfunc;


  public:
    Parser(int ac, char **av);
    virtual ~Parser();

    bool		parse_args(int ac, char **av);

    void		init_ptr_func();
    char		*recupValue(char **, int );
    bool		is_number(char *);
    static int		getTileNumberInBroadcast(std::string &);
    static unsigned int checkInQueueNeedMyLevel(ZappyAI::messageList queue);

    static bool		get_port(Parser *, char **, int );
    static bool		get_name_team(Parser *,char **, int );
    static bool		get_name_machine(Parser *, char **, int );

    char		*getNameTeam();
    int			getPort();
    char		*getNameMachine();

    void		setPort(int );
    void		setName(char *);
    void		setMachine(char *);

    static std::vector<std::string>	tokeniser(std::string & toParse, char sep);



  private:
    int			_ac;
    char		**_av;
    t_ptrfunc		_ptr[4];
    int			_port;
    char		*_name;
    char		*_machine;
  };
}