#ifndef PLAYLISTLOGIC_H
#define PLAYLISTLOGIC_H

#include <qobject.h>
#include <qurl.h>

class PlaylistLogic : public QObject
{
	Q_OBJECT
private:
	QVector<QUrl> tracklist;
	int currentTrackIndex;

public:
	PlaylistLogic(QObject* parent = nullptr);
	~PlaylistLogic();

	void addTrack(const QString& filepath);

signals:
	void appendTrack(const QString filePath);
};

#endif // !PLAYLISTLOGIC_H

