/*
 * Register.h
 *
 *  Created on: Feb 6, 2016
 *      Author: noah
 */

#ifndef Register_H_
#define Register_H_

#include <iostream>
#include <vector>
using namespace std;

#include <string.h>
#include <stdlib.h>
#include "types.h"

template<class T>
class Register {
public:
	Register ();
	virtual ~Register ();
	T data;
	void set (int pos, bool value);
	void clear (int pos);
	void clearAll ();
	void toggle (int pos);
};

template class Register<byte>;
template class Register<int16_t>;
template class Register<int32_t>;
template class Register<int64_t>;

typedef Register<byte> Register8;
typedef Register<int16_t> Register16;
typedef Register<int32_t> Register32;
typedef Register<int64_t> Register64;

void transfer (Register8 a, Register8 b);
void transfer (Register16 a, Register16 b);
void transfer (Register32 a, Register32 b);
void transfer (Register64 a, Register64 b);


#endif /* Register_H_ */
