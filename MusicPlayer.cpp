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
	mainlayout = new QVBoxLayout(this);
	playerVContainer = new QVBoxLayout();
	playerHContainer = new QHBoxLayout();
	trackInfoContainer = new QVBoxLayout();
	timeSliderContainer = new QHBoxLayout();
	infoBlockContainer = new QVBoxLayout();

	player = new QMediaPlayer(this);
	audioOutput = new QAudioOutput(this);

	startButton = new QPushButton("Старт", this);
	openButton = new QPushButton("Открыть Файл", this);
	nextTrack = new QPushButton("След. Трек", this);
	previousTrack = new QPushButton("Пред. Трек", this);

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
	playerHContainer->addWidget(previousTrack);
	playerHContainer->addWidget(startButton);
	playerHContainer->addWidget(nextTrack);

	playerVContainer->addWidget(openButton);
}

void MusicPlayer::setupLayouts()
{
	infoBlockContainer->addLayout(trackInfoContainer);
	infoBlockContainer->addLayout(timeSliderContainer);

	playerVContainer->addLayout(playerHContainer);

	mainlayout->addLayout(infoBlockContainer);
	mainlayout->addLayout(timeSliderContainer);
	mainlayout->addLayout(playerVContainer);
}

void MusicPlayer::applyDefaultStyles()
{
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

	mainlayout->setContentsMargins(20, 20, 20, 20);
	mainlayout->setSpacing(5);
}

void MusicPlayer::setConnect()
{
	connect(startButton, &QPushButton::clicked, this, &MusicPlayer::onPlayClicked);
	connect(openButton, &QPushButton::clicked, this, &MusicPlayer::onOpenFileClicked);
	connect(volumeSlider, &QSlider::valueChanged, this, &MusicPlayer::onVolumeSlide);
	connect(player, &QMediaPlayer::positionChanged, this, &MusicPlayer::onPositionChanged);
	connect(player, &QMediaPlayer::durationChanged, this, &MusicPlayer::onDurationChanged);
	connect(positionSlider, &QSlider::sliderReleased, this, &MusicPlayer::onSliderPosition);
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

void MusicPlayer::onOpenFileClicked()
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
		//QString trackBaseName = trackInfo.baseName();
		trackName->setText(QString(trackInfo.baseName()));
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
}

void MusicPlayer::onDurationChanged(qint64 value)
{
	positionSlider->setRange(0, value);
}

void MusicPlayer::onSliderPosition()
{
	player->setPosition(positionSlider->value());
}
