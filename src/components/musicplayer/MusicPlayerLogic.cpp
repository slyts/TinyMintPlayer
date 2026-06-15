#include "MusicPlayerLogic.h"
#include <qfileinfo.h>

MusicPlayerLogic::MusicPlayerLogic(QObject* parent) : QObject(parent)
{
	player = new QMediaPlayer(this);
	audioOutput = new QAudioOutput(this);
	configureMedia();
	setConnect();
}

MusicPlayerLogic::~MusicPlayerLogic()
{

}

void MusicPlayerLogic::configureMedia()
{
	player->setAudioOutput(audioOutput);
	audioOutput->setVolume(0.5f);
}

void MusicPlayerLogic::setConnect()
{
	connect(player, &QMediaPlayer::positionChanged, this, &MusicPlayerLogic::positionChanged);
	connect(player, &QMediaPlayer::durationChanged, this, &MusicPlayerLogic::durationChanged);
}

// -- slots --
void MusicPlayerLogic::play()
{
	if (isPaused)
	{
		player->play();
		isPaused = false;
		emit playClicked(false);
	}
	else
	{
		player->pause();
		isPaused = true;
		emit playClicked(true);
	}
}

void MusicPlayerLogic::openFile(QString filePath)
{
	player->setSource(QUrl::fromLocalFile(filePath));
	isPaused = true;
}

void MusicPlayerLogic::setPositionSlider(qint64 value)
{
	player->setPosition(value);
}

void MusicPlayerLogic::playlistPlay(QString filePath)
{
	player->setSource(QUrl::fromLocalFile(filePath));
	player->play();
	isPaused = false;
}