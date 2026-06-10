#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <qstring.h>
#include <qsize.h>

class ApplicationSettings
{
private:
	QString title = "TinyMint Player";
	QSize screenSize = { 600,700 };

public:
	ApplicationSettings();
	~ApplicationSettings();

	QSize getScreenSize() const;
	QString getTitle() const;
};

#endif //APPLICATIONSETTINGS_H