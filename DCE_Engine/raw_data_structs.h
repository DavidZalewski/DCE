#pragma once
#include <string>
#include <vector>
#include "nlohmann/json.hpp"


using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

enum class EntityType {
    BRIDGE,
    ROAD_JUNCTION,
    TOWN,
    AIRFIELD,
    HILL,
    STRONGHOLD
};

// The Entity struct
struct Entity {
    int id;
    EntityType type;
    std::string name;
    float latitude;
    float longitude; // Use 'long' instead of 'longitude' for brevity
    float value;
    float size;
};

struct Profile {
    float currentStress;
    float stressTolerance;
    float stressRecoveryRate;
};

struct Skill {
    float accuracy;
    float minimumDamage;
    float maximumDamage;
    float currentSkill;
};

struct Unit {
    int id;
    std::string faction;
    std::string first_name;
    std::string middle_name;
    std::string last_name;
    int age;
    Profile profile;
    Skill skill;
};

struct Buddy {
    int buddy_id;
    int unit_one_id;
    int unit_two_id;
    float cohesion;
};

struct FireTeam {
    int id;
    int buddy_one_id;
    int buddy_two_id;
    int fire_team_leader_id;
    int automatic_rifleman_id;
    int assistant_automatic_rifleman_id;
    int rifleman_id;
    int squad_leader_id;
};

struct Squad {
    int id;
    std::vector<int> fire_teams_ids;
    int squad_leader_id;
    int platoon_leader_id;
};

struct Platoon {
    int id;
    std::vector<int> squads_ids;
    int platoon_leader_id;
    int company_commander_id;
};

struct Company {
    int id;
    std::vector<int> platoon_ids;
    int company_commander_id;
};

struct Game {
    std::vector<Unit> RawUnits;
    std::vector<Buddy> Buddies;
    std::vector<FireTeam> FireTeams;
    std::vector<Squad> Squads;
    std::vector<Platoon> Platoons;
    std::vector<Company> Companies;
    std::vector<Entity> Entities;
};


// to_json for serialization
void to_json(ordered_json& j, const Entity& e) {
    j = ordered_json{
        {"id", e.id},
        {"type", static_cast<int>(e.type)}, // Convert enum to int for serialization
        {"name", e.name},
        {"latitude", e.latitude},
        {"longitude", e.longitude},
        {"value", e.value},
        {"size", e.size}
    };
}

// from_json for deserialization
void from_json(const ordered_json& j, Entity& e) {
    j.at("id").get_to(e.id);
    e.type = static_cast<EntityType>(j.at("type").get<int>()); // Convert int back to enum
    j.at("name").get_to(e.name);
    j.at("latitude").get_to(e.latitude);
    j.at("longitude").get_to(e.longitude);
    j.at("value").get_to(e.value);
    j.at("size").get_to(e.size);
}


void to_json(ordered_json& j, const Profile& p) {
    j = ordered_json{ {"currentStress", p.currentStress}, {"stressTolerance", p.stressTolerance}, {"stressRecoveryRate", p.stressRecoveryRate} };
}

void to_json(ordered_json& j, const Skill& s) {
    j = ordered_json{ {"accuracy", s.accuracy}, {"minimumDamage", s.minimumDamage}, {"maximumDamage", s.maximumDamage}, {"currentSkill", s.currentSkill} };
}

void to_json(ordered_json& j, const Unit& u) {
    //j = ordered_json::object_t{
    //   {"id", u.id},
    //   {"faction", u.faction},
    //   {"first_name", u.first_name},
    //   {"middle_name", u.middle_name},
    //   {"last_name", u.last_name},
    //   {"age", u.age},
    //   {"profile", u.profile},
    //   {"skill", u.skill}
    //};
    j = ordered_json::object();
    j["id"] = u.id;
    j["faction"] = u.faction;
    j["first_name"] = u.first_name;
    j["middle_name"] = u.middle_name;
    j["last_name"] = u.last_name;
    j["age"] = u.age;
    j["profile"] = u.profile;
    j["skill"] = u.skill;
}

void to_json(ordered_json& j, const Buddy& b) {
    j = ordered_json{ {"buddy_id", b.buddy_id}, {"unit_one_id", b.unit_one_id}, {"unit_two_id", b.unit_two_id}, {"cohesion", b.cohesion} };
}

void to_json(ordered_json& j, const FireTeam& ft) {
    j = ordered_json{ {"id", ft.id}, {"buddy_one_id", ft.buddy_one_id}, {"buddy_two_id", ft.buddy_two_id}, {"fire_team_leader_id", ft.fire_team_leader_id}, {"automatic_rifleman_id", ft.automatic_rifleman_id}, {"assistant_automatic_rifleman_id", ft.assistant_automatic_rifleman_id}, {"rifleman_id", ft.rifleman_id}, {"squad_leader_id", ft.squad_leader_id} };
}

