
# ofxConfs

managing a config file that use field=value pattern

# syntaxe

	[field]=[value0];[value1]

- lines starting with the char # are ignored
- empty lines are ignored

# how to use

test.conf

	myField=value0;value1

code

	auto conf = ConfLibrary::get("filename"); // filename.conf
	conf->get("field")->getValue(1); // (string) value1
