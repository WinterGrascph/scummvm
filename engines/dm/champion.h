/* ScummVM - Graphic Adventure Engine
*
* ScummVM is the legal property of its developers, whose names
* are too numerous to list here. Please refer to the COPYRIGHT
* file distributed with this source distribution.
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*
*/

/*
* Based on the Reverse Engineering work of Christophe Fontanel,
* maintainer of the Dungeon Master Encyclopaedia (http://dmweb.free.fr/)
*/

#ifndef DM_CHAMPION_H
#define DM_CHAMPION_H

#include "common/str.h"

#include "dm.h"
#include "gfx.h"

namespace DM {

#define k0x4000_IgnoreObjectModifiers 0x4000 // @ MASK0x4000_IGNORE_OBJECT_MODIFIERS     
#define k0x8000_IgnoreTemporaryExperience 0x8000 // @ MASK0x8000_IGNORE_TEMPORARY_EXPERIENCE 

extern Box g54_BoxChampionIcons[4]; // @ G0054_ai_Graphic562_Box_ChampionIcons
extern Color g46_ChampionColor[4]; // @ G0046_auc_Graphic562_ChampionColor

extern int16 g39_LightPowerToLightAmount[16]; // @ G0039_ai_Graphic562_LightPowerToLightAmount

class Scent {
	uint16 _scent;
public:
	explicit Scent(uint16 scent = 0): _scent(scent) {}

	uint16 getMapX() { return _scent & 0x1F; }
	uint16 getMapY() { return (_scent >> 5) & 0x1F; }
	uint16 getMapIndex() { return (_scent >> 10) & 0x3F; }

	void setMapX(uint16 val) { _scent = (_scent & ~0x1F) & (val & 0x1F); }
	void setMapY(uint16 val) { _scent = (_scent & ~(0x1F << 5)) & (val & 0x1F); }
	void setMapIndex(uint16 val) { _scent = (_scent & ~(0x1F << 10)) & (val & 0x3F); }
}; // @ SCENT

class Party {
public:
	Party() {
		_magicalLightAmount = _event73Count_ThievesEye = _event79Count_Footprints = _shieldDefense = 0;
		_fireShieldDefense = _spellShieldDefense = _scentCount = _freezeLifeTicks = _firstScentIndex = 0;
		_lastScentIndex = _event71Count_Invisibility = 0;
		for (int16 i = 0; i < 24; ++i)
			_scentStrengths[i] = 0;
	}
	int16 _magicalLightAmount;
	byte _event73Count_ThievesEye;
	byte _event79Count_Footprints;
	int16 _shieldDefense;

	int16 _fireShieldDefense;
	int16 _spellShieldDefense;
	byte _scentCount;
	byte _freezeLifeTicks;
	byte _firstScentIndex;

