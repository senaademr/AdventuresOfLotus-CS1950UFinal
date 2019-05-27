#ifndef BLANKSCREEN_H
#define BLANKSCREEN_H

#include "engine/screens/screen.h"

class BlankScreen : public Screen
{
public:
    BlankScreen(View* view);

    void initializeGL();
    void paintGL();
    void tick(float seconds);
};

#endif // BLANKSCREEN_H
