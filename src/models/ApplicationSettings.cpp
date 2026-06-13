#include "ApplicationSettings.h"

ApplicationSettings::ApplicationSettings()
{}

ApplicationSettings::~ApplicationSettings()
{}

QSize ApplicationSettings::getScreenSize() const
{
	return screenSize;
}

QString ApplicationSettings::getTitle() const
{
	return title;
}