	byte _lastScentIndex;
	Scent _scents[24]; // if I remember correctly, user defined default constructors are always called
	byte _scentStrengths[24];
	byte _event71Count_Invisibility;
}; // @  PARTY

enum IconIndice {
	kM1_IconIndiceNone = -1, // @ CM1_ICON_NONE
	k0_IconIndiceJunkCompassNorth = 0, // @ C000_ICON_JUNK_COMPASS_NORTH
	k3_IconIndiceJunkCompassWest = 3, // @ C003_ICON_JUNK_COMPASS_WEST
	k4_IconIndiceWeaponTorchUnlit = 4, // @ C004_ICON_WEAPON_TORCH_UNLIT
	k7_IconIndiceWeaponTorchLit = 7, // @ C007_ICON_WEAPON_TORCH_LIT
	k8_IconIndiceJunkWater = 8, // @ C008_ICON_JUNK_WATER
	k9_IconIndiceJunkWaterSkin = 9, // @ C009_ICON_JUNK_WATERSKIN
	k10_IconIndiceJunkJewelSymalUnequipped = 10, // @ C010_ICON_JUNK_JEWEL_SYMAL_UNEQUIPPED
	k11_IconIndiceJunkJewelSymalEquipped = 11, // @ C011_ICON_JUNK_JEWEL_SYMAL_EQUIPPED
	k12_IconIndiceJunkIllumuletUnequipped = 12, // @ C012_ICON_JUNK_ILLUMULET_UNEQUIPPED
	k13_IconIndiceJunkIllumuletEquipped = 13, // @ C013_ICON_JUNK_ILLUMULET_EQUIPPED
	k14_IconIndiceWeaponFlamittEmpty = 14, // @ C014_ICON_WEAPON_FLAMITT_EMPTY
	k16_IconIndiceWeaponEyeOfTimeEmpty = 16, // @ C016_ICON_WEAPON_EYE_OF_TIME_EMPTY
	k18_IconIndiceWeaponStormringEmpty = 18, // @ C018_ICON_WEAPON_STORMRING_EMPTY
	k20_IconIndiceWeaponStaffOfClawsEmpty = 20, // @ C020_ICON_WEAPON_STAFF_OF_CLAWS_EMPTY
	k22_IconIndiceWeaponStaffOfClawsFull = 22, // @ C022_ICON_WEAPON_STAFF_OF_CLAWS_FULL
	k23_IconIndiceWeaponBoltBladeStormEmpty = 23, // @ C023_ICON_WEAPON_BOLT_BLADE_STORM_EMPTY
	k25_IconIndiceWeaponFuryRaBladeEmpty = 25, // @ C025_ICON_WEAPON_FURY_RA_BLADE_EMPTY
	k27_IconIndiceWeaponTheFirestaff = 27, // @ C027_ICON_WEAPON_THE_FIRESTAFF
	k28_IconIndiceWeaponTheFirestaffComplete = 28, // @ C028_ICON_WEAPON_THE_FIRESTAFF_COMPLETE
	k30_IconIndiceScrollOpen = 30, // @ C030_ICON_SCROLL_SCROLL_OPEN
	k31_IconIndiceScrollClosed = 31, // @ C031_ICON_SCROLL_SCROLL_CLOSED
	k32_IconIndiceWeaponDagger = 32, // @ C032_ICON_WEAPON_DAGGER
	k38_IconIndiceWeaponDeltaSideSplitter = 38, // @ C038_ICON_WEAPON_DELTA_SIDE_SPLITTER
	k39_IconIndiceWeaponDiamondEdge = 39, // @ C039_ICON_WEAPON_DIAMOND_EDGE
	k40_IconIndiceWeaponVorpalBlade = 40, // @ C040_ICON_WEAPON_VORPAL_BLADE
	k41_IconIndiceWeaponTheInquisitorDragonFang = 41, // @ C041_ICON_WEAPON_THE_INQUISITOR_DRAGON_FANG
	k43_IconIndiceWeaponHardcleaveExecutioner = 43, // @ C043_ICON_WEAPON_HARDCLEAVE_EXECUTIONER
	k45_IconIndiceWeaponMaceOfOrder = 45, // @ C045_ICON_WEAPON_MACE_OF_ORDER
	k51_IconIndiceWeaponArrow = 51, // @ C051_ICON_WEAPON_ARROW
	k52_IconIndiceWeaponSlayer = 52, // @ C052_ICON_WEAPON_SLAYER
	k54_IconIndiceWeaponRock = 54, // @ C054_ICON_WEAPON_ROCK
	k55_IconIndiceWeaponPoisonDart = 55, // @ C055_ICON_WEAPON_POISON_DART
	k56_IconIndiceWeaponThrowingStar = 56, // @ C056_ICON_WEAPON_THROWING_STAR
	k58_IconIndiceWeaponStaff = 58, // @ C058_ICON_WEAPON_STAFF
	k59_IconIndiceWeaponWand = 59, // @ C059_ICON_WEAPON_WAND
	k60_IconIndiceWeaponTeowand = 60, // @ C060_ICON_WEAPON_TEOWAND
	k61_IconIndiceWeaponYewStaff = 61, // @ C061_ICON_WEAPON_YEW_STAFF
	k62_IconIndiceWeaponStaffOfManarStaffOfIrra = 62, // @ C062_ICON_WEAPON_STAFF_OF_MANAR_STAFF_OF_IRRA
	k63_IconIndiceWeaponSnakeStaffCrossOfNeta = 63, // @ C063_ICON_WEAPON_SNAKE_STAFF_CROSS_OF_NETA
	k64_IconIndiceWeaponTheConduitSerpentStaff = 64, // @ C064_ICON_WEAPON_THE_CONDUIT_SERPENT_STAFF
	k65_IconIndiceWeaponDragonSpit = 65, // @ C065_ICON_WEAPON_DRAGON_SPIT
	k66_IconIndiceWeaponSceptreOfLyf = 66, // @ C066_ICON_WEAPON_SCEPTRE_OF_LYF
	k81_IconIndiceArmourCloakOfNight = 81, // @ C081_ICON_ARMOUR_CLOAK_OF_NIGHT
	k104_IconIndiceArmourCrownOfNerra = 104, // @ C104_ICON_ARMOUR_CROWN_OF_NERRA
	k119_IconIndiceArmourElvenBoots = 119, // @ C119_ICON_ARMOUR_ELVEN_BOOTS
	k120_IconIndiceJunkGemOfAges = 120, // @ C120_ICON_JUNK_GEM_OF_AGES
	k121_IconIndiceJunkEkkhardCross = 121, // @ C121_ICON_JUNK_EKKHARD_CROSS
	k122_IconIndiceJunkMoonstone = 122, // @ C122_ICON_JUNK_MOONSTONE
	k124_IconIndiceJunkPendantFeral = 124, // @ C124_ICON_JUNK_PENDANT_FERAL
	k128_IconIndiceJunkBoulder = 128, // @ C128_ICON_JUNK_BOULDER
	k137_IconIndiceJunkRabbitsFoot = 137, // @ C137_ICON_JUNK_RABBITS_FOOT
	k140_IconIndiceArmourDexhelm = 140, // @ C140_ICON_ARMOUR_DEXHELM
	k141_IconIndiceArmourFlamebain = 141, // @ C141_ICON_ARMOUR_FLAMEBAIN
	k142_IconIndiceArmourPowertowers = 142, // @ C142_ICON_ARMOUR_POWERTOWERS
	k144_IconIndiceContainerChestClosed = 144, // @ C144_ICON_CONTAINER_CHEST_CLOSED
	k145_IconIndiceContainerChestOpen = 145, // @ C145_ICON_CONTAINER_CHEST_OPEN
	k147_IconIndiceJunkChampionBones = 147, // @ C147_ICON_JUNK_CHAMPION_BONES
	k148_IconIndicePotionMaPotionMonPotion = 148, // @ C148_ICON_POTION_MA_POTION_MON_POTION
	k163_IconIndicePotionWaterFlask = 163, // @ C163_ICON_POTION_WATER_FLASK
	k168_IconIndiceJunkApple = 168, // @ C168_ICON_JUNK_APPLE
	k176_IconIndiceJunkIronKey = 176, // @ C176_ICON_JUNK_IRON_KEY
	k191_IconIndiceJunkMasterKey = 191, // @ C191_ICON_JUNK_MASTER_KEY
	k194_IconIndiceArmourBootOfSpeed = 194, // @ C194_ICON_ARMOUR_BOOT_OF_SPEED
	k195_IconIndicePotionEmptyFlask = 195, // @ C195_ICON_POTION_EMPTY_FLASK
	k197_IconIndiceJunkZokathra = 197, // @ C197_ICON_JUNK_ZOKATHRA
	k201_IconIndiceActionEmptyHand = 201, // @ C201_ICON_ACTION_ICON_EMPTY_HAND
	k202_IconIndiceEyeNotLooking = 202, // @ C202_ICON_EYE_NOT_LOOKING /* One pixel is different in this bitmap from the eye in C017_GRAPHIC_INVENTORY. This is visible by selecting another champion after clicking the eye */
	k203_IconIndiceEyeLooking = 203, // @ C203_ICON_EYE_LOOKING
	k204_IconIndiceEmptyBox = 204, // @ C204_ICON_EMPTY_BOX
	k205_IconIndiceMouthOpen = 205, // @ C205_ICON_MOUTH_OPEN
	k208_IconIndiceNeck = 208, // @ C208_ICON_NECK
	k212_IconIndiceReadyHand = 212 // @ C212_ICON_READY_HAND
};

enum ChampionIndex {
	kM1_ChampionNone = -1, // @ CM1_CHAMPION_NONE
	k0_ChampionFirst = 0, // @ C00_CHAMPION_FIRST
	k1_ChampionSecond = 1,
	k2_ChampionThird = 2,
	k3_ChampionFourth = 3,
	k4_ChampionCloseInventory = 4, // @ C04_CHAMPION_CLOSE_INVENTORY
	k5_ChampionSpecialInventory = 5 // @ C05_CHAMPION_SPECIAL_INVENTORY
};

enum ChampionAttribute {
	k0x0000_ChampionAttributNone = 0x0000, // @ MASK0x0000_NONE
	k0x0008_ChampionAttributeDisableAction = 0x0008, // @ MASK0x0008_DISABLE_ACTION
	k0x0010_ChampionAttributeMale = 0x0010, // @ MASK0x0010_MALE
	k0x0080_ChampionAttributeNameTitle = 0x0080, // @ MASK0x0080_NAME_TITLE
	k0x0100_ChampionAttributeStatistics = 0x0100, // @ MASK0x0100_STATISTICS
	k0x0200_ChampionAttributeLoad = 0x0200, // @ MASK0x0200_LOAD
	k0x0400_ChampionAttributeIcon = 0x0400, // @ MASK0x0400_ICON
	k0x0800_ChampionAttributePanel = 0x0800, // @ MASK0x0800_PANEL
	k0x1000_ChampionAttributeStatusBox = 0x1000, // @ MASK0x1000_STATUS_BOX
	k0x2000_ChampionAttributeWounds = 0x2000, // @ MASK0x2000_WOUNDS
	k0x4000_ChampionAttributeViewport = 0x4000, // @ MASK0x4000_VIEWPORT
	k0x8000_ChampionAttributeActionHand = 0x8000 // @ MASK0x8000_ACTION_HAND
};


enum ChampionWound {
	k0x0000_ChampionWoundNone = 0x0000, // @ MASK0x0000_NO_WOUND
	k0x0001_ChampionWoundReadHand = 0x0001, // @ MASK0x0001_READY_HAND
	k0x0002_ChampionWoundActionHand = 0x0002, // @ MASK0x0002_ACTION_HAND
	k0x0004_ChampionWoundHead = 0x0004, // @ MASK0x0004_HEAD
	k0x0008_ChampionWoundTorso = 0x0008, // @ MASK0x0008_TORSO
	k0x0010_ChampionWoundLegs = 0x0010, // @ MASK0x0010_LEGS
	k0x0020_ChampionWoundFeet = 0x0020 // @ MASK0x0020_FEET
};


enum ChampionStatisticType {
	k0_ChampionStatLuck = 0, // @ C0_STATISTIC_LUCK
	k1_ChampionStatStrength = 1, // @ C1_STATISTIC_STRENGTH
	k2_ChampionStatDexterity = 2, // @ C2_STATISTIC_DEXTERITY
	k3_ChampionStatWisdom = 3, // @ C3_STATISTIC_WISDOM
	k4_ChampionStatVitality = 4, // @ C4_STATISTIC_VITALITY
	k5_ChampionStatAntimagic = 5, // @ C5_STATISTIC_ANTIMAGIC
	k6_ChampionStatAntifire = 6, // @ C6_STATISTIC_ANTIFIRE
	k8_ChampionStatMana = 8 // @ C8_STATISTIC_MANA /* Used as a fake statistic index for objects granting a Mana bonus */
};

enum ChampionStatisticValue {
	k0_ChampionStatMaximum = 0, // @ C0_MAXIMUM
	k1_ChampionStatCurrent = 1, // @ C1_CURRENT
	k2_ChampionStatMinimum = 2 // @ C2_MINIMUM
};

enum ChampionSkill {
	k0_ChampionSkillFighter = 0, // @ C00_SKILL_FIGHTER
	k1_ChampionSkillNinja = 1, // @ C01_SKILL_NINJA
	k2_ChampionSkillPriest = 2, // @ C02_SKILL_PRIEST
	k3_ChampionSkillWizard = 3, // @ C03_SKILL_WIZARD
	k4_ChampionSkillSwing = 4, // @ C04_SKILL_SWING
	k5_ChampionSkillThrust = 5, // @ C05_SKILL_THRUST
	k6_ChampionSkillClub = 6, // @ C06_SKILL_CLUB
	k7_ChampionSkillParry = 7, // @ C07_SKILL_PARRY
	k8_ChampionSkillSteal = 8, // @ C08_SKILL_STEAL
	k9_ChampionSkillFight = 9, // @ C09_SKILL_FIGHT
	k10_ChampionSkillThrow = 10, // @ C10_SKILL_THROW
	k11_ChampionSkillShoot = 11, // @ C11_SKILL_SHOOT
	k12_ChampionSkillIdentify = 12, // @ C12_SKILL_IDENTIFY
	k13_ChampionSkillHeal = 13, // @ C13_SKILL_HEAL
	k14_ChampionSkillInfluence = 14, // @ C14_SKILL_INFLUENCE
	k15_ChampionSkillDefend = 15, // @ C15_SKILL_DEFEND
	k16_ChampionSkillFire = 16, // @ C16_SKILL_FIRE
	k17_ChampionSkillAir = 17, // @ C17_SKILL_AIR
	k18_ChampionSkillEarth = 18, // @ C18_SKILL_EARTH
	k19_ChampionSkillWater = 19 // @ C19_SKILL_WATER
};

enum ChampionSlot {
	kM1_ChampionSlotLeaderHand = -1, // @ CM1_SLOT_LEADER_HAND
	k0_ChampionSlotReadyHand = 0, // @ C00_SLOT_READY_HAND
	k1_ChampionSlotActionHand = 1, // @ C01_SLOT_ACTION_HAND
	k2_ChampionSlotHead = 2, // @ C02_SLOT_HEAD
	k3_ChampionSlotTorso = 3, // @ C03_SLOT_TORSO
	k4_ChampionSlotLegs = 4, // @ C04_SLOT_LEGS
	k5_ChampionSlotFeet = 5, // @ C05_SLOT_FEET
	k6_ChampionSlotPouch_2 = 6, // @ C06_SLOT_POUCH_2
	k7_ChampionSlotQuiverLine_2_1 = 7, // @ C07_SLOT_QUIVER_LINE2_1
	k8_ChampionSlotQuiverLine_1_2 = 8, // @ C08_SLOT_QUIVER_LINE1_2
	k9_ChampionSlotQuiverLine_2_2 = 9, // @ C09_SLOT_QUIVER_LINE2_2
	k10_ChampionSlotNeck = 10, // @ C10_SLOT_NECK
	k11_ChampionSlotPouch_1 = 11, // @ C11_SLOT_POUCH_1
	k12_ChampionSlotQuiverLine_1_1 = 12, // @ C12_SLOT_QUIVER_LINE1_1
	k13_ChampionSlotBackpackLine_1_1 = 13, // @ C13_SLOT_BACKPACK_LINE1_1
	k14_ChampionSlotBackpackLine_2_2 = 14, // @ C14_SLOT_BACKPACK_LINE2_2
	k15_ChampionSlotBackpackLine_2_3 = 15, // @ C15_SLOT_BACKPACK_LINE2_3
	k16_ChampionSlotBackpackLine_2_4 = 16, // @ C16_SLOT_BACKPACK_LINE2_4
	k17_ChampionSlotBackpackLine_2_5 = 17, // @ C17_SLOT_BACKPACK_LINE2_5
	k18_ChampionSlotBackpackLine_2_6 = 18, // @ C18_SLOT_BACKPACK_LINE2_6
	k19_ChampionSlotBackpackLine_2_7 = 19, // @ C19_SLOT_BACKPACK_LINE2_7
	k20_ChampionSlotBackpackLine_2_8 = 20, // @ C20_SLOT_BACKPACK_LINE2_8
	k21_ChampionSlotBackpackLine_2_9 = 21, // @ C21_SLOT_BACKPACK_LINE2_9
	k22_ChampionSlotBackpackLine_1_2 = 22, // @ C22_SLOT_BACKPACK_LINE1_2
	k23_ChampionSlotBackpackLine_1_3 = 23, // @ C23_SLOT_BACKPACK_LINE1_3
	k24_ChampionSlotBackpackLine_1_4 = 24, // @ C24_SLOT_BACKPACK_LINE1_4
	k25_ChampionSlotBackpackLine_1_5 = 25, // @ C25_SLOT_BACKPACK_LINE1_5
	k26_ChampionSlotBackpackLine_1_6 = 26, // @ C26_SLOT_BACKPACK_LINE1_6
	k27_ChampionSlotBackpackLine_1_7 = 27, // @ C27_SLOT_BACKPACK_LINE1_7
	k28_ChampionSlotBackpackLine_1_8 = 28, // @ C28_SLOT_BACKPACK_LINE1_8
	k29_ChampionSlotBackpackLine_1_9 = 29, // @ C29_SLOT_BACKPACK_LINE1_9
	k30_ChampionSlotChest_1 = 30, // @ C30_SLOT_CHEST_1
	k31_ChampionSlotChest_2 = 31, // @ C31_SLOT_CHEST_2
	k32_ChampionSlotChest_3 = 32, // @ C32_SLOT_CHEST_3
	k33_ChampionSlotChest_4 = 33, // @ C33_SLOT_CHEST_4
	k34_ChampionSlotChest_5 = 34, // @ C34_SLOT_CHEST_5
	k35_ChampionSlotChest_6 = 35, // @ C35_SLOT_CHEST_6
	k36_ChampionSlotChest_7 = 36, // @ C36_SLOT_CHEST_7
	k37_ChampionSlotChest_8 = 37 // @ C37_SLOT_CHEST_8
};

enum ChampionAction {
	k0_ChampionActionN = 0, // @ C000_ACTION_N
	k1_ChampionActionBlock = 1, // @ C001_ACTION_BLOCK
	k2_ChampionActionChop = 2, // @ C002_ACTION_CHOP
	k3_ChampionActionX_C003 = 3, // @ C003_ACTION_X
	k4_ChampionActionBlowHorn = 4, // @ C004_ACTION_BLOW_HORN
	k5_ChampionActionFlip = 5, // @ C005_ACTION_FLIP
	k6_ChampionActionPunch = 6, // @ C006_ACTION_PUNCH
	k7_ChampionActionKick = 7, // @ C007_ACTION_KICK
	k8_ChampionActionWarCry = 8, // @ C008_ACTION_WAR_CRY
	k9_ChampionActionStab_C009 = 9, // @ C009_ACTION_STAB
	k10_ChampionActionClimbDown = 10, // @ C010_ACTION_CLIMB_DOWN
	k11_ChampionActionFreezeLife = 11, // @ C011_ACTION_FREEZE_LIFE
	k12_ChampionActionHit = 12, // @ C012_ACTION_HIT
	k13_ChampionActionSwing = 13, // @ C013_ACTION_SWING
	k14_ChampionActionStab_C014 = 14, // @ C014_ACTION_STAB
	k15_ChampionActionThrust = 15, // @ C015_ACTION_THRUST
	k16_ChampionActionJab = 16, // @ C016_ACTION_JAB
	k17_ChampionActionParry = 17, // @ C017_ACTION_PARRY
	k18_ChampionActionHack = 18, // @ C018_ACTION_HACK
	k19_ChampionActionBerzerk = 19, // @ C019_ACTION_BERZERK
	k20_ChampionActionFireball = 20, // @ C020_ACTION_FIREBALL
	k21_ChampionActionDispel = 21, // @ C021_ACTION_DISPELL
	k22_ChampionActionConfuse = 22, // @ C022_ACTION_CONFUSE
	k23_ChampionActionLightning = 23, // @ C023_ACTION_LIGHTNING
	k24_ChampionActionDisrupt = 24, // @ C024_ACTION_DISRUPT
	k25_ChampionActionMelee = 25, // @ C025_ACTION_MELEE
	k26_ChampionActionX_C026 = 26, // @ C026_ACTION_X
	k27_ChampionActionInvoke = 27, // @ C027_ACTION_INVOKE
	k28_ChampionActionSlash = 28, // @ C028_ACTION_SLASH
	k29_ChampionActionCleave = 29, // @ C029_ACTION_CLEAVE
	k30_ChampionActionBash = 30, // @ C030_ACTION_BASH
	k31_ChampionActionStun = 31, // @ C031_ACTION_STUN
	k32_ChampionActionShoot = 32, // @ C032_ACTION_SHOOT
	k33_ChampionActionSpellshield = 33, // @ C033_ACTION_SPELLSHIELD
	k34_ChampionActionFireshield = 34, // @ C034_ACTION_FIRESHIELD
	k35_ChampionActionFluxcage = 35, // @ C035_ACTION_FLUXCAGE
	k36_ChampionActionHeal = 36, // @ C036_ACTION_HEAL
	k37_ChampionActionCalm = 37, // @ C037_ACTION_CALM
	k38_ChampionActionLight = 38, // @ C038_ACTION_LIGHT
	k39_ChampionActionWindow = 39, // @ C039_ACTION_WINDOW
	k40_ChampionActionSpit = 40, // @ C040_ACTION_SPIT
	k41_ChampionActionBrandish = 41, // @ C041_ACTION_BRANDISH
	k42_ChampionActionThrow = 42, // @ C042_ACTION_THROW
	k43_ChampionActionFuse = 43, // @ C043_ACTION_FUSE
	k255_ChampionActionNone = 255 // @ C255_ACTION_NONE
};


class Skill {
public:
	int16 _temporaryExperience;
	int32 _experience;
	
