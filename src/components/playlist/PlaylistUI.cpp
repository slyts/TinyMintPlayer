#include <qfileinfo.h>
#include "PlaylistUI.h"

PlaylistUI::PlaylistUI(QWidget* parent) : QListWidget(parent)
{
	connect(this, &QListWidget::itemClicked, this, &PlaylistUI::onItemClicked);
}

PlaylistUI::~PlaylistUI()
{}

void PlaylistUI::addTrackUI(const QString & filepath)
{
	QFileInfo fileInfo(filepath);
	QString displayName = fileInfo.baseName();

	QListWidgetItem* item = new QListWidgetItem(displayName);
	item->setData(Qt::UserRole, filepath);

	this->addItem(item);
}

void PlaylistUI::onItemClicked(QListWidgetItem* item)
{
	QString filepath = item->data(Qt::UserRole).toString();
	emit trackSelected(filepath);
}