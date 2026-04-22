#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace api {
namespace v1 {
class subscribe : public drogon::HttpController<subscribe> {
public:
  METHOD_LIST_BEGIN
  METHOD_ADD(subscribe::get_config, "/config?token={1}", Get);
  METHOD_ADD(subscribe::get_provider, "/provider?token={1}&type={2}", Get);
  METHOD_LIST_END

  void get_config(const HttpRequestPtr &req,
           std::function<void(const HttpResponsePtr &)> &&callback,
           std::string token);
  void get_provider(const HttpRequestPtr &req,
           std::function<void(const HttpResponsePtr &)> &&callback,
           std::string token, std::string type);
};
} // namespace v1
} // namespace api
