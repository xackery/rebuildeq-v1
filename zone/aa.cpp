/*	EQEMu: Everquest Server Emulator
Copyright (C) 2001-2016 EQEMu Development Team (http://eqemulator.net)

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; version 2 of the License.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY except by those people which sell it, which
	are required to give you total support for your newly bought product;
	without even the implied warranty of MERCHANTABILITY or FITNESS FOR
	A PARTICULAR PURPOSE. See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include "../common/classes.h"
#include "../common/global_define.h"
#include "../common/eqemu_logsys.h"
#include "../common/eq_packet_structs.h"
#include "../common/races.h"
#include "../common/spdat.h"
#include "../common/string_util.h"
#include "aa.h"
#include "client.h"
#include "corpse.h"
#include "groups.h"
#include "mob.h"
#include "queryserv.h"
#include "raids.h"
#include "string_ids.h"
#include "titles.h"
#include "zonedb.h"

extern QueryServ* QServ;

void Mob::TemporaryPets(uint16 spell_id, Mob *targ, const char *name_override, uint32 duration_override, bool followme, bool sticktarg) {

	//It might not be a bad idea to put these into the database, eventually..

	//Dook- swarms and wards

	// do nothing if it's a corpse
	if (targ != nullptr && targ->IsCorpse())
		return;

	// yep, even these need pet power!
	int act_power = 0;

	if (IsClient()) {
		act_power = CastToClient()->GetFocusEffect(focusPetPower, spell_id);
		act_power = CastToClient()->mod_pet_power(act_power, spell_id);
	}

	PetRecord record;
	if (!database.GetPoweredPetEntry(spells[spell_id].teleport_zone, act_power, &record))
	{
		Log(Logs::General, Logs::Error, "Unknown swarm pet spell id: %d, check pets table", spell_id);
		Message(13, "Unable to find data for pet %s", spells[spell_id].teleport_zone);
		return;
	}

	SwarmPet_Struct pet;
	pet.count = 1;
	pet.duration = 1;

	for (int x = 0; x < MAX_SWARM_PETS; x++)
	{
		if (spells[spell_id].effectid[x] == SE_TemporaryPets)
		{
			if(spell_id == 3265 && CastToClient()->GetBuildRank(MAGICIAN, RB_MAG_SERVANTOFRO) > 0) {
				pet.count = spells[spell_id].base[x];
				pet.duration = spells[spell_id].max[x] * (CastToClient()->GetBuildRank(MAGICIAN, RB_MAG_SERVANTOFRO) / 5.0f);
			} else if(spell_id == 13167 && CastToClient()->GetBuildRank(MAGICIAN, RB_MAG_COMPANIONOFNECESSITY) > 0) {
				pet.count = spells[spell_id].base[x];
				pet.duration = spells[spell_id].max[x] * (CastToClient()->GetBuildRank(MAGICIAN, RB_MAG_COMPANIONOFNECESSITY) / 5.0f);
			} else {
				pet.count = spells[spell_id].base[x];
				pet.duration = spells[spell_id].max[x];
			}
		}
	}

	pet.duration += GetFocusEffect(focusSwarmPetDuration, spell_id) / 1000;

	pet.npc_id = record.npc_type;

	NPCType *made_npc = nullptr;

	const NPCType *npc_type = database.LoadNPCTypesData(pet.npc_id);
	if (npc_type == nullptr) {
		//log write
		Log(Logs::General, Logs::Error, "Unknown npc type for swarm pet spell id: %d", spell_id);
		Message(0, "Unable to find pet!");
		return;
	}

	if (name_override != nullptr) {
		//we have to make a custom NPC type for this name change
		made_npc = new NPCType;
		memcpy(made_npc, npc_type, sizeof(NPCType));
		strcpy(made_npc->name, name_override);
		npc_type = made_npc;
	}

	
	if (IsClient() && spell_id == 4828) {
		auto swarm_editable = new NPCType;
		memcpy(swarm_editable, npc_type, sizeof(NPCType));
		int rank = CastToClient()->GetBuildRank(SHAMAN, RB_SHM_CALLOFTHEANCIENTS);
		if (rank > 0) {
			swarm_editable->level = CastToClient()->GetLevel();
			swarm_editable = this->AdjustNPC(swarm_editable, true, true);
			//Now that we generated base HP, let's nerf it on a new formula
			swarm_editable->max_hp = floor(npc_type->max_hp * 0.2f * rank); //50 % of normal hp
			if (swarm_editable->max_hp < 50) {
				swarm_editable->max_hp = 50;
			}
			swarm_editable->AC = floor(npc_type->AC * 0.1f * rank); 
			swarm_editable->size = floor(rank * (GetLevel() / 50)); 
			swarm_editable->attack_count = 1;

			duration_override = 60; //60 second duration for COTA pet
			if (GetTarget() != nullptr) targ = GetTarget(); //the shaman's target
			
			made_npc = swarm_editable;
		}
	}

	int summon_count = 0;
	summon_count = pet.count;

	if (summon_count > MAX_SWARM_PETS)
		summon_count = MAX_SWARM_PETS;

	static const glm::vec2 swarmPetLocations[MAX_SWARM_PETS] = {
		glm::vec2(5, 5), glm::vec2(-5, 5), glm::vec2(5, -5), glm::vec2(-5, -5),
		glm::vec2(10, 10), glm::vec2(-10, 10), glm::vec2(10, -10), glm::vec2(-10, -10),
		glm::vec2(8, 8), glm::vec2(-8, 8), glm::vec2(8, -8), glm::vec2(-8, -8)
	};

	while (summon_count > 0) {
		int pet_duration = pet.duration;
		if (duration_override > 0)
			pet_duration = duration_override;

		//this is a little messy, but the only way to do it right
		//it would be possible to optimize out this copy for the last pet, but oh well
		NPCType *npc_dup = nullptr;
		if (made_npc != nullptr) {
			npc_dup = new NPCType;
			memcpy(npc_dup, made_npc, sizeof(NPCType));
		}

		NPC* swarm_pet_npc = new NPC(
			(npc_dup != nullptr) ? npc_dup : npc_type,	//make sure we give the NPC the correct data pointer
			0,
			GetPosition() + glm::vec4(swarmPetLocations[summon_count], 0.0f, 0.0f),
			FlyMode3);

		if (followme)
			swarm_pet_npc->SetFollowID(GetID());

		if (!swarm_pet_npc->GetSwarmInfo()) {
			auto nSI = new SwarmPet;
			swarm_pet_npc->SetSwarmInfo(nSI);
			swarm_pet_npc->GetSwarmInfo()->duration = new Timer(pet_duration * 1000);
		}
		else {
			swarm_pet_npc->GetSwarmInfo()->duration->Start(pet_duration * 1000);
		}

		swarm_pet_npc->StartSwarmTimer(pet_duration * 1000);

		//removing this prevents the pet from attacking
		swarm_pet_npc->GetSwarmInfo()->owner_id = GetID();

		//give the pets somebody to "love"
		if (targ != nullptr) {
			swarm_pet_npc->AddToHateList(targ, 1000, 1000);
			if (RuleB(Spells, SwarmPetTargetLock) || sticktarg)
				swarm_pet_npc->GetSwarmInfo()->target = targ->GetID();
			else
				swarm_pet_npc->GetSwarmInfo()->target = 0;
		}

		//we allocated a new NPC type object, give the NPC ownership of that memory
		if (npc_dup != nullptr)
			swarm_pet_npc->GiveNPCTypeData(npc_dup);

		entity_list.AddNPC(swarm_pet_npc, true, true);
		summon_count--;
	}

	//the target of these swarm pets will take offense to being cast on...
	if (targ != nullptr)
		targ->AddToHateList(this, 1, 0);

	// The other pointers we make are handled elsewhere.
	delete made_npc;
}

void Mob::TypesTemporaryPets(uint32 typesid, Mob *targ, const char *name_override, uint32 duration_override, bool followme, bool sticktarg) {

	SwarmPet_Struct pet;
	pet.count = 1;
	pet.duration = 1;

	pet.npc_id = typesid;

	NPCType *made_npc = nullptr;

	const NPCType *npc_type = database.LoadNPCTypesData(typesid);
	if(npc_type == nullptr) {
		//log write
		Log(Logs::General, Logs::Error, "Unknown npc type for swarm pet type id: %d", typesid);
		Message(0,"Unable to find pet!");
		return;
	}

	if(name_override != nullptr) {
		//we have to make a custom NPC type for this name change
		made_npc = new NPCType;
		memcpy(made_npc, npc_type, sizeof(NPCType));
		strcpy(made_npc->name, name_override);
		npc_type = made_npc;
	}

	int summon_count = 0;
	summon_count = pet.count;

	if(summon_count > MAX_SWARM_PETS)
		summon_count = MAX_SWARM_PETS;

	static const glm::vec2 swarmPetLocations[MAX_SWARM_PETS] = {
		glm::vec2(5, 5), glm::vec2(-5, 5), glm::vec2(5, -5), glm::vec2(-5, -5),
		glm::vec2(10, 10), glm::vec2(-10, 10), glm::vec2(10, -10), glm::vec2(-10, -10),
		glm::vec2(8, 8), glm::vec2(-8, 8), glm::vec2(8, -8), glm::vec2(-8, -8)
	};;

	while(summon_count > 0) {
		int pet_duration = pet.duration;
		if(duration_override > 0)
			pet_duration = duration_override;

		//this is a little messy, but the only way to do it right
		//it would be possible to optimize out this copy for the last pet, but oh well
		NPCType *npc_dup = nullptr;
		if(made_npc != nullptr) {
			npc_dup = new NPCType;
			memcpy(npc_dup, made_npc, sizeof(NPCType));
		}

		NPC* swarm_pet_npc = new NPC(
				(npc_dup!=nullptr)?npc_dup:npc_type,	//make sure we give the NPC the correct data pointer
				0,
				GetPosition() + glm::vec4(swarmPetLocations[summon_count], 0.0f, 0.0f),
				FlyMode3);

		if (followme)
			swarm_pet_npc->SetFollowID(GetID());

		if(!swarm_pet_npc->GetSwarmInfo()){
			auto nSI = new SwarmPet;
			swarm_pet_npc->SetSwarmInfo(nSI);
			swarm_pet_npc->GetSwarmInfo()->duration = new Timer(pet_duration*1000);
		}
		else {
			swarm_pet_npc->GetSwarmInfo()->duration->Start(pet_duration*1000);
		}

		swarm_pet_npc->StartSwarmTimer(pet_duration * 1000);

		//removing this prevents the pet from attacking
		swarm_pet_npc->GetSwarmInfo()->owner_id = GetID();

		//give the pets somebody to "love"
		if(targ != nullptr){
			swarm_pet_npc->AddToHateList(targ, 1000, 1000);

			if (RuleB(Spells, SwarmPetTargetLock) || sticktarg)
				swarm_pet_npc->GetSwarmInfo()->target = targ->GetID();
			else
				swarm_pet_npc->GetSwarmInfo()->target = 0;
		}

		//we allocated a new NPC type object, give the NPC ownership of that memory
		if(npc_dup != nullptr)
			swarm_pet_npc->GiveNPCTypeData(npc_dup);

		entity_list.AddNPC(swarm_pet_npc, true, true);
		summon_count--;
	}

	// The other pointers we make are handled elsewhere.
	delete made_npc;
}

void Mob::WakeTheDead(uint16 spell_id, Mob *target, uint32 duration)
{
	Corpse *CorpseToUse = nullptr;
	CorpseToUse = entity_list.GetClosestCorpse(this, nullptr);

	if(!CorpseToUse)
		return;

	//assuming we have pets in our table; we take the first pet as a base type.
	const NPCType *base_type = database.LoadNPCTypesData(500);
	auto make_npc = new NPCType;
	memcpy(make_npc, base_type, sizeof(NPCType));

	//combat stats
	make_npc->AC = ((GetLevel() * 7) + 550);
	make_npc->ATK = GetLevel();
	make_npc->max_dmg = (GetLevel() * 4) + 2;
	make_npc->min_dmg = 1;

	//base stats
	make_npc->cur_hp = (GetLevel() * 55);
	make_npc->max_hp = (GetLevel() * 55);
	make_npc->STR = 85 + (GetLevel() * 3);
	make_npc->STA = 85 + (GetLevel() * 3);
	make_npc->DEX = 85 + (GetLevel() * 3);
	make_npc->AGI = 85 + (GetLevel() * 3);
	make_npc->INT = 85 + (GetLevel() * 3);
	make_npc->WIS = 85 + (GetLevel() * 3);
	make_npc->CHA = 85 + (GetLevel() * 3);
	make_npc->MR = 25;
	make_npc->FR = 25;
	make_npc->CR = 25;
	make_npc->DR = 25;
	make_npc->PR = 25;

	//level class and gender
	make_npc->level = GetLevel();
	make_npc->class_ = CorpseToUse->class_;
	make_npc->race = CorpseToUse->race;
	make_npc->gender = CorpseToUse->gender;
	make_npc->loottable_id = 0;
	//name
	char NewName[64];
	sprintf(NewName, "%s`s Animated Corpse", GetCleanName());
	strcpy(make_npc->name, NewName);

	//appearance
	make_npc->beard = CorpseToUse->beard;
	make_npc->beardcolor = CorpseToUse->beardcolor;
	make_npc->eyecolor1 = CorpseToUse->eyecolor1;
	make_npc->eyecolor2 = CorpseToUse->eyecolor2;
	make_npc->haircolor = CorpseToUse->haircolor;
	make_npc->hairstyle = CorpseToUse->hairstyle;
	make_npc->helmtexture = CorpseToUse->helmtexture;
	make_npc->luclinface = CorpseToUse->luclinface;
	make_npc->size = CorpseToUse->size;
	make_npc->texture = CorpseToUse->texture;

	//cast stuff.. based off of PEQ's if you want to change
	//it you'll have to mod this code, but most likely
	//most people will be using PEQ style for the first
	//part of their spell list; can't think of any smooth
	//way to do this
	//some basic combat mods here too since it's convienent
	switch(CorpseToUse->class_)
	{
	case CLERIC:
		make_npc->npc_spells_id = 1;
		break;
	case WIZARD:
		make_npc->npc_spells_id = 2;
		break;
	case NECROMANCER:
		make_npc->npc_spells_id = 3;
		break;
	case MAGICIAN:
		make_npc->npc_spells_id = 4;
		break;
	case ENCHANTER:
		make_npc->npc_spells_id = 5;
		break;
	case SHAMAN:
		make_npc->npc_spells_id = 6;
		break;
	case DRUID:
		make_npc->npc_spells_id = 7;
		break;
	case PALADIN:
		//SPECATK_TRIPLE
		strcpy(make_npc->special_abilities, "6,1");
		make_npc->cur_hp = make_npc->cur_hp * 150 / 100;
		make_npc->max_hp = make_npc->max_hp * 150 / 100;
		make_npc->npc_spells_id = 8;
		break;
	case SHADOWKNIGHT:
		strcpy(make_npc->special_abilities, "6,1");
		make_npc->cur_hp = make_npc->cur_hp * 150 / 100;
		make_npc->max_hp = make_npc->max_hp * 150 / 100;
		make_npc->npc_spells_id = 9;
		break;
	case RANGER:
		strcpy(make_npc->special_abilities, "7,1");
		make_npc->cur_hp = make_npc->cur_hp * 135 / 100;
		make_npc->max_hp = make_npc->max_hp * 135 / 100;
		make_npc->npc_spells_id = 10;
		break;
	case BARD:
		strcpy(make_npc->special_abilities, "6,1");
		make_npc->cur_hp = make_npc->cur_hp * 110 / 100;
		make_npc->max_hp = make_npc->max_hp * 110 / 100;
		make_npc->npc_spells_id = 11;
		break;
	case BEASTLORD:
		strcpy(make_npc->special_abilities, "7,1");
		make_npc->cur_hp = make_npc->cur_hp * 110 / 100;
		make_npc->max_hp = make_npc->max_hp * 110 / 100;
		make_npc->npc_spells_id = 12;
		break;
	case ROGUE:
		strcpy(make_npc->special_abilities, "7,1");
		make_npc->max_dmg = make_npc->max_dmg * 150 /100;
		make_npc->cur_hp = make_npc->cur_hp * 110 / 100;
		make_npc->max_hp = make_npc->max_hp * 110 / 100;
		break;
	case MONK:
		strcpy(make_npc->special_abilities, "7,1");
		make_npc->max_dmg = make_npc->max_dmg * 150 /100;
		make_npc->cur_hp = make_npc->cur_hp * 135 / 100;
		make_npc->max_hp = make_npc->max_hp * 135 / 100;
		break;
	case WARRIOR:
	case BERSERKER:
		strcpy(make_npc->special_abilities, "7,1");
		make_npc->max_dmg = make_npc->max_dmg * 150 /100;
		make_npc->cur_hp = make_npc->cur_hp * 175 / 100;
		make_npc->max_hp = make_npc->max_hp * 175 / 100;
		break;
	default:
		make_npc->npc_spells_id = 0;
		break;
	}

	make_npc->loottable_id = 0;
	make_npc->merchanttype = 0;
	make_npc->d_melee_texture1 = 0;
	make_npc->d_melee_texture2 = 0;

	auto npca = new NPC(make_npc, 0, GetPosition(), FlyMode3);

	if(!npca->GetSwarmInfo()){
		auto nSI = new SwarmPet;
		npca->SetSwarmInfo(nSI);
		npca->GetSwarmInfo()->duration = new Timer(duration*1000);
	}
	else{
		npca->GetSwarmInfo()->duration->Start(duration*1000);
	}

	npca->StartSwarmTimer(duration * 1000);
	npca->GetSwarmInfo()->owner_id = GetID();

	//give the pet somebody to "love"
	if(target != nullptr){
		npca->AddToHateList(target, 100000);
		npca->GetSwarmInfo()->target = target->GetID();
	}

	//gear stuff, need to make sure there's
	//no situation where this stuff can be duped
	for (int x = EQEmu::legacy::EQUIPMENT_BEGIN; x <= EQEmu::legacy::EQUIPMENT_END; x++) // (< 21) added MainAmmo
	{
		uint32 sitem = 0;
		sitem = CorpseToUse->GetWornItem(x);
		if(sitem){
			const EQEmu::ItemData * itm = database.GetItem(sitem);
			npca->AddLootDrop(itm, &npca->itemlist, 1, 1, 255, true, true);
		}
	}

	//we allocated a new NPC type object, give the NPC ownership of that memory
	if(make_npc != nullptr)
		npca->GiveNPCTypeData(make_npc);

	entity_list.AddNPC(npca, true, true);

	//the target of these swarm pets will take offense to being cast on...
	if(target != nullptr)
		target->AddToHateList(this, 1, 0);
}

void Client::ResetAA() {
	SendClearAA();
	RefundAA();

	memset(&m_pp.aa_array[0], 0, sizeof(AA_Array) * MAX_PP_AA_ARRAY);

	int i = 0;
	for(auto &rank_value : aa_ranks) {
		auto ability_rank = zone->GetAlternateAdvancementAbilityAndRank(rank_value.first, rank_value.second.first);
		auto ability = ability_rank.first;
		auto rank = ability_rank.second;

		if(!rank) {
			continue;
		}

		m_pp.aa_array[i].AA = rank_value.first;
		m_pp.aa_array[i].value = rank_value.second.first;
		m_pp.aa_array[i].charges = rank_value.second.second;
		++i;
	}

	for(int i = 0; i < _maxLeaderAA; ++i)
		m_pp.leader_abilities.ranks[i] = 0;

	m_pp.group_leadership_points = 0;
	m_pp.raid_leadership_points = 0;
	m_pp.group_leadership_exp = 0;
	m_pp.raid_leadership_exp = 0;

	database.DeleteCharacterLeadershipAAs(CharacterID());
	// undefined for these clients
	if (ClientVersionBit() & EQEmu::versions::bit_TitaniumAndEarlier)
		Kick();
}

void Client::SendClearAA()
{
	auto outapp = new EQApplicationPacket(OP_ClearLeadershipAbilities, 0);
	FastQueuePacket(&outapp);
	outapp = new EQApplicationPacket(OP_ClearAA, 0);
	FastQueuePacket(&outapp);
}

int Client::GroupLeadershipAAHealthEnhancement()
{
	if (IsRaidGrouped()) {
		int bonus = 0;
		Raid *raid = GetRaid();
		if (!raid)
			return 0;
		uint32 group_id = raid->GetGroup(this);
		if (group_id < 12 && raid->GroupCount(group_id) >= 3) {
			switch (raid->GetLeadershipAA(groupAAHealthEnhancement, group_id)) {
			case 1:
				bonus = 30;
				break;
			case 2:
				bonus = 60;
				break;
			case 3:
				bonus = 100;
				break;
			}
		}
		if (raid->RaidCount() >= 18) {
			switch (raid->GetLeadershipAA(raidAAHealthEnhancement)) {
			case 1:
				bonus += 30;
				break;
			case 2:
				bonus += 60;
				break;
			case 3:
				bonus += 100;
				break;
			}
		}
		return bonus;
	}

	Group *g = GetGroup();

	if(!g || (g->GroupCount() < 3))
		return 0;

	switch(g->GetLeadershipAA(groupAAHealthEnhancement))
	{
		case 0:
			return 0;
		case 1:
			return 30;
		case 2:
			return 60;
		case 3:
			return 100;
	}

	return 0;
}

int Client::GroupLeadershipAAManaEnhancement()
{
	if (IsRaidGrouped()) {
		int bonus = 0;
		Raid *raid = GetRaid();
		if (!raid)
			return 0;
		uint32 group_id = raid->GetGroup(this);
		if (group_id < 12 && raid->GroupCount(group_id) >= 3) {
			switch (raid->GetLeadershipAA(groupAAManaEnhancement, group_id)) {
			case 1:
				bonus = 30;
				break;
			case 2:
				bonus = 60;
				break;
			case 3:
				bonus = 100;
				break;
			}
		}
		if (raid->RaidCount() >= 18) {
			switch (raid->GetLeadershipAA(raidAAManaEnhancement)) {
			case 1:
				bonus += 30;
				break;
			case 2:
				bonus += 60;
				break;
			case 3:
				bonus += 100;
				break;
			}
		}
		return bonus;
	}

	Group *g = GetGroup();

	if(!g || (g->GroupCount() < 3))
		return 0;

	switch(g->GetLeadershipAA(groupAAManaEnhancement))
	{
		case 0:
			return 0;
		case 1:
			return 30;
		case 2:
			return 60;
		case 3:
			return 100;
	}

	return 0;
}

int Client::GroupLeadershipAAHealthRegeneration()
{
	if (IsRaidGrouped()) {
		int bonus = 0;
		Raid *raid = GetRaid();
		if (!raid)
			return 0;
		uint32 group_id = raid->GetGroup(this);
		if (group_id < 12 && raid->GroupCount(group_id) >= 3) {
			switch (raid->GetLeadershipAA(groupAAHealthRegeneration, group_id)) {
			case 1:
				bonus = 4;
				break;
			case 2:
				bonus = 6;
				break;
			case 3:
				bonus = 8;
				break;
			}
		}
		if (raid->RaidCount() >= 18) {
			switch (raid->GetLeadershipAA(raidAAHealthRegeneration)) {
			case 1:
				bonus += 4;
				break;
			case 2:
				bonus += 6;
				break;
			case 3:
				bonus += 8;
				break;
			}
		}
		return bonus;
	}

	Group *g = GetGroup();

	if(!g || (g->GroupCount() < 3))
		return 0;

	switch(g->GetLeadershipAA(groupAAHealthRegeneration))
	{
		case 0:
			return 0;
		case 1:
			return 4;
		case 2:
			return 6;
		case 3:
			return 8;
	}

	return 0;
}

int Client::GroupLeadershipAAOffenseEnhancement()
{
	if (IsRaidGrouped()) {
		int bonus = 0;
		Raid *raid = GetRaid();
		if (!raid)
			return 0;
		uint32 group_id = raid->GetGroup(this);
		if (group_id < 12 && raid->GroupCount(group_id) >= 3) {
			switch (raid->GetLeadershipAA(groupAAOffenseEnhancement, group_id)) {
			case 1:
				bonus = 10;
				break;
			case 2:
				bonus = 19;
				break;
			case 3:
				bonus = 28;
				break;
			case 4:
				bonus = 34;
				break;
			case 5:
				bonus = 40;
				break;
			}
		}
		if (raid->RaidCount() >= 18) {
			switch (raid->GetLeadershipAA(raidAAOffenseEnhancement)) {
			case 1:
				bonus += 10;
				break;
			case 2:
				bonus += 19;
				break;
			case 3:
				bonus += 28;
				break;
			case 4:
				bonus += 34;
				break;
			case 5:
				bonus += 40;
				break;
			}
		}
		return bonus;
	}

	Group *g = GetGroup();

	if(!g || (g->GroupCount() < 3))
		return 0;

	switch(g->GetLeadershipAA(groupAAOffenseEnhancement))
	{
		case 0:
			return 0;
		case 1:
			return 10;
		case 2:
			return 19;
		case 3:
			return 28;
		case 4:
			return 34;
		case 5:
			return 40;
	}
	return 0;
}

void Client::InspectBuffs(Client* Inspector, int Rank)
{
	// At some point the removed the restriction of being a group member for this to work
	// not sure when, but the way it's coded now, it wouldn't work with mobs.
	if (!Inspector || Rank == 0)
		return;
	if (!IsTaskCompleted(FEAT_HEALTHOFTARGETSTARGET)) return;

	auto outapp = new EQApplicationPacket(OP_InspectBuffs, sizeof(InspectBuffs_Struct));
	InspectBuffs_Struct *ib = (InspectBuffs_Struct *)outapp->pBuffer;

	uint32 buff_count = GetMaxTotalSlots();
	uint32 packet_index = 0;
	for (uint32 i = 0; i < buff_count; i++) {
		if (buffs[i].spellid == SPELL_UNKNOWN)
			continue;
		ib->spell_id[packet_index] = buffs[i].spellid;
		if (Rank > 1)
			ib->tics_remaining[packet_index] = spells[buffs[i].spellid].buffdurationformula == DF_Permanent ? 0xFFFFFFFF : buffs[i].ticsremaining;
		packet_index++;
	}

	Inspector->FastQueuePacket(&outapp);
}

void Client::RefundAA() {
	int refunded = 0;

	auto rank_value = aa_ranks.begin();
	while(rank_value != aa_ranks.end()) {
		auto ability_rank = zone->GetAlternateAdvancementAbilityAndRank(rank_value->first, rank_value->second.first);
		auto ability = ability_rank.first;
		auto rank = ability_rank.second;

		if(!ability) {
			++rank_value;
			continue;
		}

		if(ability->charges > 0 && rank_value->second.second < 1) {
			++rank_value;
			continue;
		}

		//RebuildEQ - due to AA's being granted, this has to be removed for #resetaa command to work
		/*if(ability->grant_only) {
			this->Message(13, "granted AA, no points");
			++rank_value;
			continue;
		}*/

		//refunded += rank->total_cost;
		rank_value = aa_ranks.erase(rank_value);
	}

	//if(refunded > 0) {
		m_pp.aapoints += refunded;
		SaveAA();
		Save();
	//}

	SendAlternateAdvancementTable();
	SendAlternateAdvancementPoints();
	SendAlternateAdvancementStats();
}

