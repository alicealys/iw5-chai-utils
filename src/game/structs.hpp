#pragma once

namespace game
{
	typedef float vector3[3];

	//------------------------ Script

	typedef unsigned __int16 scr_string_t;
	typedef unsigned __int16 scr_thread_t;
	typedef int scr_func_t;


	union scr_entref_t
	{
		unsigned int val;

		struct
		{
			unsigned __int16 entnum;
			unsigned __int16 classnum;
		} raw;
	};

	typedef void(__cdecl* scr_call_t)(int entref);

	struct scr_classStruct_t
	{
		unsigned __int16 id;
		unsigned __int16 entArrayId;
		char charId;
		const char* name;
	};

	enum scriptType_e
	{
		SCRIPT_NONE = 0,
		SCRIPT_OBJECT = 1,
		SCRIPT_STRING = 2,
		SCRIPT_VECTOR = 4,
		SCRIPT_FLOAT = 5,
		SCRIPT_INTEGER = 6,
		SCRIPT_END = 8,
	};

	struct VariableStackBuffer
	{
		const char* pos;
		unsigned __int16 size;
		unsigned __int16 bufLen;
		unsigned __int16 localId;
		char time;
		char buf[1];
	};

	union VariableUnion
	{
		int intValue;
		float floatValue;
		unsigned int stringValue;
		const float* vectorValue;
		const char* codePosValue;
		unsigned int pointerValue;
		VariableStackBuffer* stackValue;
		unsigned int entityId;
	};

	struct VariableValue
	{
		VariableUnion u;
		scriptType_e type;
	};


	//------------------------ Entity

	union EntityStateIndexUnion
	{
		int brushModel;
		int triggerModel;
		int xmodel;
		int primaryLight;
	};

	/*


	struct $39EF277EA8613772F6FC6094760A0E98
	{
		unsigned __int32 weaponIdx : 8;
		unsigned __int32 weaponVariation : 6;
		unsigned __int32 weaponScopes : 3;
		unsigned __int32 weaponUnderBarrels : 2;
		unsigned __int32 weaponOthers : 8;
		unsigned __int32 scopeVariation : 5;
	};

	union Weapon
	{
		$39EF277EA8613772F6FC6094760A0E98 __s0;
		unsigned int data;
	};


	struct LerpEntityStatePlayer
	{
		int movementDir;
		float lerpLean;
		float torsoPitch;
		float waistPitch;
		Weapon offhandWeapon;
		Weapon stowedWeapon;
		int lastSpawnTime;
	};


	union entity_state_lerp_typeU
	{

		LerpEntityStatePlayer player;
	};

	enum trajectory_type_t
	{
		TR_STATIONARY = 0x0,
		TR_INTERPOLATE = 0x1,
		TR_LINEAR = 0x2,
		TR_LINEAR_STOP = 0x3,
		TR_SINE = 0x4,
		TR_GRAVITY = 0x5,
		TR_LOW_GRAVITY = 0x6,
		TR_ACCELERATE = 0x7,
		TR_DECELERATE = 0x8,
		TR_PHYSICS = 0x9,
		TR_ANIMATED_MOVER = 0xA,
		TR_FIRST_RAGDOLL = 0xB,
		TR_RAGDOLL = 0xB,
		TR_RAGDOLL_GRAVITY = 0xC,
		TR_RAGDOLL_INTERPOLATE = 0xD,
		TR_LAST_RAGDOLL = 0xD,
		NUM_TRTYPES = 0xE,
	};

	struct trajectory_t
	{
		trajectory_type_t	trType;
		int					trTime;
		int					trDuration;
		float				trBase[3];
		float				trDelta[3];
	};

	struct entity_state_lerp
	{
		int eFlags;
		trajectory_t pos;
		trajectory_t apos;
		entity_state_lerp_typeU u;
	};*/

