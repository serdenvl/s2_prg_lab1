#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// преобразует в отсортированный массив без повторений
int* to_setlike(int* array, int length)
{
    int* s_array = new_array(length+1);
    s_array[0] = 1; // отводится под длину массива
    s_array[1] = array[0];

    for(int i = 1; i < length; ++i)
    {
        for(int j = 1; j <= s_array[0]; ++j)
        {
            // элемент i уже находится в массиве
            if(array[i] == s_array[j])
                break;

            // j - место элемента i в отсортированном массиве 
            if(array[i] < s_array[j])
            {
                // освобождение места под элемент
                s_array[0] += 1;
                for(int k = s_array[0]; k != j; --k)
                    swap(&s_array[k-1], &s_array[k]);
                
                s_array[j] = array[i];
                break;
            }

            // если иное условие не отработало
            // добавление элемента i в конец
            if(j == s_array[0])
            {
                s_array[0] += 1;
                s_array[s_array[0]] = array[i];
                break;
            }
        }
    }

    return resize_array(s_array, s_array[0]+1);
}

// проверка на схожесть
int setlike_equal(int* arrA, int* arrB)
{
    for(int i = 0; i <= arrA[0]; ++i)
        if(arrA[i] != arrB[i])
            return 0;
    return 1;
}

// подсчет количества схожих строк
int num_similar_string(int** matrix, int M, int N)
{
    int* first = to_setlike(matrix[0], N);
    int count = 0;

    int* buff;
    for(int i = 1; i < M; ++i)
    {
        buff = to_setlike(matrix[i], N);
        count += setlike_equal(first, buff);
        free(buff);
    }

    free(first);
    return count;
}


/*
    *place_for_task*
*/

#define task_name "lab #1"
#define welcome_message "\
Дана матрица MxN. \n\
Вывести количество строк, схожих с первой. \n\
Строки похожи, если множества их элементов эквивалентны. \n\
"

int main()
{
    localize();
    welcome(task_name, welcome_message);

    int M = scan_int("M: ");
    int N = scan_int("N: ");
    int** matrix = input_matrix(M, N);

    printf("Матрица: ");
    print_matrix(matrix, M, N);

    printf("\nКоличество строк, схожих с первой: %d", num_similar_string(matrix, M, N));

    free_matrix(matrix, M);
    getchar();
}