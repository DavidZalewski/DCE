#include "pch.h"
#include "CppUnitTest.h"

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream> 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EngineTests
{
    struct Data {
        std::string name;
        int age;
    };

    // For serialization with macros (requires C++17)
    void to_json(nlohmann::json& j, const Data& data) {
        j = nlohmann::json{ {"name", data.name}, {"age", data.age} };
    }

    void from_json(const nlohmann::json& j, Data& data) {
        j.at("name").get_to(data.name);
        j.at("age").get_to(data.age);
    }

    int main() {
        Data myData = { "John Doe", 30 };

        nlohmann::json j = myData;
        std::ofstream("data.json") << j;

        // Deserialization
        std::ifstream("data.json") >> j;
        Data loadedData = j;
        // ...

        return 0;
    }

    TEST_CLASS(NLOHMANN_JSON_TESTS)
    {
    public:

        TEST_METHOD(Example_Success)
        {
            Assert::AreEqual(0, main());
        }
    };
}



