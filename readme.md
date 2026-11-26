
# ofxConfs

managing a config file that use field=value pattern

# syntaxe

	[field]=[value0];[value1]

- lines starting with the char # are ignored
- any character after a # in a line is ignored (spaces before the # too)
- empty lines are ignored
- comments are not kept : `save()` writes the file back without them
- a value can't contain a # (it would start a comment)

example

	#comment
	property=value;value #comment

# how to use

test.conf

	myField=value0;value1

code

	auto conf = ConfLibrary::get("filename"); // filename.conf
	conf->get("field")->getValue(1); // (string) value1
