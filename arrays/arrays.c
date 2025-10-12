#include <stdio.h>
int arrays(){

int grades[] ={45, 56,78,90,45};
int total = 0;
for (int i =0; i <5 ; i++)
    printf("grade[%d] = %d \n",i,grades[i]);

for (int i =0 ; i<5;i++)
  total = total + grades[i];
  printf("total : %d \n",total);

for (int i = 0 ; i<5 ;i++)
    total = total +grades[i];
   int avg = total/5 ;
    printf("avg : %d\n",avg);

return 0;
}
