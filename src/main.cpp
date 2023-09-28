#include <Arduino.h>
#include <ArduinoJson.h>

#include "pinout.h"
#include "context.h"

#include "Controller.h"
#include "RestServer.h"
#include "Monitor.h"
#include "WifiManager.h"

Context *context;
Controller controller;
Monitor monitor;
WifiManager wifi;
RestServer server(80, true);

char postBuffer[2048];

void getStatus(AsyncWebServerRequest *request)
{
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  monitor.write(response);
  request->send(response);
}

void updateConfig(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
  if (server.shouldAuthenticate(request))
  {
    return server.requestAuthentication(request);
  }

  memcpy(postBuffer + index, data, len);
  if (index + len != total)
  {
    return;
  }

  DynamicJsonDocument bodyJSON(2048);
  DeserializationError err = deserializeJson(bodyJSON, postBuffer, total);

  if (err)
  {
    return request->send(400, "text/plain", err.c_str());
  }

  if (bodyJSON.containsKey("user"))
  {
    JsonObject user = bodyJSON["user"];
    if (user.containsKey("username") && user.containsKey("password"))
    {
      strncpy(context->config->user.username, user["username"], 10);
      strncpy(context->config->user.password, user["password"], 10);
    }
  }

  if (bodyJSON.containsKey("wifi"))
  {
    JsonObject wifi = bodyJSON["wifi"];
    if (wifi.containsKey("ssid") && wifi.containsKey("password"))
    {
      strncpy(context->config->wifi.ssid, wifi["ssid"], 16);
      strncpy(context->config->wifi.password, wifi["password"], 16);
    }
  }

  if (bodyJSON.containsKey("profile"))
  {
    JsonObject profile = bodyJSON["profile"];
    if (profile.containsKey("active"))
    {
      context->config->profile.active = profile["active"];
    }

    if (profile.containsKey("configuration"))
    {
      JsonArray configuration = profile["configuration"];
      for (int i = 0; i < MAX_PROFILE; i++)
      {
        for (int j = 0; j < OUTPUTS; j++)
        {
          context->config->profile.configuration[i][j] = configuration[i][j];
        }
      }
    }
  }

  writeConfig(context->config);
  request->send(200, "plain/text", "");
}

void restart(AsyncWebServerRequest *request)
{
  if (server.shouldAuthenticate(request))
  {
    return server.requestAuthentication(request);
  }
  request->send(200, "plain/text", "");
  ESP.restart();
}

void setup()
{
  Serial.begin(115200);
  context = createContext();

  controller.begin(context);
  monitor.begin(context);
  wifi.begin(context->config);

  server.on("/status", HTTP_GET, &getStatus);
  server.on("/config", HTTP_POST, &updateConfig);
  server.on("/restart", HTTP_GET, &restart);
  server.registerUpdater();
  server.begin(context->config);
}

void loop()
{
  controller.loop();
  wifi.loop();
  delay(1);
}
