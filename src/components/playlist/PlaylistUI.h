#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <qwidget.h>
#include <qvector.h>
#include <qlistwidget.h>
#include <qurl.h>


class PlaylistUI : public QListWidget
{
	Q_OBJECT

private:
	QSize windowSize = { 600, 700 };

public:
	PlaylistUI(QWidget* parent = nullptr);
	~PlaylistUI();

	void addTrackUI(const QString& filepath);

private slots:
	void onItemClicked(QListWidgetItem* item);

signals:
	void trackSelected(QString& filepath);
};

#endif // !PLAYLIST_H
