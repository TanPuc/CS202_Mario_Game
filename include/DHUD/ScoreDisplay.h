#include "DCore/GUIElement.h"

class ScoreDisplay: public GUIElement
{
private:
    long long currentScore;
public:
    ScoreDisplay();
    
    void updateScore(long long newScore);
    void draw() override;
};