	void resetToZero() { _temporaryExperience = _experience = 0; }
}; // @ SKILL

class Champion {
	Thing _slots[30];
	Skill _skills[20];
	uint16 _attributes;
	byte _statistics[7][3];
	uint16 _wounds;
public:
	char _name[8];
	char _title[20];
	direction _dir;
	ViewCell _cell;
	ChampionAction _actionIndex;
	uint16 _symbolStep;
	char _symbols[5];
	uint16 _directionMaximumDamageReceived;
	uint16 _maximumDamageReceived;
	uint16 _poisonEventCount;
	int16 _enableActionEventIndex;
	int16 _hideDamageReceivedIndex;
	int16 _currHealth;
	int16 _maxHealth;
	int16 _currStamina;
	int16 _maxStamina;
	int16 _currMana;
	int16 _maxMana;
	int16 _actionDefense;
	int16 _food;
	int16 _water;
	uint16 _load;
	int16 _shieldDefense;
	byte _portrait[464]; // 32 x 29 pixel portrait

	Thing &getSlot(ChampionSlot slot) { return _slots[slot]; }
	void setSlot(ChampionSlot slot, Thing val) { _slots[slot] = val; }

	Skill &getSkill(ChampionSkill skill) { return _skills[skill]; }
	void setSkillExp(ChampionSkill skill,  int32 val) { _skills[skill]._experience = val; }
	void setSkillTempExp(ChampionSkill skill,  int16 val) { _skills[skill]._temporaryExperience= val; }

