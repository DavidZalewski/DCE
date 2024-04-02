#include "pch.h"
#include "CppUnitTest.h"
#include "../DCE_Engine/structs.h"
#include "../DCE_Engine/entity.h"
#include "../DCE_Engine/psychological_profile.h"
#include "../DCE_Engine/weapon_skill.h"
#include "../DCE_Engine/leadership_morale.h"
#include "../DCE_Engine/singleton_base.h"

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

		TEST_METHOD(NetworkSynchronization_Construct_Success) {
			NetworkSynchronization sync(true, false, true, false);
			Assert::IsTrue(sync.isPlayer);
			Assert::IsFalse(sync.isLocal);
			Assert::IsTrue(sync.isMultiplayer);
			Assert::IsFalse(sync.isGlobal);
		}

		TEST_METHOD(AbstractBaseClassSingleton_Construct_Success) {
			SingletonBase& singleton = SingletonBase::getInstance();
			singleton.sharedProperty1 = 123;
			singleton.sharedProperty2 = 346;

			ChildClass1 child1;
			ChildClass2 child2;

			child1.modifySharedProperty1(10);
			child2.modifySharedProperty2(20);

			std::cout << "Shared Property 1: " << child1.getSharedProperty1() << std::endl;
			std::cout << "Shared Property 2: " << child2.getSharedProperty2() << std::endl;

			Assert::IsNotNull(&singleton);
		}

		TEST_METHOD(Unit_And_Relationship_Construct_Success) {
			PsychologicalProfile profile(0.5f, 0.7f, 0.3f);
			WeaponSkill skill(0.8f, 10.0f, 20.0f, 0.6f);
			LeadershipMorale morale(-0.5f, 0.7f, 0.8f, 0.3f, 0.9f);
			float latitude = 40.712784;
			float longitude = -74.005941;
			Location l = { latitude, longitude };

			Unit u = { 1, Faction::BLUE, "Joe", "Ocazio", "Cortez", 33, profile, std::vector<Relationship>(), Rank::PLATOON_LEADER, 
			skill, morale, CombatStatus::CALM, 0.5f, l, true, std::vector<Unit>(), std::map<Unit, float>(), 0.5f};

			Assert::IsNotNull(&u);

			Relationship r = { &u, RelationshipType::CLOSE, 0.8 };

			Assert::IsNotNull(&r);
		}

		TEST_METHOD(Buddy_Construct_Success) {
			PsychologicalProfile profile(0.5f, 0.7f, 0.3f);
			WeaponSkill skill(0.8f, 10.0f, 20.0f, 0.6f);
			LeadershipMorale morale(-0.5f, 0.7f, 0.8f, 0.3f, 0.9f);
			Location l = { 40.712784, -74.005941 };

			Unit u1 = { 1, Faction::BLUE, "Joe", "Ocazio", "Cortez", 33, profile, std::vector<Relationship>(), Rank::PLATOON_LEADER,
			skill, morale, CombatStatus::CALM, 0.5f, l, true, std::vector<Unit>(), std::map<Unit, float>(), 0.5f };

			Unit u2 = { 2, Faction::BLUE, "David", "M", "Hartmann", 33, profile, std::vector<Relationship>(), Rank::SQUAD_LEADER,
			skill, morale, CombatStatus::CALM, 0.5f, l, true, std::vector<Unit>(), std::map<Unit, float>(), 0.5f };

			Buddy b(Faction::BLUE, &u1, &u2, 0.6f);

			Assert::IsNotNull(&b);
		}

		TEST_METHOD(FireTeam_Construct_Success) {
			PsychologicalProfile profile(0.5f, 0.7f, 0.3f);
			WeaponSkill skill(0.8f, 10.0f, 20.0f, 0.6f);
			LeadershipMorale morale(-0.5f, 0.7f, 0.8f, 0.3f, 0.9f);
			Location l = { 40.712784, -74.005941 };

			Unit u1 = { 1, Faction::BLUE, "Joe", "Ocazio", "Cortez", 33, profile, std::vector<Relationship>(), Rank::SQUAD_LEADER,
			skill, morale, CombatStatus::CALM, 0.5f, l, true, std::vector<Unit>(), std::map<Unit, float>(), 0.5f };

			Unit u2 = { 2, Faction::BLUE, "David", "M", "Hartmann", 33, profile, std::vector<Relationship>(), Rank::ASSISTANT_AUTOMATIC_RIFLEMAN,
			skill, morale, CombatStatus::CALM, 0.5f, l, true, std::vector<Unit>(), std::map<Unit, float>(), 0.5f };

			Unit u3 = { 3, Faction::BLUE, "Blaine", "Roy", "Feltz", 33, profile, std::vector<Relationship>(), Rank::AUTOMATIC_RIFLEMAN,
			skill, morale, CombatStatus::CALM, 0.5f, l, true, std::vector<Unit>(), std::map<Unit, float>(), 0.5f };

			Unit u4 = { 4, Faction::BLUE, "Malarkey", "", "Toatrs", 33, profile, std::vector<Relationship>(), Rank::RIFLEMAN,
			skill, morale, CombatStatus::CALM, 0.5f, l, true, std::vector<Unit>(), std::map<Unit, float>(), 0.5f };

			Buddy b1(Faction::BLUE, &u1, &u2, 0.6f);
			Buddy b2(Faction::BLUE, &u3, &u4, 0.5f);

			FireTeam ft(&u1, &u1, &u3, &u2, &u4, b1, b2);

			Assert::IsNotNull(&ft);
		}

		TEST_METHOD(Squad_Construct_Success) {
			PsychologicalProfile profile(0.5f, 0.7f, 0.3f);
			WeaponSkill skill(0.8f, 10.0f, 20.0f, 0.6f);
			LeadershipMorale morale(-0.5f, 0.7f, 0.8f, 0.3f, 0.9f);
			Location l = { 40.712784, -74.005941 };

			Unit u1 = { 1, Faction::BLUE, "Joe", "Ocazio", "Cortez", 33, profile, std::vector<Relationship>(), Rank::SQUAD_LEADER,
			skill, morale, CombatStatus::CALM, 0.5f, l, true, std::vector<Unit>(), std::map<Unit, float>(), 0.5f };

			Unit u2 = { 2, Faction::BLUE, "David", "M", "Hartmann", 33, profile, std::vector<Relationship>(), Rank::ASSISTANT_AUTOMATIC_RIFLEMAN,
			skill, morale, CombatStatus::CALM, 0.5f, l, true, std::vector<Unit>(), std::map<Unit, float>(), 0.5f };

			Unit u3 = { 3, Faction::BLUE, "Blaine", "Roy", "Feltz", 33, profile, std::vector<Relationship>(), Rank::AUTOMATIC_RIFLEMAN,
			skill, morale, CombatStatus::CALM, 0.5f, l, true, std::vector<Unit>(), std::map<Unit, float>(), 0.5f };

			Unit u4 = { 4, Faction::BLUE, "Malarkey", "", "Toatrs", 33, profile, std::vector<Relationship>(), Rank::RIFLEMAN,
			skill, morale, CombatStatus::CALM, 0.5f, l, true, std::vector<Unit>(), std::map<Unit, float>(), 0.5f };

			Buddy b1(Faction::BLUE, &u1, &u2, 0.6f);
			Buddy b2(Faction::BLUE, &u3, &u4, 0.5f);

			FireTeam ft1(&u1, &u1, &u3, &u2, &u4, b1, b2);



			Unit u5 = { 5, Faction::BLUE, "Joe", "Ocazio", "Cortez", 33, profile, std::vector<Relationship>(), Rank::FIRE_TEAM_LEADER,
			skill, morale, CombatStatus::CALM, 0.5f, l, true, std::vector<Unit>(), std::map<Unit, float>(), 0.5f };

			Unit u6 = { 6, Faction::BLUE, "David", "M", "Hartmann", 33, profile, std::vector<Relationship>(), Rank::ASSISTANT_AUTOMATIC_RIFLEMAN,
			skill, morale, CombatStatus::CALM, 0.5f, l, true, std::vector<Unit>(), std::map<Unit, float>(), 0.5f };

			Unit u7 = { 7, Faction::BLUE, "Blaine", "Roy", "Feltz", 33, profile, std::vector<Relationship>(), Rank::AUTOMATIC_RIFLEMAN,
			skill, morale, CombatStatus::CALM, 0.5f, l, true, std::vector<Unit>(), std::map<Unit, float>(), 0.5f };

			Unit u8 = { 8, Faction::BLUE, "Malarkey", "", "Toatrs", 33, profile, std::vector<Relationship>(), Rank::RIFLEMAN,
			skill, morale, CombatStatus::CALM, 0.5f, l, true, std::vector<Unit>(), std::map<Unit, float>(), 0.5f };

			Buddy b3(Faction::BLUE, &u1, &u2, 0.6f);
			Buddy b4(Faction::BLUE, &u3, &u4, 0.5f);

			FireTeam ft2(&u1, &u5, &u7, &u6, &u8, b3, b4);

			// will use the fireteam declarations later

			Squad squad(&u1);

			Assert::IsNotNull(&squad);
		}

		TEST_METHOD(Platoon_Construct_Success) {
			PsychologicalProfile profile(0.5f, 0.7f, 0.3f);
			WeaponSkill skill(0.8f, 10.0f, 20.0f, 0.6f);
			LeadershipMorale morale(-0.5f, 0.7f, 0.8f, 0.3f, 0.9f);
			Location l = { 40.712784, -74.005941 };

			Unit u1 = { 1, Faction::BLUE, "Joe", "Ocazio", "Cortez", 33, profile, std::vector<Relationship>(), Rank::PLATOON_LEADER,
			skill, morale, CombatStatus::CALM, 0.5f, l, true, std::vector<Unit>(), std::map<Unit, float>(), 0.5f };

			Platoon platoon(&u1);

			Assert::IsNotNull(&platoon);
		}

		TEST_METHOD(Company_Construct_Success) {
			PsychologicalProfile profile(0.5f, 0.7f, 0.3f);
			WeaponSkill skill(0.8f, 10.0f, 20.0f, 0.6f);
			LeadershipMorale morale(-0.5f, 0.7f, 0.8f, 0.3f, 0.9f);
			Location l = { 40.712784, -74.005941 };

			Unit u1 = { 1, Faction::BLUE, "Joe", "Ocazio", "Cortez", 33, profile, std::vector<Relationship>(), Rank::COMPANY_COMMANDER,
			skill, morale, CombatStatus::CALM, 0.5f, l, true, std::vector<Unit>(), std::map<Unit, float>(), 0.5f };

			Company company(&u1);

			Assert::IsNotNull(&company);
		}

		TEST_METHOD(Order_Construct_Success) {
			std::function<bool()> lambda = [] { return true; };
			Order::Condition condition = lambda;
			OrderType orderType = OrderType::MOVE;
			Location location = { 40.323233, -70.113040 }; // Assuming Location has a default constructor
			Order* previousOrder = nullptr;
			Order* nextOrder = nullptr;
			Unit* unit = nullptr; // Assuming Unit has a default constructor

			Order order(condition, orderType, location, previousOrder, nextOrder, unit);

			Assert::IsNotNull(&order);
		}

		TEST_METHOD(CombatEvent_Construct_Success) {
			MockCombatEvent ce(1, Location{ 40.111222, -70.717059 });

			Assert::IsNotNull(&ce);
		}

		TEST_METHOD(MockCombatFrame_Construct_Success) {
			MockCombatEvent ce(1, Location{ 40.111222, -70.717059 });
			MockCombatFrame cf = MockCombatFrame();

			Assert::IsNotNull(&cf);
			cf.apply(ce);
			Assert::IsTrue(cf.WAS_CALLED);
		}
	};
}
