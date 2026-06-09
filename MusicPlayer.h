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
	
	QVBoxLayout* layout;

	QPushButton* startButton;
	QPushButton* openButton;
	QMediaPlayer* player;
	QAudioOutput* audioOutput;
	QSlider* volumeSlider;
	QSlider* positionSlider;
	QLabel* timeLabel;
	
	bool isPaused = true;

	void setAppSettings();

	void createObjects();
	void setupUi();
	void setConnect();
	void configureMedia();

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