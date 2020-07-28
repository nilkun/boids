/***********************************
  GAME ENGINE WITH A FANTASTIC NAME
  ------A NEW SCREEN MANAGER-------
  ---------------------------------
  by nilkun
  Rev: Aug 28, 2018
 ***********************************

    USE THIS TO CREATE AND MANAGE
    THE RENDERER AND MAIN WINDOW

************************************/
#pragma once

#include <SDL2/SDL.h>

class Screen {

/* CREATING A SINGLETON */

public:
    static Screen* instance()
      {
        return &singleton;
      }

private:
  static Screen singleton;
  Screen() {};                                  
  Screen(const Screen&);                 
  Screen& operator=(const Screen&);      
    
/* END OF SINGLETON CREATION */

private:
  static SDL_Window *m_window;
  static SDL_Renderer *m_renderer;

  static const char* m_title;
  int width;
  int height;

/* initialization.cpp */
public:
  void init(const char *title, int width, int height);
  void close();
  static SDL_Renderer* getRenderer();

  void clear();
  void render();
};
