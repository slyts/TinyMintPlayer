#ifndef APPLICATION_H
#define APPLICATION_H

#include "../components/musicplayer/MusicPlayerConnector.h"

class Application
{
private:
	MusicPlayerConnector* player;
public:
	void init();
};

#endif // APPLICATION_H