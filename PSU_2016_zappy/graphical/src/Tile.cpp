//
// Tile.cpp for Tile in /home/tekm/tek2/PSU_2016_zappy/graphical
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Mon Jun 26 14:09:05 2017 leroy_0
// Last update Mon Jun 26 14:09:42 2017 leroy_0
//

#include "Tile.hpp"
#include <iostream>

Zappy::Tile::Tile(const TileType & type, int nb, int id, const sf::Vector2f pos)
{
  _textureNames[TileType::LOGO] = new std::string(LOGO_BLOCK);
  _textureNames[TileType::CONNECT] = new std::string(CONNECT_BLOCK);
  _textureNames[TileType::BCKGRND] = new std::string(BACKGROUND);
  _textureNames[TileType::PLAYER] = new std::string(PLAYER_BLOCK);
  _textureNames[TileType::GROUND] = new std::string(GROUND_BLOCK);
  _textureNames[TileType::BLUE] = new std::string(BLUE_BLOCK);
  _textureNames[TileType::RED] = new std::string(RED_BLOCK);
  _textureNames[TileType::GREEN] = new std::string(GREEN_BLOCK);
  _textureNames[TileType::CYAN] = new std::string(CYAN_BLOCK);
  _textureNames[TileType::YELLOW] = new std::string(YELLOW_BLOCK);
  _textureNames[TileType::ORANGE] = new std::string(ORANGE_BLOCK);
  _textureNames[TileType::HEART] = new std::string(HEART_BLOCK);

  _id = id;
  _nb = nb;
  _type = type;
  _animate = 0;
  _texture = NULL;
  _textbox = NULL;
  if (type != TileType::EMPTY)
  {
    _texture = new sf::Texture();
    if (type == TileType::PLAYER)
      _texture->loadFromFile(*_textureNames[type] + std::string("player-0.png"));
    else
      _texture->loadFromFile(*_textureNames[type]);
    setTexture(*_texture);
    _x = -1 * (_texture->getSize().x / 4);
    _y = 0;
  }
  setPosition(pos);
  _newpos = getPosition();
}

Zappy::Tile::~Tile()
{
  delete _texture;
  if (_textbox != NULL)
    delete _textbox;
}

void				Zappy::Tile::animate(e_dir dir)
{
  sf::Vector2u	oldSize;
  sf::IntRect 	rectSourceSprite;

  if (dir == e_dir::UP)
  {
    _y = (_texture->getSize().y / 4) * 3;
  }
  else if (dir == e_dir::DOWN)
  {
    _y = (_texture->getSize().y / 4) * 0;
  }
  else if (dir == e_dir::RIGHT)
  {
    _y = (_texture->getSize().y / 4) * 2;
  }
  else if (dir == e_dir::LEFT)
  {
    _y = (_texture->getSize().y / 4) * 1;
  }
  _x += (_texture->getSize().x / 4);
  if (_x >= _texture->getSize().x)
    _x = 0;
  rectSourceSprite = sf::IntRect(_x, _y, (_texture->getSize().x / 4), (_texture->getSize().y / 4));
  setTextureRect(rectSourceSprite);
}

void				Zappy::Tile::set_position(const sf::Vector2f & pos)
{
  e_dir	 		dir;

  setPosition(pos);
  _newpos = getPosition();

  if (getPosition().x < pos.x && getPosition().x < pos.x)
    dir = e_dir::RIGHT;
  else if (getPosition().x > pos.x && getPosition().x > pos.x)
    dir = e_dir::LEFT;
  else if (getPosition().y < pos.y && getPosition().y < pos.y)
    dir = e_dir::DOWN;
  else if (getPosition().y > pos.y && getPosition().y > pos.y)
    dir = e_dir::UP;
  else
    return ;

  _animate = 0;
  animate(dir);
}

bool				Zappy::Tile::goTo(sf::Vector2f newpos)
{
  e_dir	 		dir;

  if (_textbox != NULL)
  {
    delete _textbox;
    _textbox = NULL;
  }

  if (_newpos.x == getPosition().x && _newpos.y == getPosition().y)
    _newpos = newpos;

  if (getPosition().x < _newpos.x && getPosition().x + SPEED < _newpos.x)
  {
    setPosition(getPosition().x + SPEED, getPosition().y);
    dir = e_dir::RIGHT;
		
  }
  else if (getPosition().x > _newpos.x && getPosition().x + SPEED > _newpos.x)
  {
    setPosition(getPosition().x - SPEED, getPosition().y);
    dir = e_dir::LEFT;
  }
  else if (getPosition().y < _newpos.y && getPosition().y + SPEED < _newpos.y)
  {
    setPosition(getPosition().x, getPosition().y + SPEED);
    dir = e_dir::DOWN;
  }
  else if (getPosition().y > _newpos.y && getPosition().y + SPEED > _newpos.y)
  {
    setPosition(getPosition().x, getPosition().y - SPEED);
    dir = e_dir::UP;
  }
  else
  {
    _newpos = getPosition();
    return (false);
  }
  _animate += SPEED;
  if (_animate > SPEED * ANIMATE_FRQ)
  {
    animate(dir);
    _animate = 0;
  }
  return (true);
}

void				Zappy::Tile::setBroadcast(const std::string & msg)
{
  if (_textbox == NULL)
  {
    _textbox = new Zappy::TextBox(MSGFONT, 16, getPosition().x, getPosition().y - 10);
  }
  _textbox->setString(msg);
  if (_textbox->getBackground() == NULL)
  {
    _textbox->addBackground(MSGBOX);
  }
}

void 				Zappy::Tile::updateSkinTeam(const std::vector<std::string> & teamNames)
{
  int 			x = 0;

  for (auto it = teamNames.begin(); it < teamNames.end(); ++it)
  {
    if (getTeam() == (*it))
    {
      delete _texture;
      _texture = new sf::Texture();
      if (x < 9)
	_texture->loadFromFile(*_textureNames[TileType::PLAYER] + std::string("player-") + std::to_string(x) + std::string(".png"));
      else
	_texture->loadFromFile(*_textureNames[TileType::PLAYER] + std::string("player-0.png"));
      setTexture(*_texture);
    }
    x++;
  }
}

void				Zappy::Tile::setLevel(int lvl)
{
  _lvl = lvl;
  setScale(getScale().x + 0.2f, getScale().y + 0.2f);
}

void				Zappy::Tile::setTeam(std::string & name)
{
  _teamname = name;
}

void	 			Zappy::Tile::setQuantity(int nb)
{
  _nb = nb;
}

Zappy::TextBox 		*Zappy::Tile::getBroadcast() const
{
  return (_textbox);
}

int 				Zappy::Tile::getLevel() const
{
  return (_lvl);
}

std::string			Zappy::Tile::getTeam() const
{
  return (_teamname);
}

sf::Vector2u        Zappy::Tile::getSize() const
{
  if (_texture == NULL)
    return (sf::Vector2u(1, 1));
  return (sf::Vector2u(_texture->getSize().x * getScale().x, _texture->getSize().y * getScale().y));
}

TileType			Zappy::Tile::getType() const
{
  return (_type);
}

int 				Zappy::Tile::getQuantity() const
{
  return (_nb);
}

int 				Zappy::Tile::getId() const
{
  return (_id);
}