SwarmPet::SwarmPet()
{
	target = 0;
	owner_id = 0;
	duration = nullptr;
}

SwarmPet::~SwarmPet()
{
	target = 0;
	owner_id = 0;
	safe_delete(duration);
}

Mob *SwarmPet::GetOwner()
{
	return entity_list.GetMobID(owner_id);
}

//New AA
void Client::SendAlternateAdvancementTable() {
	for(auto &aa : zone->aa_abilities) {
		uint32 charges = 0;
		auto ranks = GetAA(aa.second->first_rank_id, &charges);
		if(ranks) {
			if(aa.second->GetMaxLevel(this) == ranks) {
				SendAlternateAdvancementRank(aa.first, ranks);
			} else {
				SendAlternateAdvancementRank(aa.first, ranks);
				SendAlternateAdvancementRank(aa.first, ranks + 1);
			}
		} else {
			SendAlternateAdvancementRank(aa.first, 1);
		}
	}
}

void Client::SendAlternateAdvancementRank(int aa_id, int level) {
	if(!zone)
		return;

	auto ability_rank = zone->GetAlternateAdvancementAbilityAndRank(aa_id, level);
	auto ability = ability_rank.first;
	auto rank = ability_rank.second;

	if(!ability) {
		return;
	}

	if(!(ability->classes & (1 << GetClass()))) {
		return;
	}

	if(!CanUseAlternateAdvancementRank(rank)) {
		return;
	}

	int size = sizeof(AARankInfo_Struct) + (sizeof(AARankEffect_Struct) * rank->effects.size()) + (sizeof(AARankPrereq_Struct) * rank->prereqs.size());
	auto outapp = new EQApplicationPacket(OP_SendAATable, size);
	AARankInfo_Struct *aai = (AARankInfo_Struct*)outapp->pBuffer;

	aai->id = rank->id;
	aai->upper_hotkey_sid = rank->upper_hotkey_sid;
	aai->lower_hotkey_sid = rank->lower_hotkey_sid;
	aai->title_sid = rank->title_sid;
	aai->desc_sid = rank->desc_sid;
	aai->cost = rank->cost;
	aai->seq = aa_id;
	aai->type = ability->type;
	aai->spell = rank->spell;
	aai->spell_type = rank->spell_type;
	
	int rb_rank = 0;
	
	aai->spell_refresh = rank->recast_time;

	if (rank->id == aaCalloftheWild) {
		rb_rank = GetBuildRank(DRUID, RB_DRU_CALLOFTHEWILD);
		if(rb_rank)
			aai->spell_refresh = 1800 - (rb_rank-1) * 300;
	} else if (rank->id == aaAncestralAid) {
		if(GetBuildRank(SHAMAN, RB_SHM_ANCESTRALAID))
			aai->spell_refresh = 16;
	} else if (rank->id == aaSpiritCall) {
		if(GetBuildRank(SHAMAN, RB_SHM_SPIRITCALL))
			aai->spell_refresh = 16;
	}else if (rank->id == aaCalloftheAncients) {
		if (GetBuildRank(SHAMAN, RB_SHM_CALLOFTHEANCIENTS))
			aai->spell_refresh = 900;
	}else if (rank->id == aaSecondaryRecall) {
		rb_rank = GetBuildRank(DRUID, RB_DRU_SECONDARYRECALL);
		if(rb_rank) {
			if(rb_rank == 1) aai->spell_refresh = 86400; // 24 hours
			else if(rb_rank == 2) aai->spell_refresh = 64800; // 18 hours
			else if(rb_rank == 3) aai->spell_refresh = 43200; // 12 hours
			else if(rb_rank == 4) aai->spell_refresh = 21600; // 6 hours
			else if(rb_rank == 5) aai->spell_refresh = 10800; // 3 hours
		}
	} else if (rank->id == aaClockworkBanker) { 
		rb_rank = GetBuildRank(MAGICIAN, RB_MAG_CLOCKWORKMERCHANT);
		if(rb_rank) {
			if(rb_rank == 1) aai->spell_refresh = 86400; // 24 hours
			else if(rb_rank == 2) aai->spell_refresh = 43200; // 12 hours
			else if(rb_rank == 3) aai->spell_refresh = 21600; // 6 hours
			else if(rb_rank == 4) aai->spell_refresh = 10800; // 3 hours
			else if(rb_rank == 5) aai->spell_refresh = 3600; // 1 hour
		}
	}
	else if (rank->id == aaCalloftheHero) {
		rb_rank = GetBuildRank(MAGICIAN, RB_MAG_CALLOFTHEHERO);
		if (rb_rank) {
			aai->spell_refresh = 2 * ((5 - rb_rank) * 5 + 10);
		}
	}
	else if (rank->id == aaLifeBurn) {
		aai->spell_refresh = 30;	
	}
	else if (rank->id == aaBloodMagic) {
		rb_rank = GetBuildRank(NECROMANCER, RB_NEC_BLOODMAGIC);
		if (rb_rank > 0) aai->spell_refresh = 360 - (rb_rank * 30);
	}
	else if (rank->id == aaCelestialRegeneration) {
		rb_rank = GetBuildRank(CLERIC, RB_CLR_CELESTIALREGENERATION);
		if (rb_rank > 0) aai->spell_refresh = 360;
	} else if (rank->id == aaDivineArbitration) {
		rb_rank = GetBuildRank(CLERIC, RB_CLR_DIVINEARBITRATION);
		if (rb_rank > 0) aai->spell_refresh = 180 - (rb_rank * 30);
	} else if (rank->id == aaBoastfulBellow) {
		rb_rank = GetBuildRank(BARD, RB_BRD_BOASTFULBELLOW);
		if (rb_rank) {
			aai->spell_refresh = rank->recast_time - (rb_rank * 2);
		}
	} else if (rank->id == aaLessonoftheDevoted) {
		rb_rank = GetBuildRank(CLERIC, RB_CLR_HARMONICBALANCE);
		if (rb_rank) {
			aai->spell_refresh = rank->recast_time - (rb_rank * 30);
		}
		rb_rank = GetBuildRank(BARD, RB_BRD_KINSONG);
		if (rb_rank) {
			aai->spell_refresh = rank->recast_time - (30 * rb_rank);
		}
		rb_rank = GetBuildRank(DRUID, RB_DRU_NATURESBLIGHT);
		if (rb_rank) {
			aai->spell_refresh = (rank->recast_time / 2) - (10 * rb_rank);
		}
		rb_rank = GetBuildRank(MONK, RB_MNK_GRACEOFTHEORDER);
		if (rb_rank) {
			aai->spell_refresh = rank->recast_time - (30 * rb_rank);
		}
		rb_rank = GetBuildRank(NECROMANCER, RB_NEC_SERVANTOFBLOOD);
		if (rb_rank) {
			aai->spell_refresh = rank->recast_time - (30 * rb_rank);
		}
		rb_rank = GetBuildRank(PALADIN, RB_PAL_FLAMESOFREDEMPTION);
		if (rb_rank) {
			aai->spell_refresh = rank->recast_time - (30 * rb_rank);
		}
		rb_rank = GetBuildRank(ROGUE, RB_ROG_ASSASSINSTAINT);
		if (rb_rank) {
			aai->spell_refresh = rank->recast_time - (30 * rb_rank);
		}
		rb_rank = GetBuildRank(SHADOWKNIGHT, RB_SHD_REAPERSSTRIKE);
		if (rb_rank) {
			aai->spell_refresh = rank->recast_time - (30 * rb_rank);
		}
		rb_rank = GetBuildRank(SHAMAN, RB_SHM_FATESEERSBOON);
		if (rb_rank) {
			aai->spell_refresh = rank->recast_time - (30 * rb_rank);
		}
	} 
	
	aai->classes = ability->classes;
	aai->level_req = rank->level_req;
	aai->current_level = level;
	aai->max_level = ability->GetMaxLevel(this);
	aai->prev_id = rank->prev_id;

	if((rank->next && !CanUseAlternateAdvancementRank(rank->next)) || ability->charges > 0) {
		aai->next_id = -1;
	} else {
		aai->next_id = rank->next_id;
	}
	aai->total_cost = rank->total_cost;
	aai->expansion = rank->expansion;
	aai->category = ability->category;
	aai->charges = ability->charges;
	aai->grant_only = ability->grant_only;
	aai->total_effects = rank->effects.size();
	aai->total_prereqs = rank->prereqs.size();

	outapp->SetWritePosition(sizeof(AARankInfo_Struct));
	for(auto &effect : rank->effects) {
		outapp->WriteSInt32(effect.effect_id);
		outapp->WriteSInt32(effect.base1);
		outapp->WriteSInt32(effect.base2);
		outapp->WriteSInt32(effect.slot);
	}

	for(auto &prereq : rank->prereqs) {
		outapp->WriteSInt32(prereq.first);
		outapp->WriteSInt32(prereq.second);
	}

	QueuePacket(outapp);
	safe_delete(outapp);
}

