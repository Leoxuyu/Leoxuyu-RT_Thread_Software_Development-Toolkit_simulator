/*
 * main.c
 *
 *  Created on: 2019��3��28��
 *      Author: work
 */

#include "rtthread.h"
#include "cJSON.h"

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




int main(void)
{
	cJSON_Test();
}















