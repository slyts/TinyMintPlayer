#include "MusicPlayerConnector.h"

MusicPlayerConnector::MusicPlayerConnector(QWidget* parent) : QObject(parent)
{
	ui = new MusicPlayerUI(parent);
	logic = new MusicPlayerLogic(this);

	connectUI();
	connectLogic();
}

void MusicPlayerConnector::merge(PlaylistConnector* playlist)
{
	ui->setPlaylistWidget(playlist->getUi());

	connect(ui, &MusicPlayerUI::fileOpen, playlist->getLogic(), &PlaylistLogic::addTrack);
	
	connect(playlist->getUi(), &PlaylistUI::trackSelected, logic, &MusicPlayerLogic::playlistPlay);
	connect(playlist->getUi(), &PlaylistUI::trackSelected, ui, &MusicPlayerUI::playlistPlay);
}

void MusicPlayerConnector::connectUI()
{
	connect(ui, &MusicPlayerUI::playClicked, logic, &MusicPlayerLogic::play);
	connect(ui, &MusicPlayerUI::fileOpen, logic, &MusicPlayerLogic::openFile);
	connect(ui, &MusicPlayerUI::sliderRelease, logic, &MusicPlayerLogic::setPositionSlider);
}

void MusicPlayerConnector::connectLogic()
{
	connect(logic, &MusicPlayerLogic::positionChanged, ui, &MusicPlayerUI::updatePosition);
	connect(logic, &MusicPlayerLogic::durationChanged, ui, &MusicPlayerUI::updateDuration);
	connect(logic, &MusicPlayerLogic::playClicked, ui, &MusicPlayerUI::updateStartButton);
}