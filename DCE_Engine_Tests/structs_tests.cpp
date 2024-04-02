#include "pch.h"
#include "CppUnitTest.h"
#include "../DCE_Engine/structs.h"
#include "../DCE_Engine/entity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DCEEngineTests
{
	TEST_CLASS(StructsTests)
	{
	public:

		TEST_METHOD(Location_Construct_Success)
		{
			float latitude = 40.712784;
			float longitude = -74.005941;
			Location l = { latitude, longitude };
			Assert::AreEqual(latitude, l.latitude);
			Assert::AreEqual(longitude, l.longitude);
		}

		TEST_METHOD(RawEntity_Construct_Success)
		{
			int64_t id = 1;
			EntityType type = EntityType::BRIDGE;
			std::string name = "Some Bridge";
			float lat = 41.848132;
			float lon = -74.004928;
			float value = 0.6;
			float size = 0.25;
			RawEntity re{ id, type, name, lat, lon, value, size };

			Assert::AreEqual(name, re.name);
		}

		TEST_METHOD(EntityGraph_Construct_Success)
		{
			Entity e = Entity("filename.csv");
			float value = 0.6;
			
			EntityGraph eg{ value, &e };

			Assert::IsNotNull(&e);
		}
	};
}
