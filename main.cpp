#include <qapplication.h>
#include "Application.h"

int main(int argc, char *argv[])
{
    QApplication qapp(argc, argv);
    Application app;
    app.init();
    return qapp.exec();
}
