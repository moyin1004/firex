#include "api_v1_subscribe.h"
#include "drogon/HttpAppFramework.h"
#include "drogon/HttpResponse.h"
#include "trantor/utils/Logger.h"

using namespace api::v1;

void subscribe::get_config(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,
    std::string token) {
  std::string user_agent = req->getHeader("User-Agent");
  if (user_agent.find("mihomo") == std::string::npos &&
      user_agent.find("clash.meta") == std::string::npos) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(HttpStatusCode::k401Unauthorized);
    callback(resp);
    return;
  }
  auto &custome_config = app().getCustomConfig();
  if (custome_config["token"].asString() != token) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(HttpStatusCode::k401Unauthorized);
    callback(resp);
    return;
  }
  LOG_DEBUG << "subscribe get token: " << token;
  std::string datapath = custome_config["datapath"].asString();
  auto resp = HttpResponse::newFileResponse(datapath + "subscribe/config.yaml");
  callback(resp);
}

void subscribe::get_provider(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback, std::string token,
    std::string type) {
  auto &custome_config = app().getCustomConfig();
  if (custome_config["token"].asString() != token) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(HttpStatusCode::k401Unauthorized);
    callback(resp);
    return;
  }
  LOG_DEBUG << "subscribe get token: " << token << ", type: " << type;
  std::string target_type = type;
  std::string datapath = custome_config["datapath"].asString();
  if (target_type == "txt") {
    auto resp =
        HttpResponse::newFileResponse(datapath + "subscribe/provider_uri.txt");
    callback(resp);
  } else {
    auto resp =
        HttpResponse::newFileResponse(datapath + "subscribe/provider.yaml");
    callback(resp);
  }
}