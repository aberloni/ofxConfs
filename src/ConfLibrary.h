#pragma once

#include <iostream>
#include <vector>

#include "ConfReader.h"

/// <summary>
/// https://stackoverflow.com/questions/1008019/how-do-you-implement-the-singleton-design-pattern
/// </summary>
class ConfLibrary
{
public:



	static ConfLibrary& getInstance()
	{
		static ConfLibrary instance;
		return instance;
	}

private:
	
	static ConfLibrary* instance;
	vector<ConfReader*> confs;

	ConfLibrary() {}

	/// <summary>
	/// return : reader of given UID
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
	
	ConfLibrary(ConfLibrary const&)			= delete;
	void operator=(ConfLibrary const&)		= delete;

	/// <summary>
	/// return reader of given UID
	/// </summary>
	static ConfReader* get(std::string uid)
	{
		return getInstance().fetch(uid);
	}

	static ConfReader* getOceanConf(std::string ouid)
	{
		return get(ouid + "/ocean");
	}

};