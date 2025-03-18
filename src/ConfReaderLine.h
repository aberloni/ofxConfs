#pragma once

#include <stdio.h>
#include "ofMain.h"

/// <summary>
/// champ=value;value
/// </summary>
class ConfReaderLine
{
	string property;		// line header separated by '='
	vector<string> values;	// all values separated by ';'

	string separator_header = "=";
	string separator_values = ";";

public:

	ConfReaderLine(string raw)
	{
		auto split = ofSplitString(raw, separator_header);
		if (split.size() == 1)
		{
			property = raw;
			return;
		}

		property = split[0];

		raw = split[1];
		split = ofSplitString(raw, separator_values);
		for (auto s : split)
		{
			values.push_back(s);
		}

		//cout << "Config RAW : " << raw << endl;
		//cout << stringify() << endl;

	}

	string getHeader()
	{
		return property;
	}

	bool hasValues()
	{
		return values.size() > 0;
	}

	bool isProperty(string prop)
	{
		return property == prop;
	}

	/// <summary>
	/// is given field
	/// </summary>
	bool hasValue(string val)
	{
		for (auto v : values)
		{
			if (v == val)
				return true;
		}
		return false;
	}

	size_t countValues()
	{
		return values.size();
	}

	/// <summary>
	/// default : string
	/// </summary>
	string getValue(size_t column)
	{
		return getString(column);
	}

	size_t getInt(size_t column)
	{
		return ofToInt(getString(column));
	}

	float getFloat(size_t column)
	{
		return ofToFloat(getString(column));
	}

	/// <summary>
	/// returns empty if not present (out of bounds)
	/// </summary>
	string getString(size_t column)
	{
		if(column < 0 || column >= countValues()) return ""; // oob => empty
		return values[column];
	}

	/// <summary>
	/// return : success
	/// </summary>
	bool setField(size_t column, string value)
	{
		// make empty missing fields
		if (column >= countValues())
		{
			//cout << "oob:values" << endl;
			while (values.size() <= column)
			{
				values.push_back("");
			}
		}

		//cout << "set:field:" << property << " #" << column << " = " << value << endl;

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