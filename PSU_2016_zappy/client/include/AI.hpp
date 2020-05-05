/*
** zappyAI.hpp for PSU_2016_zappy in /home/bruere_s/Projets/PSU_2016_zappy/client/include/zappyAI.hpp
**
** Made by Sebastien Bruere
** Login   <sebastien.bruere@epitech.eu>
**
** Started on  Wed Jun 28 15:00:02 2017 Sebastien Bruere
** Last update Wed Jun 28 15:00:02 2017 Sebastien Bruere
*/

#pragma once

#include		<vector>
#include		<stack>
#include		"Communication.hpp"
#include		"Network.hpp"
#include		"Inventory.hpp"
#include		"Incantation.hpp"
#include		"Vision.hpp"
#include		"MessageList.hpp"
#include		"PathFinder.hpp"

namespace		ZappyAI
{
  enum			state {
    HANDLING_ELEVATION, //0
    IDLE_ELEVATION, //1
    ASKING_ELEVATION, //2
    LOOKING_FOR_MATES, //3
    IDLE //4
  };

  class			AI {
  public:
    AI(const std::string &, const std::string &, int, unsigned int);
    virtual ~AI();

    bool		initAI();
    bool		connexionToServer();
    bool		run();
    bool		getInitialProperty();
    void		demandForkToParent();
    int			handleSpecialMessage();
    void		pickFood();
    bool		handleLevelUp();


  private:
    Communication	*_com;
    Inventory		_inv;
    Incantation		_inc;
    Vision		_vision;
    messageList		_queue;
    std::string		_name;
    std::string		_machine;
    int			_port;
    int			_maxClient;
    int			_mapX;
    int			_mapY;
    int			_server_fd;
    int			_ppid;
    unsigned int	_level;
    state		_state;
    bool		move;
    bool		_lay;
    int			_destinationTile;
    unsigned int	_maxIdleElevationTurn;
    unsigned int	_id;
    int			_targetId;
    unsigned int	_numberOfMates;
    std::vector<std::string> _sendQueue;
    std::vector<int>	_joiningId;

    void dropStones(ZappyAI::Incantation::requirement & requirement);
    void searchForRessources(int &maxTurn);
    void pathfinder(std::list<ZappyAI::PathFinder::path> &list);
    void handlingElevation();

    void handlingBroadcast(std::string & it);

    bool isNotConsidered(int tocheck);
  };
}