#include <qfileinfo.h>
#include "Playlist.h"

void Playlist::getTrack()
{}

void Playlist::getTrackList()
{}

void Playlist::addTrack(const QString & filepath)
{
	trackList.append(QUrl(filepath));

	QFileInfo fileInfo(filepath);
	QString displayName = fileInfo.baseName();

	QListWidgetItem* item = new QListWidgetItem(displayName);
	item->setData(Qt::UserRole, filepath);

	this->addItem(item);
}

void Playlist::removeTrack(int index)
{}

void Playlist::clear()
{}

void Playlist::onItemClicked(QListWidgetItem* item)
{
	QString filepath = item->data(Qt::UserRole).toString();
	emit trackSelected(filepath);
}

Playlist::Playlist(QWidget* parent) : QListWidget(parent)
{
	connect(this, &QListWidget::itemClicked, this, &Playlist::onItemClicked);
}

Playlist::~Playlist()
{}
