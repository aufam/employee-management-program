#include "employee.h"
#include <delameta/debug.h>
#include <delameta/opts.h>
#include <catch2/catch_session.hpp>

using namespace Project;
using delameta::Result;
using etl::Ok, etl::Err;

auto http_start(std::string host) -> Result<void>;

OPTS_MAIN(
    (EmployeeManagement, "Employee Management CLI Tools")
    ,
    /*   Type   |  Arg    | Short |      Long      |              Help               |      Default   */
    (std::string, mode    , 'm'   , "mode"         , "Specify mode. Valid values: "
                                                     "add, list, view, edit, delete, "
                                                     "http, test"
                                                                                    , "http"     )

    // http mode:
    (std::string, host    ,  'H'  , "host"         , "Specify host and port"         , "localhost:5000")

    // fields:
    (std::string, id      ,  'i'  , "id"           , "Specify `id` field"            , ""              )
    (std::string, name    ,  'n'  , "name"         , "Specify `name` field"          , ""              )
    (std::string, phone   ,  'p'  , "phone-number" , "Specify `phoneNumber` field"   , ""              )
    (std::string, position,  'P'  , "position"     , "Specify `position` field"      , ""              )
    (std::string, email   ,  'e'  , "email-address", "Specify `emailAddress` field"  , ""              )

    // filter query
    (std::string, sort_by ,  's'  , "sort-by"      , "Specify `sort-by` query"       , "id"            )
    ,
    (Result<void>)
) {
    if (mode == "http") {
        return http_start(host);
    }

    if (mode == "add") {
        auto employee = TRY(finshot::Employee::Add(name, phone, position, email));
        fmt::println("{}", employee);
        return Ok();
    }

    if (mode == "list") {
        auto employees = TRY(finshot::Employee::List(sort_by));
        fmt::println("{}", fmt::join(employees, "\n"));
        return Ok();
    }

    if (mode == "view") {
        auto employee = TRY(finshot::Employee::View(id));
        fmt::println("{}", employee);
        return Ok();
    }

    if (mode == "edit") {
        auto name_ = name.empty() ? std::nullopt : std::optional(name);
        auto phone_ = phone.empty() ? std::nullopt : std::optional(phone);
        auto position_ = position.empty() ? std::nullopt : std::optional(position);
        auto email_ = email.empty() ? std::nullopt : std::optional(email);
        auto employee = TRY(finshot::Employee::Edit(id, name_, phone_, position_, email_));
        fmt::println("{}", employee);
        return Ok();
    }

    if (mode == "delete") {
        auto res = finshot::Employee::Delete(id);
        fmt::println("{}", res);
        return Ok();
    }

    if (mode == "test") {
        const char* argv[] = {"test", "--success"};
        const auto argc = sizeof(argv) / sizeof(size_t);

        Catch::Session session;
        int res = session.run(argc, argv);

        if (res != 0) {
            return Err("Test failed");
        }

        return Ok();
    }

    return Err("Unknown mode");
}

