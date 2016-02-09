/*
 * nes.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: noah
 */

#include "vm.h"


VM::VM ()
{
	proc = Register8 (); // processor flags
	sp   = Register8 (); // stack pointer
	acu  = Register64 (); // Mathematical register

	A = Register8 ();
	B = Register8 (); // 1 byte or 8 bit registers
	C = Register8 ();

	D = Register16 ();
	E = Register16 (); // 2 byte or 16 bit registers
	F = Register16 ();

	G = Register32 ();
	H = Register32 (); // 4 byte or 32 bit registers
	I = Register32 ();

	X = Register64 ();
	Y = Register64 (); // 8 byte or 64 bit registers
	Z = Register64 ();

	memory = vector<byte> ();
	memory.reserve (32*1024*1024);
	parts = vector<byte> ();

	place = 0;
	opcode = 0x00;
}

VM::~VM ()
{

}

void VM::feed (vector<byte> input)
{
	parts = input;
}

void VM::runCycle ()
{
	updateOpcode ();

	switch (opcode)
	{
	case 0x01:
		transfer (A, B);
		break;
	case 0x02:
		transfer (B, A);
		break;
	case 0x03:
		transfer (A, C);
		break;
	case 0x04:
		transfer (C, A);
		break;
	case 0x05:
		transfer (B, C);
		break;
	case 0x06:
		transfer (C, B);
		break;
	case 0x07:
		A.data++;
		break;
	case 0x08:
		A.data--;
		break;
	case 0x09:
		B.data++;
		break;
	case 0x0A:
		B.data--;
		break;
	case 0x0B:
		C.data++;
		break;
	case 0x0C:
		C.data--;
		break;
	case 0x0D:
		A.data = A.data + B.data;
		break;
	case 0x0E:
		B.data = A.data + B.data;
		break;
	case 0x0F:
		A.data = A.data + C.data;
		break;
	case 0x10:
		C.data = A.data + C.data;
		break;
	case 0x11:
		B.data = B.data + B.data;
		break;
	case 0x12:
		C.data = B.data + C.data;
		break;
	case 0x13:
		A.data = A.data - B.data;
		break;
	case 0x14:
		A.data = A.data - C.data;
		break;
	case 0x15:
		B.data = B.data - A.data;
		break;
	case 0x16:
		B.data = B.data - C.data;
		break;
	case 0x17:
		C.data = C.data - A.data;
		break;
	case 0x18:
		C.data = C.data - B.data;
		break;
	case 0x19:
		A.data = A.data * B.data;
		break;
	case 0x1A:
		B.data = A.data * B.data;
		break;
	case 0x1B:
		A.data = A.data * C.data;
		break;
	case 0x1C:
		C.data = A.data * C.data;
		break;
	case 0x1D:
		B.data = B.data * C.data;
		break;
	case 0x1E:
		C.data = B.data * C.data;
		break;
	case 0x1F:
		A.data = A.data / B.data;
		break;
	case 0x20:
		A.data = A.data / C.data;
		break;
	case 0x21:
		B.data = B.data / A.data;
		break;
	case 0x22:
		B.data = B.data / C.data;
		break;
	case 0x23:
		C.data = C.data / A.data;
		break;
	case 0x24:
		C.data = C.data / B.data;
		break;
	case 0x25:
		updateOpcode ();
		A.data += opcode;
		break;
	case 0x26:
		updateOpcode ();
		A.data -= opcode;
		break;
	case 0x27:
		updateOpcode ();
		A.data *= opcode;
		break;
	case 0x28:
		updateOpcode ();
		A.data /= opcode;
		break;
	case 0x29:
		updateOpcode ();
		B.data += opcode;
		break;
	case 0x2A:
		updateOpcode ();
		B.data -= opcode;
		break;
	case 0x2B:
		updateOpcode ();
		B.data *= opcode;
		break;
	case 0x2C:
		updateOpcode ();
		B.data /= opcode;
		break;
	case 0x2D:
		updateOpcode ();
		C.data += opcode;
		break;
	case 0x2E:
		updateOpcode ();
		C.data -= opcode;
		break;
	case 0x2F:
		updateOpcode ();
		C.data *= opcode;
		break;
	case 0x30:
		updateOpcode ();
		C.data /= opcode;
		break;
	case 0x31:
		updateOpcode ();
		setMemory (opcode, A);
		break;
	case 0x32:
		updateOpcode ();
		setMemory (opcode, B);
		break;
	case 0x33:
		updateOpcode ();
		setMemory (opcode, C);
		break;
	case 0x34:
		updateOpcode ();
		loadMemory (opcode, A);
		break;
	case 0x35:
		updateOpcode ();
		loadMemory (opcode, B);
		break;
	case 0x36:
		updateOpcode ();
		loadMemory (opcode, C);
		break;
	default:
		break;
	}
}

void VM::updateOpcode ()
{
	opcode = parts[place++];
}

void VM::loadMemory (int place, Register8 &val)
{
	val.data = memory[place];
}

void VM::loadMemory (int place, Register16 &val)
{
	int16_t a;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 8; j++)
			a |= (memory[place + i] >> j) & 1 << j;
	val.data = memory[place]; // todo come back to this
}

void VM::loadMemory (int place, Register32 &val)
{
	val.data = memory[place];
}

void VM::loadMemory (int place, Register64 &val)
{
	val.data = memory[place];
}


void VM::setMemory (int place, Register8 val)
{
	memory[place] = val.data;
}

void VM::setMemory (int place, Register16 val)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 8; j++)
			memory[place + i] |= (val.data >> j) & 1 << j;
	}
}

void VM::setMemory (int place, Register32 val)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
			memory[place + i] |= (val.data >> j) & 1 << j;
	}
}

void VM::setMemory (int place, Register64 val)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			memory[place + i] |= (val.data >> j) & 1 << j;
	}
}
