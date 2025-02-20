#include "employee.h"
#include <delameta/http/http.h>

using namespace Project;
using delameta::Result, delameta::Error;
namespace http = delameta::http;

auto http_start(std::string host) -> Result<void> {
    http::Http app;

    static auto convert_error = [](const Error& e) -> http::Error {
        return {e.code, e.what};
    };

    app.Get("/api/employees").args(
        http::arg::default_val("sort-by", "id"),
        http::arg::default_val("asc", true)
    )|[](std::string sort_by, bool ascending) {
        return finshot::Employee::List(sort_by, ascending).except(convert_error);
    };

    app.Get("/api/employee").args(
        http::arg::arg("id")
    )|[](std::string id) {
        return finshot::Employee::View(id).except(convert_error);
    };

    app.Post("/api/employee").args(
        http::arg::json_item("name"),
        http::arg::json_item("phoneNumber"),
        http::arg::json_item("position"),
        http::arg::json_item("emailAddress")
    )|[](std::string name, std::string phoneNumber, std::string position, std::string emailAddress) {
        return finshot::Employee::Add(name, phoneNumber, position, emailAddress).except(convert_error);
    };

    app.Put("/api/employee").args(
        http::arg::json_item("id"),
        http::arg::json_item_default_val("name", std::nullopt),
        http::arg::json_item_default_val("phoneNumber", std::nullopt),
        http::arg::json_item_default_val("position", std::nullopt),
        http::arg::json_item_default_val("emailAddress", std::nullopt)
    )|[](
        std::string id,
        std::optional<std::string> name,
        std::optional<std::string> phoneNumber,
        std::optional<std::string> position,
        std::optional<std::string> emailAddress
    ) {
        return finshot::Employee::Edit(id, name, phoneNumber, position, emailAddress).except(convert_error);
    };

    app.Delete("/api/employee").args(
        http::arg::arg("id")
    )|[](std::string id) {
        return finshot::Employee::Delete(id).except(convert_error);
    };

    fmt::println("Server is starting at {}", host);
    return app.listen(http::Http::ListenArgs{.host=host});
}

