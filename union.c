/* We will try to analyse a data struction in common use name "union".*/
/*--------------------------------------------------------------------*/
#include<stdint.h>
#include<stdio.h>

/*in this case the member of u1 share the 8-bit's memory with each other. 
 *It's pointed out that each member of u1 just use the part of the 8-bit's memory.*/
typedef union{
  uint8_t s:1;
  uint8_t mp:1;
  uint8_t spare:3;
  uint8_t version:3;
}u1;
int main(){
  u1 a;
  a.s=1;
  a.mp=1;
  a.spare=2;
  a.version=4;
  /*GDB x/1xb &a*/
}
/*The content displayed in the GDB will be "0x4" that is 0000 0100 in binary.
 *If we change the location of line 18 and 19,we will get the different result "0x2".
 *It's obvious and logical that the member of u1 defined laterly will held the whole space
 *of "u1".*/

/*In this case the struct block and b whill share the memory witch each other.*/
typedef union{
  struct{
    uint8_t s:1;
    uint8_t mp:1;
    uint8_t spare:2;
    uint8_t version:4;
  }bf;
  uint8_t b;
}u1;
int main(){
  u1 a;
  a.bf.s=1;
  a.bf.mp=1;
  a.bf.spare=2;
  a.bf.version=4;
  /*GDB x/1xb &a*/
}
/*The content displayed in the GDB will be "0x4b" that is 0100 1011 in binary.Beacuse big
 *or little end isn't appropriate in bits,we may get the moudle of memory of union u1.bf:
low--________
     |version|
     |       |
     |       |
     |_______|
     |spare  |
     |_______|
     |mp     |
hig--|s______|*/

/*In else case like that :
union{
  char c,
  int m,
  short n;
};
 *change the value of each member of the union will imflact others,it's logical and understandable.
 *so not described here*/
