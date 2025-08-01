#include "DGUI/GUIManager.h"
#include "DGUI/Button.h"


GUIManager::~GUIManager() 
{
    for (auto& element : elements) 
    {
        delete element; // Clean up memory
    }
    elements.clear();
}

GUIManager& GUIManager::getInstance() 
{
    static GUIManager instance;
    return instance;
}

void GUIManager::addElement(GUIElement* element) 
{
    if (element) 
    {
        elements.push_back(element);
    }
}

void GUIManager::clearElements() 
{
    for (auto& element : elements) 
    {
        delete element; // Clean up memory
    }
    elements.clear();
}

void GUIManager::handleInput()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
    {
        Vector2 mousePoint = GetMousePosition();
        for (GUIElement* element : elements) 
        
        {
            if (element->contains(mousePoint)) 
            {
                Button* button = dynamic_cast<Button*>(element);
                if (button) 
                {
                    button->onClick();
                    break; // just click one button at a time
                }
            }
        }
    }
}

void GUIManager::draw() 
{
    for (auto& element : elements) 
    {
        if (element->isVisible) 
        {
            element->draw();
        }
    }
}




