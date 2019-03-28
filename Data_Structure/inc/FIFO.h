/*
 * FIFO.h
 *
 *  Created on: 2019��3��28��
 *      Author: work
 */

#ifndef DATA_STRUCTURE_INC_FIFO_H_
#define DATA_STRUCTURE_INC_FIFO_H_

#include "rtthread.h"

typedef struct
{
	rt_uint32_t size;
	//����ָ�룬��ʱ������һ���ڴ�������
	rt_uint8_t *data_p;
	int front; //ָ���ͷ�������������ָ�Ŀռ䲻���Ԫ��
	int tail; //ָ���β��������������һ��Ԫ��
}FIFO_Queue;


rt_err_t FIFO_Init(FIFO_Queue *fifo,rt_uint32_t size);
rt_bool_t FIFO_PushElement(FIFO_Queue *fifo,rt_uint8_t data);
rt_bool_t FIFO_PopElement(FIFO_Queue *fifo,rt_uint8_t *data);

void FIFO_Clean(FIFO_Queue *fifo);
void FIFO_Destory(FIFO_Queue *fifo);









#endif /* DATA_STRUCTURE_INC_FIFO_H_ */
