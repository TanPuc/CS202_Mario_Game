#include "DGUI/GUIManager.h"
#include "DGUI/Button.h"
#include "DGUI/ImageButton.h"


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
    Vector2 mousePoint = GetMousePosition();
    for (GUIElement* element : elements) 
    {
        if (auto imgBtn = dynamic_cast<ImageButton*>(element))
        {
            imgBtn->update();
        }
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
        {
            if (element->contains(mousePoint)) 
            {
                if (auto button = dynamic_cast<Button*>(element)) 
                {
                    button->onClick();
                    break; 
                }
                
                if (auto imgBtn = dynamic_cast<ImageButton*>(element)) 
                {
                    imgBtn->onClick();
                    break;
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




