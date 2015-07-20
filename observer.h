#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

class Subject;


class Observer {
public:
	virtual void update (std::string) = 0;
};


#endif