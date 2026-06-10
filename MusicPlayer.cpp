#include <qfiledialog.h>
#include <qstring.h>

#include "MusicPlayer.h"

void MusicPlayer::setAppSettings()
{
	setWindowTitle(settings.getTitle());
	setFixedSize(settings.getScreenSize());
}

void MusicPlayer::createObjects()
{
	playlist = new Playlist(this);

	mainVlayout = new QVBoxLayout();
	mainHlayout = new QHBoxLayout(this);


	playerVContainer = new QVBoxLayout();
	playerHContainer = new QHBoxLayout();
	trackInfoContainer = new QVBoxLayout();
	timeSliderContainer = new QHBoxLayout();
	infoBlockContainer = new QVBoxLayout();

	player = new QMediaPlayer(this);
	audioOutput = new QAudioOutput(this);

	startButton = new QPushButton("Старт", this);
	openButton = new QPushButton("Открыть Файл", this); // временно
	nextTrack = new QPushButton("next", this);
	previousTrack = new QPushButton("prev", this);
	playlistButton = new QPushButton("list", this);
	volumeButton = new QPushButton("vol", this);
	loopButton = new QPushButton("Цикл", this);
	mixButton = new QPushButton("mix", this);

	volumeSlider = new QSlider(Qt::Vertical, this);

	volumeSlider->hide(); // Временно

	positionSlider = new QSlider(Qt::Horizontal, this);

	timeLabelStart = new QLabel("00:00", this);
	timeLabelEnd = new QLabel("00:00", this);
	trackName = new QLabel("Unknown - Artist", this);
	
	trackImage = new QLabel(this);

}

void MusicPlayer::setupUi()
{
	setupTrackInfoArea();
	setupTimeSliderArea();
	setupButtonsArea();
	setupLayouts();
	applyDefaultStyles();
}

void MusicPlayer::setupTrackInfoArea()
{
	trackInfoContainer->addWidget(trackImage);
	trackInfoContainer->addWidget(trackName);
}

void MusicPlayer::setupTimeSliderArea()
{
	timeSliderContainer->addWidget(timeLabelStart);
	timeSliderContainer->addWidget(positionSlider);
	timeSliderContainer->addWidget(timeLabelEnd);
}

void MusicPlayer::setupButtonsArea()
{
	playerHContainer->addWidget(loopButton);
	playerHContainer->addWidget(mixButton);
	playerHContainer->addWidget(previousTrack);
	playerHContainer->addWidget(startButton);
	playerHContainer->addWidget(nextTrack);
	playerHContainer->addWidget(volumeButton);
	playerHContainer->addWidget(playlistButton);

	playerVContainer->addWidget(openButton);
}

void MusicPlayer::setupLayouts()
{

	infoBlockContainer->addLayout(trackInfoContainer);
	infoBlockContainer->addLayout(timeSliderContainer);

	playerVContainer->addLayout(playerHContainer);

	mainVlayout->addLayout(infoBlockContainer);
	mainVlayout->addLayout(playerVContainer);

	mainHlayout->addLayout(mainVlayout);
	mainHlayout->addWidget(playlist);
}

void MusicPlayer::applyDefaultStyles()
{
	playlist->hide();

	trackImage->setFixedSize(200, 200);
	trackImage->setStyleSheet("background-color: #2c2c2c;");

	trackInfoContainer->setAlignment(Qt::AlignCenter);
	trackName->setAlignment(Qt::AlignCenter);

	infoBlockContainer->insertStretch(0, 1);
	infoBlockContainer->insertStretch(3, 1);

	timeSliderContainer->insertStretch(0, 1);
	timeSliderContainer->insertStretch(4, 1);

	positionSlider->setMinimumWidth(150);
	positionSlider->setMaximumWidth(150);

	mainVlayout->setContentsMargins(20, 20, 20, 20);
	mainVlayout->setSpacing(5);
}

void MusicPlayer::setConnect()
{
	connect(startButton, &QPushButton::clicked, this, &MusicPlayer::onPlayClicked);
	connect(openButton, &QPushButton::clicked, this, &MusicPlayer::onOpenFileClicked);
	connect(volumeSlider, &QSlider::valueChanged, this, &MusicPlayer::onVolumeSlide);
	connect(player, &QMediaPlayer::positionChanged, this, &MusicPlayer::onPositionChanged);
	connect(player, &QMediaPlayer::durationChanged, this, &MusicPlayer::onDurationChanged);
	connect(positionSlider, &QSlider::sliderReleased, this, &MusicPlayer::onSliderPosition);
	connect(playlistButton, &QPushButton::clicked, this, &MusicPlayer::onPlaylistButtonCliked);
	connect(playlist, &Playlist::trackSelected, this, [this](const QString& filePath)
		{
			QFileInfo trackInfo(filePath);
			player->setSource(QUrl::fromLocalFile(filePath));
			trackName->setText(QString(trackInfo.baseName()));
			player->play();
		});
}

void MusicPlayer::configureMedia()
{
	player->setAudioOutput(audioOutput);
	audioOutput->setVolume(0.5f);
}

MusicPlayer::MusicPlayer(QWidget* parent) : QWidget(parent)
{
	setAppSettings();
	createObjects();
	configureMedia();
	setupUi();
	setConnect();
}

MusicPlayer::~MusicPlayer()
{}

void MusicPlayer::onPlayClicked()
{
	if (isPaused)
	{
		player->play();
		isPaused = false;
	}
	else
	{
		player->pause();
		isPaused = true;
	}
}

void MusicPlayer::onOpenFileClicked() // временное решение
{
	QString filePath = QFileDialog::getOpenFileName(
		this, 
		"Выберите файл", 
		"", 
		"*.mp3 *.wav *.flac *.ogg"
	);

	if (!filePath.isEmpty())
	{
		player->setSource(QUrl::fromLocalFile(filePath));
		QFileInfo trackInfo(filePath);
		trackName->setText(QString(trackInfo.baseName()));
		playlist->addTrack(filePath);
		isPaused = true;
	}
}

void MusicPlayer::onVolumeSlide(int value)
{
	float changedValue = value / 100.0f;
	audioOutput->setVolume(changedValue);
}

void MusicPlayer::onPositionChanged(qint64 value)
{
	if (!positionSlider->isSliderDown()) {
		positionSlider->setValue(value);
	}

	QTime time(0, 0, 0);
	time = time.addMSecs(value);
	timeLabelStart->setText(time.toString("mm:ss"));
}

void MusicPlayer::onDurationChanged(qint64 value)
{
	positionSlider->setRange(0, value);

	QTime time(0, 0, 0);
	time = time.addMSecs(value);
	timeLabelEnd->setText(time.toString("mm:ss"));
}

void MusicPlayer::onSliderPosition()
{
	player->setPosition(positionSlider->value());
}

void MusicPlayer::onPlaylistButtonCliked()
{
	playlist->setVisible(!playlist->isVisible());
	if (playlist->isVisible())
	{
		nextTrack->hide();
		previousTrack->hide();
		volumeButton->hide();
		loopButton->hide();
		mixButton->hide();
	}
	else
	{
		nextTrack->show();
		previousTrack->show();
		volumeButton->show();
		loopButton->show();
		mixButton->show();
	}
}
