#pragma once

#include <wchar.h>
#include <windows.h>

#include <map>
#include <string>

class Module;

class ModuleManager {
	private:
		std::map<std::string, Module*> moduleList;

		void FixName(std::string& name);

	public:
		ModuleManager();
		~ModuleManager();

		// Module Management
		void Add(Module* module);
		Module* Get(std::string name);
		void Remove(Module* module);

		void LoadModules();
		void UnloadModules();
		void ReloadConfig();
		void MpqLoaded();

		bool OnUserInput(wchar_t* module, wchar_t* msg, bool fromGame);

		void OnLoop();

		void OnGameJoin();
		void OnGameExit();

		void OnDraw();
		void OnAutomapDraw();
		void OnOOGDraw();

		void OnLeftClick(bool up, unsigned int x, unsigned int y, bool* block);
		void OnRightClick(bool up, unsigned int x, unsigned int y, bool* block);
		void OnKey(bool up, BYTE key, LPARAM lParam, bool* block);

		void OnChatPacketRecv(BYTE* packet, bool* block);
		void OnRealmPacketRecv(BYTE* packet, bool* block);
		void OnGamePacketRecv(BYTE* packet, bool* block);

		void OnChatMsg(const char* user, const char* msg, bool fromGame, bool* block);
};
