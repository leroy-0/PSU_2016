//
// typedef.hpp for typedef in /home/tekm/tek2/PSU_2016_zappy/graphical
// 
// Made by leroy_0
// Login   <maxime.leroy@epitech.eu>
// 
// Started on  Fri Jun 23 20:55:52 2017 leroy_0
// Last update Mon Jun 26 16:45:27 2017 leroy_0
//

#ifndef __TYPEDEF_HPP__
#define __TYPEDEF_HPP__

enum	MenuType
  {
    MAIN,
    CONNECTION,
    GAME,
    EXIT
  };

enum	TileType
  {
    BLUE = 0,
    RED,
    GREEN,
    CYAN,
    YELLOW,
    ORANGE,
    HEART,
    SIZE,
    LOGO,
    CONNECT,
    BCKGRND,
    PLAYER,
    GROUND,
    EMPTY
  };

#define     WINSIZE_X       (1920)
#define     WINSIZE_Y       (1080)

#define     GAME_POSX       (414)
#define     GAME_POSY       (50)

#define     GAME_WIDTH      (1091)
#define     GAME_HEIGHT     (931)

#define     PADDING_QNT     (40)
#define     PADDING_INFO    (100)
#define     PADDING_BOX     (25)

#define     SPEED           (2)
#define     ANIMATE_FRQ     (6)

#define     MENU_AMBIENT    "graphical/media/sounds/menu_ambient.ogg"
#define     GAME_AMBIENT    "graphical/media/sounds/game_ambient.ogg"
#define     BONUS_SOUND     "graphical/media/sounds/tk78.ogg"

#define     LOGO_BLOCK      "graphical/media/assets/logo.png"
#define     CONNECT_BLOCK   "graphical/media/assets/connect.png"
#define     BACKGROUND      "graphical/media/assets/background.png"

#define     MSGFONT         "graphical/media/fonts/pokemon_gb.ttf"
#define     MSGBOX          "graphical/media/assets/textbox.png"

#define     MENU            "graphical/media/assets/menu.jpg"
#define     CURSOR          "graphical/media/assets/cursor.png"
#define     CURSORMOVE      (180)
#define     CURSOR_PADDING  (30)

#define     RED_BLOCK     "graphical/media/assets/red_emerald.png"
#define     BLUE_BLOCK    "graphical/media/assets/blue_emerald.png"
#define     GREEN_BLOCK   "graphical/media/assets/green_emerald.png"
#define     CYAN_BLOCK    "graphical/media/assets/cyan_emerald.png"
#define     YELLOW_BLOCK  "graphical/media/assets/yellow_emerald.png"
#define     ORANGE_BLOCK  "graphical/media/assets/orange_emerald.png"
#define     HEART_BLOCK   "graphical/media/assets/heart_emerald.png"
#define     PLAYER_BLOCK  "graphical/media/assets/"
#define     GROUND_BLOCK  "graphical/media/assets/grass.png"

#endif    //__TYPEDEF_HPP__
