#pragma once

#include <iostream>
#include <vector>

#include "ConfReader.h"

/// <summary>
/// https://stackoverflow.com/questions/1008019/how-do-you-implement-the-singleton-design-pattern
/// </summary>
class ConfLibrary
{
	static ConfLibrary* instance;
	vector<ConfReader*> confs;

	ConfLibrary() {}

	/// <summary>
	/// return : reader of given UID
	/// add it to local buff
	/// </summary>
	ConfReader* fetch(string uid)
	{
		for (ConfReader* cr : confs)
		{
			if (cr->isFile(uid)) return cr;
		}

		auto conf = new ConfReader(uid);
		confs.push_back(conf);

		return conf;
	}

public:

	static ConfLibrary& getInstance()
	{
		static ConfLibrary instance;
		return instance;
	}
	
	ConfLibrary(ConfLibrary const&)			= delete;
	void operator=(ConfLibrary const&)		= delete;

	/// <summary>
	/// return reader of given UID
	/// a file .conf within data/ folder
	/// </summary>
	static ConfReader* get(std::string uid)
	{
		return getInstance().fetch(uid);
	}

	static bool hasField(string file, string field)
	{
		return getBool(file, field);
	}

	/// <summary>
	/// missing : returns false
	/// non numeric value eval presence of value
	/// </summary>
	static bool getBool(string file, string field)
	{
		auto conf = ConfLibrary::get(file);
		if (conf == nullptr) return false;

		auto line = conf->get(field);
		if (line == nullptr) return false;

		return conf->isFieldActive(field);
	}

	/// <summary>
	/// missing : 0f
	/// </summary>
	static float getFloat(string file, string field, int column = -1)
	{
		auto conf = ConfLibrary::get(file);
		if (conf == nullptr) return 0;

		auto line = conf->get(field);
		if (line == nullptr) return 0;

		if (column < 0) column = 0;

		if (line->countValues() >= column) return 0;
		
		return ofToFloat(line->getValue(column));
	}

};