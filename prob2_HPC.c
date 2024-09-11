
#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 int i,j,k,of; 

void print_2d(int **ary,int row,int col)
{
    for ( i = 0; i <row; ++i) {
        for ( j = 0; j < col; ++j) {
            printf("%d ",ary[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
int rows,col,rows2,col2; int **array,**array2,res[rows][col2];
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);


    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank==0)
    {
		rows=rows/size;
		rows2=rows2/size;
          of=0;
        printf("Enter dimentions of the first matrix: ");
        fflush(stdout); 
        scanf("%d %d",&rows,&col);

        array = (int**)malloc(rows * sizeof(int*));
        for ( i = 0; i < rows; i++)
        array[i] = (int*)malloc(col * sizeof(int));
        printf("Enter  its elements : \n");
        fflush(stdout);
        for ( i = 0; i < rows; i++)
        {
            for ( j = 0; j < col; j++)
            {
                scanf("%d",&array[i][j]);
            }
            
        }
        printf("\n");
        printf("Enter dimentions of the second matrix: ");
        fflush(stdout); 
        scanf("%d %d",&rows2,&col2);
        array2 = (int**)malloc(rows2 * sizeof(int*));
        for ( i = 0; i < rows2; i++)
        array2[i] = (int*)malloc(col2 * sizeof(int));
		 printf("Enter  its elements : \n");
        fflush(stdout);
        for ( i = 0; i < rows2; i++)
        {
            for ( j = 0; j < col2; j++)
            {
                scanf("%d",&array2[i][j]);
            }
            
        }
        for ( i = 1; i < size; i++)
        {
            MPI_Send( &rows , 1 , MPI_INT, i ,0, MPI_COMM_WORLD);
            MPI_Send( &col , 1 , MPI_INT, i ,0, MPI_COMM_WORLD);
            MPI_Send( &rows2 , 1 , MPI_INT, i ,0, MPI_COMM_WORLD);
            MPI_Send( &col2 , 1 , MPI_INT, i ,0, MPI_COMM_WORLD);
			MPI_Send(&array,rows*col,MPI_INT, i ,0, MPI_COMM_WORLD);
			MPI_Send(&array2,rows2*col2,MPI_INT, i ,0, MPI_COMM_WORLD);

        }
        for ( i = 1; i < size; i++) 
        {
            for ( j = 0; j <rows; j++)
            {
                MPI_Send(array[j], col, MPI_INT, i, 0, MPI_COMM_WORLD); 
            }
        }
        for ( i = 1; i < size; i++) 
        {
            for ( j = 0; j <rows; j++)
            {
                MPI_Send(array2[j], col2, MPI_INT, i, 0, MPI_COMM_WORLD); 
            }
        }
        
    }
    else
    {
  
        MPI_Recv(&rows, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&col, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&rows2, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&col2, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&array, rows*col, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&array2, rows2*col2, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        array = (int**)malloc(rows * sizeof(int*));
        for ( i = 0; i < rows; i++)
        array[i] = (int*)malloc(col * sizeof(int));
        array2 = (int**)malloc(rows2 * sizeof(int*));
        for ( i = 0; i < rows2; i++)
        array2[i] = (int*)malloc(col2 * sizeof(int));
        for ( j = 0; j <rows; j++)
        {
            MPI_Recv(array[j], col, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(array2[j], col, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        for (k=0; k<rows; k++)
      for (i=0; i<col2; i++) {
        res[i][k] = 0.0;
        for (j=0; j<rows; j++)
          res[i][k] +=  array[i][j] * array2[j][k];
      }

    }

    printf("printing the 2d array at process %d:- \n",rank);
    
    print_2d(array,rows,col);
    print_2d(array2,rows2,col2);
   for ( i = 0; i < rows; i++)
   {
	for ( j = 0; j < col2; i++)
	{
		printf("%d",res[i][j]);
	}
	
   }
   

    

    
    MPI_Finalize();
    return 0;
}
