#ifndef FS_H
#define FS_H

#include <fstream>
#include <sys/stat.h>
#include <iostream>
#include <vector>
using namespace std;
#include "types.h"
void write (vector<string> file, string loc);
string open (string file);
string openBytes (string file);
bool exists (string file);


#endif
