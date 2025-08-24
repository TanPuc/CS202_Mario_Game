#ifndef MARIOSPRITE_H
#define MARIOSPRITE_H

#include "CharacterSprite.h"

class MarioSprite : public CharacterSprite
{
public:
    MarioSprite()
        : CharacterSprite(
              "assets/SMB3_Mario_Luigi_SpriteSheet.png",
              {{0, 16, 16, 16}},                                   // idleAnimation
              {{16 + FRAME_PADDING, 16, 16, 16}, {0, 16, 16, 16}}, // walkAnimation
              {{32 + FRAME_PADDING * 2, 16, 16, 16}},              // jumpAnimation
              {{108, 16, 16, 16}},                                 // decelerationAnimation
              {{0, 16, 16, 16}},                                   // duckAnimation
              {{306, 16, 16, 16}},                                 // deadAnimation
              {{126, 16, 16, 16}}                                  // slidingAnimation
          )
    {
    }

    void SwitchForm(CHARACTER_FORM newForm) override
    {
        std::cout << "Form Switched in MarioSprite\n";
        switch (newForm)
        {
        case SMALL:
        {
            idleAnimation = {{0, 16, 16, 16}};
            walkAnimation = {{16 + FRAME_PADDING, 16, 16, 16}, {0, 16, 16, 16}};
            jumpAnimation = {{32 + FRAME_PADDING * 2, 16, 16, 16}};
            decelerationAnimation = {{108, 16, 16, 16}};
            duckAnimation = {{0, 16, 16, 16}};
            deadAnimation = {{306, 16, 16, 16}};
            slidingAnimation = {{126, 16, 16, 16}};
            break;
        }
        case BIG:
        {
            idleAnimation = {{0, 88, 16, 16 * 2}};
            walkAnimation = {{(16 + FRAME_PADDING) * 2, 88, 16, 16 * 2}, {16 + FRAME_PADDING, 88, 16, 16 * 2}, {0, 88, 16, 16 * 2}};
            jumpAnimation = {{(16 + FRAME_PADDING) * 4, 88, 16, 16 * 2}};
            decelerationAnimation = {{194, 88, 16, 16 * 2}};
            duckAnimation = {{54, 96, 16, 16 * 1.5f}};
            deadAnimation = {{306, 16, 16, 16}};
            slidingAnimation = {{212, 88, 16, 16 * 2}};
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
            std::cerr << "Unknown Mario form!" << std::endl;
            break;
        }
        }
        frameRec = currentAnimation->frames[0];
    }
};

#endif // MARIOSPRITE_H