#include "employee.h"
#include <delameta/http/http.h>
#include <fstream>
#include <mutex>

using namespace Project;
using delameta::Result, delameta::Error;
using delameta::http::Status;
using etl::Ok, etl::Err;

std::string finshot::database = "database.txt";
std::mutex finshot::database_mutex;

auto finshot::Employee::Add(
    std::string name,
    std::string phoneNumber,
    std::string position,
    std::string emailAddress
) -> Result<Employee> {
    TRY(Employee::ValidateField(name));
    TRY(Employee::ValidatePhoneNumber(phoneNumber));
    TRY(Employee::ValidateField(position));
    TRY(Employee::ValidateEmailAddress(emailAddress));

    std::lock_guard<std::mutex> lock(database_mutex);

    int max_id = 0;
    std::fstream file(database, std::ios::in | std::ios::out | std::ios::app);
    if (!file)
        return Err(Error{Status::StatusInternalServerError, "Cannot open " + database});

    std::string line;
    while (std::getline(file, line)) {
        try {
            int read_id = std::stoi(line);
            max_id = std::max(max_id, read_id);
        } catch (const std::exception& e) {
            return Err(Error{Status::StatusInternalServerError, "Failed to parse line"});
        }
    }

    int id = max_id + 1;
    if (id >= 1000)
        return Err(Error{Status::StatusInternalServerError, "Database is full"});

    auto id_str = fmt::format("{:03}", id);
    file.clear();
    file.seekp(0, std::ios::end);
    file << fmt::format("{};{};{};{};{}\n", id_str, name, phoneNumber, position, emailAddress);

    return Ok(Employee{
        id_str,
        name,
        phoneNumber,
        position,
        emailAddress,
    });
}