	byte& getStatistic(ChampionStatisticType type, ChampionStatisticValue valType) { return _statistics[type][valType]; }
	void setStatistic(ChampionStatisticType type, ChampionStatisticValue valType, byte newVal) { _statistics[type][valType] = newVal; }

	uint16 getAttributes() { return _attributes; }
	uint16 getAttributes(ChampionAttribute flag) { return _attributes & flag; }
	void setAttributeFlag(ChampionAttribute flag, bool value) {
		if (value) {
			_attributes |= flag;
		} else {
			_attributes &= ~flag;
		}
	}
	void clearAttributes(ChampionAttribute attribute = k0x0000_ChampionAttributNone) { _attributes = attribute; }

	uint16 getWounds() { return _wounds; }
	void setWoundsFlag(ChampionWound flag, bool value) {
		if (value) {
			_wounds |= flag;
		} else {
			_wounds &= ~flag;
		}
	}
	uint16 getWoundsFlag(ChampionWound wound) { return _wounds & wound; }
	void clearWounds() { _wounds = k0x0000_ChampionWoundNone; }
	void resetToZero() { // oh boy > . <
		for (int16 i = 0; i < 30; ++i)
			_slots[i] = Thing::_none;
		for (int16 i = 0; i < 20; ++i)
			_skills[i].resetToZero();
		_attributes = _wounds = 0;
		memset(_statistics, 0, 7 * 3);
		memset(_name, '\0', 8);
		memset(_title, '\0', 20);
		_dir = kDirNorth;
		_cell = k0_ViewCellFronLeft;
		_actionIndex = k0_ChampionActionN;
		_symbolStep = 0;
		memset(_symbols, '\0', 5);
		_directionMaximumDamageReceived = _maximumDamageReceived = _poisonEventCount = _enableActionEventIndex = 0;
		_hideDamageReceivedIndex = _currHealth = _maxHealth = _currStamina = _maxStamina = _currMana = _maxMana = 0;
		_actionDefense = _food = _water = _load = _shieldDefense = 0;
		memset(_portrait, 0, 464);
	}
	void resetSkillsToZero() {
		for (int16 i = 0; i < 20; ++i)
			_skills[i].resetToZero();
	}
}; // @ CHAMPION_INCLUDING_PORTRAIT

class ChampionMan {
	DMEngine *_vm;