void Client::SendAlternateAdvancementStats() {
	auto outapp = new EQApplicationPacket(OP_AAExpUpdate, sizeof(AltAdvStats_Struct));
	AltAdvStats_Struct *aps = (AltAdvStats_Struct *)outapp->pBuffer;
	aps->experience = (uint32)(((float)330.0f * (float)m_pp.expAA) / (float)GetRequiredAAExperience());
	aps->unspent = m_pp.aapoints;
	aps->percentage = m_epp.perAA;
	QueuePacket(outapp);
	safe_delete(outapp);
}

void Client::SendAlternateAdvancementPoints() {
	auto outapp = new EQApplicationPacket(OP_RespondAA, sizeof(AATable_Struct));
	AATable_Struct* aa2 = (AATable_Struct *)outapp->pBuffer;

	int i = 0;
	for(auto &aa : zone->aa_abilities) {
		uint32 charges = 0;
		auto ranks = GetAA(aa.second->first_rank_id, &charges);
		if(ranks) {
			AA::Rank *rank = aa.second->GetRankByPointsSpent(ranks);
			if(rank) {
				aa2->aa_list[i].AA = rank->id;
				aa2->aa_list[i].value = rank->total_cost;
				aa2->aa_list[i].charges = charges;
				i++;
			}
		}
	}


	aa2->aa_spent = GetSpentAA();
	QueuePacket(outapp);
	safe_delete(outapp);
}

