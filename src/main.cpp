#include "employee.h"
#include "fmt/ranges.h"
#include <delameta/debug.h>
#include <delameta/opts.h>
#include <optional>

using namespace Project;
using delameta::Result;
using etl::Ok, etl::Err;

auto http_start(std::string host) -> Result<void>;

OPTS_MAIN(
    (EmployeeManagement, "Employee Management CLI Tools")
    ,
    /*   Type   |  Arg  | Short |   Long    |              Help               |      Default   */
    ,
    (Result<void>)
) {
    return http_start("localhost:5000");
}

