
# ofxConfs

# how to use

test.conf

	myField=value0;value1

code

	auto conf = ConfLibrary::get("filename"); // filename.conf
	conf->get("field")->getValue(1); // (string) value1
