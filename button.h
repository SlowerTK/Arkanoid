#ifndef BUTTON_H
#define BUTTON_H
#include "mouse.h"

class Button {
public:
    SDL_Texture *tex;
    SDL_Rect srect;
    SDL_Rect drect;
    bool isSelected = false;
    Button();
    virtual ~Button();
    
    void update(Mouse&);
    void draw();

};

#endif /* BUTTON_H */