#include "Utils/Log.h"
#include "Engine.h"

LogConfig LOG_CONFIG = {};

int main()
{
    // Init logging
    LOG_CONFIG.reporting_level = Debug;
    LOG_CONFIG.restart = true;
    if (LOG_CONFIG.restart) {
        Log::restart();
    }

    Engine engine = Engine();

    engine.run();


    return 0;
}