	uint16 getChampionPortraitX(uint16 index); // @ M27_PORTRAIT_X
	uint16 getChampionPortraitY(uint16 index); // @ M28_PORTRAIT_Y

	ChampionIndex getIndexInCell(ViewCell cell); // @ F0285_CHAMPION_GetIndexInCell
	int16 getDecodedValue(char *string, uint16 characterCount); // @ F0279_CHAMPION_GetDecodedValue
	void drawHealthOrStaminaOrManaValue(int16 posy, int16 currVal, int16 maxVal); // @ F0289_CHAMPION_DrawHealthOrStaminaOrManaValue
	uint16 handSlotIndex(uint16 slotBoxIndex);// @ M70_HAND_SLOT_INDEX
public:
	Champion _champions[4];
	uint16 _g305_partyChampionCount;	// @ G0305_ui_PartyChampionCount
	bool _303_partyDead; // @ G0303_B_PartyDead
	Thing _414_leaderHandObject; // @ G0414_T_LeaderHandObject
	ChampionIndex _g411_leaderIndex;	// @ G0411_i_LeaderIndex
	uint16 _g299_candidateChampionOrdinal; // @ G0299_ui_CandidateChampionOrdinal
	bool _g300_partyIsSleeping; // @ G0300_B_PartyIsSleeping
	uint16 _g506_actingChampionOrdinal; // @ G0506_ui_ActingChampionOrdinal
	IconIndice _g413_leaderHandObjectIconIndex; // @ G0413_i_LeaderHandObjectIconIndex
	bool _g415_leaderEmptyHanded; // @ G0415_B_LeaderEmptyHanded
	Party _g407_party; // @ G0407_s_Party
	ChampionIndex _g514_magicCasterChampionIndex; // @ G0514_i_MagicCasterChampionIndex
	bool _g420_mousePointerHiddenToDrawChangedObjIconOnScreen; // @ G0420_B_MousePointerHiddenToDrawChangedObjectIconOnScreen

