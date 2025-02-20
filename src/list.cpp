#include "employee.h"
#include <delameta/http/http.h>
#include <fstream>
#include <mutex>
#include <sstream>
#include <string>

using namespace Project;
using delameta::Result, delameta::Error;
using delameta::http::Status;
using etl::Ok, etl::Err;

auto finshot::Employee::List(
    std::string sort_by,
    bool ascending
) -> Result<std::vector<Employee>> {
    if (
        sort_by != "id" &&
        sort_by != "name" &&
        sort_by != "phone-number"
    ) {
        return Err(Error{Status::StatusBadRequest, "Invalid `sort-by` value"});
    }

    std::lock_guard<std::mutex> lock(database_mutex);

    std::ifstream file(database);
    if (!file)
        return Err(Error{Status::StatusInternalServerError, "Cannot open " + database});

    std::vector<Employee> res;
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);

        Employee e;
        if (
            std::getline(ss, e.id, ';') &&
            std::getline(ss, e.name, ';') &&
            std::getline(ss, e.phoneNumber, ';') &&
            std::getline(ss, e.position, ';') &&
            std::getline(ss, e.emailAddress, ';')
        ) {
            res.push_back(e);
        } else {
            return Err(Error{Status::StatusInternalServerError, "Fail to parse data"});
        }
    }

    if (sort_by == "id") {
        std::sort(res.begin(), res.end(), [&](const Employee& a, const Employee& b) {
            return ascending ? a.id < b.id : a.id > b.id;
        });
    } else if (sort_by == "name") {
        std::sort(res.begin(), res.end(), [&](const Employee& a, const Employee& b) {
            return ascending ? a.name < b.name : a.name > b.name;
        });
    } else if (sort_by == "phone-number") {
        std::sort(res.begin(), res.end(), [&](const Employee& a, const Employee& b) {
            return ascending ? a.phoneNumber < b.phoneNumber : a.phoneNumber > b.phoneNumber;
        });
    }

    return Ok(std::move(res));
}
