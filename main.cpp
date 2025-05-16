#include "Emulator.h"
#include "core/log/Logger.h"
int main()
{
    // Only show WARNING and above
    Logger::setLogLevel(Logger::Level::DEBUG);
    LOG(INFO, "ciao stronzi");
    Emulator emu;

    return 0;
}