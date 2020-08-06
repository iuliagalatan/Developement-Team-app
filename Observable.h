#pragma once
#include <vector>
#include "Observer.h"

class Observable
{
private:
	
	std::vector<Observer*> observers;
public:
	virtual ~Observable();

	void addObserver(Observer* obs);

	void removeObserver(Observer* obs);

	void notify();
};
