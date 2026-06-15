#ifndef MUSICPLAYERLOGIC_H
#define MUSICPLAYERLOGIC_H

#include <qobject.h>
#include <qmediaplayer.h>
#include <qaudiooutput.h>

class MusicPlayerLogic : public QObject
{
	Q_OBJECT

private:
	QAudioOutput* audioOutput;
	QMediaPlayer* player;

	bool isPaused;

	void configureMedia();
	void setConnect();
public:
	MusicPlayerLogic(QObject * parent = nullptr);
	~MusicPlayerLogic();

public slots:
	void play();
	void openFile(QString filePath);
	void setPositionSlider(qint64 value);
	void playlistPlay(QString filePath);

signals:
	void positionChanged(qint64 ms);
	void durationChanged(qint64 ms);
	void playClicked(bool isPaused);
	void fileOpened(QString filePath);
};

#endif // !MUSICPLAYERLOGIC_H
