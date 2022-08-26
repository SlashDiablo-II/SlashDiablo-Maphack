#include "Config.h"

#include <stddef.h>

#include <algorithm>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>

#include "BH.h"
#include "Common.h"
#include "Common/Input.h"

namespace {

using ::common::input::VirtualKey;

}  // namespace

/* Parse()
Parse the configuration file and stores the results in a key->value pair.
Can be called multiple times so you can reload the configuration.
*/
bool Config::Parse() {

	//If this is a config with a pre-set of values, can't parse!
	if (configName.length() == 0)
		return false;

	//Open the configuration file
	std::fstream file(BH::path + configName);
	if (!file.is_open())
		return false;

	//Lock Critical Section then wipe contents incase we are reloading.
	contents.erase(contents.begin(), contents.end());
	orderedKeyVals.clear();

	//Begin to loop the configuration file one line at a time.
	std::string line;
	int lineNo = 0;
	while (std::getline(file, line)) {
		lineNo++;
		std::string comment;
		//Remove any comments from the config
		if (line.find("//") != std::string::npos) {
			comment = line.substr(line.find("//"));
			line = line.erase(line.find("//"));
		}

		//Insure we have something in the line now.
		if (line.length() == 0)
			continue;

		//Grab the Key and Value

		ConfigEntry entry;
		entry.line = lineNo;
		entry.key = Trim(line.substr(0, line.find_first_of(":")));
		entry.value = Trim(line.substr(line.find_first_of(":") + 1));

		entry.comment = line.substr(line.find_first_of(":") + 1, line.find(entry.value) - line.find_first_of(":") - 1);
		entry.pointer = NULL;

		//Store them!
		contents.insert(std::pair<std::string, ConfigEntry>(entry.key, entry));
		orderedKeyVals.push_back(std::pair<std::string, std::string>(entry.key, entry.value));
	}
	file.close();
	return true;
}

bool Config::Write() {
	//If this is a config with a pre-set of values, can't parse!
	if (configName.length() == 0)
		return false;

	//Open the configuration file
	std::fstream file(BH::path + configName);
	if (!file.is_open())
		return false;

	//Read in the configuration value
	std::vector<std::string> configLines;
	char line[2048];
	while (!file.eof()) {
		file.getline(line, 2048);
		configLines.push_back(line);
	}
	file.close();

	std::map<ConfigEntry, std::string> changed;
	for (std::map<std::string, ConfigEntry>::iterator it = contents.begin(); it != contents.end(); ++it) {
		std::string newValue;
		if (!HasChanged((*it).second, newValue))
			continue;
		std::pair<ConfigEntry, std::string> change;
		change.first = (*it).second;
		change.second = newValue.c_str();
		changed.insert(change);
	}

	if (changed.size() == 0)
		return true;

	for (std::vector<std::string>::iterator it = configLines.begin(); it < configLines.end(); it++) {
		//Remove any comments from the config
		std::string comment;
		if ((*it).find_first_of("//") != std::string::npos) {
			comment = (*it).substr((*it).find_first_of("//"));
			(*it) = (*it).erase((*it).find_first_of("//"));
		}

		//Insure we have something in the line now.
		if ((*it).length() == 0) {
			*it = comment;
			continue;
		}

		std::string key = Trim((*it).substr(0, (*it).find_first_of(":")));
		*it = *it + comment;

		for (std::map<ConfigEntry, std::string>::iterator cit = changed.begin(); cit != changed.end(); ++cit)
		{
			if ((*cit).first.key.compare(key) != 0)
				continue;

			if ((*cit).second.size() == 0)
			{
				*it = "//Purge";
				contents[key].value = "";
				changed.erase((*cit).first);
				break;
			}

			std::stringstream newLine;
			newLine << key << ":" << (*cit).first.comment << (*cit).second << comment;
			*it = newLine.str();
			contents[key].value = (*cit).second;

			changed.erase((*cit).first);
			break;
		}
	}

	for (std::map<ConfigEntry, std::string>::iterator cit = changed.begin(); cit != changed.end(); ++cit)
	{
		std::stringstream newConfig;

		newConfig << (*cit).first.key << ": " << (*cit).second;

		configLines.push_back(newConfig.str());
	}

	std::ofstream outFile(BH::path + configName);
	for (std::vector<std::string>::iterator it = configLines.begin(); it < configLines.end(); it++) {
		if ((*it).compare("//Purge") == 0)
			continue;

		if (std::next(it) == configLines.end())
			outFile << (*it);
		else
			outFile << (*it) << std::endl;
	}
	outFile.close();

	return true;
}

std::string Config::GetConfigName() {
	return BH::path + configName;
}

void Config::SetConfigName(std::string name) {
	configName = name;
}

