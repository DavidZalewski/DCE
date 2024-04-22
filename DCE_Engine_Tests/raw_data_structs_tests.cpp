#include "pch.h"
#include "CppUnitTest.h"
#include "../DCE_Engine/raw_data_structs.h"
#include <nlohmann/json.hpp>


#include <iostream>
#include <fstream> 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

namespace EngineTests
{
	TEST_CLASS(RawStructsTests)
	{
	public:

		TEST_METHOD(Serialize_RawStructs_Success)
		{
			std::vector<Unit> RawUnits = std::vector<Unit>();
			std::vector<Buddy> Buddies = std::vector<Buddy>();
			std::vector<FireTeam> FireTeams = std::vector<FireTeam>();
			std::vector<Squad> Squads = std::vector<Squad>();
			std::vector<Platoon> Platoons = std::vector<Platoon>();
			std::vector<Company> Companies = std::vector<Company>();

			for (int i = 0; i < NUM_UNITS; i++)
				RawUnits.push_back(CreateUnit());

			Assert::AreEqual((size_t)NUM_UNITS, RawUnits.size());

			int i = 0;
			while (i < NUM_UNITS) {
				int unit1Id = i + 1;
				int unit2Id = i + 2;
				if (unit2Id > NUM_UNITS)
					break;

				Buddies.push_back(CreateBuddy(unit1Id, unit2Id));
				i += 2;
			}

			Assert::AreEqual((size_t)44, Buddies.size());

			i = 0;
			while (i < Buddies.size())
			{
				if (i + 1 >= Buddies.size())
					break;

				Buddy b1 = Buddies.at(i);
				Buddy b2 = Buddies.at(i + 1);

				int buddy1Id = b1.buddy_id;
				int buddy2Id = b2.buddy_id;
				int fireTeamLeaderId = b1.unit_one_id;
				int automaticRifleManId = b1.unit_two_id;
				int assistantAutomaticRifleManId = b2.unit_one_id;
				int rifleManId = b2.unit_two_id;
				int squadLeaderId = 717; // PLACEHOLDER
				FireTeam ft = { ++_fireTeamID, buddy1Id, buddy2Id, fireTeamLeaderId, automaticRifleManId, assistantAutomaticRifleManId, rifleManId, squadLeaderId };
				FireTeams.push_back(ft);

				i += 2;
			}

			i = 0;

			while (i < FireTeams.size())
			{
				if (i + 1 >= FireTeams.size())
					break;

				int ftId1 = FireTeams.at(i).id;
				int ftId2 = FireTeams.at(i + 1).id;
				int squadLeaderId = 717; // PLACEHOLDER
				int platoonLeaderId = 818; // PLACEHOLDER
				std::vector<int> ftIds = std::vector<int>();
				ftIds.push_back(ftId1);
				ftIds.push_back(ftId2);
				Squad squad = { ++_squadID, ftIds, squadLeaderId, platoonLeaderId };
				Squads.push_back(squad);

				i += 2;
			}

			i = 0;

			while (i < Squads.size())
			{
				if (i + 1 >= Squads.size())
					break;

				int platoonLeaderId = 818; // PLACEHOLDER
				int companyCommanderId = 919; // PLACEHOLDER
				std::vector<int> squadIds = std::vector<int>();
				squadIds.push_back(Squads.at(i).id);
				squadIds.push_back(Squads.at(i + 1).id);
				Platoon platoon = { ++_platoonID, squadIds, platoonLeaderId, companyCommanderId };
				Platoons.push_back(platoon);

				i += 2;
			}

			i = 0;

			while (i < Platoons.size())
			{
				if (i + 1 >= Platoons.size())
					break;

				int companyCommanderId = 919; // PLACEHOLDER
				std::vector<int> platoonIds = std::vector<int>();
				platoonIds.push_back(Platoons.at(i).id);
				platoonIds.push_back(Platoons.at(i + 1).id);
				Company company = { ++_companyID, platoonIds, companyCommanderId };
				Companies.push_back(company);

				i += 2;
			}

			std::vector<Entity> Entities = std::vector<Entity>();
			Entities.push_back(Entity{ 1, EntityType::TOWN, "A small town", 44.113948, -120.313453, 0.5, 0.8 });
			Entities.push_back(Entity{ 2, EntityType::AIRFIELD, "Airfield", 42.123448, -150.111555, 0.7, 0.9 });
			Entities.push_back(Entity{ 3, EntityType::HILL, "A small hill", 43.757839, -124.983743, 0.3, 0.5 });
			Entities.push_back(Entity{ 4, EntityType::ROAD_JUNCTION, "A road junction", 40.938284, -112.858434, 0.6, 0.5 });
			Entities.push_back(Entity{ 5, EntityType::BRIDGE, "A small bridge", 44.113948, -120.313453, 0.5, 0.8 });

			Game game = { RawUnits, Buddies, FireTeams, Squads, Platoons, Companies, Entities };

			// ... fill in game data ...
			ordered_json j = ordered_json();
			to_json(j, game);
			std::string json_string = j.dump(4);
			Assert::IsNotNull(&json_string);

			std::ofstream("raw_data_structs_data.json") << j;
			std::ofstream("raw_data_structs_data_pretty.json") << json_string;
		}

		TEST_METHOD(Deserialize_RawStructs_Success)
		{
			std::ifstream file("raw_data_structs_data_pretty.json");
			ordered_json j;
			file >> j;

			Game game;
			from_json(j, game);

			Assert::IsTrue(!game.RawUnits.empty());
			Assert::IsTrue(!game.Buddies.empty());
			Assert::IsTrue(!game.FireTeams.empty());
			Assert::IsTrue(!game.Squads.empty());
			Assert::IsTrue(!game.Platoons.empty());
			Assert::IsTrue(!game.Companies.empty());
		}

	private:
		int _unitID = 0;
		int _buddyID = 0;
		int _fireTeamID = 0;
		int _squadID = 0;
		int _platoonID = 0;
		int _companyID = 0;
		const int NUM_UNITS = 88;
		const int NUM_BUDDIES = 44;
		const int NUM_FIRETEAMS = 11;
		const int NUM_SQUADS = 4;

		Profile CreateProfile() {
			Profile profile = { 0.5f, 0.7f, 0.3f };
			return profile;
		}

		Skill CreateSkill() {
			Skill skill = { 0.8f, 10.0f, 20.0f, 0.6f };
			return skill;
		}

		Unit CreateUnit() {
			Unit u = { ++_unitID, "BLUE", "John", "M", "Hartmann", 33, CreateProfile(), CreateSkill() };
			return u;
		}

		Buddy CreateBuddy(int unit1Id, int unit2Id) {
			Buddy b = { ++_buddyID, unit1Id, unit2Id, 0.5f };
			return b;
		}


	};
}