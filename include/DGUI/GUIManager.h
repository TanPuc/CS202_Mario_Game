#include "DCore/GUIElement.h"
#include <vector>

class GUIManager
{
    private:
        std::vector<GUIElement*> elements;
        GUIManager() = default; // Private constructor for singleton pattern
    
    public:
        GUIManager(const GUIManager&) = delete; // Prevent copying
        GUIManager& operator=(const GUIManager&) = delete; // Prevent assignment
        ~GUIManager();

        static GUIManager& getInstance();
        void addElement(GUIElement* element);
        void clearElements();
        void handleInput();
        void draw();
};