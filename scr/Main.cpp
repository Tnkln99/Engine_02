#include "Log.h"
#include "Mesh.h"
#include "Object.h"
#include "Engine.h"

LogConfig LOG_CONFIG = {};


int main(int argc, char *argv[])
{
    Engine engine = Engine();

    engine.run();

    return 0;
}