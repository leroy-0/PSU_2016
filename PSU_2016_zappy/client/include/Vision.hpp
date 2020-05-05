#ifndef PROJECT_VISION_HPP
#define PROJECT_VISION_HPP

#include	"Stones.hpp"
#include	<vector>
#include	<list>
#include	<iostream>

namespace	ZappyAI
{
  class		Vision
  {
  public:
    Vision();
    ~Vision();
    struct t_vision
    {
      t_vision(){player = 0; food = 0; pos = 0;};
      unsigned int			pos;
      std::vector<ZappyAI::Stones>	stones;
      unsigned int			player = 0;
      unsigned int			food = 0;
    };

    void				look(std::string toParse);
    void				dump();
    inline std::list<ZappyAI::Vision::t_vision>getVision() const {return this->vision;}
  private:
    std::list<ZappyAI::Vision::t_vision>	vision;

  private:
    void				updateVision(std::string & tile, int howMuch);
    t_vision				getTileStruct(std::string & tile, int howMuch);

  public:
    static int				getRowNb(int pos);
    bool				isTileEmpty(int);
  };
}

#endif //PROJECT_VISION_HPP
