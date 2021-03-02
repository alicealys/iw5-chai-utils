#pragma once

namespace game
{
	constexpr utils::function<void(LocalClientNum_t localClientNum, const char* text)> Cbuf_AddText(0x545680);

	constexpr utils::function<void(const int clientNum, const char* commandString, const char* notifyString)> Cmd_RegisterNotification(0x5461C0);
	constexpr utils::function<void(const char* name, void(), cmd_function_t* allocatedCmd)> Cmd_AddCommandInternal(0x545DF0);

	constexpr utils::function<dvar_t* (const char* dvarName, bool value, unsigned int flags, const char* description)> Dvar_RegisterBool(0x5BE9F0);

	constexpr utils::function<void(int clientNum, svscmd_type type, const char* text)> SV_GameSendServerCommand(0x573220);
	constexpr utils::function<void(int arg, char* buffer, int bufferLength)> SV_Cmd_ArgvBuffer(0x5459F0);
	constexpr utils::function<char* (int start)> ConcatArgs(0x502150);
	constexpr utils::function<void(int clientNum)> ClientCommand(0x502CB0);

	constexpr utils::function<const char* (scr_string_t stringValue)> SL_ConvertToString(0x564270);

	constexpr utils::function<void(unsigned int notifyListOwnerId, scr_string_t stringValue, VariableValue* top)> VM_Notify(0x569720);

	constexpr utils::function<void(int value)> Scr_AddInt(0x56AA20);
	constexpr utils::function<void(scr_string_t value)> Scr_AddConstString(0x56ACC0);
	constexpr utils::function<void(const float* value)> Scr_AddVector(0x56AD20);
	constexpr utils::function<void()> Scr_AddUndefined(0x56AB10);
	constexpr utils::function<void(const char* value)> Scr_AddString(0x56AC00);
	constexpr utils::function<void(gentity_s* ent)> Scr_AddEntity(0x52B060);

	constexpr utils::function<__int16(gentity_s* ent, int handle, unsigned int paramcount)> Scr_ExecEntThread(0x52B170);
	constexpr utils::function<void(unsigned __int16 handle)> Scr_FreeThread(0x569E20);

	constexpr utils::function<void()> Scr_LoadLevel(0x517410);
	constexpr utils::function<void()> Scr_LoadGameType(0x527AF0);
	constexpr utils::function<void()> Scr_StartupGameType(0x527B10);

	constexpr utils::function<void(gentity_s*)> Scr_PlayerConnect(0x527B30);
	constexpr utils::function<void(gentity_s*)> Scr_PlayerDisconnect(0x527B60);
	constexpr utils::function<void(gentity_s*, gentity_s*, gentity_s*, int, int, MeansOfDeath, Weapon, bool, const float*, const float*, HitLocation, int)> Scr_PlayerDamage(0x527B90);
	constexpr utils::function<void(gentity_s*, gentity_s*, gentity_s*, int, MeansOfDeath, Weapon, bool, const float*, HitLocation, int, int)> Scr_PlayerKilled(0x527CF0);
	constexpr utils::function<unsigned int(int, unsigned int)> Scr_GetEntityId(0x567D80);

	constexpr utils::function<void(scr_entref_t entref)> PlayerCmd_finishPlayerDamage(0x500960);

	constexpr utils::function<char* (Weapon weapon, bool isAlternate, char* output, unsigned int maxStringLen)> BG_GetWeaponNameComplete(0x42F760);
	constexpr utils::function<weapClass_t(Weapon weapon, bool isAlternate)> BG_GetWeaponClass(0x436ED0);
	constexpr utils::function<const char* (int type)> BG_GetWeaponClassName(0x42F160);

	constexpr utils::function<scr_string_t(HitLocation hitLoc)> G_GetHitLocationString(0x5052A0);

	inline int Cmd_Argc()
	{
		return cmd_args->argc[cmd_args->nesting];
	}

	inline const char* Cmd_Argv(int argIndex)
	{
		if (argIndex >= cmd_args->argc[cmd_args->nesting])
		{
			return "";
		}
		return cmd_args->argv[cmd_args->nesting][argIndex];
	}

	inline int SV_Cmd_Argc()
	{
		return sv_cmd_args->argc[sv_cmd_args->nesting];
	}

	inline const char* SV_Cmd_Argv(int argIndex)
	{
		if (argIndex >= sv_cmd_args->argc[sv_cmd_args->nesting])
		{
			return "";
		}
		return sv_cmd_args->argv[sv_cmd_args->nesting][argIndex];
	}
}
