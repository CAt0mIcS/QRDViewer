#include "stdafx.h"
#include "Application.h"

#include "Windows/MainWindow.h"

int main(int argc, char** argv)
{
    QRDViewer::Application app("C:\\dev\\ProgramFiles\\QRDViewer\\Db.dbs", argc, argv);
    MainWindow win;
    win.show();

    return app.Run();
}