void Client::SendAlternateAdvancementTimer(int ability, int begin, int end) {
	auto outapp = new EQApplicationPacket(OP_AAAction, sizeof(UseAA_Struct));
	UseAA_Struct* uaaout = (UseAA_Struct*)outapp->pBuffer;
	uaaout->ability = ability;
	uaaout->begin = begin;
	uaaout->end = end;
	QueuePacket(outapp);
	safe_delete(outapp);
}

//sends all AA timers.
void Client::SendAlternateAdvancementTimers() {
	//we dont use SendAATimer because theres no reason to allocate the EQApplicationPacket every time
	auto outapp = new EQApplicationPacket(OP_AAAction, sizeof(UseAA_Struct));
	UseAA_Struct* uaaout = (UseAA_Struct*)outapp->pBuffer;

	PTimerList::iterator c, e;
	c = p_timers.begin();
	e = p_timers.end();
	for(; c != e; ++c) {
		PersistentTimer *cur = c->second;
		if(cur->GetType() < pTimerAAStart || cur->GetType() > pTimerAAEnd)
			continue;	//not an AA timer
		//send timer
		uaaout->begin = cur->GetStartTime();
		uaaout->end = static_cast<uint32>(time(nullptr));
		uaaout->ability = cur->GetType() - pTimerAAStart; // uuaaout->ability is really a shared timer number
		QueuePacket(outapp);
	}

	safe_delete(outapp);
}

void Client::ResetAlternateAdvancementTimer(int ability) {
	AA::Rank *rank = zone->GetAlternateAdvancementRank(casting_spell_aa_id);
	if(rank) {
		SendAlternateAdvancementTimer(rank->spell_type, 0, time(0));
		p_timers.Clear(&database, rank->spell_type + pTimerAAStart);
	}
}

void Client::ResetAlternateAdvancementTimers() {
	auto outapp = new EQApplicationPacket(OP_AAAction, sizeof(UseAA_Struct));
	UseAA_Struct* uaaout = (UseAA_Struct*)outapp->pBuffer;

	PTimerList::iterator c, e;
	c = p_timers.begin();
	e = p_timers.end();
	std::vector<int> r_timers;
	for(; c != e; ++c) {
		PersistentTimer *cur = c->second;
		if(cur->GetType() < pTimerAAStart || cur->GetType() > pTimerAAEnd)
			continue;
		//send timer
		uaaout->begin = 0;
		uaaout->end = static_cast<uint32>(time(nullptr));
		uaaout->ability = cur->GetType() - pTimerAAStart;
		r_timers.push_back(cur->GetType());
		QueuePacket(outapp);
	}

	for(auto &i : r_timers) {
		p_timers.Clear(&database, i);
	}

	safe_delete(outapp);
}

void Client::PurchaseAlternateAdvancementRank(int rank_id) {
	AA::Rank *rank = zone->GetAlternateAdvancementRank(rank_id);
	if(!rank) {
		return;
	}

	if(!rank->base_ability) {
		return;
	}

	if(!CanPurchaseAlternateAdvancementRank(rank, true, true)) {
		return;
	}

	FinishAlternateAdvancementPurchase(rank, false);
}

bool Client::GrantAlternateAdvancementAbility(int aa_id, int points, bool ignore_cost) {
	bool ret = false;
	for(int i = 1; i <= points; ++i) {
		auto ability_rank = zone->GetAlternateAdvancementAbilityAndRank(aa_id, i);
		auto ability = ability_rank.first;
		auto rank = ability_rank.second;

		if(!rank) {
			continue;
		}

		if(!rank->base_ability) {
			continue;
		}

		if(!CanPurchaseAlternateAdvancementRank(rank, !ignore_cost, false)) {
			continue;
		}

		ret = true;
		FinishAlternateAdvancementPurchase(rank, ignore_cost);
	}

	return ret;
}

void Client::FinishAlternateAdvancementPurchase(AA::Rank *rank, bool ignore_cost) {
	int rank_id = rank->base_ability->first_rank_id;

	if(rank->base_ability->charges > 0) {
		uint32 charges = 0;
		GetAA(rank_id, &charges);

		if(charges > 0) {
			return;
		}

		SetAA(rank_id, rank->current_value, rank->base_ability->charges);
	}
	else {
		SetAA(rank_id, rank->current_value, 0);

		//if not max then send next aa
		if(rank->next) {
			SendAlternateAdvancementRank(rank->base_ability->id, rank->next->current_value);
		}
	}

	int cost = !ignore_cost ? rank->cost : 0;

	m_pp.aapoints -= cost ;
	SaveAA();

	SendAlternateAdvancementPoints();
	SendAlternateAdvancementStats();

	if(rank->prev) {
		Message_StringID(15, AA_IMPROVE,
						 std::to_string(rank->title_sid).c_str(),
						 std::to_string(rank->prev->current_value).c_str(),
						 std::to_string(cost).c_str(),
						 cost == 1 ? std::to_string(AA_POINT).c_str() : std::to_string(AA_POINTS).c_str());

		/* QS: Player_Log_AA_Purchases */
		if(RuleB(QueryServ, PlayerLogAAPurchases)) {
			std::string event_desc = StringFormat("Ranked AA Purchase :: aa_id:%i at cost:%i in zoneid:%i instid:%i", rank->id, cost, GetZoneID(), GetInstanceID());
			QServ->PlayerLogEvent(Player_Log_AA_Purchases, CharacterID(), event_desc);
		}
	}
	else {
		Message_StringID(15, AA_GAIN_ABILITY,
						 std::to_string(rank->title_sid).c_str(),
						 std::to_string(cost).c_str(),
						 cost == 1 ? std::to_string(AA_POINT).c_str() : std::to_string(AA_POINTS).c_str());
		/* QS: Player_Log_AA_Purchases */
		if(RuleB(QueryServ, PlayerLogAAPurchases)) {
			std::string event_desc = StringFormat("Initial AA Purchase :: aa_id:%i at cost:%i in zoneid:%i instid:%i", rank->id, cost, GetZoneID(), GetInstanceID());
			QServ->PlayerLogEvent(Player_Log_AA_Purchases, CharacterID(), event_desc);
		}
	}

	CalcBonuses();

	if(cost > 0) {
		if(title_manager.IsNewAATitleAvailable(m_pp.aapoints_spent, GetBaseClass()))
			NotifyNewTitlesAvailable();
	}
}

//need to rewrite this
void Client::IncrementAlternateAdvancementRank(int rank_id) {
	AA::Rank *rank = zone->GetAlternateAdvancementRank(rank_id);
	if(!rank) {
		return;
	}

	if(!rank->base_ability) {
		return;
	}

	int points = GetAA(rank_id);
	GrantAlternateAdvancementAbility(rank->base_ability->id, points + 1, true);
}

