/*
 * RegisterMap.c
 *
 *  Created on: 2019��3��27��
 *      Author: work
 */

#include "RegisterMap.h"

//��������
REG_MAP *REG_MAP_Create(void)
{
	REG_MAP *handle = RT_NULL;
	handle = (REG_MAP *)rt_malloc(sizeof(REG_MAP));
	if(handle==RT_NULL)
	{
		//û�����뵽�ڴ�ͷ��ؿ�ֵ
		return RT_NULL;
	}
	//�������
	handle->head.DATA = 0;
	handle->head.next = &handle->head;
	handle->head.prev = &handle->head;//ѭ��˫������
	handle->head.DataType = NO_DATA;
	handle->num = 0;
	return handle;
}

//ʵ��β��
rt_err_t REG_MAP_Append(char *name,int address,DataType_t type,int data, REG_MAP *handle)
{
	struct REG_NODE *new = RT_NULL;
	new = (struct REG_NODE *)rt_malloc(sizeof(struct REG_NODE));
	if(new==RT_NULL)
	{
		return RT_ERROR;
	}
	new->DATA = data;
	new->Address=address;
	new->DataType=type;
	rt_memset(new->NAME,'\0',REG_NAME_LEN_MAX);
	if(rt_strlen(name)>REG_NAME_LEN_MAX)
	{
		rt_memcpy(new->NAME,name,REG_NAME_LEN_MAX);
	}
	else
	{
		rt_memcpy(new->NAME,name,rt_strlen(name));
	}
	new->next = &handle->head;
	new->prev = handle->head.prev;
	handle->head.prev->next = new;
	handle->head.prev = new;
	handle->num++;
	return RT_EOK;
}

//ʵ��ͷ��
rt_err_t REG_MAP_Prevend(char *name,int address,DataType_t type,int data, REG_MAP *handle)
{
	struct REG_NODE *new = RT_NULL;
	new = (struct REG_NODE *)rt_malloc(sizeof(struct REG_NODE));
	if(new==RT_NULL)
	{
		return RT_ERROR;
	}
	new->DATA = data;
	new->Address=address;
	new->DataType=type;
	rt_memset(new->NAME,'\0',REG_NAME_LEN_MAX);
	if(rt_strlen(name)>REG_NAME_LEN_MAX)
	{
		rt_memcpy(new->NAME,name,REG_NAME_LEN_MAX);
	}
	else
	{
		rt_memcpy(new->NAME,name,rt_strlen(name));
	}
	new->next = handle->head.next;
	new->prev = &handle->head;
	handle->head.next->prev = new;
	handle->head.next = new;
	handle->num++;
	return RT_EOK;
}

//���Ĵ�����ַ��ѯ����
int REG_MAP_Find_Data_By_Address(int address,REG_MAP *handle)
{
	int ret=-1;
	struct REG_NODE *tail = RT_NULL;
	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (tail->Address==address)
		{
			ret=tail->DATA;
		}
	}
	return ret;
}

//���Ĵ������Ʋ�ѯ����
int REG_MAP_Find_Data_By_Name(const char *name,REG_MAP *handle)
{
	int ret=-1;
	struct REG_NODE *tail = RT_NULL;
	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (rt_strcmp(tail->NAME,name)==0)
		{
			ret=tail->DATA;
		}
	}
	return ret;
}


//���Ĵ�����ַ��ѯ����
DataType_t REG_MAP_Find_Type_By_Address(int address,REG_MAP *handle)
{
	DataType_t ret=NO_DATA;
	struct REG_NODE *tail = RT_NULL;
	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (tail->Address==address)
		{
			ret=tail->DataType;
		}
	}
	return ret;
}

//���Ĵ������Ʋ�ѯ����
DataType_t REG_MAP_Find_Type_By_Name(const char *name,REG_MAP *handle)
{
	DataType_t ret=NO_DATA;
	struct REG_NODE *tail = RT_NULL;
	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (rt_strcmp(tail->NAME,name)==0)
		{
			ret=tail->DataType;
		}
	}
	return ret;
}

//���Ĵ�����ַ�޸�����
rt_err_t REG_MAP_Modify_Data_By_Address(int address,int data,REG_MAP *handle)
{
	struct REG_NODE *tail = RT_NULL;
	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (tail->Address==address)
		{
			tail->DATA=data;
			return RT_EOK;
		}
	}
	return RT_ERROR;
}

