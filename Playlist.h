#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <qwidget.h>
#include <qvector.h>
#include <qlistwidget.h>
#include <qurl.h>


class Playlist : public QListWidget
{
	Q_OBJECT

private:
	QVector<QUrl> trackList;
	int currentTrackIndex;

	QSize windowSize = { 600, 700 };
public:
	Playlist(QWidget* parent = nullptr);
	~Playlist();

	void getTrack();
	void getTrackList();

	void addTrack(const QString& filepath);
	void removeTrack(int index);
	void clear();

private slots:
	void onItemClicked(QListWidgetItem* item);

signals:
	void trackSelected(QString& filepath);
};

#endif // !PLAYLIST_H
