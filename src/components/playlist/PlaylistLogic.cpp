#include "PlaylistLogic.h"

PlaylistLogic::PlaylistLogic(QObject* parent) : QObject(parent)
{}

PlaylistLogic::~PlaylistLogic()
{}

void PlaylistLogic::addTrack(const QString& filepath)
{
	tracklist.append(QUrl(filepath));
	emit appendTrack(filepath);
}