/* ReadBoolean(std::string key, bool value)
*	Reads in a boolean from the key-pair.
*/
bool Config::ReadBoolean(std::string key, bool& value) {
	//Check if configuration value exists
	if (contents.find(key) == contents.end()) {
		contents[key].key = key;
		contents[key].value = value;
	}

	contents[key].type = CTBoolean;
	contents[key].pointer = (void*)&value;

	//Convert string to boolean
	const char* szValue = contents[key].value.c_str();
	if ((_stricmp(szValue, "1") == 0) || (_stricmp(szValue, "y") == 0) || (_stricmp(szValue, "yes") == 0) || (_stricmp(szValue, "true") == 0))
		value = true;
	else
		value = false;
	return value;
}

/* ReadInt(std::string key, int value)
*	Reads in a decimal or hex(which is converted to decimal) from the key-pair.
*/
int Config::ReadInt(std::string key, int& value) {
	//Check if configuration value exists
	if (contents.find(key) == contents.end()) {
		contents[key].key = key;
		contents[key].value = value;
	}

	contents[key].type = CTInt;
	contents[key].pointer = (void*)&value;

	if (!contents[key].value.find("0x")) {
		from_string<int>(value, contents[key].value, std::hex);
	}
	else {
		from_string<int>(value, contents[key].value, std::dec);
	}
	return value;
}

/* ReadInt(std::string key, int value)
*	Reads in a decimal or hex(which is converted to decimal) from the key-pair.
*/
unsigned int Config::ReadInt(std::string key, unsigned int& value) {
	//Check if configuration value exists
	if (contents.find(key) == contents.end()) {
		contents[key].key = key;
		contents[key].value = value;
	}

	contents[key].type = CTInt;
	contents[key].pointer = &value;

	if (!contents[key].value.find("0x")) {
		from_string<unsigned int>(value, contents[key].value, std::hex);
	}
	else {
		from_string<unsigned int>(value, contents[key].value, std::dec);
	}
	return value;
}

std::string Config::ReadString(std::string key, std::string &value) {
	//Check if configuration value exists
	if (contents.find(key) == contents.end())
	{
		contents[key].key = key;
		contents[key].value = value;
	}

	contents[key].pointer = &value;
	contents[key].type = CTString;

	value = contents[key].value;
	return value;
}

/* ReadToggle(std::string key, std::string toggle, bool state)
*	Reads in a toggle from the key->pair
*	Config Example:
*		Key: True, VK_A
*/
Toggle Config::ReadToggle(std::string key, std::string toggle, bool state, Toggle& value) {
	//Check if configuration value exists.
	Toggle ret;
	if (contents.find(key) == contents.end()) {
		contents[key].key = key;
		contents[key].value = ((state) ? "True, " : "False, ") + toggle;
	}

	contents[key].toggle = &value;
	contents[key].type = CTToggle;

	size_t stateVKeyDelimiterIndex = contents[key].value.find_first_of(",");

	// Read state string.
	std::string stateStr =
			Trim(contents[key].value.substr(0, stateVKeyDelimiterIndex));

	// Read virtual-key string and get mapped code.
	std::string virtualKeyStr =
			Trim(contents[key].value.substr(stateVKeyDelimiterIndex + 1));
	std::optional<VirtualKey> virtualKeyOptional =
			VirtualKey::GetFromSymbolName(virtualKeyStr);
	VirtualKey virtualKey =
			virtualKeyOptional.value_or(VirtualKey::GetUnset());

	ret.toggle = virtualKey.code;
	ret.state = StringToBool(std::move(stateStr));

	value = ret;
	return ret;
}

/* ReadKey(std::string key, std::string toggle)
*	Reads in a key from the key->pair.
*/
unsigned int Config::ReadKey(std::string key, std::string toggle, unsigned int &value) {
	//Check if configuration value exists.
	if (contents.find(key) == contents.end()) {
		contents[key].key = key;
		contents[key].value = toggle;
	}

	contents[key].pointer = &value;
	contents[key].type = CTKey;

	// Grab the proper key code and make sure it's valid
	std::optional<VirtualKey> virtualKeyOptional =
			VirtualKey::GetFromSymbolName(contents[key].value);
	if (!virtualKeyOptional.has_value()) {
		virtualKeyOptional = VirtualKey::GetFromSymbolName(toggle);
	}
	VirtualKey virtualKey = virtualKeyOptional.value_or(VirtualKey::GetUnset());

	value = virtualKey.code;

	return virtualKey.code;
}

/* ReadArray(std::string key)
*	Reads in a index-based array from the array
*/
std::vector<std::string> Config::ReadArray(std::string key, std::vector<std::string> &value) {
	int currentIndex = 0;
	value.clear();
	while (true) {
		std::stringstream index;
		index << currentIndex;
		std::string currentKey = key + "[" + index.str() + "]";
		if (contents.find(currentKey) == contents.end())
			break;
		value.push_back(contents[currentKey].value);
		contents[currentKey].pointer = &value;
		contents[currentKey].type = CTArray;
		currentIndex++;
	}
	return value;
}

