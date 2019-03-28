/*
 * main.c
 *
 *  Created on: 2019��3��28��
 *      Author: work
 */

#include "rtthread.h"
#include "cJSON.h"
#include "FIFO.h"
#include "LIFO.h"

void cJSON_Test(void)
{
	cJSON_hook_init();
    cJSON * root =  cJSON_CreateObject();
    cJSON * item =  cJSON_CreateObject();
    cJSON * next =  cJSON_CreateObject();
    cJSON_AddItemToObject(root, "rc", cJSON_CreateNumber(0));//���ڵ������
    cJSON_AddItemToObject(root, "operation", cJSON_CreateString("CALL"));
    cJSON_AddItemToObject(root, "service", cJSON_CreateString("telephone"));
    cJSON_AddItemToObject(root, "text", cJSON_CreateString("��绰������"));
    cJSON_AddItemToObject(root, "semantic", item);//root�ڵ������semantic�ڵ�
    cJSON_AddItemToObject(item, "slots", next);//semantic�ڵ������item�ڵ�
    cJSON_AddItemToObject(next, "name", cJSON_CreateString("����"));//���name�ڵ�
    rt_kprintf("%s\n", cJSON_PrintUnformatted(root));
}

void FIFO_Test(void)
{
	rt_uint8_t AAA;
	FIFO_Queue fifo;
	FIFO_Init(&fifo,10);

	int i=0;
	while(FIFO_PushElement(&fifo,i))
	{
		rt_thread_delay(10);
		rt_kprintf("FIFO PushElement:%d\n",i);
		i++;
	}
	while(FIFO_PopElement(&fifo,&AAA))
	{
		rt_kprintf("FIFO PopElement:%d\n",AAA);
	}
}

void LIFO_Test(void)
{
	rt_uint8_t AAA;
	LIFO_Stack Lifo;
	LIFO_Init(&Lifo,10);
	int i=0;
	while(LIFO_PushElement(&Lifo,i))
	{
		rt_thread_delay(10);
		rt_kprintf("LIFO PushElement:%d\n",i);
		i++;
	}
	while(LIFO_PopElement(&Lifo,&AAA))
	{
		rt_kprintf("LIFO PopElement:%d\n",AAA);
	}
}


int main(void)
{
//	cJSON_Test();
	FIFO_Test();
	LIFO_Test();
}















