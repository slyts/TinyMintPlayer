#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <qwidget.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qmediaplayer.h>
#include <qaudiooutput.h>
#include <qslider.h>
#include <qlabel.h>

#include "ApplicationSettings.h"

class MusicPlayer : public QWidget
{
	Q_OBJECT
private:
	ApplicationSettings settings;

	QMediaPlayer* player;
	QAudioOutput* audioOutput;

	QVBoxLayout* mainlayout;
	QVBoxLayout* playerVContainer;
	QHBoxLayout* playerHContainer;
	QVBoxLayout* trackInfoContainer;
	QHBoxLayout* timeSliderContainer;
	QVBoxLayout* infoBlockContainer;

	QPushButton* startButton;
	QPushButton* openButton;
	QPushButton* nextTrack;
	QPushButton* previousTrack;

	QSlider* volumeSlider;
	QSlider* positionSlider;

	QLabel* timeLabelStart;
	QLabel* timeLabelEnd;
	QLabel* trackName;
	QLabel* trackImage;
	
	bool isPaused = true;

	void setAppSettings();

	void createObjects();
	void setupUi();
	void setConnect();
	void configureMedia();

	void setupTrackInfoArea();
	void setupTimeSliderArea();
	void setupButtonsArea();
	void setupLayouts();
	void applyDefaultStyles();

public:
	MusicPlayer(QWidget* parent = nullptr);
	~MusicPlayer();

private slots:
	void onPlayClicked();
	void onOpenFileClicked();
	void onVolumeSlide(int value);
	void onDurationChanged(qint64 value);
	void onPositionChanged(qint64 value);
	void onSliderPosition();

};

#endif //MUSICPLAYER_H