void to_json(ordered_json& j, const Squad& s) {
    j = ordered_json{ {"id", s.id}, {"fire_teams_ids", s.fire_teams_ids}, {"squad_leader_id", s.squad_leader_id}, {"platoon_leader_id", s.platoon_leader_id} };
}

void to_json(ordered_json& j, const Platoon& p) {
    j = ordered_json{ {"id", p.id}, {"squads_ids", p.squads_ids}, {"platoon_leader_id", p.platoon_leader_id}, {"company_commander_id", p.company_commander_id} };
}

void to_json(ordered_json& j, const Company& c) {
    j = ordered_json{ {"id", c.id}, {"platoon_ids", c.platoon_ids}, {"company_commander_id", c.company_commander_id} };
}

void to_json(ordered_json& j, const Game& g) {
    j = ordered_json{ {"RawUnits", g.RawUnits}, {"Buddies", g.Buddies}, {"FireTeams", g.FireTeams}, {"Squads", g.Squads}, {"Platoons", g.Platoons}, {"Companies", g.Companies}, {"Entities", g.Entities} };
}



void from_json(const ordered_json& j, Profile& p) {
    j.at("currentStress").get_to(p.currentStress);
    j.at("stressTolerance").get_to(p.stressTolerance);
    j.at("stressRecoveryRate").get_to(p.stressRecoveryRate);
}

void from_json(const ordered_json& j, Skill& s) {
    j.at("accuracy").get_to(s.accuracy);
    j.at("minimumDamage").get_to(s.minimumDamage);
    j.at("maximumDamage").get_to(s.maximumDamage);
    j.at("currentSkill").get_to(s.currentSkill);
}

void from_json(const ordered_json& j, Unit& u) {
    j.at("id").get_to(u.id);
    j.at("faction").get_to(u.faction);
    j.at("first_name").get_to(u.first_name);
    j.at("middle_name").get_to(u.middle_name);
    j.at("last_name").get_to(u.last_name);
    j.at("age").get_to(u.age);
    j.at("profile").get_to(u.profile);
    j.at("skill").get_to(u.skill);
}

void from_json(const ordered_json& j, Buddy& b) {
    j.at("buddy_id").get_to(b.buddy_id);
    j.at("unit_one_id").get_to(b.unit_one_id);
    j.at("unit_two_id").get_to(b.unit_two_id);
    j.at("cohesion").get_to(b.cohesion);
}

void from_json(const ordered_json& j, FireTeam& ft) {
    j.at("id").get_to(ft.id);
    j.at("buddy_one_id").get_to(ft.buddy_one_id);
    j.at("buddy_two_id").get_to(ft.buddy_two_id);
    j.at("fire_team_leader_id").get_to(ft.fire_team_leader_id);
    j.at("automatic_rifleman_id").get_to(ft.automatic_rifleman_id);
    j.at("assistant_automatic_rifleman_id").get_to(ft.assistant_automatic_rifleman_id);
    j.at("rifleman_id").get_to(ft.rifleman_id);
    j.at("squad_leader_id").get_to(ft.squad_leader_id);
}

void from_json(const ordered_json& j, Squad& s) {
    j.at("id").get_to(s.id);
    j.at("fire_teams_ids").get_to(s.fire_teams_ids);
    j.at("squad_leader_id").get_to(s.squad_leader_id);
    j.at("platoon_leader_id").get_to(s.platoon_leader_id);
}

void from_json(const ordered_json& j, Platoon& p) {
    j.at("id").get_to(p.id);
    j.at("squads_ids").get_to(p.squads_ids);
    j.at("platoon_leader_id").get_to(p.platoon_leader_id);
    j.at("company_commander_id").get_to(p.company_commander_id);
}

void from_json(const ordered_json& j, Company& c) {
    j.at("id").get_to(c.id);
    j.at("platoon_ids").get_to(c.platoon_ids);
    j.at("company_commander_id").get_to(c.company_commander_id);
}

void from_json(const ordered_json& j, Game& g) {
    j.at("RawUnits").get_to(g.RawUnits);
    j.at("Buddies").get_to(g.Buddies);
    j.at("FireTeams").get_to(g.FireTeams);
    j.at("Squads").get_to(g.Squads);
    j.at("Platoons").get_to(g.Platoons);
    j.at("Companies").get_to(g.Companies);
    j.at("Entities").get_to(g.Entities);
}


