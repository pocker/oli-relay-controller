#include "RestServer.h"

#include <Update.h>
#include <FS.h>
#include <SPIFFS.h>

void redirectToIndex(AsyncWebServerRequest *);
void loadFile(AsyncWebServerRequest *);
void handleUpdate(AsyncWebServerRequest *, const String &, size_t, uint8_t *, size_t, bool);

RestServer::RestServer(int port = 80, bool spiffs = true)
{
    this->server = new AsyncWebServer(port);

    if (spiffs)
    {
        SPIFFS.begin(true);
        this->server->on("/", HTTP_GET, &redirectToIndex);
        this->server->onNotFound(&loadFile);
    }
}

RestServer::~RestServer()
{
    delete this->server;
}

void RestServer::begin(Config *config)
{
    this->config = config;
    this->server->begin();
}

char *RestServer::getUsername()
{
    return this->config->user.username;
}

char *RestServer::getPassword()
{
    return this->config->user.password;
}

void RestServer::registerUpdater()
{
    this->server->on(
        "/update", HTTP_POST, [&](AsyncWebServerRequest *request)
        {
            if (!request->authenticate(this->getUsername(), this->getPassword()))
            {
                return request->requestAuthentication();
            } },
        &handleUpdate);
}

bool RestServer::shouldAuthenticate(AsyncWebServerRequest *request)
{
    return !request->authenticate(this->getUsername(), this->getPassword());
}

void RestServer::requestAuthentication(AsyncWebServerRequest *request)
{
    request->requestAuthentication();
}

AsyncCallbackWebHandler &RestServer::on(const char *uri, WebRequestMethodComposite method, ArBodyHandlerFunction onBody)
{
    return this->server->on(
        uri, method, [](AsyncWebServerRequest *request) {}, nullptr, onBody);
}

AsyncCallbackWebHandler &RestServer::on(const char *uri, WebRequestMethodComposite method, ArRequestHandlerFunction onRequest)
{
    return this->server->on(uri, method, onRequest);
}

void redirectToIndex(AsyncWebServerRequest *request)
{
    request->redirect("/index.html");
}

String getContentType(String filename)
{
    if (filename.endsWith(".htm"))
        return "text/html";
    else if (filename.endsWith(".html"))
        return "text/html";
    else if (filename.endsWith(".css"))
        return "text/css";
    else if (filename.endsWith(".jpg"))
        return "image/jpeg";
    return "text/plain";
}

void loadFile(AsyncWebServerRequest *request)
{
    if (!SPIFFS.exists(request->url()))
    {
        return request->send(404, "text/plain", "404 - Not found");
    }

    if (request->method() != HTTP_GET)
    {
        return request->send(405, "text/plain", "405 - Method not allowed");
    }

    request->send(SPIFFS, request->url(), getContentType(request->url()));
}

void handleUpdate(AsyncWebServerRequest *request, const String &filename, size_t index, uint8_t *data, size_t len, bool final)
{
    if (!index)
    {
        Serial.println("Update");
        Serial.println(filename);
        int cmd = (filename.indexOf("spiffs") > -1) ? U_SPIFFS : U_FLASH;
        if (!Update.begin(UPDATE_SIZE_UNKNOWN, cmd))
        {
            Update.printError(Serial);
        }
    }

    Update.write(data, len);

    if (final)
    {
        if (Update.end(true))
        {
            request->send(202, "text/plain");
        }
        else
        {
            request->send(500, "text/plain", Update.errorString());
        }
        delay(100);
        ESP.restart();
    }
}