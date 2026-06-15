#ifndef APPLICATION_H
#define APPLICATION_H

#include "../components/musicplayer/MusicPlayerConnector.h"
#include "../components/playlist/PlaylistConnector.h"

class Application
{
private:
	MusicPlayerConnector* playerConnector;
	PlaylistConnector* playlistConnector;
public:
	void init();
};

#endif // APPLICATION_H