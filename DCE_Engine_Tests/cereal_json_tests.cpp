#include "pch.h"
#include "CppUnitTest.h"

#include <cereal/archives/json.hpp>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace cereal_json_tests
{
    struct Data {
        std::string name;
        int age;

        template <class Archive>
        void serialize(Archive& ar) {
            ar(CEREAL_NVP(name), CEREAL_NVP(age));
        }
    };

    int main() {
        // Serialization
        std::ofstream os("cereal_data.json");
        cereal::JSONOutputArchive archive(os);
        Data myData = { "John Doe", 30 };
        archive(myData);


        // Deserialization
        std::ifstream is("cereal_data.json");
        cereal::JSONInputArchive inputArchive(is);
        Data loadedData;
        inputArchive(loadedData);
        // ...
        return 0;
    }

    TEST_CLASS(CEREAL_JSON_TESTS)
    {
    public:

        TEST_METHOD(Example_Success)
        {
            Assert::AreEqual(0, main());
        }
    };
}



