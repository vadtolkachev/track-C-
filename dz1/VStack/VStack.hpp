#pragma once
#include "defines.hpp"
#include <new>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <cstring>
#include <math.h>


class VStack
{
public:
	VStack();
	VStack(const VStack &stack);
	~VStack();

	int checkFirstCanary() const;
	int checkSecondCanary() const;
	int checkThirdCanary() const;
	int checkFourthCanary() const;
	int checkSize() const;
	int checkCapacity() const;
	int checkPoison(data_t *data) const;
	int checkSum1(long *ref) const;
	int checkSum2(long *ref) const;
	int checkNullptr() const;

	int checkStack(data_t *data, long *ref) const;
	int checkStack_print(const char *file, int line, const char *func) const;
	int checkStack_dump(const char *file, int line, const char *func) const;

	int getTop(data_t *res) const;
	int getSize() const;
	int getCapacity() const;

	int push(data_t data);
	int pop();

	bool isEmpty() const;

	void printStack() const;
	void printBadStack() const;
	void print_err(const char *err, const char *file, int line, const char *func, void *what, int format) const;
	void dumpStack(const char *str) const;
	void dumpBadStack() const;
	void dump_err(const char *err, const char *file, int line, const char *func, void *what, int format) const;

	void getDumpFileName(char str[45]) const;
	
	void calcSum1();
	void calcSum2();

	VStack &operator=(const VStack &stack);
	

private:
	long unsigned m_canary1;

	long m_sum1;
	long m_sum2;

	int m_size;
	int m_capacity;	
	data_t *m_stack;
	FILE *m_dumpFile;

	long unsigned m_canary2;
};

