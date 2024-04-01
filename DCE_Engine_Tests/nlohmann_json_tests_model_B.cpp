#include "pch.h"
#include "CppUnitTest.h"

#include <nlohmann/json.hpp>

#include <iostream>
#include <fstream> 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace nlohmann_json_tests_model_b
{
    struct Person {
        std::string name;
        int age;
    };

    void serialize_example() {
        Person person = { "John Doe", 30 };
        nlohmann::json j = person; // automatic serialization
        std::ofstream file("person.json");
        file << j;
    }
    
    void deserialize_example() {
        std::ifstream file("person.json");
        nlohmann::json j;
        file >> j;
        Person person = j.get<Person>();
    }

    int main() {
        serialize_example();
        deserialize_example();

        return 0;
    }

    TEST_CLASS(NLOHMANN_JSON_TESTS_MODEL_B)
    {
    public:

        TEST_METHOD(Example_Success)
        {
            Assert::AreEqual(0, main());
        }
    };
}



