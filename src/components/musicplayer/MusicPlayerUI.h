#ifndef MUSICPLAYERUI_H
#define MUSICPLAYERUI_H

#include <qwidget.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qslider.h>
#include <qlabel.h>
#include <qstring.h>

#include "../../models/ApplicationSettings.h"

class MusicPlayerUI : public QWidget
{
	Q_OBJECT

private:
	ApplicationSettings settings;
	QWidget* playlistWidget;

	QVBoxLayout* mainVlayout;
	QHBoxLayout* mainHlayout;
	QVBoxLayout* playerVContainer;
	QHBoxLayout* playerHContainer;
	QVBoxLayout* trackInfoContainer;
	QHBoxLayout* timeSliderContainer;
	QVBoxLayout* infoBlockContainer;

	QPushButton* startButton;
	QPushButton* openButton;
	QPushButton* nextTrack;
	QPushButton* previousTrack;
	QPushButton* playlistButton;
	QPushButton* volumeButton;
	QPushButton* loopButton;
	QPushButton* mixButton;

	QSlider* volumeSlider;
	QSlider* positionSlider;

	QLabel* timeLabelStart;
	QLabel* timeLabelEnd;
	QLabel* trackName;
	QLabel* trackImage;

	void setAppSettings();
	void createObjects();
	void setupUi();	
	void setupTrackInfoArea();
	void setupTimeSliderArea();
	void setupButtonsArea();
	void setupLayouts();
	void applyDefaultStyles();
	QString formatTime(qint64 ms) const;
	void setConnect();
	void onVolumeSlide(int value);

	bool isUserDragging = false;

public:
	MusicPlayerUI(QWidget* parent = nullptr);
	~MusicPlayerUI();

	void setPlaylistWidget(QWidget* widget);

public slots:
	void onOpenFileClicked();
	void onClickPlay();
	void onSliderPressed();
	void onSliderReleased();
	void onSliderMoved(int value);

	void updatePosition(qint64 value);
	void updateDuration(qint64 value);
	void updateStartButton(bool isPaused);
	void onPlaylistButtonCliked();
	void playlistPlay(const QString file);

signals:
	void playClicked();
	void volumeChanged(int value);
	void fileOpen(QString path);
	void sliderRelease(qint64 value);

};

#endif //MUSICPLAYERUI_H