	struct entityState_s
	{
		int					number;
		int					type;
		char				lerp[0x68]; //struct LerpEntityState 0x68
		int					staticState; // union StaticEntityStateTypeUnion 0x4
		int					time2;
		int					otherEntityNum;
		int					attackerEntityNum;
		int					groundEntityNum;
		int					loopSound;
		int					surfType;
		EntityStateIndexUnion index;
		int					clientNum;
		// clientnum   // 144 0x90
	};

	struct gentity_s
	{
		entityState_s		state;
		//entity_shared		shared;
		//gclient_s			client; // 344 [0x158]
	}; // 0x1F8


	/*
	player stance
		"prone"
		"crouch"
		"stand"
	
	*/

	enum MeansOfDeath
	{
		MOD_UNKNOWN = 0,
		MOD_PISTOL_BULLET = 1,
		MOD_RIFLE_BULLET = 2,
		MOD_EXPLOSIVE_BULLET = 3,
		MOD_GRENADE = 4,
		MOD_GRENADE_SPLASH = 5,
		MOD_PROJECTILE = 6,
		MOD_PROJECTILE_SPLASH = 7,
		MOD_MELEE = 8,
		MOD_HEAD_SHOT = 9,
		MOD_CRUSH = 10,
		MOD_FALLING = 11,
		MOD_SUICIDE = 12,
		MOD_TRIGGER_HURT = 13,
		MOD_EXPLOSIVE = 14,
		MOD_IMPACT = 15,
		MOD_NUM = 16
	};

	enum HitLocation
	{
		HITLOC_NONE = 0,
		HITLOC_HELMET = 1,
		HITLOC_HEAD = 2,
		HITLOC_NECK = 3,
		HITLOC_TORSO_UPR = 4,
		HITLOC_TORSO_LWR = 5,
		HITLOC_R_ARM_UPR = 6,
		HITLOC_L_ARM_UPR = 7,
		HITLOC_R_ARM_LWR = 8,
		HITLOC_L_ARM_LWR = 9,
		HITLOC_R_HAND = 10,
		HITLOC_L_HAND = 11,
		HITLOC_R_LEG_UPR = 12,
		HITLOC_L_LEG_UPR = 13,
		HITLOC_R_LEG_LWR = 14,
		HITLOC_L_LEG_LWR = 15,
		HITLOC_R_FOOT = 16,
		HITLOC_L_FOOT = 17,
		HITLOC_GUN = 18,
		HITLOC_NUM = 19,
	};

	enum DamageFlags
	{
		DFLAGS_RADIUS = 1,							// damage was indirect
		DFLAGS_NO_ARMOR = 2,						// armor does not protect from this damage
		DFLAGS_NO_KNOCKBACK = 4,					// do not affect velocity, just view angles
		DFLAGS_PENETRATION = 8,						// damage occurred after one or more penetrations
		DFLAGS_STUN = 16,							// non-lethal
		DFLAGS_SHIELD_EXPLOSIVE_IMPACT = 32,		// missile impacted on the front of the victim's shield
		DFLAGS_SHIELD_EXPLOSIVE_IMPACT_HUGE = 64,	//   ...and was from a projectile with "Big Explosion" checked on.
		DFLAGS_SHIELD_EXPLOSIVE_SPLASH = 128,		// explosive splash, somewhat deflected by the victim's shield

		// script-defined:
		DFLAGS_NO_TEAM_PROTECTION = 256,
		DFLAGS_NO_PROTECTION = 512,
		DFLAGS_PASSTHRU = 1024,
	};

	//------------------------ Weapons

	struct Weapon
	{
		unsigned int data;
	};

