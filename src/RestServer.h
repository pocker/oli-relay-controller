#pragma once

#define MBEDTLS_GCM_C
#include <ESPAsyncWebServer.h>

#include "config.h"

class RestServer
{

private:
    AsyncWebServer *server;
    Config *config;
    char *getUsername();
    char *getPassword();

public:
    RestServer(int, bool);
    ~RestServer();
    void begin(Config *config);
    void registerUpdater();
    bool shouldAuthenticate(AsyncWebServerRequest *request);
    void requestAuthentication(AsyncWebServerRequest *request);

    AsyncCallbackWebHandler &on(const char *uri, WebRequestMethodComposite method, ArBodyHandlerFunction onBody);
    AsyncCallbackWebHandler &on(const char *uri, WebRequestMethodComposite method, ArRequestHandlerFunction onRequest);
};