/*
 * RegisterMap.c
 *
 *  Created on: 2019��3��27��
 *      Author: work
 */

#ifndef INC_REGISTERMAP_C_
#define INC_REGISTERMAP_C_

#include "rtthread.h"

/* ʹ�����ݳ־û��ӿ� */
#define REG_MAP_USING_DATA_PERSISTENCE

/* �Ĵ��������ַ����������ֵ */
#define REG_NAME_LEN_MAX			0x0010

/* �Ĵ����洢���ݵ����� */
typedef enum
{
	NO_DATA,
	IEEE32,
	UINT_32B,
	UINT_16B,
	UINT_8B,
	BOOLEAN
}DataType_t;

//��������ڵ���Ϣ�ṹ��
struct REG_NODE
{
	struct REG_NODE *next;	//ָ����һ���ڵ��ַ
	char NAME[REG_NAME_LEN_MAX];			//�Ĵ�������
	int Address;			//���ݵ�ַ
	DataType_t DataType;	//���� ��������
	int DATA;				//�ⲿ�û���������
	struct REG_NODE *prev;	//ָ����һ���ڵ��ַ
};

//������������
typedef struct REG_MAP_t
{
    struct REG_NODE head;	//����
    int num;				//������Ŀ
}REG_MAP;


REG_MAP *REG_MAP_Create(void);
//��
rt_err_t REG_MAP_Append(char *name,int address,DataType_t type,int data, REG_MAP *handle);
rt_err_t REG_MAP_Prevend(char *name,int address,DataType_t type,int data, REG_MAP *handle);

//��
int REG_MAP_Find_Data_By_Address(int address,REG_MAP *handle);
int REG_MAP_Find_Data_By_Name(const char *name,REG_MAP *handle);
DataType_t REG_MAP_Find_Type_By_Address(int address,REG_MAP *handle);
DataType_t REG_MAP_Find_Type_By_Name(const char *name,REG_MAP *handle);

//��
rt_err_t REG_MAP_Modify_Data_By_Address(int address,int data,REG_MAP *handle);
rt_err_t REG_MAP_Modify_Data_By_Name(const char *name,int data,REG_MAP *handle);
rt_err_t REG_MAP_Modify_Type_By_Address(int address,DataType_t type,REG_MAP *handle);
rt_err_t REG_MAP_Modify_Type_By_Name(const char *name,DataType_t type,REG_MAP *handle);

//ɾ
rt_err_t REG_MAP_Del_By_Address(int address, REG_MAP *handle);
rt_err_t REG_MAP_Del_By_Name(const char *name, REG_MAP *handle);

//����
void REG_MAP_Destroy(REG_MAP *handle);

void REG_MAP_Test(void);

void Print_REG_MAP(REG_MAP *handle);


#endif /* INC_REGISTERMAP_C_ */
