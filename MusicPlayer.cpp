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
	layout = new QVBoxLayout(this);

	player = new QMediaPlayer(this);
	audioOutput = new QAudioOutput(this);

	startButton = new QPushButton("Старт", this);
	openButton = new QPushButton("Открыть Файл", this);
	volumeSlider = new QSlider(Qt::Vertical, this);
	positionSlider = new QSlider(Qt::Horizontal, this);
	timeLabel = new QLabel("00:00 / 00:00", this);
}

void MusicPlayer::setupUi()
{
	layout->addWidget(volumeSlider);
	layout->addWidget(timeLabel);
	layout->addWidget(positionSlider);
	layout->addWidget(startButton);
	layout->addWidget(openButton);
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