/* ReadGroup(std::string key)
*	Reads in a map from the key->pair
*	Config Example:
*		Value[Test]: 0
*		Value[Pickles]: 1
*/
std::map<std::string, std::string> Config::ReadAssoc(std::string key, std::map<std::string, std::string> &value) {

	for (std::map<std::string, ConfigEntry>::iterator it = contents.begin(); it != contents.end(); it++) {
		if (!(*it).first.find(key + "[")) {
			std::pair<std::string, std::string> assoc;
			//Pull the value from between the []'s
			assoc.first = (*it).first.substr((*it).first.find("[") + 1, (*it).first.length() - (*it).first.find("[") - 2);
			// Check if key is already defined in map
			if (value.find(assoc.first) == value.end()) {
				assoc.second = (*it).second.value;
				value.insert(assoc);
			}
			else {
				value[key] = (*it).second.value;
			}

			(*it).second.pointer = &value;
			(*it).second.type = CTAssoc;
		}
	}

	return value;
}

std::map<std::string, bool> Config::ReadAssoc(std::string key, std::map<std::string, bool> &value) {

	for (std::map<std::string, ConfigEntry>::iterator it = contents.begin(); it != contents.end(); it++) {
		if (!(*it).first.find(key + "[")) {
			std::pair<std::string, bool> assoc;
			assoc.first = (*it).first.substr((*it).first.find("[") + 1, (*it).first.length() - (*it).first.find("[") - 2);
			transform(assoc.first.begin(), assoc.first.end(), assoc.first.begin(), ::tolower);

			if (value.find(assoc.first) == value.end()) {
				assoc.second = StringToBool((*it).second.value);
				value.insert(assoc);
			}
			else {
				value[assoc.first] = StringToBool((*it).second.value);
			}

			(*it).second.pointer = &value;
			(*it).second.type = CTAssocBool;
		}
	}

	return value;
}

std::map<std::string, unsigned int> Config::ReadAssoc(std::string key, std::map<std::string, unsigned int> &value) {

	for (std::map<std::string, ConfigEntry>::iterator it = contents.begin(); it != contents.end(); it++) {
		if ((*it).first.find(key + "[") != std::string::npos) {
			std::pair<std::string, unsigned int> assoc;
			//Pull the value from between the []'s
			assoc.first = (*it).first.substr((*it).first.find("[") + 1, (*it).first.length() - (*it).first.find("[") - 2);
			//Simply store the value that was after the :
			if ((*it).second.value.find("0x") != std::string::npos)
				from_string<unsigned int>(assoc.second, (*it).second.value, std::hex);
			else
				from_string<unsigned int>(assoc.second, (*it).second.value, std::dec);

			if (value.find(assoc.first) == value.end()) {
				value.insert(assoc);
			}
			else {
				value[assoc.first] = assoc.second;
			}

			(*it).second.pointer = &value;
			(*it).second.type = CTAssocInt;
		}
	}

	return value;
}

std::vector<std::pair<std::string, std::string>> Config::ReadMapList(std::string key, std::vector<std::pair<std::string, std::string>>& values) {

	for (std::vector<std::pair<std::string, std::string>>::iterator it = orderedKeyVals.begin(); it != orderedKeyVals.end(); it++) {
		if (!(*it).first.find(key + "[")) {
			std::pair<std::string, std::string> assoc;
			//Pull the value from between the []'s
			assoc.first = (*it).first.substr((*it).first.find("[") + 1, (*it).first.length() - (*it).first.find("[") - 2);
			//Also store the value
			assoc.second = (*it).second;
			values.push_back(assoc);
		}
	}

	return values;
}

std::list<std::string> Config::GetDefinedKeys() {
	std::list<std::string> ret;

	for (std::map<std::string, ConfigEntry>::iterator it = contents.begin(); it != contents.end(); it++) {
		std::string key = (*it).first;

		if (key.find("[") != std::string::npos)
			key = key.substr(0, key.find("["));

		ret.push_back(key);
	}
	ret.unique();
	return ret;
}

