#include <drogon/drogon.h>
#include <filesystem>
#include <iostream>

using namespace drogon;

int main() {
  std::cout << "当前工作目录: " << std::filesystem::current_path() << std::endl;
  auto &httpserver = app();
  httpserver.loadConfigFile("./config.yaml");
  httpserver.registerHandler(
      "api/v1/ping",
      [](const HttpRequestPtr &req,
         std::function<void(const HttpResponsePtr &)> &&callback) {
        LOG_DEBUG << "subscribe ping";
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(HttpStatusCode::k200OK);
        resp->setBody("pong");
        callback(resp);
      }, {Get});
  auto handlers = httpserver.getHandlersInfo();
  LOG_DEBUG << "subscribe handlers: " << handlers.size();
  for (auto &handler : handlers) {
    LOG_DEBUG << "subscribe handler: " << std::get<0>(handler) << ", "
              << std::get<1>(handler) << ", " << std::get<2>(handler);
  }
  httpserver.run();
}