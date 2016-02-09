#include "fs.h"

void write (vector<string> file, string loc)
{
	ofstream out (loc.c_str ());
	
	for (int i = 0; i < file.size (); i++)
	{
		out << file[i] << endl;
	}
	out.close ();
}

string open (string file)
{
	std::ifstream t(file.c_str ());
	std::string str((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());
    return str;
}

bool exists (string file)
{
	ifstream ifile(file.c_str ());
	return ifile;
}
