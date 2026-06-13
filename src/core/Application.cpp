#include "Application.h"

void Application::init()
{
	player = new MusicPlayerConnector();
	player->getUi()->show();
}
