#ifndef PROJECT_PATHFINDER_HPP
#define PROJECT_PATHFINDER_HPP

#include		<vector>
#include		"Stones.hpp"
#include		"Vision.hpp"

namespace		ZappyAI
{
  class			PathFinder
  {
  public:
    PathFinder() {};
    ~PathFinder() {};
    enum	direction
    {
      FORWARD = 1,
      LEFT = 2,
      RIGHT = 3,
      UNKNOWN = 4
    };
    //Utiliser le toGather avant le toDo
    struct	path
    {
      path() { gatherFood = true ;};
      int				pos;
      ZappyAI::PathFinder::direction	toDo = UNKNOWN;
      std::vector<ZappyAI::Stones>	toGather;
      bool				gatherFood;
    };
    static std::list<ZappyAI::PathFinder::path>
    	findPath
	  (std::map<ZappyAI::Stones, int> toFind,
		 std::list<ZappyAI::Vision::t_vision> vision);
    static ZappyAI::PathFinder::path	generateNode(std::vector<ZappyAI::Stones> toGather, bool gatherFood, int pos);
    static void				dump(std::list<ZappyAI::PathFinder::path> path);
    static std::list<ZappyAI::PathFinder::path>stickPath(std::list<ZappyAI::PathFinder::path>	path);
    static std::list<ZappyAI::PathFinder::path>goToBroadcast(int directionTile, int fd, ZappyAI::messageList &_queue);
  };
}

#endif //PROJECT_PATHFINDER_HPP