bool Config::HasChanged(ConfigEntry entry, std::string& value) {
	if (entry.type != CTToggle && entry.pointer == NULL)
		return false;

	switch (entry.type) {
	case CTBoolean: {
		bool currentBool = *((bool*)entry.pointer);
		bool storedBool = StringToBool(entry.value);

		if (storedBool == currentBool)
			return false;

		value = currentBool ? "True" : "False";
		return true;
	}
	case CTInt: {
		int currentInt = *((int*)entry.pointer);

		int storedInt = 0;
		std::stringstream stream;
		bool hex = false;
		if (entry.value.find("0x") != std::string::npos) {
			from_string<int>(storedInt, entry.value, std::hex);
			stream << std::hex;
			hex = true;
		}
		else {
			from_string<int>(storedInt, entry.value, std::dec);
		}

		if (currentInt == storedInt)
			return false;

		stream << currentInt;
		value = ((hex) ? "0x" : "") + stream.str();
		return true;
	}
	case CTString: {
		std::string currentString = *((std::string*)entry.pointer);

		if (currentString.compare(entry.value) == 0)
			return false;

		value = currentString;
		return true;
	}
	case CTArray: {
		std::vector<std::string> valTest = *((std::vector<std::string>*)entry.pointer);
		std::string ind = entry.key.substr(entry.key.find("[") + 1, entry.key.length() - entry.key.find("[") - 2);
		int index = atoi(ind.c_str());

		if (index >= valTest.size()) {
			value = "";
			return true;
		}

		std::string currentString = valTest.at(index);

		if (currentString.compare(entry.value) == 0)
			return false;

		value = currentString;
		return true;
	}

	case CTAssoc: {
		std::string assocKey = entry.key.substr(entry.key.find("[") + 1, entry.key.length() - entry.key.find("[") - 2);
		std::map<std::string, std::string> valTest = *((std::map<std::string, std::string>*)entry.pointer);

		std::string currentString = valTest[assocKey];

		if (currentString.compare(entry.value) == 0)
			return false;

		value = currentString;
		return true;
	}
	case CTAssocBool: {
		std::string assocKey = entry.key.substr(entry.key.find("[") + 1, entry.key.length() - entry.key.find("[") - 2);
		std::transform(assocKey.begin(), assocKey.end(), assocKey.begin(), ::tolower);
		std::map<std::string, bool> valTest = *((std::map<std::string, bool>*)entry.pointer);

		bool currentBool = valTest[assocKey];

		if (currentBool == StringToBool(entry.value))
			return false;

		value = currentBool ? "True" : "False";
		return true;
	}
	case CTAssocInt: {
		std::string assocKey = entry.key.substr(entry.key.find("[") + 1, entry.key.length() - entry.key.find("[") - 2);
		std::map<std::string, unsigned int> valTest = *((std::map<std::string, unsigned int>*)entry.pointer);
		int currentInt = valTest[assocKey];

		int storedInt = 0;
		std::stringstream stream;
		bool hex = false;
		if (entry.value.find("0x") != std::string::npos) {
			from_string<int>(storedInt, entry.value, std::hex);
			stream << std::hex;
			hex = true;
		}
		else {
			from_string<int>(storedInt, entry.value, std::dec);
		}

		if (currentInt == storedInt)
			return false;

		stream << currentInt;
		value = ((hex) ? "0x" : "") + stream.str();
		return true;
	}
	case CTToggle: {
		size_t delimiterIndex = entry.value.find_first_of(",");

		// Get the state for the old Toggle.
		std::string oldStateStr = Trim(entry.value.substr(0, delimiterIndex));

		// Get the virtual-key for the old Toggle.
		std::string oldVirtualKeyStr =
				Trim(entry.value.substr(delimiterIndex + 1));
		std::optional<VirtualKey> oldVirtualKeyOptional =
				VirtualKey::GetFromSymbolName(oldVirtualKeyStr);

		bool oldState = StringToBool(std::move(oldStateStr));
		VirtualKey oldVirtualKey =
				oldVirtualKeyOptional.value_or(VirtualKey::GetUnset());

		if (entry.toggle->toggle == oldVirtualKey.code && entry.toggle->state == oldState)
			return false;

		std::stringstream stream;
		const VirtualKey& newKey = VirtualKey::GetFromCode(entry.toggle->toggle);

		stream << ((entry.toggle->state) ? "True" : "False") << ", " << newKey.symbol_name;

		value = stream.str();
		return true;
	}
	case CTKey: {
		unsigned int currentKeyCode = *((unsigned int*)entry.pointer);

		// Get the virtual-key for the old Key.
		std::optional<VirtualKey> oldVirtualKeyOptional =
				VirtualKey::GetFromSymbolName(entry.value);
		VirtualKey oldVirtualKey =
				oldVirtualKeyOptional.value_or(VirtualKey::GetUnset());

		if (oldVirtualKey.code == currentKeyCode) {
			return false;
		}

		const VirtualKey& newVirtualKey = VirtualKey::GetFromCode(currentKeyCode);
		value = newVirtualKey.symbol_name;
		return true;
	}
	}
	return false;
}

bool Config::StringToBool(std::string input) {
	const char* boolStr = input.c_str();
	return (_stricmp(boolStr, "1") == 0) || (_stricmp(boolStr, "y") == 0) || (_stricmp(boolStr, "yes") == 0) || (_stricmp(boolStr, "true") == 0);
}
