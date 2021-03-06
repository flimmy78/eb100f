

#include "includes.h"


u8 return_rs485_buff[15];



#define		MY_INTERNAL_PROTOCOL_HEAD	0xEE

static void packet_cmd(u8 addr)
{
	u8 parity_byte;
	
	return_rs485_buff[0] = MY_INTERNAL_PROTOCOL_HEAD;
	return_rs485_buff[1] = addr;
    
	parity_byte = return_rs485_buff[1] + return_rs485_buff[2] + return_rs485_buff[3] + return_rs485_buff[4] + return_rs485_buff[5];

	return_rs485_buff[6]=parity_byte;
}



void send_to_rs485_data(u8 addr)
{
	packet_cmd(addr);
	RS485_SendBytes(7,return_rs485_buff);
 	delayms(40);

}


void return_data_to_rs485(u8 data1,u8 data2,u8 data3)
{

	u8 parity_byte = 0;

	return_rs485_buff[0] = 0xff;
	return_rs485_buff[1] = 0x01;
	

	return_rs485_buff[2] = data1;
	return_rs485_buff[3] = 0x88;
	return_rs485_buff[4] = data2;
	return_rs485_buff[5] = data3;

	
	for(u8 i=1;i<6;i++)
	{
		
		parity_byte += return_rs485_buff[i];
	}
	//parity_byte = return_rs485_buff[1] + return_rs485_buff[2] + return_rs485_buff[3] + return_rs485_buff[4] + return_rs485_buff[5];

	return_rs485_buff[6]=parity_byte;
	RS485_SendBytes(7,return_rs485_buff);
 	delayms(10);


}

static void send_buff_init(void)
{
	u8 i;

	for(i=0;i<10;i++)
	{
		return_rs485_buff[i] = 0;

	}
}

void my_proto_call_preset(u8 cno,u8 val,u8 addr)
{
	send_buff_init();
	return_rs485_buff[3] = 0x07;
	return_rs485_buff[4] = cno;
	return_rs485_buff[5] = val;

	send_to_rs485_data(addr);
}

void my_proto_set_preset(u8 cno,u8 val,u8 addr)
{
	send_buff_init();
	return_rs485_buff[3] = 0x03;
	return_rs485_buff[4] = cno;
	return_rs485_buff[5] = val;

	send_to_rs485_data(addr);
}


