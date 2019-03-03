#include <stdio.h>
#include "VVector.hpp"


int main()
{
	VVector<int> tmp;
	tmp.push(1);
	tmp.push(2);
	tmp.push(3);
	tmp.getSize();

	VVector<int> tmp2(tmp);
	printf("size2 = %u\n", tmp2.getSize());
	printf("isEmpy2 = %d\n", tmp2.isEmpty());
	printf("tmp2[0] = %d\n", tmp2[0]);
	tmp2[0] = 7;
	printf("tmp2[0] = %d\n", tmp2[0]);

	tmp.pop();
	tmp.pop();

	tmp2.clear();
	tmp2 = tmp;


	VVector<VVector<int>> tmps;
	tmps.push(tmp);
	tmps.push(tmp2);


	printf("hello world!\n");

	return 0;
}