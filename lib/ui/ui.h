#ifndef _USBS_UI_H
#define _USBS_UI_H

#include <M5StickCPlus.h>

#define TFTW  135  // screen width
#define TFTH  240  // screen height
#define TFTW2 67   // half screen width
#define TFTH2 120  // half screen height

class StickUI {
    public:
        explicit StickUI();
        void Begin();
        void Update();

    private:
        void turnOnDisplay();
        void turnOffDisplay();
        void drawHeader();
        void drawFooter();

    private:
        enum class screenState {
            unknown,
            off,
            on,
        };

    private:
        screenState screenState;
};

extern StickUI UI;

#endif