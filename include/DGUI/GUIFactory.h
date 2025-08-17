#include "DGUI/UIImage.h"
#include <string>

class GUIFactory
{
    public:
    static UIImage* createImage(Texture2D tex, Vector2 pos)
    {
        return new UIImage(tex, pos);
    }
};
