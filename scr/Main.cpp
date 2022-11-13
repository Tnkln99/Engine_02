#include "Log.h"
#include "Mesh.h"
#include "Object.h"
#include "Engine.h"

LogConfig LOG_CONFIG = {};


int main()
{
    Engine engine = Engine();

    engine.run();

    glGetError();

    return 0;
}