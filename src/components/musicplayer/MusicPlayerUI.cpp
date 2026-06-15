#include <qfiledialog.h>

#include "MusicPlayerUI.h"

MusicPlayerUI::MusicPlayerUI(QWidget* parent) : QWidget(parent)
{
	setAppSettings();
	createObjects();
	setupUi();
	setConnect();
}

MusicPlayerUI::~MusicPlayerUI()
{}

void MusicPlayerUI::setPlaylistWidget(QWidget * widget)
{
	playlistWidget = widget;
	if (playlistWidget)
	{
		playlistWidget->hide();
		mainHlayout->addWidget(playlistWidget);
	}
}

void MusicPlayerUI::setAppSettings()
{
	setWindowTitle(settings.getTitle());
	setFixedSize(settings.getScreenSize());
}

void MusicPlayerUI::createObjects()
{
	mainVlayout = new QVBoxLayout();
	mainHlayout = new QHBoxLayout(this);

	playerVContainer = new QVBoxLayout();
	playerHContainer = new QHBoxLayout();
	trackInfoContainer = new QVBoxLayout();
	timeSliderContainer = new QHBoxLayout();
	infoBlockContainer = new QVBoxLayout();

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

void MusicPlayerUI::setupUi()
{
	setupTrackInfoArea();
	setupTimeSliderArea();
	setupButtonsArea();
	setupLayouts();
	applyDefaultStyles();
}

void MusicPlayerUI::setupTrackInfoArea()
{
	trackInfoContainer->addWidget(trackImage);
	trackInfoContainer->addWidget(trackName);
}

void MusicPlayerUI::setupTimeSliderArea()
{
	timeSliderContainer->addWidget(timeLabelStart);
	timeSliderContainer->addWidget(positionSlider);
	timeSliderContainer->addWidget(timeLabelEnd);
}

void MusicPlayerUI::setupButtonsArea()
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

void MusicPlayerUI::setupLayouts()
{
	infoBlockContainer->addLayout(trackInfoContainer);
	infoBlockContainer->addLayout(timeSliderContainer);

	playerVContainer->addLayout(playerHContainer);

	mainVlayout->addLayout(infoBlockContainer);
	mainVlayout->addLayout(playerVContainer);

	mainHlayout->addLayout(mainVlayout);
}

void MusicPlayerUI::applyDefaultStyles()
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

	mainVlayout->setContentsMargins(20, 20, 20, 20);
	mainVlayout->setSpacing(5);
}

QString MusicPlayerUI::formatTime(qint64 ms) const
{
	QTime time(0, 0, 0);
	time = time.addMSecs(ms);
	return time.toString("mm:ss");
}

void MusicPlayerUI::setConnect()
{
	connect(startButton, &QPushButton::clicked, this, &MusicPlayerUI::onClickPlay);
	connect(openButton, &QPushButton::clicked, this, &MusicPlayerUI::onOpenFileClicked);
	connect(positionSlider, &QSlider::sliderPressed, this, &MusicPlayerUI::onSliderPressed);
	connect(positionSlider, &QSlider::sliderMoved, this, &MusicPlayerUI::onSliderMoved);
	connect(positionSlider, &QSlider::sliderReleased, this, &MusicPlayerUI::onSliderReleased);
	connect(playlistButton, &QPushButton::clicked, this, &MusicPlayerUI::onPlaylistButtonCliked);
}

// -- slots --
void MusicPlayerUI::onOpenFileClicked()
{
	QString filePath = QFileDialog::getOpenFileName(
		this,
		"Выберите файл",
		"",
		"*.mp3 *.wav *.flac *.ogg"
	);

	if (!filePath.isEmpty())
	{
		QFileInfo trackInfo(filePath);
		trackName->setText(QString(trackInfo.baseName()));
		emit fileOpen(filePath);
		startButton->setText("Старт");
	}
}

void MusicPlayerUI::onClickPlay()
{
	emit playClicked();
}

void MusicPlayerUI::onSliderPressed()
{
	isUserDragging = true;
}

void MusicPlayerUI::onSliderMoved(int value)
{
	timeLabelStart->setText(formatTime(value));
}

void MusicPlayerUI::onSliderReleased()
{
	isUserDragging = false;
	emit sliderRelease(positionSlider->value());
}

void MusicPlayerUI::updatePosition(qint64 value)
{
	if (!isUserDragging && !positionSlider->isSliderDown()) {
		positionSlider->setValue(value);
		timeLabelStart->setText(formatTime(value));
	}
}

void MusicPlayerUI::updateDuration(qint64 value)
{
	positionSlider->setRange(0, value);
	timeLabelEnd->setText(formatTime(value));
}

void MusicPlayerUI::updateStartButton(bool isPaused)
{
	if (!isPaused)
	{
		startButton->setText("Пауза");
	}
	else
	{
		startButton->setText("Старт");
	}
}

void MusicPlayerUI::onPlaylistButtonCliked()
{
	playlistWidget->setVisible(!playlistWidget->isVisible());
	if (playlistWidget->isVisible())
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

void MusicPlayerUI::playlistPlay(const QString filePath)
{
	startButton->setText("Пауза");
	QFileInfo trackInfo(filePath);
	trackName->setText(QString(trackInfo.baseName()));
}