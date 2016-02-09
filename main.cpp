
#include <iostream>
#include <vector>

using namespace std;

#include "fs.h"
#include "vm.h"
#include "nes.h"
#include <thread>

string getType (string input)
{
	if (input[0] == 'N' and input[1] == 'E' and input[2] == 'S')
	{
		return "NES";
	}
	else if (input[0] == 'M' and input[1] == 'V' and input[2] == 'M')
	{
		return "MVM";
	}
	return "";
}

int main (int argc, char **args)
{
	string data;

	VM machine = VM ();
	string arg;
	for (int i = 1; i < argc; i++)
	{
		arg = args[i];
		if (exists (arg))
		{
			data = open (arg);
		}
	}

	string type = getType (data);

	vector<byte> newdata = vector<byte> ();
	for (int i = 0; i < data.size (); i++)
		newdata.push_back (data[i]);

	if (type == "NES")
	{
		vector<byte> tmp = Nes::convert (newdata);
		machine.feed (tmp);
	}
	else if (type == "MVM")
	{
		vector<byte> newerdata = vector<byte> ();
		for (int i = 16; i < newdata.size (); i++)
			newerdata.push_back (newdata[i]);
		machine.feed (newerdata);
		while (machine.place < machine.parts.size ())
		{
			machine.runCycle ();
		}
	}
}
