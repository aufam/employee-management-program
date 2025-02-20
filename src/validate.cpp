#include "employee.h"
#include <delameta/http/http.h>
#include <algorithm>
#include <cctype>
#include <regex>

using namespace Project;
using delameta::Result, delameta::Error;
using delameta::http::Status;
using etl::Ok, etl::Err;

#define CHECK_NOT_EMPTY(field) if (field.empty()) return Err(Error{Status::StatusBadRequest, "Field cannot be empty"})

auto finshot::Employee::ValidateField(const std::string& field) -> Result<void> {
    CHECK_NOT_EMPTY(field);

    for (char ch: field) {
        if (ch == ',') return Err(Error{Status::StatusBadRequest, "Field value cannot contains `,`"});
        if (ch == ';') return Err(Error{Status::StatusBadRequest, "Field value cannot contains `;`"});
    }

    return Ok();
}

auto finshot::Employee::ValidateId(const std::string& id) -> Result<void> {
    CHECK_NOT_EMPTY(id);

    if (id.size() == 3 && std::all_of(id.begin(), id.end(), ::isdigit))
        return Ok();

    return Err(Error{Status::StatusBadRequest, "Id must be a 3 digit numeric"});
}

auto finshot::Employee::ValidatePhoneNumber(const std::string& phone) -> Result<void> {
    CHECK_NOT_EMPTY(phone);

    std::regex phoneRegex(R"(^[0-9]{2,3}-[0-9]{3,4}-[0-9]{4}$)");
    if (std::regex_match(phone, phoneRegex))
        return Ok();

    return Err(Error{Status::StatusBadRequest, "Invalid phone number"});
}

auto finshot::Employee::ValidateEmailAddress(const std::string& email) -> Result<void> {
    CHECK_NOT_EMPTY(email);

    std::regex emailRegex(R"(^[_a-z0-9-]+(\.[_a-z0-9-]+)*@(?:\w+\.)+\w+$)");
    if (std::regex_match(email, emailRegex))
        return Ok();

    return Err(Error{Status::StatusBadRequest, "Invalid email address"});
}
