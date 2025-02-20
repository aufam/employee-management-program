#ifndef EMP_H
#define EMP_H

#include <boost/preprocessor.hpp> // enabling advance preprocessor
#include <fmt/format.h>           // fmt trait
#include <fmt/ranges.h>
#include <delameta/json.h>        // JSON_TRAITS
#include <mutex>

namespace Project::finshot {
    /// employee data structure
    struct Employee {
        // fields
        std::string id;
        std::string name;
        std::string phoneNumber;
        std::string position;
        std::string emailAddress;

        /// add new employee into the database.
        /// returns result of employee's id.
        static auto Add(
            std::string name,
            std::string phoneNumber,
            std::string position,
            std::string emailAddress
        ) -> delameta::Result<Employee>;

        //. list all employees and sort by:
        /// `id`, `name`, or `phone-number`
        static auto List(
            std::string sort_by,
            bool ascending = true
        ) -> delameta::Result<std::vector<Employee>>;

        /// view detailed employee information
        static auto View(
            std::string id
        ) -> delameta::Result<Employee>;

        /// edit the corresponding employee
        static auto Edit(
            std::string id,
            std::optional<std::string> name,
            std::optional<std::string> phoneNumber,
            std::optional<std::string> position,
            std::optional<std::string> emailAddress
        ) -> delameta::Result<Employee>;

        /// delete the corresponding employee
        static auto Delete(
            std::string id
        ) -> delameta::Result<void>;

        static auto ValidateField(const std::string& field) -> delameta::Result<void>;
        static auto ValidateId(const std::string& id) -> delameta::Result<void>;
        static auto ValidatePhoneNumber(const std::string& phoneNumber) -> delameta::Result<void>;
        static auto ValidateEmailAddress(const std::string& emailAddress) -> delameta::Result<void>;
    };

    extern std::string database;
    extern std::mutex database_mutex;
}

JSON_TRAITS(
    (Project::finshot::Employee)
    ,
    (, id)
    (, name)
    (, position)
    (, phoneNumber)
    (, emailAddress)
)

/// fmt traits
template<> struct fmt::formatter<Project::finshot::Employee> {
    using Self = Project::finshot::Employee;

    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.end(); }

    template <typename Ctx>
    inline auto format(const Self& self, Ctx& ctx) const {
        return fmt::format_to(ctx.out(),
            "Employee {{id: {}, name: {}, phone-number: {}, position: {}, email-address: {}}}",
            self.id, self.name, self.phoneNumber, self.position, self.emailAddress
        );
    }
};

#endif
