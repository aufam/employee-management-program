#include "employee.h"
#include <delameta/http/http.h>
#include <fstream>
#include <sstream>
#include <mutex>

using namespace Project;
using delameta::Result, delameta::Error;
using delameta::http::Status;
using etl::Ok, etl::Err;

auto finshot::Employee::View(
    std::string id
) -> Result<Employee> {
    std::lock_guard<std::mutex> lock(database_mutex);

    std::ifstream file(database);
    if (!file)
        return Err(Error{Status::StatusInternalServerError, "Cannot open " + database});

    std::vector<Employee> res;
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);

        Employee e;
        std::getline(ss, e.id, ';');
        if (id == e.id) {
            if (
                std::getline(ss, e.name, ';') &&
                std::getline(ss, e.phoneNumber, ';') &&
                std::getline(ss, e.position, ';') &&
                std::getline(ss, e.emailAddress, ';')
            ) {
                return Ok(e);
            } else {
                return Err(Error{Status::StatusInternalServerError, "Fail to parse data"});
            }
        }
    }

    return Err(Error{Status::StatusNotFound, "Id not found"});
}