void Client::ActivateAlternateAdvancementAbility(int rank_id, int target_id) {
	AA::Rank *rank = zone->GetAlternateAdvancementRank(rank_id);
	if (!rank) {
		return;
	}

	AA::Ability *ability = rank->base_ability;
	if (!ability) {
		return;
	}
	if (rank_id == aaOrigin) {
		if (IsTaskActivityActive(307, 11)) UpdateTaskActivity(FEAT_GETTINGSTARTED, 11, 1);
	}

	if (rank_id == aaBoastfulBellow && GetBuildRank(BARD, RB_BRD_BOASTFULBELLOW) < 1 ||
		rank_id == aaDanceofBlades && GetBuildRank(BARD, RB_BRD_DANCEOFBLADES) < 1 ||

		rank_id == aaDivineAvatar && GetBuildRank(CLERIC, RB_CLR_DIVINEAVATAR) < 1 ||
		rank_id == aaCelestialRegeneration && GetBuildRank(CLERIC, RB_CLR_CELESTIALREGENERATION) < 1 ||
		rank_id == aaDivineArbitration && GetBuildRank(CLERIC, RB_CLR_DIVINEARBITRATION) < 1 ||
		rank_id == aaDivineResurrection && GetBuildRank(CLERIC, RB_CLR_DIVINERESURRECTION) < 1 ||
		rank_id == aaDivineRetribution && GetBuildRank(CLERIC, RB_CLR_DIVINERETRIBUTION) < 1 ||
		rank_id == aaTurnUndead2 && GetBuildRank(CLERIC, RB_CLR_TURNUNDEAD) < 1 ||
		rank_id == aaExquisiteBenediction && GetBuildRank(CLERIC, RB_CLR_EXQUISITEBENEDICTION) < 1 ||
		
		rank_id == aaTeleportBind && GetBuildRank(DRUID, RB_DRU_TELEPORTBIND) < 1 ||
		rank_id == aaEntrap && GetBuildRank(DRUID, RB_DRU_ENTRAP) < 1 ||
		rank_id == aaExodus && GetBuildRank(DRUID, RB_DRU_EXODUS) < 1 ||
		rank_id == aaCalloftheWild && GetBuildRank(DRUID, RB_DRU_CALLOFTHEWILD) < 1 ||
		rank_id == aaSecondaryRecall && GetBuildRank(DRUID, RB_DRU_SECONDARYRECALL) < 1 ||
		rank_id == aaDireCharm && GetBuildRank(DRUID, RB_DRU_DIRECHARM) < 1 ||
		rank_id == aaConvergenceofSpirits && GetBuildRank(DRUID, RB_DRU_CONVERGENCEOFSPIRITS) < 1 ||
		rank_id == aaSpiritoftheWood && GetBuildRank(DRUID, RB_DRU_SPIRITOFTHEWOOD) < 1 ||
		rank_id == aaNaturesBoon && GetBuildRank(DRUID, RB_DRU_NATURESBOON) < 1 ||
		rank_id == aaNaturesGuardian && GetBuildRank(DRUID, RB_DRU_NATURESGUARDIAN) < 1 ||

		rank_id == aaSoothingWords && GetBuildRank(ENCHANTER, RB_ENC_SOOTHINGWORDS) < 1 ||
		rank_id == aaMindOverMatter && GetBuildRank(ENCHANTER, RB_ENC_MINDOVERMATTER) < 1 ||
		rank_id == aaColorShock && GetBuildRank(ENCHANTER, RB_ENC_COLORSHOCK) < 1 ||

		rank_id == aaSharedHealth && GetBuildRank(MAGICIAN, RB_MAG_SHAREDHEALTH) < 1 ||
		rank_id == aaDimensionalShield && GetBuildRank(MAGICIAN, RB_MAG_DIMENSIONALSHIELD) < 1 ||
		rank_id == aaHostintheShell && GetBuildRank(MAGICIAN, RB_MAG_HOSTINTHESHELL) < 1 ||
		rank_id == aaHeartofStone && GetBuildRank(MAGICIAN, RB_MAG_HEARTOFSTONE) < 1 ||
		rank_id == aaImprovedReclaimEnergy && GetBuildRank(MAGICIAN, RB_MAG_IMPROVEDRECLAIMENERGY) < 1 ||
		rank_id == aaTurnSummoned2 && GetBuildRank(MAGICIAN, RB_MAG_TURNSUMMONED) < 1 ||
		rank_id == aaHeartofVapor && GetBuildRank(MAGICIAN, RB_MAG_HEARTOFVAPOR) < 1 ||
		rank_id == aaSmallModulationShard && GetBuildRank(MAGICIAN, RB_MAG_MODULATIONSHARD) < 1 ||		
		rank_id == aaHeartofIce && GetBuildRank(MAGICIAN, RB_MAG_HEARTOFICE) < 1 ||
		rank_id == aaSuspendedMinion && GetBuildRank(MAGICIAN, RB_MAG_SUSPENDEDMINION) < 1 ||
		rank_id == aaCalloftheHero && GetBuildRank(MAGICIAN, RB_MAG_CALLOFTHEHERO) < 1 ||
		rank_id == aaMendCompanion && GetBuildRank(MAGICIAN, RB_MAG_MENDCOMPANION) < 1 ||
		rank_id == aaClockworkBanker && GetBuildRank(MAGICIAN, RB_MAG_CLOCKWORKMERCHANT) < 1 ||
		rank_id == aaHeartofFlames && GetBuildRank(MAGICIAN, RB_MAG_HEARTOFFLAMES) < 1 ||
		rank_id == aaCompanionofNecessity && GetBuildRank(MAGICIAN, RB_MAG_COMPANIONOFNECESSITY) < 1 ||
		rank_id == aaServantofRo && GetBuildRank(MAGICIAN, RB_MAG_SERVANTOFRO) < 1 ||

		rank_id == aaPurifyBody && GetBuildRank(MONK, RB_MNK_PURIFYBODY) < 1 ||

		rank_id == aaLifeBurn && GetBuildRank(NECROMANCER, RB_NEC_LIFEBURN) < 1 ||
		rank_id == aaBloodMagic && GetBuildRank(NECROMANCER, RB_NEC_BLOODMAGIC) < 1 ||
		rank_id == aaDyingGrasp && GetBuildRank(NECROMANCER, RB_NEC_DYINGGRASP) < 1 ||

		rank_id == aaHandofPiety && GetBuildRank(PALADIN, RB_PAL_HANDOFPIETY) < 1 ||
		rank_id == aaPurification && GetBuildRank(PALADIN, RB_PAL_PURIFICATION) < 1 ||		
		rank_id == aaActOfValor && GetBuildRank(PALADIN, RB_PAL_ACTOFVALOR) < 1 ||
		rank_id == aaDivineStun && GetBuildRank(PALADIN, RB_PAL_DIVINESTUN) < 1 ||
		
		rank_id == aaAppraisal && GetBuildRank(ROGUE, RB_ROG_APPRAISAL) < 1 ||

		rank_id == aaLeechTouch && GetBuildRank(SHADOWKNIGHT, RB_SHD_LEECHTOUCH) < 1 ||
		rank_id == aaDeathPeace2 && GetBuildRank(SHADOWKNIGHT, RB_SHD_EMBRACEDEATH) < 1 ||
		rank_id == aaSteadfastServant && GetBuildRank(SHADOWKNIGHT, RB_SHD_STEADFASTSERVANT) < 1 ||

		rank_id == aaAncestralAid && GetBuildRank(SHAMAN, RB_SHM_ANCESTRALAID) < 1 ||
		rank_id == aaPurifySoul && GetBuildRank(SHAMAN, RB_SHM_PURIFYSOUL) < 1 ||
		rank_id == aaSpiritCall && GetBuildRank(SHAMAN, RB_SHM_SPIRITCALL) < 1 ||
		rank_id == aaVirulentParalysis && GetBuildRank(SHAMAN, RB_SHM_VIRULENTPARALYSIS) < 1 ||
		rank_id == aaRabidBear && GetBuildRank(SHAMAN, RB_SHM_RABIDBEAR) < 1 ||
		rank_id == aaAncestralGuard && GetBuildRank(SHAMAN, RB_SHM_ANCESTRALGUARD) < 1 ||
		rank_id == aaFeralSwipe && GetBuildRank(SHAMAN, RB_SHM_FERALSWIPE) < 1 ||
		rank_id == aaCannibalization && GetBuildRank(SHAMAN, RB_SHM_CANNIBALIZE) < 1 ||
		rank_id == aaParagonofSpirit && GetBuildRank(SHAMAN, RB_SHM_PARAGONOFSPIRIT) < 1 ||		
		( //Lesson of the Devoted is used by multiple classes different builds
			rank_id == aaLessonoftheDevoted && 				
			GetBuildRank(BARD, RB_BRD_KINSONG) < 1 &&
			GetBuildRank(CLERIC, RB_CLR_HARMONICBALANCE) < 1 &&			
			GetBuildRank(DRUID, RB_DRU_NATURESBLIGHT) < 1 &&
			GetBuildRank(MONK, RB_MNK_GRACEOFTHEORDER) < 1 &&
			GetBuildRank(NECROMANCER, RB_NEC_SERVANTOFBLOOD) < 1 &&
			GetBuildRank(PALADIN, RB_PAL_FLAMESOFREDEMPTION) < 1 &&
			GetBuildRank(ROGUE, RB_ROG_ASSASSINSTAINT) < 1 &&			
			GetBuildRank(SHADOWKNIGHT, RB_SHD_REAPERSSTRIKE) < 1 &&
			GetBuildRank(SHAMAN, RB_SHM_FATESEERSBOON) < 1 
		) //end lessons
		) {
		Message(13, "You cannot use this ability until you unlock it via %s.", CreateSayLink("#builds", "#builds").c_str());
		return;
	}
	
	// Break Invis when activating abilities
	CastToClient()->BreakInvisibleSpells();

	if(!CastToClient()->IsStanding()) {
		Message(13, "You must be standing to use an ability.");
		return;
	}
	
	// Dont let client waste a reuse timer if they can't use it
	if (IsStunned() || IsFeared() || IsMezzed() || IsAmnesiad() || IsPet() || IsCasting()) {
		return;
	}
	
	//Shin: set spell Id override
	int spellid = rank->spell;
	int manacost = -1;
	//calculate cooldown
	int cooldown = rank->recast_time - GetAlternateAdvancementCooldownReduction(rank);
	if (cooldown < 0) {
		cooldown = 0;
	}
	uint8 rb_rank = 0;
	

	if(rank_id == aaHeartofFlames) {
		if(GetBuildRank(MAGICIAN, RB_MAG_HEARTOFFLAMES))
			spellid = 37903;
	} else if (rank_id == aaEntrap) {
		rb_rank = GetBuildRank(DRUID, RB_DRU_ENTRAP);
		if(rb_rank) {
			if (rb_rank == 1) spellid = 3614;
			else if (rb_rank == 2) spellid = 12610;
			else if (rb_rank == 3) spellid = 23551;
			else if (rb_rank == 4) spellid = 30682;
			else spellid = 30682;
			
			if (GetLevel() < 15) manacost = 8;
			else if (GetLevel() < 29) manacost = 13;
			else if (GetLevel() < 51) manacost = 86;
			else if (GetLevel() < 55) manacost = 115;
			else if (GetLevel() < 60) manacost = 152;
			else manacost = 248;

			if (rb_rank >= 5) rb_rank = 8;
			manacost /= (0.4f * rb_rank);
		}
	}
	else if (rank_id == aaCalloftheWild) {
		rb_rank = GetBuildRank(DRUID, RB_DRU_CALLOFTHEWILD);
		if (rb_rank) {
			spellid = 958;
			cooldown = 1800 - (rb_rank - 1) * 300;
		}
	} 
	else if (rank_id == aaSoothingWords) {
			rb_rank = GetBuildRank(ENCHANTER, RB_ENC_SOOTHINGWORDS);
			if (rb_rank) {
				//spellid = 958;
				cooldown = 1800 - (rb_rank - 1) * 300;
			}

	} else if(rank_id == aaSecondaryRecall) {
		rb_rank = GetBuildRank(DRUID, RB_DRU_SECONDARYRECALL);
		if(rb_rank) {
			if(rb_rank == 1) cooldown = 86400; // 24 hours
			else if(rb_rank == 2) cooldown = 64800; // 18 hours
			else if(rb_rank == 3) cooldown = 43200; // 12 hours
			else if(rb_rank == 4) cooldown = 21600; // 6 hours
			else if(rb_rank == 5) cooldown = 10800; // 3 hours
		}
	} else if(rank_id == aaClockworkBanker) {
		rb_rank = GetBuildRank(MAGICIAN, RB_MAG_CLOCKWORKMERCHANT);
		if(rb_rank) {
			if(rb_rank == 1) cooldown = 86400; // 24 hours
			else if(rb_rank == 2) cooldown = 43200; // 12 hours
			else if(rb_rank == 3) cooldown = 21600; // 6 hours
			else if(rb_rank == 4) cooldown = 10800; // 3 hours
			else if(rb_rank == 5) cooldown = 3600; // 1 hours
		}
	}
	else if (rank_id == aaCalloftheHero) {
		rb_rank = GetBuildRank(MAGICIAN, RB_MAG_CALLOFTHEHERO);
		if (rb_rank)
			cooldown = 2 * ((5 - rb_rank) * 5 + 10);
	}
	else if (rank_id == aaLifeBurn) {
		cooldown = 30;
	} else if (rank->id == aaCelestialRegeneration) {
		rb_rank = GetBuildRank(CLERIC, RB_CLR_CELESTIALREGENERATION);
		if (rb_rank > 0) cooldown = 360;
	} else if (rank_id == aaDivineArbitration) {
		rb_rank = GetBuildRank(CLERIC, RB_CLR_DIVINEARBITRATION);
		if (rb_rank > 0) {
			cooldown = 180 - (rb_rank * 30);
			BuildEcho(StringFormat("Divine Arbitration %u reduced cooldown by %i", rb_rank, (rb_rank * 30)));
		}
	} else if (rank_id == aaDivineResurrection) {
		rb_rank = GetBuildRank(CLERIC, RB_CLR_DIVINERESURRECTION);
		if (rb_rank > 0) {
			cooldown = 86400 - ((5 - rb_rank) * 14400); //12 hours per rank
			BuildEcho(StringFormat("Divine Resurrection %u reduced cooldown by %i", rb_rank, (rb_rank * 43200)));
		}
	}
	else if (rank_id == aaAppraisal) {
		rb_rank = GetBuildRank(ROGUE, RB_ROG_APPRAISAL);
		if (rb_rank) {
			AddBuff(this, 271, rb_rank);
			if (IsClient() && CastToClient()->ClientVersionBit() & EQEmu::versions::bit_UFAndLater)
			{
				EQApplicationPacket *outapp = MakeBuffsPacket(false);
				CastToClient()->FastQueuePacket(&outapp);
			}

			cooldown = 10;
			CastToClient()->GetPTimers().Start(rank->spell_type + pTimerAAStart, cooldown);
			SendAlternateAdvancementTimer(rank->spell_type, 0, 0);
			return;
		}
	} else if (rank_id == aaDyingGrasp) {
		cooldown = 360 - GetBuildRank(NECROMANCER, RB_NEC_DYINGGRASP);
	} else if (rank_id == aaLeechTouch) {
		rb_rank = GetBuildRank(SHADOWKNIGHT, RB_SHD_LEECHTOUCH);
		if(rb_rank) {
			if (GetLevel() < 15) { //lifetap
				spellid = 341;  //10
				cooldown = 4;
			} else if (GetLevel() < 29) { //lifespike
				spellid = 502; //19
				cooldown = 4;
			} else if (GetLevel() < 51) { //lifedraw
				spellid = 445; //195
				cooldown = 4;
			} else if (GetLevel() < 55) { //siphon life
				spellid = 446; //250
				cooldown = 4;
			} else if (GetLevel() < 60) { //drain spirit
				spellid = 525; //514
				cooldown = 4;
			} else { //drain soul
				spellid = 447; // 656
				cooldown = 4;
			}
		}		
	} else if (rank_id == aaSpiritoftheWood || rank_id == aaNaturesBoon || rank_id == aaAncestralAid) {
		if(GetBuildRank(DRUID, RB_DRU_SPIRITOFTHEWOOD) || GetBuildRank(DRUID, RB_DRU_NATURESBOON) || GetBuildRank(SHAMAN, RB_SHM_ANCESTRALAID)) {
			cooldown = 16;
			if (GetLevel() < 10)  manacost = 20;
			else if (GetLevel() < 31) manacost = GetLevel() * 2.6f;
			else if (GetLevel() < 41) manacost = GetLevel() * 4.6f;
			else if (GetLevel() < 51) manacost = GetLevel() * 5.6f;
			else  manacost = GetLevel() * 7.5f;
			
			if (rank_id == aaNaturesBoon) {
				cooldown = 85 - (12 * GetBuildRank(DRUID, RB_DRU_NATURESBOON));
				if (cooldown < 20) {
					cooldown = 20;
				}
			}
		}
	} else if (rank_id == aaConvergenceofSpirits) {
		if(GetBuildRank(DRUID, RB_DRU_CONVERGENCEOFSPIRITS))
			manacost = GetMaxMana() * 0.02f; //2% of mana for cos
	} else if (rank_id == aaHandofPiety) {
		if(GetBuildRank(PALADIN, RB_PAL_HANDOFPIETY) > 0)
			manacost = GetMaxMana() * 0.01f;
	} else if (rank_id == aaFadingMemories) {
		if(GetBuildRank(BARD, RB_BRD_FADINGMEMORIES) > 0) {
			manacost = (GetMaxMana() * 0.5f) - ((GetMaxMana() * 0.3f) * 0.2f * GetBuildRank(BARD, RB_BRD_FADINGMEMORIES));
	} else if (rank_id == aaEscape)
		if(GetBuildRank(ROGUE, RB_ROG_ESCAPE)) {
			//manacost = (GetMaxEndurance() * 0.5f) - ((GetMaxEndurance() * 0.3f) * 0.2f * GetBuildRank(ROGUE, RB_ROG_ESCAPE));
			//TODO: Figure out endurance cost calculation prior to this executing
		}
	} else if (rank_id == aaSpiritCall) {
		if(GetBuildRank(SHAMAN, RB_SHM_SPIRITCALL)) {
			spellid = 164;
			if (GetLevel() < 14) {
				cooldown = 16;
			} else if (GetLevel() < 22) {
				cooldown = 16;
			} else if (GetLevel() < 30) {
				cooldown = 16;
			} else if (GetLevel() < 38) {
				cooldown = 16;
			} else if (GetLevel() < 46) {
				cooldown = 16;
			} else if (GetLevel() < 52) {
				cooldown = 16;
			} else if (GetLevel() < 58) {
				cooldown = 16;
			} else {
				cooldown = 16;
			}
		}
	} else if (rank_id == aaCalloftheAncients) {
		if (GetBuildRank(SHAMAN, RB_SHM_CALLOFTHEANCIENTS)) {
			cooldown = 900;
		}
	} else if (rank_id == aaSteadfastServant) {
		if(GetBuildRank(SHADOWKNIGHT, RB_SHD_STEADFASTSERVANT)) {
			if (GetLevel() < 14) { //leering corpse 7
				spellid = 491;
				manacost = 40;
				cooldown = 16;
			} else if (GetLevel() < 22) { //bone walk 14
				spellid = 351;
				manacost = 80;
				cooldown = 16;
			} else if (GetLevel() < 30) { //convoke shadow 22
				spellid = 362;
				manacost = 120;
				cooldown = 16;
			} else if (GetLevel() < 38) { //Restless Bones 30
				spellid = 492;
				manacost = 160;
				cooldown = 16;
			} else if (GetLevel() < 46) { //Aniamte Dead 38
				spellid = 440;
				manacost = 200;
				cooldown = 16;
			} else if (GetLevel() < 52) { //Summon Dead 46
				spellid = 441;
				manacost = 290;
				cooldown = 16;
			} else if (GetLevel() < 58) { //Malignant Dead 52
				spellid = 442;
				manacost = 390;
				cooldown = 16;
			} else { //Cackling Bones 58
				spellid = 495;
				manacost = 450;
				cooldown = 16;
			}		
		}
	} else if (rank_id == aaLessonoftheDevoted) {
		rb_rank = GetBuildRank(BARD, RB_BRD_KINSONG);
		if (rb_rank > 0) { spellid = 6239; cooldown = 360 - (30 * rb_rank); }
		rb_rank = GetBuildRank(CLERIC, RB_CLR_HARMONICBALANCE);
		if (rb_rank > 0) { spellid = 6233; cooldown = 360 - (30 * rb_rank); }
		rb_rank = GetBuildRank(DRUID, RB_DRU_NATURESBLIGHT);
		if (rb_rank > 0) { spellid = 6237; cooldown = 120 - (10 * rb_rank); }
		rb_rank = GetBuildRank(MONK, RB_MNK_GRACEOFTHEORDER);
		if (rb_rank > 0) { spellid = 6238; cooldown = 360 - (30 * rb_rank); }
		rb_rank = GetBuildRank(NECROMANCER, RB_NEC_SERVANTOFBLOOD);
		if (rb_rank > 0) { spellid = 6242; cooldown = 360 - (30 * rb_rank); }
		rb_rank = GetBuildRank(PALADIN, RB_PAL_FLAMESOFREDEMPTION);
		if (rb_rank > 0) { spellid = 6234; cooldown = 360 - (30 * rb_rank); }
		rb_rank = GetBuildRank(ROGUE, RB_ROG_ASSASSINSTAINT);
		if (rb_rank > 0) { spellid = 6240; cooldown = 360 - (30 * rb_rank); }
		rb_rank = GetBuildRank(SHAMAN, RB_SHM_FATESEERSBOON);
		if (rb_rank > 0) { spellid = 6241; cooldown = 360 - (30 * rb_rank); }
		rb_rank = GetBuildRank(SHADOWKNIGHT, RB_SHD_REAPERSSTRIKE);
		if (rb_rank > 0) { spellid = 6236; cooldown = 360 - (30 * rb_rank); }
	} else if (rank_id == aaBoastfulBellow) {
		rb_rank = GetBuildRank(BARD, RB_BRD_BOASTFULBELLOW);
		if(rb_rank) {
			cooldown = rank->recast_time - (rb_rank * 2);
		}
		
	} else if (rank_id == aaPurifyBody) {
		cooldown = 5;  //bring this in parity with Paladin
	}

	manacost = ModifyManaUsage(manacost, spellid, GetTarget(), false);
	if(!IsValidSpell(spellid)) {
		return;
	}

	if(!CanUseAlternateAdvancementRank(rank)) {
		return;
	}

	//make sure it is not a passive
	if(!rank->effects.empty()) {
		return;
	}

	uint32 charges = 0;
	// We don't have the AA
	if (!GetAA(rank_id, &charges))
		return;

	//if expendable make sure we have charges
	if(ability->charges > 0 && charges < 1)
		return;

	//check cooldown
	if(!p_timers.Expired(&database, rank->spell_type + pTimerAAStart)) {
		uint32 aaremain = p_timers.GetRemainingTime(rank->spell_type + pTimerAAStart);
		uint32 aaremain_hr = aaremain / (60 * 60);
		uint32 aaremain_min = (aaremain / 60) % 60;
		uint32 aaremain_sec = aaremain % 60;

		if(aaremain_hr >= 1) {
			Message(13, "You can use this ability again in %u hour(s) %u minute(s) %u seconds",
			aaremain_hr, aaremain_min, aaremain_sec);
		}
		else {
			Message(13, "You can use this ability again in %u minute(s) %u seconds",
			aaremain_min, aaremain_sec);
		}

		return;
	}

	if (!IsCastWhileInvis(spellid))
		CommonBreakInvisible();

	if (spells[spellid].sneak && (!hidden || (hidden && (Timer::GetCurrentTime() - tmHidden) < 4000))) {
		Message_StringID(MT_SpellFailure, SNEAK_RESTRICT);
		return;
	}
	
	// Modern clients don't require pet targeted for AA casts that are ST_Pet
	if (spells[spellid].targettype == ST_Pet || spells[spellid].targettype == ST_SummonedPet)
		target_id = GetPetID();

	// Bards can cast instant cast AAs while they are casting another song
	if(spells[spellid].cast_time == 0 && GetClass() == BARD && IsBardSong(casting_spell_id)) {
		if(!SpellFinished(spellid, entity_list.GetMob(target_id), EQEmu::CastingSlot::AltAbility, spells[spellid].mana, -1, spells[spellid].ResistDiff, false)) {
			return;
		}
		ExpendAlternateAdvancementCharge(ability->id);
	} else {
		if(!CastSpell(spellid, target_id, EQEmu::CastingSlot::AltAbility, -1, -1, 0, -1, rank->spell_type + pTimerAAStart, cooldown, nullptr, rank->id)) {
			return;
		}
	}

	CastToClient()->GetPTimers().Start(rank->spell_type + pTimerAAStart, cooldown);
	SendAlternateAdvancementTimer(rank->spell_type, 0, 0);
}

