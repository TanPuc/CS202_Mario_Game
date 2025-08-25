#pragma once
#include <vector>
#include <algorithm>

class Subject;

class Observer 
{
public:
    virtual ~Observer() = default;
    virtual void update(Subject* subject) = 0;
};

class Subject
{
    private:
        std::vector<Observer*> observers;
    
    public:
        virtual ~Subject() {}
        void attach(Observer* observer)
        {
            if (std::find(observers.begin(), observers.end(), observer) == observers.end()) 
            {
                observers.push_back(observer);
            }
        }
        void detach(Observer* observer)
        {
            if (observer) 
            {
                observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
            }
        }
        void notifyObservers()
        {
            for (Observer* observer : observers) 
            {
                if (observer) 
                {
                    observer->update(this);
                }
            }
        }
};