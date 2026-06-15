#include "PlaylistConnector.h"

PlaylistConnector::PlaylistConnector(QWidget * parent) : QObject(parent)
{
	ui = new PlaylistUI(parent);
	logic = new PlaylistLogic(this);

	connectUI();
	connectLogic();
}

void PlaylistConnector::connectUI()
{
}

void PlaylistConnector::connectLogic()
{
	connect(logic, &PlaylistLogic::appendTrack, ui, &PlaylistUI::addTrackUI);
}