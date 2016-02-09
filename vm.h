/*
 * VM.h
 *
 *  Created on: Feb 6, 2016
 *      Author: noah
 */

#ifndef VM_H_
#define VM_H_

#include <iostream>
#include <vector>

using std::vector;


#include "vm.h"
#include "register.h"
#include "types.h"

class VM
{
public:
	VM();
	virtual ~VM();
	void feed (vector<byte> input);
	void runCycle ();
	void updateOpcode ();

	void loadMemory (int place, Register8 &val);
	void loadMemory (int place, Register16 &val);
	void loadMemory (int place, Register32 &val);
	void loadMemory (int place, Register64 &val);

	void setMemory (int place, Register8 val);
	void setMemory (int place, Register16 val);
	void setMemory (int place, Register32 val);
	void setMemory (int place, Register64 val);
	vector<byte> parts;
	vector<byte> memory;

	Register8 proc;
	Register8 sp; // stack pointer
	Register64 acu;

	Register8 A;
	Register8 B;
	Register8 C;

	Register16 D;
	Register16 E;
	Register16 F;

	Register32 G;
	Register32 H;
	Register32 I;

	Register64 X;
	Register64 Y;
	Register64 Z;

	int place;
	byte opcode;
};
#endif /* VM_H_ */
