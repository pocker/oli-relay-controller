#include "context.h"

Context *createContext()
{
    initConfig();
    Context *context = new Context();
    context->config = loadConfig();
    return context;
};