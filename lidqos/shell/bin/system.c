/*
 * system.c
 *
 *  Created on: Nov 26, 2014
 *      Author: lidq
 */

#include <shell/system.h>

s_sys_var *sys_var = NULL;

int main(int argc, char **args)
{
	printf("Start System Process.\n");

//	void *p = malloc(0x1000);
//	printf("%x\n", p);
//
//	void *p2 = malloc(0x1000);
//	printf("%x\n", p2);
//
//	void *p3 = malloc(0x1000);
//	printf("%x\n", p3);
//
//	void *p4 = malloc(0x1000);
//	printf("%x\n", p4);

//	free(p);
//	free(p2);
//	free(p3);
//	free(p4);

//	int num = 50;
//	void *ps[num];
//	for (int i = 0; i < num; i++)
//	{
//		ps[i] = malloc(0x1000);
//		//printf("%x\n", ps[i]);
//	}
//	for (int i = 0; i < 0x20; i++)
//	{
//		free(ps[i]);
//	}
	for (int i = 0; i < 15000; i++)
	{
		putchar('A');
	}


//	printf("%x\n", malloc(0x4));
//	printf("%x\n", malloc(0x4));
//	printf("%x\n", malloc(0x4));
//	printf("%x\n", malloc(0x4));

	for (;;)
	{
	}

	return 0;
}
