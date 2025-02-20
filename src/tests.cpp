#include "employee.h"
#include <catch2/catch_test_macros.hpp>
#include <optional>

using namespace Project;

TEST_CASE("Employee", "[field-validation]") {
    REQUIRE(finshot::Employee::ValidateField("").is_err());
    REQUIRE(finshot::Employee::ValidateField("sdsf;sdd").is_err());
    REQUIRE(finshot::Employee::ValidateField("Suprapto").is_ok());

    REQUIRE(finshot::Employee::ValidatePhoneNumber("088123456789").is_err());
    REQUIRE(finshot::Employee::ValidatePhoneNumber("12-234-5678").is_ok());
    REQUIRE(finshot::Employee::ValidatePhoneNumber("123-456-7890").is_ok());
    REQUIRE(finshot::Employee::ValidatePhoneNumber("123-456-789").is_err());

    REQUIRE(finshot::Employee::ValidateEmailAddress("user@example.com").is_ok());
    REQUIRE(finshot::Employee::ValidateEmailAddress("user.name@example.com").is_ok());
    REQUIRE(finshot::Employee::ValidateEmailAddress("user123@example.com").is_ok());
    REQUIRE(finshot::Employee::ValidateEmailAddress("user_name@example.com").is_ok());
    REQUIRE(finshot::Employee::ValidateEmailAddress("user@example.co.uk").is_ok());
    REQUIRE(finshot::Employee::ValidateEmailAddress("user@example.io").is_ok());
    REQUIRE(finshot::Employee::ValidateEmailAddress("longemailaddress1234567890@example.com").is_ok());
    REQUIRE(finshot::Employee::ValidateEmailAddress("user@domain123.com").is_ok());

    REQUIRE(finshot::Employee::ValidateEmailAddress("userexample.com").is_err());        // missing @ symbol
    REQUIRE(finshot::Employee::ValidateEmailAddress("@example.com").is_err());           // missing local part
    REQUIRE(finshot::Employee::ValidateEmailAddress("user@").is_err());                  // missing domain part
    REQUIRE(finshot::Employee::ValidateEmailAddress("User@Example.com").is_err());       // case insensitive
    REQUIRE(finshot::Employee::ValidateEmailAddress("user..name@example.com").is_err()); // consecutive dots in local part
    REQUIRE(finshot::Employee::ValidateEmailAddress(".user@example.com").is_err());      // dot at the start of local part
    REQUIRE(finshot::Employee::ValidateEmailAddress("user.@example.com").is_err());      // dot at the end of local part
    REQUIRE(finshot::Employee::ValidateEmailAddress("user+alias@example.com").is_err()); // invalid character +
    REQUIRE(finshot::Employee::ValidateEmailAddress("user#example.com").is_err());       // invalid character #
    REQUIRE(finshot::Employee::ValidateEmailAddress("user@exam!ple.com").is_err());      // invalid character !
    REQUIRE(finshot::Employee::ValidateEmailAddress("user @example.com").is_err());      // space in email
    REQUIRE(finshot::Employee::ValidateEmailAddress("user@ example.com").is_err());      // space in domain
    REQUIRE(finshot::Employee::ValidateEmailAddress("user@@example.com").is_err());      // double @
    REQUIRE(finshot::Employee::ValidateEmailAddress("user@example").is_err());           // no TLD
    REQUIRE(finshot::Employee::ValidateEmailAddress("user@example..com").is_err());      // double dot in domain
    REQUIRE(finshot::Employee::ValidateEmailAddress("usér@example.com").is_err());       // unicode character
    REQUIRE(finshot::Employee::ValidateEmailAddress("user@-example.com").is_err());      // hyphen at start of domain
    REQUIRE(finshot::Employee::ValidateEmailAddress("user@example-.com").is_err());      // hyphen at end of domain
    REQUIRE(finshot::Employee::ValidateEmailAddress("").is_err());                       // empty string
}

TEST_CASE("Employee", "[api]") {
    SECTION("rename database") {
        finshot::database = "test.txt";
    }

    auto compare = [](const finshot::Employee& self, const finshot::Employee& other) {
        REQUIRE(self.id == other.id);
        REQUIRE(self.phoneNumber == other.phoneNumber);
        REQUIRE(self.position == other.position);
        REQUIRE(self.emailAddress == other.emailAddress);
    };

    SECTION("Create") {
        auto first = finshot::Employee::Add("Slamet", "123-456-7890", "HR Manager", "slamet@example.com").unwrap();
        auto second = finshot::Employee::Add("Jamal", "321-654-0987", "Jr Developer", "jamal@example.com").unwrap();

        REQUIRE(first.id == "001");
        REQUIRE(second.id == "002");

        auto sort_by_id = finshot::Employee::List("id").unwrap();
        auto sort_by_name = finshot::Employee::List("name").unwrap();

        REQUIRE(sort_by_id.size() == 2);
        REQUIRE(sort_by_name.size() == 2);

        compare(sort_by_id[0], first);
        compare(sort_by_id[1], second);
        compare(sort_by_name[1], first);
        compare(sort_by_name[0], second);
    }

    SECTION("Update") {
        auto to_update = finshot::Employee::Edit("002", std::nullopt, std::nullopt, "Sr Developer", std::nullopt).unwrap();
        auto updated = finshot::Employee::View("002").unwrap();
        compare(to_update, updated);
        REQUIRE(updated.position == "Sr Developer");
    }

    SECTION("Delete") {
        finshot::Employee::Delete("001").unwrap();
        auto l = finshot::Employee::List("id").unwrap();
        REQUIRE(l.size() == 1);
        REQUIRE(l.front().id == "002");
    }

    SECTION("remove test file") {
        ::remove("test.txt");
    }
}
