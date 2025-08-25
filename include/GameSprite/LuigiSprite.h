#ifndef LUIGISPRITE_H
#define LUIGISPRITE_H

#include "CharacterSprite.h"

class LuigiSprite : public CharacterSprite
{
public:
    LuigiSprite()
        : CharacterSprite(
              "assets/SMB3_Mario_Luigi_SpriteSheet.png",
              {{0, 52, 16, 16}},                                   // idleAnimation
              {{16 + FRAME_PADDING, 52, 16, 16}, {0, 52, 16, 16}}, // walkAnimation
              {{32 + FRAME_PADDING * 2, 52, 16, 16}},              // jumpAnimation
              {{108, 52, 16, 16}},                                 // decelerationAnimation
              {{0, 52, 16, 16}},                                   // duckAnimation
              {{306, 52, 16, 16}},                                 // deadAnimation
              {{126, 52, 16, 16}}                                  // slidingAnimation
          )
    {
    }

    void SwitchForm(CHARACTER_FORM newForm) override
    {
        std::cout << "Form Switched in LuigiSprite\n";
        switch (newForm)
        {
        case SMALL:
        {
            idleAnimation = {{0, 52, 16, 16}};
            walkAnimation = {{16 + FRAME_PADDING, 52, 16, 16}, {0, 52, 16, 16}};
            jumpAnimation = {{32 + FRAME_PADDING * 2, 52, 16, 16}};
            decelerationAnimation = {{108, 52, 16, 16}};
            duckAnimation = {{0, 52, 16, 16}};
            deadAnimation = {{306, 52, 16, 16}};
            slidingAnimation = {{126, 52, 16, 16}};
            break;
        }
        case BIG:
        {
            idleAnimation = {{0, 174, 16, 16 * 2}};
            walkAnimation = {{(16 + FRAME_PADDING) * 2, 174, 16, 16 * 2}, {16 + FRAME_PADDING, 174, 16, 16 * 2}, {0, 174, 16, 16 * 2}};
            jumpAnimation = {{(16 + FRAME_PADDING) * 4, 174, 16, 16 * 2}};
            decelerationAnimation = {{194, 174, 16, 16 * 2}};
            duckAnimation = {{54, 182, 16, 16 * 1.5f}};
            deadAnimation = {{306, 52, 16, 16}};
            slidingAnimation = {{212, 174, 16, 16 * 2}};
            break;
        }
        case FIRE:
        {
            idleAnimation = {{0, 260, 16, 16 * 2}};
            walkAnimation = {{(16 + FRAME_PADDING) * 2, 260, 16, 16 * 2}, {16 + FRAME_PADDING, 260, 16, 16 * 2}, {0, 260, 16, 16 * 2}};
            jumpAnimation = {{(16 + FRAME_PADDING) * 4, 260, 16, 16 * 2}};
            decelerationAnimation = {{194, 260, 16, 16 * 2}};
            duckAnimation = {{54, 268, 16, 16 * 1.5f}};
            deadAnimation = {{306, 16, 16, 16}};
            slidingAnimation = {{212, 260, 16, 16 * 2}};
            break;
        }
        default:
        {
            std::cerr << "Unknown Luigi form!" << std::endl;
            break;
        }
        }
        frameRec = currentAnimation->frames[0];
    }
};

#endif // LUIGISPRITE_H