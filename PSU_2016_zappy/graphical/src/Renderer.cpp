//
// Renderer.cpp for Renderer in /home/tekm/tek2/PSU_2016_zappy/graphical
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Fri Jun 23 14:29:29 2017 leroy_0
// Last update Fri Jun 23 14:29:30 2017 leroy_0
//

#include "Renderer.hpp"

Zappy::Renderer::Renderer(const unsigned int width, const unsigned int height)
{
	_game = new Zappy::Game();
	_width = width;
	_height = height;
    _type = MenuType::MAIN;

    _event = new sf::Event();
    _menu = new Zappy::Menu(width, height);
    _window = new sf::RenderWindow(sf::VideoMode(width, height), "PokeZappy");

    _background = new Zappy::Tile(TileType::BCKGRND, 1, 0, sf::Vector2f(0, 0));
    _background->setScale(static_cast<float>(width) / static_cast<float>(_background->getSize().x) , static_cast<float>(height) / static_cast<float>(_background->getSize().y) - 0.048);
    _logo = new Zappy::Tile(TileType::LOGO, 1, 0, sf::Vector2f(40, 80));
    _connect = new Zappy::Tile(TileType::CONNECT, 1, 0, sf::Vector2f(width / 2, _height / 4));
    _ipBox = new Zappy::TextBox(MSGFONT, 30, width * 1.2 / 3, height / 2);
    _ipBox->setString("   Ip Address   ");
    _ipBox->addBackground(MSGBOX);
    _portBox = new Zappy::TextBox(MSGFONT, 30, width * 2.2 / 3, height / 2);
    _portBox->setString(" Port ");
    _portBox->addBackground(MSGBOX);

    _textbox = new Zappy::TextBox(MSGFONT, 10, width - 100, height);

    _menuAmbient = new Zappy::Music(MENU_AMBIENT, 100, true);
    _gameAmbient = new Zappy::Music(GAME_AMBIENT, 100, true);
    _bonusSound = new Zappy::Music(BONUS_SOUND, 100, false);

    _firstBox = true;

    _menuAmbient->play();
}

Zappy::Renderer::~Renderer()
{
    delete _menuAmbient;
    delete _gameAmbient;
    delete _bonusSound;
    delete _game;
    delete _menu;
    delete _background;
    delete _event;
    delete _window;
    delete _connect;
    delete _logo;
    delete _ipBox;
}

void        Zappy::Renderer::manageMenu()
{
    switch(_type)
    {
        case MenuType::MAIN:
        manageMain();
        break;
        case MenuType::CONNECTION:
        manageConnection();
        break;
        case MenuType::GAME:
        manageGame();
        break;
        case MenuType::EXIT:
        _window->close();
        break;
    }
}

void            Zappy::Renderer::display()
{
    std::vector<Zappy::Tile *>      mapObjects = _game->getMapObjects();
    std::vector<Zappy::Tile *>      mapPlayers = _game->getMapPlayers();
    std::vector<Zappy::Tile *>      blockInfo = _game->getBlockInfoTiles();
    std::vector<Zappy::TextBox *>   textboxinfo = _game->getBlockInfoTexts();

    _window->draw(*_background);
    for (auto it = mapObjects.begin(); it < mapObjects.end(); ++it)
    {
        if ((*it)->getQuantity() > 0)
            _window->draw(*(*it));
    }
    for (auto it = mapPlayers.begin(); it < mapPlayers.end(); ++it)
    {
        _window->draw(*(*it));
        if ((*it)->getBroadcast() != NULL)
        {
            _window->draw(*((*it)->getBroadcast()->getBackground()));
            _window->draw(*((*it)->getBroadcast()));
        }
    }
    auto info = textboxinfo.begin();
    for (auto it = blockInfo.begin(); it < blockInfo.end(); ++it)
    {
        _window->draw(*(*it));
        _window->draw(*(*info)->getBackground());
        _window->draw(*(*info));
        info++;
    }
}

