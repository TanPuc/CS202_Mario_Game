#include "DCore/GUIElement.h"

class UIImage: public GUIElement
{
    protected:
    Texture2D texture;
    
public:
    UIImage(Texture2D tex, Vector2 pos);
    void draw() override;
};