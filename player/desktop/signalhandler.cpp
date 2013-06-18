#include "signalhandler.h"

void SignalHandler::ping() 
{
	qDebug() << "signal received from QML app";
}
