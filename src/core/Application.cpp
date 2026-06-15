#include "Application.h"

void Application::init()
{
	playerConnector = new MusicPlayerConnector();
	playlistConnector = new PlaylistConnector();

	playerConnector->getUi()->show();
	playerConnector->merge(playlistConnector);
}