int Mob::GetAlternateAdvancementCooldownReduction(AA::Rank *rank_in) {
	if(!rank_in) {
		return 0;
	}

	AA::Ability *ability_in = rank_in->base_ability;
	if(!ability_in) {
		return 0;
	}

	for(auto &aa : aa_ranks) {
		auto ability_rank = zone->GetAlternateAdvancementAbilityAndRank(aa.first, aa.second.first);
		auto ability = ability_rank.first;
		auto rank = ability_rank.second;

		if(!ability) {
			continue;
		}

		for(auto &effect : rank->effects) {
			if(effect.effect_id == SE_HastenedAASkill && effect.base2 == ability_in->id) {
				return effect.base1;
			}
		}
	}

	return 0;
}

void Mob::ExpendAlternateAdvancementCharge(uint32 aa_id) {
	for(auto &iter : aa_ranks) {
		AA::Ability *ability = zone->GetAlternateAdvancementAbility(iter.first);
		if(ability && aa_id == ability->id) {
			if(iter.second.second > 0) {
				iter.second.second -= 1;

				if(iter.second.second == 0) {
					if(IsClient()) {
						AA::Rank *r = ability->GetRankByPointsSpent(iter.second.first);
						if(r) {
							CastToClient()->GetEPP().expended_aa += r->cost;
						}
					}
					if (IsClient()) {
						auto c = CastToClient();
						c->RemoveExpendedAA(ability->first_rank_id);
					}
					aa_ranks.erase(iter.first);
				}

				if(IsClient()) {
					Client *c = CastToClient();
					c->SaveAA();
					c->SendAlternateAdvancementPoints();
				}
			}

			return;
		}
	}
}

bool ZoneDatabase::LoadAlternateAdvancement(Client *c) {
	c->ClearAAs();
	std::string query = StringFormat(
		"SELECT "
		"aa_id, "
		"aa_value, "
		"charges "
		"FROM "
		"`character_alternate_abilities` "
		"WHERE `id` = %u", c->CharacterID());
	MySQLRequestResult results = database.QueryDatabase(query);

	int i = 0;
	for(auto row = results.begin(); row != results.end(); ++row) {
		uint32 aa = atoi(row[0]);
		uint32 value = atoi(row[1]);
		uint32 charges = atoi(row[2]);

		auto rank = zone->GetAlternateAdvancementRank(aa);
		if(!rank) {
			continue;
		}

		auto ability = rank->base_ability;
		if(!ability) {
			continue;
		}

		rank = ability->GetRankByPointsSpent(value);

		if(c->CanUseAlternateAdvancementRank(rank)) {
			c->GetPP().aa_array[i].AA = aa;
			c->GetPP().aa_array[i].value = value;
			c->GetPP().aa_array[i].charges = charges;
			c->SetAA(aa, value, charges);
			i++;
		}
	}

	return true;
}

