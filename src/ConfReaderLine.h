#pragma once

#include <stdio.h>
#include "ofMain.h"

/// <summary>
/// champ=value;value
/// </summary>
class ConfReaderLine
{
	string property;
	vector<string> values;

public:

	ConfReaderLine(string raw)
	{
		auto split = ofSplitString(raw, "=");
		if (split.size() == 1)
		{
			property = raw;
			return;
		}

		property = split[0];

		raw = split[1];
		split = ofSplitString(raw, ";");
		for (auto s : split)
		{
			values.push_back(s);
		}

		//cout << "Config RAW : " << raw << endl;
		//cout << stringify() << endl;

	}

	bool hasValues()
	{
		return values.size() > 0;
	}

	bool isProperty(string prop)
	{
		return property == prop;
	}

	bool hasValue(string field)
	{
		for (auto v : values)
		{
			if (v == field)
				return true;
		}
		return false;
	}

	string getValue(int column)
	{
		if (values.size() < column)
			return "";

		return values[column];
	}

	/// <summary>
	/// return : success
	/// </summary>
	bool setField(int column, string value)
	{
		if (values.size() <= column)
		{
			//cout << "oob:values" << endl;
			while (values.size() <= column)
			{
				values.push_back("");
			}
		}

		cout << "set:field:" << property << " #" << column << " = " << value << endl;

		values[column] = value;

		return true;
	}

	string stringify()
	{
		string ret = property + "=";
		for (auto v : values)
		{
			ret += v + ";";
		}

		// remove last ;
		ret = ofUTF8Substring(ret, 0, ret.size() - 1);

		//ret += "\n";

		return ret;
	}
};