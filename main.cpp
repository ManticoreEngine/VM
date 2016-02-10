
#include <iostream>
#include <vector>

using namespace std;

#include "fs.h"
#include "vm.h"
#include "nes.h"
#include <thread>


void parseHeader (vector<byte> codes, VM machine)
{
	if (codes[3] == 0x01)
	{
		machine.graphical = true;
	}
	else if (codes[3] == 0x00)
	{
		machine.graphical = false;
	}
	else
	{
		cout << "unspecified byte detected, binary ruined at 4th byte" << endl;
		exit (EXIT_FAILURE);
	}
}

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
	{
		newdata.push_back (data[i]);
	}

	if (type == "NES")
	{
		vector<byte> tmp = Nes::convert (newdata);
		machine.feed (tmp);
	}
	else if (type == "MVM")
	{
		vector<byte> header = vector<byte> ();
		vector<byte> newdata = vector<byte> ();
		for (int i = 0; i < data.size (); i++)
		{
			if (i < 16)
				header.push_back(data[i]);
			else
				newdata.push_back (data[i]);
		}
		machine.feed (newdata);
		parseHeader (header, machine);

		while (machine.place < machine.parts.size ())
		{
			machine.runCycle ();
		}
	}
}
