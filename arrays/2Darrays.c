#include <stdio.h>
#define Rows 2
#define Coll 3

int matrix(){


int matrix[Rows][Coll]={{1,2,3},{4,5,6}};
//printf("matrix[0][2]= %d",matrix[0][2]);

// dynamic access of the values by inputs in those diferent values

for(int i =0 ;i<Rows ; i++){
    for(int j =0 ;j<Coll ; j++){
        printf("Enter : matrix[%d][%d] = ",i,j);
        scanf("%d",&matrix[i][j]);

    }
}

for (int i=0 ;i<Rows ; i++){
    for(int j=0;j<Coll;j++){
        printf("matrix[%d][%d] =%d",i,j,matrix[i][j]);
        printf("\n");
    }
}

return 0;
}
void matrix1(){
    // static access
 //for(int i =0 ; i< Rows ; i++){
    // for(int j=0;j<Coll ;j++){
      // printf("matrix[%d][%d] = %d \n",i,j,matrix[i][j]);
    // }
}


