/*
 * Register.cpp
 *
 *  Created on: Feb 6, 2016
 *      Author: noah
 */

#include "register.h"

template<class T>
Register<T>::Register()
{
	data = 0;
}

template<class T>
Register<T>::~Register()
{

}

template<class T>
void Register<T>::set(int pos, bool value)
{
	data |= value << pos;
}

template<class T>
void Register<T>::clear(int pos)
{
	data |= 0 << pos;
}

template<class T>
void Register<T>::clearAll ()
{
	for (int i = 0; i < 64; i++)
		data |= 0 << i;
}

template<class T>
void Register<T>::toggle(int pos)
{
	data ^=1 << pos;
}


void transfer (Register8 a, Register8 b)
{
	b.data = a.data;
}

void transfer (Register16 a, Register16 b)
{
	b.data = a.data;
}

void transfer (Register32 a, Register32 b)
{
	b.data = a.data;
}

void transfer (Register64 a, Register64 b)
{
	b.data = a.data;
}