	explicit ChampionMan(DMEngine *vm);
	void resetDataToStartGame(); // @ F0278_CHAMPION_ResetDataToStartGame
	void addCandidateChampionToParty(uint16 championPortraitIndex); // @ F0280_CHAMPION_AddCandidateChampionToParty
	void drawChampionBarGraphs(ChampionIndex champIndex); // @ F0287_CHAMPION_DrawBarGraphs
	uint16 getStaminaAdjustedValue(Champion *champ, int16 val); // @ F0306_CHAMPION_GetStaminaAdjustedValue
	uint16 getMaximumLoad(Champion *champ); // @ F0309_CHAMPION_GetMaximumLoad
	void drawChampionState(ChampionIndex champIndex); // @ F0292_CHAMPION_DrawState
	uint16 championIconIndex(int16 val, direction dir); // @ M26_CHAMPION_ICON_INDEX
	void drawHealthStaminaManaValues(Champion *champ); // @ F0290_CHAMPION_DrawHealthStaminaManaValues
	void drawSlot(uint16 champIndex, ChampionSlot slotIndex); // @ F0291_CHAMPION_DrawSlot
	void renameChampion(Champion* champ); // @ F0281_CHAMPION_Rename
	uint16 getSkillLevel(ChampionIndex champIndex, ChampionSkill skillIndex);// @ F0303_CHAMPION_GetSkillLevel
	Common::String getStringFromInteger(uint16 val, bool padding, uint16 paddingCharCount); // @ F0288_CHAMPION_GetStringFromInteger
	void applyModifiersToStatistics(Champion *champ, ChampionSlot slotIndex, IconIndice iconIndex,
									int16 modifierFactor, Thing thing); // @ F0299_CHAMPION_ApplyObjectModifiersToStatistics
	bool hasObjectIconInSlotBoxChanged(int16 slotBoxIndex, Thing thing); // @ F0295_CHAMPION_HasObjectIconInSlotBoxChanged
	void drawChangedObjectIcons(); // @ F0296_CHAMPION_DrawChangedObjectIcons
	void addObjectInSlot(ChampionIndex champIndex, Thing thing, ChampionSlot slotIndex); // @ F0301_CHAMPION_AddObjectInSlot
};


}

#endif