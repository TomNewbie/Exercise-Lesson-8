#include <stdio.h>


int num_max(int array[], int length){
    int max = -1000000;
    for(int i = 0; i < length; i++){
        if(max < array[i]){
            max = array[i];
        }
    }
    return max;
}

int num_min(int array[], int length){
    int min = 1000000;
    for(int i = 0; i < length; i++){
        if(min > array[i]){
            min = array[i];
        }
    }
    return min;
}

void print2D_array(int *arr, int x, int y){
    printf("\n");
    int (*array)[y] = (int (*)[y])arr;
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            printf("%d    ", array[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}
void axis_0(char *a, int *arr, int x, int y, int newarray[]){
    // This function take array[][] and output the newarray[]
    // axis is the dimension matrix
    // x is the row matrix
    // y is the column matrix
    // If char a = 'm' -> return min, a = 'M' return max
    int (*array)[y] = (int (*)[y])arr;
    for(int i = 0; i < y; i++){
        int sub_array[x];
        for(int j = 0; j < x; j++){
            sub_array[j] = array[j][i]; 
        }
        if(a[0] == 'M'){
            newarray[i] = num_max(sub_array, x);
        }
        else if(a[0] == 'm'){
            newarray[i] = num_min(sub_array, x);
        }
        else{
            printf("Invalid character");
            break;
        }
    }

    int *p = (int *) newarray;    
    printf("\n================\n");
    printf("%s axis 0: ", a);
    print2D_array(p, 1, y);
}

void axis_1(char *a, int *arr, int x, int y, int newarray[]){
    // This function take array[][] and output the newarray[]
    // axis is the dimension matrix
    // x is the row matrix
    // y is the column matrix
    // If char a = 'm' -> return min, a = 'M' return max
    int (*array)[y] = (int (*)[y]) arr;
    for(int i = 0; i < x; i++){
        int sub_array[y];
        for(int j = 0; j < y; j++){
            sub_array[j] = array[i][j]; 
        }
        if(a[0] == 'M'){
            newarray[i] = num_max(sub_array, y);
        }
        else if(a[0] == 'm'){
            newarray[i] = num_min(sub_array, y);
        }
        else{
            printf("Invalid character");
            break;
        }
    }
    
    int *p = (int *) newarray;
    printf("\n================\n");
    printf("%s axis 1: ", a);
    print2D_array(p, x, 1);
}

int sum_all(int *arr, int x, int y){
    int sum = 0;
    for(int i = 0; i < x*y; i++){
        sum = sum + *(arr + i);
    }
    return sum;
}

int sum_axis_0(int *arr, int x, int y, int new_array[]){
    for(int i = 0; i < y; i++){
        int sum = 0;

        for(int j = 0; j < x; j++){
            sum = sum + arr[j*y + i];
        }
        new_array[i] = sum;
    }
    int *p = (int *) new_array;
    
    printf("\n================\n");
    printf("sum axis 0: ");
    print2D_array(p, 1, y);
}

int sum_axis_1(int *arr, int x, int y, int new_array[]){
    for(int i = 0; i < x; i++){
        int sum = 0;

        for(int j = 0; j < y; j++){
            sum = sum + arr[i*y + j];
        }
        new_array[i] = sum;
    }
    int *p = (int *) new_array;
    
    printf("\n================\n");
    printf("sum axis 1: ");
    print2D_array(p, x, 1);
}

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}
void transpose(int *arr, int x, int y, int *new_array){
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            new_array[x*j + i] = arr[y*i + j];
        }
    }    
}

void vstack(int arr1[], int arr2[], int x, int *new_array){
    for(int i = 0; i < x; i++){
        new_array[i] = arr1[i];
        new_array[x + i] = arr2[i];
    }
}

void flatten(int *new_array, int arr[], int x){
    for(int i = 0; i < x; i++){
        arr[i] = new_array[i];
        arr[i + x] = new_array[i + x];
    }
}

void reshape(int *arr, int x, int y, int *new_array){
    for(int i = 0; i < x*y; i++){
        new_array[i] = arr[i];
    }
}

void compare_greater_than(int *arr, int x, int y, int num, char         *new_array){
    for(int i = 0; i < x*y; i++){
        if(arr[i] <= num ){
            new_array[i] = 'F';
        }
        else{
            new_array[i] = 'T';
        }
    }
}

int main(){
    //Min max axis 0 - 1;
    int array[3][2] = {{1, 2}, {3, 4}, {5, 6}};
    int *ptr;
    ptr = (int *) array;        
    int newarray_axis_0[2]; 
    int newarray_axis_1[3];  
 
    print2D_array(ptr, 3, 2);

    axis_0( "min" ,ptr, 3, 2, newarray_axis_0);  
    axis_0( "Max" ,ptr, 3, 2, newarray_axis_0);  

    axis_1( "min" ,ptr, 3, 2, newarray_axis_1);
    axis_1( "Max" ,ptr, 3, 2, newarray_axis_1);

    //Sum function
    int sum = sum_all(ptr, 3, 2);
    printf("\n Sum all : %d\n", sum);
    sum_axis_0(ptr, 3, 2, newarray_axis_0);
    sum_axis_1(ptr, 3, 2, newarray_axis_1);

    //Transpose
    int square_arr[3][4] = {{1, 2, 3, 6}, {4, 5, 6, 9}, {7, 8, 9, 69}};
    int new_array[4][3];
    transpose(&square_arr[0][0], 3, 4, &new_array[0][0]);
    printf("Old matrix: ");
    print2D_array(&square_arr[0][0], 3, 4);
    printf("New matrix: ");    
    print2D_array(&new_array[0][0], 4, 3);

    //Vstack function
    int arr1[] = {6, 9, 69, 100};
    int arr2[] = {9, 6, 96, 169};
    int new_array2[2][4];
    vstack(arr1, arr2, 4, &new_array2[0][0]);
    printf("array 1: ");
    print2D_array(arr1, 1, 4);
    printf("array 2: ");
    print2D_array(arr2, 1, 4);
    printf("New array: ");
    print2D_array(&new_array2[0][0], 2, 4);

    //Flatten the new_array2
    int arr3[8];
    flatten(&new_array2[0][0], arr3, 4);
    printf("Previous array: ");   
    print2D_array(&new_array2[0][0], 2, 4);
    printf("array 3: ");
    print2D_array(arr3, 1, 8);

    //Reshape
    int square_arr2[3][4] = {{1, 2, 3, 6}, {4, 5, 6, 9}, {7, 8, 9, 69}};
    int reshape_arr[4][3];
    reshape(&square_arr2[0][0], 3, 4, &reshape_arr[0][0]);
    printf("array: ");   
    print2D_array(&square_arr2[0][0], 3, 4);
    printf("new array: ");
    print2D_array(&reshape_arr[0][0], 4, 3);

    //Compare 
    int square_arr3[3][4] = {{1, 2, 3, 1}, {-2, 5, 6, 1}, {0, 8, -1, 2}};
    char arr_result[3][4];
    print2D_array(&square_arr3[0][0], 3, 4);
    compare_greater_than(&square_arr3[0][0], 3, 4, 2, &arr_result[0][0]);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            printf("%c   ", arr_result[i][j]);
        }
        printf("\n");
    }
    
    return 0;

}