//���Ĵ��������޸�����
rt_err_t REG_MAP_Modify_Data_By_Name(const char *name,int data,REG_MAP *handle)
{
	struct REG_NODE *tail = RT_NULL;
	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (rt_strcmp(tail->NAME,name)==0)
		{
			tail->DATA=data;
			return RT_EOK;
		}
	}
	return RT_ERROR;
}

//���Ĵ�����ַ�޸�����
rt_err_t REG_MAP_Modify_Type_By_Address(int address,DataType_t type,REG_MAP *handle)
{
	struct REG_NODE *tail = RT_NULL;
	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (tail->Address==address)
		{
			tail->DataType=type;
			return RT_EOK;
		}
	}
	return RT_ERROR;
}

//���Ĵ��������޸�����
rt_err_t REG_MAP_Modify_Type_By_Name(const char *name,DataType_t type,REG_MAP *handle)
{
	struct REG_NODE *tail = RT_NULL;
	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (rt_strcmp(tail->NAME,name)==0)
		{
			tail->DataType=type;
			return RT_EOK;
		}
	}
	return RT_ERROR;
}

//����ַɾ���Ĵ���
rt_err_t REG_MAP_Del_By_Address(int address, REG_MAP *handle)
{
	struct REG_NODE *tail = RT_NULL;
	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if(tail->Address==address)
		{
			tail->next->prev = tail->prev;
			tail->prev->next = tail->next;
			rt_free(tail);
			handle->num--;
			return RT_EOK;
		}
	}
	return RT_ERROR;
}

//������ɾ���Ĵ���
rt_err_t REG_MAP_Del_By_Name(const char *name, REG_MAP *handle)
{
	struct REG_NODE *tail = RT_NULL;
	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		if (rt_strcmp(tail->NAME,name)==0)
		{
			tail->next->prev = tail->prev;
			tail->prev->next = tail->next;
			rt_free(tail);
			handle->num--;
			return RT_EOK;
		}
	}
	return RT_ERROR;
}

//��������
void REG_MAP_Destroy(REG_MAP *handle)
{
	struct REG_NODE *tail = RT_NULL;
	struct REG_NODE *save = RT_NULL;
	for (tail = handle->head.next; tail != &handle->head; tail = save)
	{
		save = tail->next;
		rt_free(tail);
	}
	rt_free(handle);
}

void Print_REG_MAP(REG_MAP *handle)
{
	struct REG_NODE *tail = RT_NULL;
	printf("------------------------------------------\n");
	printf("NAME\t\tADD\t\tDATA\n");
	printf("------------------------------------------\n");
	for (tail = handle->head.next; tail != &handle->head; tail = tail->next)
	{
		printf("[%s]\t\t[%d]\t\t0x%08X\n",tail->NAME,tail->Address,tail->DATA);
	}
	printf("------------------------------------------\n");
}

//TODO:�������ݳ־û���REG_MAPд���ļ�ϵͳ����Ҫfatfs֧��

void REG_MAP_Test(void)
{
	REG_MAP *handle = RT_NULL;
	//������REG_MAP
	handle = REG_MAP_Create();
	if(handle !=RT_NULL)
	{
		//���һЩ����
		REG_MAP_Append("pas",1,UINT_32B,0x55,handle);
		REG_MAP_Append("name",55,UINT_32B,0x54,handle);
		REG_MAP_Append("usage",3,UINT_32B,0x51,handle);
		REG_MAP_Append("get",4,UINT_32B,0x50,handle);
		//��������
		int findnum=REG_MAP_Find_Data_By_Name("get",handle);
		printf("findnum:0x%02X\n",findnum);
		//��ʾREG_MAP��������
		Print_REG_MAP(handle);
		//�޸�REG_MAP����
		REG_MAP_Modify_Data_By_Address(1,1024,handle);
		REG_MAP_Modify_Data_By_Name("usage",8848,handle);
		//��ʾREG_MAP��������
		Print_REG_MAP(handle);
		//ɾ��REG_MAP�ڵ�
		REG_MAP_Del_By_Address(55,handle);
		REG_MAP_Del_By_Name("usage",handle);
		//��ʾREG_MAP��������
		Print_REG_MAP(handle);
		//����REG_MAP�������ݣ��ͷ�����������ڴ�
		REG_MAP_Destroy(handle);
	}
}
