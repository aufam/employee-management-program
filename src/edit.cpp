#include "employee.h"
#include <delameta/http/http.h>
#include <fstream>
#include <sstream>
#include <mutex>

using namespace Project;
using delameta::Result, delameta::Error;
using delameta::http::Status;
using etl::Ok, etl::Err;

auto finshot::Employee::Edit(
    std::string id,
    std::optional<std::string> name,
    std::optional<std::string> phoneNumber,
    std::optional<std::string> position,
    std::optional<std::string> emailAddress
) -> Result<Employee> {
    TRY(ValidateId(id));

    if (name) {
        TRY(ValidateField(*name));
    }
    if (phoneNumber) {
        TRY(ValidatePhoneNumber(*phoneNumber));
    }
    if (position) {
        TRY(ValidateField(*position));
    }
    if (emailAddress) {
        TRY(ValidateEmailAddress(*emailAddress));
    }

    std::lock_guard<std::mutex> lock(database_mutex);

    std::ifstream file(database, std::ios::in);
    if (!file)
        return Err(Error{Status::StatusInternalServerError, "Cannot open " + database});

    std::vector<Employee> employees;
    std::string line;
    int target_idx = -1;

    for (int i = 0; std::getline(file, line); ++i) {
        std::stringstream ss(line);

        Employee e;
        if (
            std::getline(ss, e.id, ';') &&
            std::getline(ss, e.name, ';') &&
            std::getline(ss, e.phoneNumber, ';') &&
            std::getline(ss, e.position, ';') &&
            std::getline(ss, e.emailAddress, ';')
        ) {
            employees.push_back(e);
            if (e.id == id) target_idx = i;
        } else {
            return Err(Error{Status::StatusInternalServerError, "Fail to parse data"});
        }
    }

    file.close();

    if (target_idx < 0)
        return Err(Error{Status::StatusNotFound, "Id not found"});

    auto &e = employees[target_idx];
    if (name) {
        e.name = *name;
    }
    if (phoneNumber) {
        e.phoneNumber = *phoneNumber;
    }
    if (position) {
        e.position = *position;
    }
    if (emailAddress) {
        e.emailAddress = *emailAddress;
    }

    std::ofstream outfile(database, std::ios::out | std::ios::trunc);
    if (!outfile)
        return Err(Error{Status::StatusInternalServerError, "Cannot open " + database});

    for (auto &e: employees) {
        outfile << fmt::format("{};{};{};{};{}\n", e.id, e.name, e.phoneNumber, e.position, e.emailAddress);
    }
    outfile.close();

    return Ok(e);
}