AA::Ability *Zone::GetAlternateAdvancementAbility(int id) {
	auto iter = aa_abilities.find(id);
	if(iter != aa_abilities.end()) {
		return iter->second.get();
	}

	return nullptr;
}

AA::Ability *Zone::GetAlternateAdvancementAbilityByRank(int rank_id) {
	AA::Rank *rank = GetAlternateAdvancementRank(rank_id);

	if(!rank)
		return nullptr;

	return rank->base_ability;
}

AA::Rank *Zone::GetAlternateAdvancementRank(int rank_id) {
	auto iter = aa_ranks.find(rank_id);
	if(iter != aa_ranks.end()) {
		return iter->second.get();
	}

	return nullptr;
}

std::pair<AA::Ability*, AA::Rank*> Zone::GetAlternateAdvancementAbilityAndRank(int id, int points_spent) {
	AA::Ability *ability = GetAlternateAdvancementAbility(id);

	if(!ability) {
		return std::make_pair(nullptr, nullptr);
	}

	AA::Rank *rank = ability->GetRankByPointsSpent(points_spent);
	if(!rank) {
		return std::make_pair(nullptr, nullptr);
	}

	return std::make_pair(ability, rank);
}

uint32 Mob::GetAA(uint32 rank_id, uint32 *charges) const {
	if(zone) {
		AA::Ability *ability = zone->GetAlternateAdvancementAbilityByRank(rank_id);
		if(!ability)
			return 0;

		auto iter = aa_ranks.find(ability->id);
		if(iter != aa_ranks.end()) {
			if(charges) {
				*charges = iter->second.second;
			}
			return iter->second.first;
		}
	}
	return 0;
}

bool Mob::IsFeatUnlocked(int feat_id) {
	if (!IsClient()) return false;
	return (CastToClient()->IsTaskCompleted(feat_id));
}

uint32 Mob::GetAAByAAID(uint32 aa_id, uint32 *charges) const {
	if(zone) {
		AA::Ability *ability = zone->GetAlternateAdvancementAbility(aa_id);

		if(!ability)
			return 0;

		auto iter = aa_ranks.find(ability->id);
		if(iter != aa_ranks.end()) {
			if(charges) {
				*charges = iter->second.second;
			}
			return iter->second.first;
		}
	}

	return 0;
}

bool Mob::SetAA(uint32 rank_id, uint32 new_value, uint32 charges) {
	if(zone) {
		AA::Ability *ability = zone->GetAlternateAdvancementAbilityByRank(rank_id);

		if(!ability) {
			return false;
		}

		if(new_value > ability->GetMaxLevel(this)) {
			return false;
		}

		aa_ranks[ability->id] = std::make_pair(new_value, charges);
	}

	return true;
}


bool Mob::CanUseAlternateAdvancementRank(AA::Rank *rank) {
	AA::Ability *ability = rank->base_ability;

	if(!ability)
		return false;

	if(!(ability->classes & (1 << GetClass()))) {
		return false;
	}

	// Passive and Active Shroud AAs
	// For now we skip them
	if(ability->category == 3 || ability->category == 4) {
		return false;
	}

	//the one titanium hack i will allow
	//just to make sure we dont crash the client with newer aas
	//we'll exclude any expendable ones
	if(IsClient() && CastToClient()->ClientVersionBit() & EQEmu::versions::bit_TitaniumAndEarlier) {
		if(ability->charges > 0) {
			return false;
		}
	}

	if(IsClient()) {
		if(rank->expansion && !(CastToClient()->GetPP().expansions & (1 << (rank->expansion - 1)))) {
			return false;
		}
	} else {
		if(rank->expansion && !(RuleI(World, ExpansionSettings) & (1 << (rank->expansion - 1)))) {
			return false;
		}
	}

	auto race = GetPlayerRaceValue(GetBaseRace());
	race = race > 16 ? 1 : race;
	if(!(ability->races & (1 << (race - 1)))) {
		return false;
	}

	auto deity = GetDeityBit();
	if(!(ability->deities & deity)) {
		return false;
	}

	if(IsClient() && CastToClient()->Admin() < ability->status) {
		return false;
	}

	if(GetBaseRace() == 522) {
		//drakkin_heritage
		if(!(ability->drakkin_heritage & (1 << GetDrakkinHeritage()))) {
			return false;
		}
	}

	return true;
}

bool Mob::CanPurchaseAlternateAdvancementRank(AA::Rank *rank, bool check_price, bool check_grant) {
	AA::Ability *ability = rank->base_ability;

	if(!ability)
		return false;

	if(!CanUseAlternateAdvancementRank(rank)) {
		return false;
	}

	//You can't purchase grant only AAs they can only be assigned
	if(check_grant && ability->grant_only) {
		return false;
	}

	//check level req
	//if(rank->level_req > GetLevel()) {
	//	return false;
	//}

	uint32 current_charges = 0;
	auto points = GetAA(rank->id, &current_charges);

	//check that we are on previous rank already (if exists)
	//grant ignores the req to own the previous rank.
	if(check_grant && rank->prev) {
		if(points != rank->prev->current_value) {
			return false;
		}
	}

	//check that we aren't already on this rank or one ahead of us
	if(points >= rank->current_value) {
		return false;
	}

	//if expendable only let us purchase if we have no charges already
	//not quite sure on how this functions client side atm
	//I intend to look into it later to make sure the behavior is right
	if(ability->charges > 0 && current_charges > 0) {
		return false;
	}

	//check prereqs
	for(auto &prereq : rank->prereqs) {
		AA::Ability *prereq_ability = zone->GetAlternateAdvancementAbility(prereq.first);

		if(prereq_ability) {
			auto ranks = GetAA(prereq_ability->first_rank_id);
			if(ranks < prereq.second) {
				return false;
			}
		}
	}

	//check price, if client
	if(check_price && IsClient()) {
		if(rank->cost > CastToClient()->GetAAPoints()) {
			return false;
		}
	}

	return true;
}

void Zone::LoadAlternateAdvancement() {
	Log(Logs::General, Logs::Status, "Loading Alternate Advancement Data...");
	if(!database.LoadAlternateAdvancementAbilities(aa_abilities,
		aa_ranks))
	{
		aa_abilities.clear();
		aa_ranks.clear();
		Log(Logs::General, Logs::Status, "Failed to load Alternate Advancement Data");
		return;
	}

	Log(Logs::General, Logs::Status, "Processing Alternate Advancement Data...");
	for(const auto &ability : aa_abilities) {
		ability.second->first = GetAlternateAdvancementRank(ability.second->first_rank_id);

		//process these ranks
		AA::Rank *current = ability.second->first;
		int i = 1;
		int prev_id = -1;
		while(current) {
			current->prev_id = prev_id;
			current->prev = GetAlternateAdvancementRank(current->prev_id);
			current->next = GetAlternateAdvancementRank(current->next_id);
			current->base_ability = ability.second.get();
			current->current_value = i;

			if(current->prev) {
				current->total_cost = current->cost + current->prev->total_cost;

				//check prereqs here
				for(auto &prev_prereq : current->prev->prereqs) {
					//if prev has an aa we dont have set
					//	then set it here too
					//if prev has an aa we have
					//	then set to whichever is highest

					auto iter = current->prereqs.find(prev_prereq.first);
					if(iter == current->prereqs.end()) {
						//not found
						current->prereqs[prev_prereq.first] = prev_prereq.second;
					} else {
						//they already have it too!
						auto points = std::max(iter->second, prev_prereq.second);
						current->prereqs[iter->first] = points;
					}
				}
			}
			else {
				current->prev_id = -1;
				current->total_cost = current->cost;
			}

			if(!current->next) {
				current->next_id = -1;
			}

			i++;
			prev_id = current->id;
			current = current->next;
		}
	}

	Log(Logs::General, Logs::Status, "Loaded Alternate Advancement Data");
}

bool ZoneDatabase::LoadAlternateAdvancementAbilities(std::unordered_map<int, std::unique_ptr<AA::Ability>> &abilities,
													std::unordered_map<int, std::unique_ptr<AA::Rank>> &ranks)
{
	Log(Logs::General, Logs::Status, "Loading Alternate Advancement Abilities...");
	abilities.clear();
	std::string query = "SELECT id, name, category, classes, races, deities, drakkin_heritage, status, type, charges, "
		"grant_only, first_rank_id FROM aa_ability WHERE enabled = 1";
	auto results = QueryDatabase(query);
	if(results.Success()) {
		for(auto row = results.begin(); row != results.end(); ++row) {
			auto ability = new AA::Ability;
			ability->id = atoi(row[0]);
			ability->name = row[1];
			ability->category = atoi(row[2]);
			//EQ client has classes left shifted by one bit for some odd reason
			ability->classes = atoi(row[3]) << 1;
			ability->races = atoi(row[4]);
			ability->deities = atoi(row[5]);
			ability->drakkin_heritage = atoi(row[6]);
			ability->status = atoi(row[7]);
			ability->type = atoi(row[8]);
			ability->charges = atoi(row[9]);
			ability->grant_only = atoi(row[10]) != 0 ? true : false;
			ability->first_rank_id = atoi(row[11]);
			ability->first = nullptr;

			abilities[ability->id] = std::unique_ptr<AA::Ability>(ability);
		}
	} else {
		Log(Logs::General, Logs::Error, "Failed to load Alternate Advancement Abilities");
		return false;
	}

	Log(Logs::General, Logs::Status, "Loaded %d Alternate Advancement Abilities", (int)abilities.size());

	Log(Logs::General, Logs::Status, "Loading Alternate Advancement Ability Ranks...");
	ranks.clear();
	query = "SELECT id, upper_hotkey_sid, lower_hotkey_sid, title_sid, desc_sid, cost, level_req, spell, spell_type, recast_time, "
		"next_id, expansion FROM aa_ranks";
	results = QueryDatabase(query);
	if(results.Success()) {
		for(auto row = results.begin(); row != results.end(); ++row) {
			auto rank = new AA::Rank;
			rank->id = atoi(row[0]);
			rank->upper_hotkey_sid = atoi(row[1]);
			rank->lower_hotkey_sid = atoi(row[2]);
			rank->title_sid = atoi(row[3]);
			rank->desc_sid = atoi(row[4]);
			rank->cost = atoi(row[5]);
			rank->level_req = atoi(row[6]);
			rank->spell = atoi(row[7]);
			rank->spell_type = atoi(row[8]);
			rank->recast_time = atoi(row[9]);
			rank->next_id = atoi(row[10]);
			rank->expansion = atoi(row[11]);
			rank->base_ability = nullptr;
			rank->total_cost = 0;
			rank->prev_id = -1;
			rank->next = nullptr;
			rank->prev = nullptr;

			ranks[rank->id] = std::unique_ptr<AA::Rank>(rank);
		}
	} else {
		Log(Logs::General, Logs::Error, "Failed to load Alternate Advancement Ability Ranks");
		return false;
	}

	Log(Logs::General, Logs::Status, "Loaded %d Alternate Advancement Ability Ranks", (int)ranks.size());

	Log(Logs::General, Logs::Status, "Loading Alternate Advancement Ability Rank Effects...");
	query = "SELECT rank_id, slot, effect_id, base1, base2 FROM aa_rank_effects";
	results = QueryDatabase(query);
	if(results.Success()) {
		for(auto row = results.begin(); row != results.end(); ++row) {
			AA::RankEffect effect;
			int rank_id = atoi(row[0]);
			effect.slot = atoi(row[1]);
			effect.effect_id = atoi(row[2]);
			effect.base1 = atoi(row[3]);
			effect.base2 = atoi(row[4]);

			if(effect.slot < 1)
				continue;

			if(ranks.count(rank_id) > 0) {
				AA::Rank *rank = ranks[rank_id].get();
				rank->effects.push_back(effect);
			}
		}
	} else {
		Log(Logs::General, Logs::Error, "Failed to load Alternate Advancement Ability Rank Effects");
		return false;
	}

	Log(Logs::General, Logs::Status, "Loaded Alternate Advancement Ability Rank Effects");

	Log(Logs::General, Logs::Status, "Loading Alternate Advancement Ability Rank Prereqs...");
	query = "SELECT rank_id, aa_id, points FROM aa_rank_prereqs";
	results = QueryDatabase(query);
	if(results.Success()) {
		for(auto row = results.begin(); row != results.end(); ++row) {
			int rank_id = atoi(row[0]);
			int aa_id = atoi(row[1]);
			int points = atoi(row[2]);

			if(aa_id <= 0 || points <= 0) {
				continue;
			}

			if(ranks.count(rank_id) > 0) {
				AA::Rank *rank = ranks[rank_id].get();
				rank->prereqs[aa_id] = points;
			}
		}
	} else {
		Log(Logs::General, Logs::Error, "Failed to load Alternate Advancement Ability Rank Prereqs");
		return false;
	}

	Log(Logs::General, Logs::Status, "Loaded Alternate Advancement Ability Rank Prereqs");

	return true;
}

