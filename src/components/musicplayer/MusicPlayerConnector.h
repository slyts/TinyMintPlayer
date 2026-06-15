#ifndef MUSICPLAYERCONNECTOR_H
#define MUSICPLAYERCONNECTOR_H

#include <qobject.h>

#include "MusicPlayerUI.h"
#include "MusicPlayerLogic.h"
#include "../playlist/PlaylistConnector.h"
#include "../IConnector.h"

class MusicPlayerConnector : public QObject, public IConnector
{
	Q_OBJECT
private:
	MusicPlayerLogic* logic;
	MusicPlayerUI* ui;

	void connectUI() override;
	void connectLogic() override;

public:
	MusicPlayerConnector(QWidget* parent = nullptr);

	void merge(PlaylistConnector* playlist);

	MusicPlayerUI* getUi() const { return ui; }
	MusicPlayerLogic* getLogic() const { return logic; }
};

#endif //MUSICPLAYERCONNECTOR_H