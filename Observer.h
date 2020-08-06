#pragma once

/*
	Observer - Abstract class
	update method needs to be implemented by observers
*/
class Observer
{
public:
	virtual void update() = 0;
	virtual void show() = 0;
	virtual ~Observer() {}
};
