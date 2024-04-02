#include "pch.h"
#include "CppUnitTest.h"
#include "../DCE_Engine/structs.h"
#include "../DCE_Engine/entity.h"
#include "../DCE_Engine/psychological_profile.h"
#include "../DCE_Engine/weapon_skill.h"
#include "../DCE_Engine/leadership_morale.h"

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

		TEST_METHOD(PsychologicalProfile_Construct_Success)
		{
			PsychologicalProfile profile(0.5f, 0.7f, 0.3f);
			Assert::AreEqual(0.5f, profile.currentStress);
			Assert::AreEqual(0.7f, profile.stressTolerance);
			Assert::AreEqual(0.3f, profile.stressRecoveryRate);
		}

		TEST_METHOD(WeaponSkill_Construct_Success)
		{
			WeaponSkill skill(0.8f, 10.0f, 20.0f, 0.6f);
			Assert::AreEqual(0.8f, skill.accuracy);
			Assert::AreEqual(10.0f, skill.minimumDamage);
			Assert::AreEqual(20.0f, skill.maximumDamage);
			Assert::AreEqual(0.6f, skill.currentSkill);
		}

		TEST_METHOD(LeadershipMorale_Construct_Success)
		{
			LeadershipMorale morale(-0.5f, 0.7f, 0.8f, 0.3f, 0.9f);
			Assert::AreEqual(-0.5f, morale.currentOpinion);
			Assert::AreEqual(0.7f, morale.decisiveness);
			Assert::AreEqual(0.8f, morale.decisionMaking);
			Assert::AreEqual(0.3f, morale.hesitation);
			Assert::AreEqual(0.9f, morale.offense);
		}
	};
}
