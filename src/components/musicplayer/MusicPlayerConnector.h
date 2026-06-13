#ifndef MUSICPLAYERCONNECTOR_H
#define MUSICPLAYERCONNECTOR_H

#include <qobject.h>

#include "MusicPlayerUI.h"
#include "MusicPlayerLogic.h"

//class PlaylistConnector;

class MusicPlayerConnector : public QObject
{
	Q_OBJECT
private:
	MusicPlayerLogic* logic;
	MusicPlayerUI* ui;

	void connectMusicplayerUI();
	void connectMusicplayerLogic();

public:
	MusicPlayerConnector(QWidget* parent = nullptr);

	//void merge(PlaylistConnector* playlist);

	MusicPlayerUI* getUi() const { return ui; }
	MusicPlayerLogic* getLogic() const { return logic; }
};

#endif //MUSICPLAYERCONNECTOR_H