bool Mob::CheckAATimer(int timer)
{
	if (timer >= aaTimerMax)
		return false;
	if (aa_timers[timer].Enabled()) {
		if (aa_timers[timer].Check(false)) {
			aa_timers[timer].Disable();
			return false;
		} else {
			return true;
		}
	}
	return false;
}


void Client::RebuildAA() {
	SendClearAA();
	RefundAA();

	memset(&m_pp.aa_array[0], 0, sizeof(AA_Array) * MAX_PP_AA_ARRAY);
	
	if (GetBuildRank(BARD, RB_BRD_BOASTFULBELLOW)) SetAA(aaBoastfulBellow, 1);
	if (GetBuildRank(BARD, RB_BRD_DANCEOFBLADES)) SetAA(aaDanceofBlades, 1);
	if (GetBuildRank(CLERIC, RB_CLR_DIVINEAVATAR)) SetAA(aaDivineAvatar, 1);
	if (GetBuildRank(CLERIC, RB_CLR_CELESTIALREGENERATION)) SetAA(aaCelestialRegeneration, 1);
	if (GetBuildRank(CLERIC, RB_CLR_DIVINEARBITRATION)) SetAA(aaDivineArbitration, 1);
	if (GetBuildRank(CLERIC, RB_CLR_DIVINERESURRECTION)) SetAA(aaDivineResurrection, 1);
	if (GetBuildRank(CLERIC, RB_CLR_DIVINERETRIBUTION)) SetAA(aaDivineRetribution, 1);
	if (GetBuildRank(CLERIC, RB_CLR_TURNUNDEAD)) SetAA(aaTurnUndead2, 1);
	if (GetBuildRank(CLERIC, RB_CLR_EXQUISITEBENEDICTION)) SetAA(aaExquisiteBenediction, 1);
	if (GetBuildRank(DRUID, RB_DRU_TELEPORTBIND)) SetAA(aaTeleportBind, 1);
	if (GetBuildRank(DRUID, RB_DRU_ENTRAP)) SetAA(aaEntrap, 1);
	if (GetBuildRank(DRUID, RB_DRU_EXODUS)) SetAA(aaExodus, 1);
	if (GetBuildRank(DRUID, RB_DRU_CALLOFTHEWILD)) SetAA(aaCalloftheWild, 1);
	if (GetBuildRank(DRUID, RB_DRU_SECONDARYRECALL)) SetAA(aaSecondaryRecall, 1);
	if (GetBuildRank(DRUID, RB_DRU_DIRECHARM)) SetAA(aaDireCharm, 1);
	if (GetBuildRank(DRUID, RB_DRU_CONVERGENCEOFSPIRITS)) SetAA(aaConvergenceofSpirits, 1);
	if (GetBuildRank(DRUID, RB_DRU_SPIRITOFTHEWOOD)) SetAA(aaSpiritoftheWood, 1);
	if (GetBuildRank(DRUID, RB_DRU_NATURESBOON)) SetAA(aaNaturesBoon, 1);
	if (GetBuildRank(DRUID, RB_DRU_NATURESGUARDIAN)) SetAA(aaNaturesGuardian, 1);
	if (GetBuildRank(ENCHANTER, RB_ENC_SOOTHINGWORDS)) SetAA(aaSoothingWords, 1);
	if (GetBuildRank(ENCHANTER, RB_ENC_MINDOVERMATTER)) SetAA(aaMindOverMatter, 1);
	if (GetBuildRank(ENCHANTER, RB_ENC_COLORSHOCK)) SetAA(aaColorShock, 1);
	if (GetBuildRank(MAGICIAN, RB_MAG_SHAREDHEALTH)) SetAA(aaSharedHealth, 1);
	if (GetBuildRank(MAGICIAN, RB_MAG_DIMENSIONALSHIELD)) SetAA(aaDimensionalShield, 1);
	if (GetBuildRank(MAGICIAN, RB_MAG_HOSTINTHESHELL)) SetAA(aaHostintheShell, 1);
	if (GetBuildRank(MAGICIAN, RB_MAG_HEARTOFSTONE)) SetAA(aaHeartofStone, 1);
	if (GetBuildRank(MAGICIAN, RB_MAG_IMPROVEDRECLAIMENERGY)) SetAA(aaImprovedReclaimEnergy, 1);
	if (GetBuildRank(MAGICIAN, RB_MAG_TURNSUMMONED)) SetAA(aaTurnSummoned2, 1);
	if (GetBuildRank(MAGICIAN, RB_MAG_HEARTOFVAPOR)) SetAA(aaHeartofVapor, 1);
	if (GetBuildRank(MAGICIAN, RB_MAG_MODULATIONSHARD)) SetAA(aaSmallModulationShard, 1);
	if (GetBuildRank(MAGICIAN, RB_MAG_HEARTOFICE)) SetAA(aaHeartofIce, 1);
	if (GetBuildRank(MAGICIAN, RB_MAG_SUSPENDEDMINION)) SetAA(aaSuspendedMinion, 1);
	if (GetBuildRank(MAGICIAN, RB_MAG_CALLOFTHEHERO)) SetAA(aaCalloftheHero, 1);
	if (GetBuildRank(MAGICIAN, RB_MAG_MENDCOMPANION)) SetAA(aaMendCompanion, 1);
	if (GetBuildRank(MAGICIAN, RB_MAG_CLOCKWORKMERCHANT)) SetAA(aaClockworkBanker, 1);
	if (GetBuildRank(MAGICIAN, RB_MAG_HEARTOFFLAMES)) SetAA(aaHeartofFlames, 1);
	if (GetBuildRank(MAGICIAN, RB_MAG_COMPANIONOFNECESSITY)) SetAA(aaCompanionofNecessity, 1);
	if (GetBuildRank(MAGICIAN, RB_MAG_SERVANTOFRO)) SetAA(aaServantofRo, 1);
	if (GetBuildRank(MONK, RB_MNK_PURIFYBODY)) SetAA(aaPurifyBody, 1);
	if (GetBuildRank(NECROMANCER, RB_NEC_LIFEBURN)) SetAA(aaLifeBurn, 1);
	if (GetBuildRank(NECROMANCER, RB_NEC_BLOODMAGIC)) SetAA(aaBloodMagic, 1);
	if (GetBuildRank(NECROMANCER, RB_NEC_DYINGGRASP)) SetAA(aaDyingGrasp, 1);
	if (GetBuildRank(PALADIN, RB_PAL_HANDOFPIETY)) SetAA(aaHandofPiety, 1);
	if (GetBuildRank(PALADIN, RB_PAL_PURIFICATION)) SetAA(aaPurification, 1);
	if (GetBuildRank(PALADIN, RB_PAL_ACTOFVALOR)) SetAA(aaActOfValor, 1);
	if (GetBuildRank(PALADIN, RB_PAL_DIVINESTUN)) SetAA(aaDivineStun, 1);
	if (GetBuildRank(ROGUE, RB_ROG_APPRAISAL)) SetAA(aaAppraisal, 1);
	if (GetBuildRank(SHADOWKNIGHT, RB_SHD_LEECHTOUCH)) SetAA(aaLeechTouch, 1);
	if (GetBuildRank(SHADOWKNIGHT, RB_SHD_EMBRACEDEATH)) SetAA(aaDeathPeace2, 1);
	if (GetBuildRank(SHADOWKNIGHT, RB_SHD_STEADFASTSERVANT)) SetAA(aaSteadfastServant, 1);
	if (GetBuildRank(SHAMAN, RB_SHM_ANCESTRALAID)) SetAA(aaAncestralAid, 1);
	if (GetBuildRank(SHAMAN, RB_SHM_PURIFYSOUL)) SetAA(aaPurifySoul, 1);
	if (GetBuildRank(SHAMAN, RB_SHM_SPIRITCALL)) SetAA(aaSpiritCall, 1);
	if (GetBuildRank(SHAMAN, RB_SHM_VIRULENTPARALYSIS)) SetAA(aaVirulentParalysis, 1);
	if (GetBuildRank(SHAMAN, RB_SHM_RABIDBEAR)) SetAA(aaRabidBear, 1);
	if (GetBuildRank(SHAMAN, RB_SHM_ANCESTRALGUARD)) SetAA(aaAncestralGuard, 1);
	if (GetBuildRank(SHAMAN, RB_SHM_FERALSWIPE)) SetAA(aaFeralSwipe, 1);
	if (GetBuildRank(SHAMAN, RB_SHM_CANNIBALIZE)) SetAA(aaCannibalization, 1);
	if (GetBuildRank(SHAMAN, RB_SHM_PARAGONOFSPIRIT)) SetAA(aaParagonofSpirit, 1);
	if (GetBuildRank(BARD, RB_BRD_KINSONG)) SetAA(aaLessonoftheDevoted, 1);
	if (GetBuildRank(CLERIC, RB_CLR_HARMONICBALANCE)) SetAA(aaLessonoftheDevoted, 1);
	if (GetBuildRank(DRUID, RB_DRU_NATURESBLIGHT)) SetAA(aaLessonoftheDevoted, 1);
	if (GetBuildRank(MONK, RB_MNK_GRACEOFTHEORDER)) SetAA(aaLessonoftheDevoted, 1);
	if (GetBuildRank(NECROMANCER, RB_NEC_SERVANTOFBLOOD)) SetAA(aaLessonoftheDevoted, 1);
	if (GetBuildRank(PALADIN, RB_PAL_FLAMESOFREDEMPTION)) SetAA(aaLessonoftheDevoted, 1);
	if (GetBuildRank(ROGUE, RB_ROG_ASSASSINSTAINT)) SetAA(aaLessonoftheDevoted, 1);
	if (GetBuildRank(SHADOWKNIGHT, RB_SHD_REAPERSSTRIKE)) SetAA(aaLessonoftheDevoted, 1);
	if (GetBuildRank(SHAMAN, RB_SHM_FATESEERSBOON)) SetAA(aaLessonoftheDevoted, 1);

	if (IsTaskCompleted(FEAT_PETDISCIPLINE)) SetAA(aaPetDiscipline, 1);
	if (IsTaskCompleted(FEAT_INNATERUNSPEED)) SetAA(aaInnateRunSpeed, 3);
	if (IsTaskCompleted(FEAT_PETAFFINITY)) SetAA(aaPetAffinity, 1);

	SetAA(aaOrigin, 1);
	SendAlternateAdvancementPoints();
	SendAlternateAdvancementStats();
	CalcBonuses();
	SaveAA();

	/*
	for (int i = 0; i < _maxLeaderAA; ++i)
		m_pp.leader_abilities.ranks[i] = 0;

	m_pp.group_leadership_points = 0;
	m_pp.raid_leadership_points = 0;
	m_pp.group_leadership_exp = 0;
	m_pp.raid_leadership_exp = 0;

	database.DeleteCharacterLeadershipAAs(CharacterID());*/
	
}