void    Zappy::Renderer::manageConnection()
{
    _window->draw(*_menu);
    _window->draw(*_logo);
    _window->draw(*_connect);
    _window->draw(*(_ipBox->getBackground()));
    _window->draw(*_ipBox);
    _window->draw(*(_portBox->getBackground()));
    _window->draw(*_portBox);

    if (_firstBox)
    {
        if (!_connectString.empty())
            _ipBox->setString(_connectString);
    }
    else
    {
        if (!_connectString.empty())
            _portBox->setString(_connectString);
    }

    if (_game->isConnected() && _game->isReady())
    {
        _menuAmbient->stop();
        _gameAmbient->play();
        _type = MenuType::GAME;
        _window->clear();
        display();
        _window->display();
    }
}

void    Zappy::Renderer::manageGame()
{
    if (!_game->run())
        _type = MenuType::MAIN;
    display();
}

void    Zappy::Renderer::manageMain()
{
    std::vector<Zappy::TextBox *>   menuChoices = _menu->getMenuChoices();

    _window->draw(*_menu);
    _window->draw(*_logo);
    _window->draw(*_menu->getCursor());
    for (auto it = menuChoices.begin(); it < menuChoices.end(); ++it)
    {
        _window->draw(*(*it));
    }
}

void    Zappy::Renderer::manageEvents()
{
    while (_window->pollEvent(*_event))
    {
        if (_event->type == sf::Event::Closed || (_event->type == sf::Event::KeyPressed && _event->key.code == sf::Keyboard::Escape))
        {
            if (_type == MenuType::MAIN)
                _type = MenuType::EXIT;
            else
            {
                if (_type == MenuType::GAME)
                {
                    _gameAmbient->stop();
                    _menuAmbient->play();
                }
                _type = MenuType::MAIN;
            }
        }
        if (_type == MenuType::GAME)
        {
            if (_event->type == sf::Event::MouseButtonPressed)
            {
                _game->manageMouse(sf::Mouse::getPosition());
            }
            if (_event->type == sf::Event::KeyPressed && _event->key.code == sf::Keyboard::A)
            {
                _bonusSound->play();
            }
        }
        if (_type == MenuType::CONNECTION)
        {
            if (_event->type == sf::Event::KeyPressed && _event->key.code == sf::Keyboard::Return)
            {
                _game->connect(_ipBox->getString().toAnsiString(), std::atoi(_portBox->getString().toAnsiString().c_str()));
                if (!_game->isConnected())
                {
                    _connectString = "";
                    _firstBox = true;
                    _ipBox->setString("Server is down");
                    _portBox->setString(" Port ");
                }
            }
            else if (_event->type == sf::Event::KeyPressed && _event->key.code == sf::Keyboard::BackSpace)
            {
                if  (_connectString.size() != 0)
                {
                    _connectString.resize(_connectString.size() - 1);
                }
            }
            else if (_event->type == sf::Event::KeyPressed && _event->key.code == sf::Keyboard::Tab)
            {
                if (_firstBox)
                    _firstBox = false;
                else
                    _firstBox = true;
                _connectString.clear();
            }
            else if (_event->type == sf::Event::TextEntered)
            {
                if (_event->text.unicode < 0x80
                    && _event->text.unicode != 8 && _event->text.unicode != 9 && _event->text.unicode != 13)
                {
                    if (_firstBox && _connectString.size() < 15)
                        _connectString += (char)_event->text.unicode;
                    else if (!_firstBox && _connectString.size() < 6)
                        _connectString += (char)_event->text.unicode;
                }
            }
        }
        if (_type == MenuType::MAIN)
        {
            if (_event->type == sf::Event::KeyPressed && (_event->key.code == sf::Keyboard::Down
                || _event->key.code == sf::Keyboard::Up))
                _menu->setCursorPos(_event->key.code);
            if (_event->type == sf::Event::KeyPressed && _event->key.code == sf::Keyboard::Return)
            {
                _menu->setMenuType(&_type);
            }
        }
    }
}

void 	Zappy::Renderer::run()
{
    while (_window->isOpen())
    {
        _window->clear();
        manageMenu();
        if (_type != MenuType::EXIT)
        {
            manageEvents();
            _window->display();
        }
    }
}