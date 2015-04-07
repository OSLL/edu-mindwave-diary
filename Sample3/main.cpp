#include <QApplication>
#include "mainwindow.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

char* newVarName;

void
wait() {
    printf( "\n" );
    printf( "Press the ENTER key...\n" );
    fflush( stdout );
    getc( stdin );
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    newVarName = "text";

    char *comPortName  = NULL;
    int   dllVersion   = 0;
    int   connectionId = 0;
    int   packetsRead  = 0;
    int   errCode      = 0;

    double secondsToRun = 0;
    time_t startTime    = 0;
    time_t currTime     = 0;
    char  *currTimeStr  = NULL;

    dllVersion = TG_GetDriverVersion();
    printf( "ThinkGear DLL version: %d\n", dllVersion );

    /* Get a connection ID handle to ThinkGear */




    MainWindow w;
    w.show();
    return a.exec();
}
