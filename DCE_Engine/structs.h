#pragma once
#include <cstdint>
#include <vector>
#include <map>
#include <string>

#include "entity.h"
#include "leadership_morale.h"
#include "weapon_skill.h"
#include "psychological_profile.h"
#include <functional>

enum EntityType { BRIDGE, TOWN, ROAD_JUNCTION };
enum Faction { RED, BLUE, CIV, NONE };
enum Rank {
    COMPANY_COMMANDER = 14,
    PLATOON_LEADER = 13,
    PLATOON_NCO = 12,
    PLATOON_OFFICER = 11,
    SQUAD_LEADER = 10,
    DETACHMENT_LEADER = SQUAD_LEADER,
    FIRE_TEAM_LEADER = 9,
    AUTOMATIC_RIFLEMAN = 8,
    ASSISTANT_AUTOMATIC_RIFLEMAN = 7,
    RIFLEMAN = 6
};
enum CombatStatus { CARELESS, CALM, COMBAT_AWARE, STEALTH, COMBAT, SUPPRESSED, PINNED };
enum RelationshipType { UNKNOWN, KNOWN, CLOSE, AT_ODDS };

struct Location {
    float latitude;
    float longitude;
};

struct RawEntity {
    long id;
    EntityType type;
    std::string name;
    float lat;
    float lon;
    float value;
    float size;
};

struct EntityGraph {
    float value;
    Entity* nearbyEntity;
};

struct NetworkSynchronization {
    NetworkSynchronization(bool isPlayer, bool isLocal, bool isMultiplayer, bool isGlobal)
        : isPlayer(isPlayer), isLocal(isLocal), isMultiplayer(isMultiplayer), isGlobal(isGlobal) {}

    bool isPlayer;
    bool isLocal;
    bool isMultiplayer;
    bool isGlobal;
};

// Forward declare
struct Unit;

// Struct for Relationship
struct Relationship {
    Unit* unit;
    RelationshipType type;
    float value;
};

// Struct for Unit
struct Unit {
    int unit_id;
    Faction faction;
    std::string first_name;
    std::string middle_name;
    std::string last_name;
    int age;
    PsychologicalProfile psychological_profile;
    std::vector<Relationship> relationships;
    Rank rank;
    WeaponSkill weapon_skill;
    LeadershipMorale leadership_morale;
    CombatStatus combat_status;
    float fire_rate_aggressiveness;
    Location location;
    bool alive;
    std::vector<Unit> whoDoTheyBelieveIsStillAliveOnTheirSide;
    std::map<Unit, float> knowsAbout;
    float group_cohesion;
};

class Buddy {
public:
    Faction faction; // what side they belong to
    Unit* buddy1; // pointer to Unit
    Unit* buddy2; // pointer to Unit
    float cohesion; // how effective they work together

    Buddy(Faction faction, Unit* buddy1, Unit* buddy2, float cohesion)
        : faction(faction), buddy1(buddy1), buddy2(buddy2), cohesion(cohesion) {}
};

class IChainOfCommand {
public:
    virtual std::string getSuperiorUnit() = 0; // get the superior in charge
    virtual std::string getLeaderUnit() = 0; // get the Chain of Command leader of this team
    virtual std::string getLeaderRole() = 0; // get their specialized role description
    virtual std::map<std::string, Unit*> AllUnits() = 0; // key: ROLE, unit: Unit
    virtual std::vector<Unit*> getAllUnitsExceptLeader() = 0; // list of pointers to map
    virtual std::vector<std::string> getAllRoles() = 0; // get_keys equivalent
    virtual std::vector<Buddy*> getAllBuddies() = 0; // get all buddies
};

class FireTeam : public IChainOfCommand {
public:
    Unit* SquadLeader; // who is your squad leader?
    Unit* FireTeamLeader;
    Unit* AutomaticRifleman;
    Unit* AssistantAutomaticRifleman;
    Unit* Rifleman;
    Buddy BuddyTeamOne;
    Buddy BuddyTeamTwo;

    FireTeam(Unit* SquadLeader, Unit* FireTeamLeader, Unit* AutomaticRifleman, Unit* AssistantAutomaticRifleman, Unit* Rifleman, Buddy BuddyTeamOne, Buddy BuddyTeamTwo)
        : SquadLeader(SquadLeader), FireTeamLeader(FireTeamLeader), AutomaticRifleman(AutomaticRifleman), AssistantAutomaticRifleman(AssistantAutomaticRifleman), Rifleman(Rifleman), BuddyTeamOne(BuddyTeamOne), BuddyTeamTwo(BuddyTeamTwo) {}

