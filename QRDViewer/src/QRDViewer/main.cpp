#include "stdafx.h"
#include "Application.h"

int main(int argc, char** argv)
{
    QRDViewer::Application app("D:\\dev\\ProgramFiles\\QRDViewer\\Db.dbs", argc, argv);
    return app.Run();
}
