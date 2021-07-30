#include<stdio.h>
#include<stdlib.h>

int main(){
    int numL, numC, numColor;
    scanf("%d %d %d", &numL, &numC, &numColor);
    int matrix[numL][numC];
    for(int i=0; i<numL; i++)
        for(int j=0; j<numC; j++)
            scanf("%d", &matrix[i][j]);

    for(int i=0; i<numL; i++){
        for(int j=0; j<numC; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }



    return 0;
}