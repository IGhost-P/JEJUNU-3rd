// 플래처
uint16_t Fletcher16( uint8_t *data, int count )
{
   uint16_t sum1 = 0;
   uint16_t sum2 = 0;
   int index;

   for ( index = 0; index < count; ++index )
   {
      sum1 = (sum1 + data[index]) % 255;
      sum2 = (sum2 + sum1) % 255;
   }

   return (sum2 << 8) | sum1;
}
// 애들러#
 
unsigned long adler32(unsigned char *data, int len) /* where data is the location of the data in physical memory and len is the length of the data in bytes */
{
    unsigned long a = 1, b = 0;
    int index;
 
    /* Process each byte of the data in order */
    for (index = 0; index < len; ++index)
    {
        a = (a + data[index]) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
    }
 
    return (b << 16) | a;
}

// CRC
#include <inttypes.h> // uint32_t, uint8_t

uint32_t CRC32(const uint8_t data[], size_t data_length) {
	uint32_t crc32 = 0xFFFFFFFFu;
	
	for (size_t i = 0; i < data_length; i++) {
		const uint32_t lookupIndex = (crc32 ^ data[i]) & 0xff;
		crc32 = (crc32 >> 8) ^ CRCTable[lookupIndex];  // CRCTable is an array of 256 32-bit constants
	}
	
	// Finalize the CRC-32 value by inverting all the bits
	crc32 ^= 0xFFFFFFFFu;
	return crc32;
}
//
#include <stdio.h>
#define MAXNUM 100
 
int data_num;
 
void sending_message(int* message)
{
    printf("데이터의 갯수를 입력하시오.");
    scanf_s("%d", &data_num);
    if (data_num >= MAXNUM)
    {
        printf(" 최대 가능한 데이터 갯수를 초과하였습니다.\n 프로그램 종료.\n");
        exit(-1);
    }
 
 
    printf("데이터를 입력하시오.\n");
    for (int i = 0; i < data_num; i++)
    {
        scanf_s("%d", &message[i]);
    }
    printf("데이터 입력이 끝났습니다.\n\n");
 
}
 
int calculaton_Checksum(int* message)
{
    /* 임의의 길이를 갖는 메시지를 넘겨받아 Checksum을 계산하여 return한다.*/
    int Checksum;
    int sum = 0, pre_sum = 0;
 
    for (int n = 0; n < data_num; n++)
    {
        sum += message[n];
        if (pre_sum > sum)
            sum++;
        pre_sum = sum;
    }
 
    Checksum = ~sum;
 
    message[data_num] = Checksum;
    data_num++;
 
    return Checksum;
}
 
int check_Checksum(int* message)
{
    /* Checksum이 부착된 임의의 메시지를 넘겨받아, 에러가 검출되면 0, 아니면 1을 return한다. */
    int result = 0;
    int sum = 0, pre_sum = 0;
 
    for (int n = 0; n < data_num; n++)
    {
        sum += message[n];
        if ((unsigned int)pre_sum >(unsigned int)sum)
            sum++;
        (int)pre_sum = (int)sum;
    }
 
    result = ~sum;
 
    if (result == 0)
        return 1;
    else
        return 0;
}
 
void print(int* message)
{
    printf("message: ");
 
    for (int i = 0; i < data_num; i++)
        printf("%d ", message[i]);
    printf("\n");
}
 
int main(void)
{
    int mes[MAXNUM];
    int Cks;
 
    sending_message(mes);
    printf("sender: \n");
    print(mes);
 
    Cks = calculaton_Checksum(mes);
    printf("checksum: %d\n\n", Cks);
 
    if (!check_Checksum(mes))
        printf("Checksum error!!");
    else{
        printf("Receiver: \n");
        print(mes);
    }
    return 0;
}


출처: https://neuro.tistory.com/131 [Ayoujin]