#ifndef OOP_OBSERVER_H
#define OOP_OBSERVER_H

#include <string>

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onNotify(const std::string& event, double value) = 0;
};

class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void addObserver(IObserver* observer) = 0;
    virtual void removeObserver(IObserver* observer) = 0;
    virtual void notifyObservers(const std::string& event, double value) = 0;
};

#endif