	enum weapClass_t
	{
		WEAPCLASS_RIFLE = 0,
		WEAPCLASS_SNIPER = 1,
		WEAPCLASS_MG = 2,
		WEAPCLASS_SMG = 3,
		WEAPCLASS_SPREAD = 4,
		WEAPCLASS_PISTOL = 5,
		WEAPCLASS_GRENADE = 6,
		WEAPCLASS_ROCKETLAUNCHER = 7,
		WEAPCLASS_TURRET = 8,
		WEAPCLASS_THROWINGKNIFE = 9,
		WEAPCLASS_NON_PLAYER = 10,
		WEAPCLASS_ITEM = 11,
		WEAPCLASS_NUM = 12,
	};


	//------------------------ Cmd
	enum LocalClientNum_t
	{
		LOCAL_CLIENT_INVALID = 0xFFFFFFFF,
		LOCAL_CLIENT_0 = 0x0,
		LOCAL_CLIENT_LAST = 0x0,
		LOCAL_CLIENT_COUNT = 0x1,
	};

	struct CmdArgs
	{
		int nesting;
		LocalClientNum_t localClientNum[8];
		int controllerIndex[8];
		int argc[8];
		const char** argv[8];
	};

	struct CmdArgsPrivate
	{
		char textPool[8192];
		const char* argvPool[512];
		int usedTextPool[8];
		int totalUsedArgvPool;
		int totalUsedTextPool;
	};

	struct cmd_function_t
	{
		cmd_function_t* next;
		const char* name;
		const char* autoCompleteDir;
		const char* autoCompleteExt;
		void(__cdecl* function)();
		int flags;
	};


	//------------------------ Dvars
	enum DvarFlags
	{
		DVAR_FLAG_NONE = 0,
		DVAR_FLAG_ARCHIVE = 1,			// config saved
		DVAR_FLAG_LATCHED = 2,			// read only
		DVAR_FLAG_CHEAT = 4,			// cheat protected
		DVAR_FLAG_REPLICATED = 8,		// send to client
		DVAR_FLAG_UNK1 = 16,
		DVAR_FLAG_UNK2 = 32,
		DVAR_FLAG_UNK3 = 64,
		DVAR_FLAG_UNK4 = 128,			// bg_regdvars used
		DVAR_FLAG_USERCREATED = 256,	// set cmd, or script created
		DVAR_FLAG_UNK5 = 512,
		DVAR_FLAG_UNK6 = 1024,
		DVAR_FLAG_UNK7 = 2048,
		DVAR_FLAG_UNK8 = 4096,
	};

	enum DvarType
	{
		DVAR_TYPE_BOOL = 0,
		DVAR_TYPE_FLOAT = 1,
		DVAR_TYPE_FLOAT_2 = 2,
		DVAR_TYPE_FLOAT_3 = 3,
		DVAR_TYPE_FLOAT_4 = 4,
		DVAR_TYPE_INT = 5,
		DVAR_TYPE_ENUM = 6,
		DVAR_TYPE_STRING = 7,
		DVAR_TYPE_COLOR = 8,
		//DVAR_TYPE_INT64 = 9
	};

	union DvarValue
	{
		bool enabled;
		int integer;
		unsigned int unsignedInt;
		float value;
		float vector[4];
		const char* string;
		char color[4];
	};

	struct EnumLimits
	{
		int stringCount;
		const char** strings;
	};

	struct IntegerLimits
	{
		int min;
		int max;
	};

	struct FloatLimits
	{
		float min;
		float max;
	};

	union DvarLimits
	{
		EnumLimits enumeration;
		IntegerLimits integer;
		FloatLimits value;
		FloatLimits vector;
	};

	struct dvar_t
	{
		const char* name;
		unsigned int flags;
		char type;
		bool modified;
		DvarValue current;
		DvarValue latched;
		DvarValue reset;
		DvarLimits domain;
		bool(__cdecl* domainFunc)(dvar_t*, DvarValue);
		dvar_t* hashNext;
	};

	enum svscmd_type
	{
		SV_CMD_CAN_IGNORE = 0x0,
		SV_CMD_RELIABLE = 0x1,
	};
} // namespace game