    std::string getSuperiorUnit() override; // get the superior in charge outside of this team
    std::string getLeaderUnit() override; // get the Chain of Command leader of this team
    std::string getLeaderRole() override; // get their specialized role description
    std::map<std::string, Unit*> AllUnits() override; // key: ROLE, unit: Unit
    std::vector<Unit*> getAllUnitsExceptLeader() override; // list of pointers to map
    std::vector<std::string> getAllRoles() override; // get_keys equivalent
    std::vector<Buddy*> getAllBuddies() override; // get all buddies
};

class Squad : public IChainOfCommand {
public:
    std::vector<FireTeam*> getAllFireTeams; // list of pointers to FireTeam
    Unit* squadLeader; // pointer to Unit in members

    Squad(Unit* squadLeader)
        : squadLeader(squadLeader) {}

    std::string getSuperiorUnit() override; // get the superior in charge outside of this team
    std::string getLeaderUnit() override; // get the Chain of Command leader of this team
    std::string getLeaderRole() override; // get their specialized role description
    std::map<std::string, Unit*> AllUnits() override; // key: ROLE, unit: Unit
    std::vector<Unit*> getAllUnitsExceptLeader() override; // list of pointers to map
    std::vector<std::string> getAllRoles() override; // get_keys equivalent
    std::vector<Buddy*> getAllBuddies() override; // get all buddies
};

class Platoon : public IChainOfCommand {
public:
    std::vector<Squad*> getAllSquads(); // list of pointers to Squad
    Unit* platoonLeader;

    Platoon(Unit* platoonLeader) : platoonLeader(platoonLeader) {}

    std::string getSuperiorUnit() override; // get the superior in charge outside of this team
    std::string getLeaderUnit() override; // get the Chain of Command leader of this team
    std::string getLeaderRole() override; // get their specialized role description
    std::map<std::string, Unit*> AllUnits() override; // key: ROLE, unit: Unit
    std::vector<Unit*> getAllUnitsExceptLeader() override; // list of pointers to map
    std::vector<std::string> getAllRoles() override; // get_keys equivalent
    std::vector<Buddy*> getAllBuddies() override; // get all buddies
};

class Company : public IChainOfCommand {
public:
    std::vector<Platoon*> getAllPlatoons(); // list of pointers to Platoon
    Unit* companyLeader;

    Company(Unit* companyLeader) : companyLeader(companyLeader) {}

    std::string getSuperiorUnit() override; // get the superior in charge outside of this team
    std::string getLeaderUnit() override; // get the Chain of Command leader of this team
    std::string getLeaderRole() override; // get their specialized role description
    std::map<std::string, Unit*> AllUnits() override; // key: ROLE, unit: Unit
    std::vector<Unit*> getAllUnitsExceptLeader() override; // list of pointers to map
    std::vector<std::string> getAllRoles() override; // get_keys equivalent
    std::vector<Buddy*> getAllBuddies() override; // get all buddies
};

enum class OrderType { MOVE, ATTACK, DEFEND, PATROL };
enum class OrderStatus { INCOMPLETE, ENROUTE, FAILED, COMPLETED };

class Order {
public:
    using Condition = std::function<bool()>;

    Order(Condition condition, OrderType orderType, Location location, Order* previousOrder, Order* nextOrder, Unit* unit)
        : condition(condition), orderType(orderType), location(location), previousOrder(previousOrder), nextOrder(nextOrder), unit(unit), status(OrderStatus::INCOMPLETE) {}

    Condition condition;
    OrderType orderType;
    Location location;
    Order* previousOrder;
    Order* nextOrder;
    Unit* unit;
    OrderStatus status;
};

class CombatEvent {
public:
    virtual ~CombatEvent() {}
    long getId() const { return id; }
    const std::string& getDescription() const { return description; }
    const Location& getLocation() const { return location; }
protected:
    CombatEvent(long id, const std::string& description, const Location& location)
        : id(id), description(description), location(location) {}
private:
    long id;
    std::string description;
    Location location;
};

class MockCombatEvent : public CombatEvent {
public:
    MockCombatEvent(long id, const Location& location)
        : CombatEvent(id, "Mock Combat Event", location) {}
};

class IFrame {
public:
    virtual ~IFrame() {}
    virtual void apply(CombatEvent& event) = 0;
};

class CombatFrame : public IFrame {
public:
    void apply(CombatEvent& event) override {
        // Apply changes to the combat event
    }
};

class SquadFrame : public IFrame {
public:
    void apply(CombatEvent& event) override {
        // Apply changes to the combat event
    }
};

class PlatoonFrame : public IFrame {
public:
    void apply(CombatEvent& event) override {
        // Apply changes to the combat event
    }
};

class MockCombatFrame : public CombatFrame {
public:
    bool WAS_CALLED = false;
    // Override virtual methods to provide mock implementation
    void apply(CombatEvent& event) override {
        // Apply changes to the combat event
        WAS_CALLED = true;
    }
};