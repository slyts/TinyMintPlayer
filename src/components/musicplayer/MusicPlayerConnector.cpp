#include "MusicPlayerConnector.h"

MusicPlayerConnector::MusicPlayerConnector(QWidget* parent) : QObject(parent)
{
	ui = new MusicPlayerUI(parent);
	logic = new MusicPlayerLogic(this);

	connectMusicplayerUI();
	connectMusicplayerLogic();
}

void MusicPlayerConnector::connectMusicplayerUI()
{
	connect(ui, &MusicPlayerUI::playClicked, logic, &MusicPlayerLogic::play);
	connect(ui, &MusicPlayerUI::fileOpen, logic, &MusicPlayerLogic::openFile);
	connect(ui, &MusicPlayerUI::sliderRelease, logic, &MusicPlayerLogic::setPositionSlider);
}

void MusicPlayerConnector::connectMusicplayerLogic()
{
	connect(logic, &MusicPlayerLogic::positionChanged, ui, &MusicPlayerUI::updatePosition);
	connect(logic, &MusicPlayerLogic::durationChanged, ui, &MusicPlayerUI::updateDuration);
	connect(logic, &MusicPlayerLogic::playClicked, ui, &MusicPlayerUI::updateStartButton);
}