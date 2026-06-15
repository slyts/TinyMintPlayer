#ifndef PLAYLISTCONNECTOR
#define PLAYLISTCONNECTOR

#include <qobject.h>

#include "PlaylistLogic.h"
#include "PlaylistUI.h"
#include "../IConnector.h"

class PlaylistConnector: public QObject, public IConnector
{
	Q_OBJECT
private:
	PlaylistUI* ui;
	PlaylistLogic* logic;

	void connectUI() override;
	void connectLogic() override;
public:
	PlaylistConnector(QWidget* parent = nullptr);

	PlaylistUI* getUi() { return ui; }
	PlaylistLogic* getLogic() { return logic; }
};


#endif // !PLAYLISTCONNECTOR