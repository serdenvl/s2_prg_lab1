#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void welcome(char *task_name, char *description)
{
    red_print(task_name);
    printf("\nЗадание: ");
    red_print(description);
    printf("\n");
}

int red_print(char *message)
{
    if (message[0] != '\n')
        printf("\n");
    printf(message);
}

void localize()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

// * ///////////////

int question(char *message)
{
    while (1)
    {
        red_print(message);
        printf(" (Y/N):");

        switch (getchar())
        {
        case 'n':
        case 'N':
            return 0;
        case 'y':
        case 'Y':
            return 1;
        default:
            while (getchar() != '\n')
                ;
            printf("Wrong answer");
        }
    }
}

// * ///////////////

int scan_int(char *message)
{
    return scan_int_limit(message, -__INT_MAX__, __INT_MAX__);
}

int scan_int_limit(char *message, int min, int max)
{
    int buff;
    do
    {
        if (message != "")
            red_print(message);
        scanf("%d", &buff);

        if (buff < min)
            printf("\nЗначение должно быть не меньше %d", min);
        if (buff > max)
            printf("\nЗначение должно быть не больше %d", max);
    } while (buff < min || max < buff);

    return buff;
}

int scan_variant(char *message, char *variants[], int length)
{
    int buff;
    while (1)
    {
        if (message != "")
            red_print(message);
        for (int i = 0; i < length; ++i)
            printf("\n%d - %s", i, variants[i]);

        printf("\n");
        buff = scan_int("");
        if (0 <= buff && buff < length)
            return buff;

        printf("Неверный ответ\n");
        while (getchar() != '\n')
            ;
    }
}

void scan_array(int *array, int length)
{
    for (int i = 0; i < length; ++i)
        array[i] = scan_int("");
}

void scan_matrix(int **matrix, int M, int N)
{
    for (int i = 0; i < M; ++i)
        scan_array(matrix[i], N);
}

void scan_matrix_s(int M, int N, int matrix[M][N])
{
    for (int i = 0; i < M; ++i)
        scan_array(matrix[i], N);
}

// * ///////////////

int *new_array(int length)
{
    return (int *)calloc(length, sizeof(int));
}

int *resize_array(int *array, int new_length)
{
    return (int *)realloc(array, new_length);
}

int **new_matrix(int M, int N)
{
    int **matrix = (int **)malloc(M * sizeof(int *));
    for (int i = 0; i < M; ++i)
        matrix[i] = new_array(N);
    return matrix;
}

void free_matrix(int **matrix, int M)
{
    for (int i = 0; i < M; ++i)
        free(matrix[i]);
    free(matrix);
}

// * ///////////////

void print_array(int *array, int length)
{
    printf("| ");
    for (int i = 0; i < length; ++i)
        printf("%d ", array[i]);
    printf("|");
}

void print_matrix(int **matrix, int M, int N)
{
    for (int i = 0; i < M; ++i)
    {
        printf("\n");
        print_array(matrix[i], N);
    }
}

void print_matrix_s(int M, int N, int matrix[M][N])
{
    for (int i = 0; i < M; ++i)
    {
        printf("\n");
        print_array(matrix[i], N);
    }
}

// * ///////////////

void zeromize_array(int *array, int length)
{
    for (int i = 0; i < length; ++i)
        array[i] = 0;
}

void zeromize_matrix(int **matrix, int M, int N, int min, int max)
{
    for (int i = 0; i < M; ++i)
        zeromize_array(matrix[i], N);
}

void zeromize_matrix_s(int M, int N, int matrix[M][N], int min, int max)
{
    for (int i = 0; i < M; ++i)
        zeromize_array(matrix[i], N);
}

void randomize_array(int *array, int length, int min, int max)
{
    for (int i = 0; i < length; ++i)
        array[i] = random(min, max);
}

void randomize_matrix(int **matrix, int M, int N, int min, int max)
{
    for (int i = 0; i < M; ++i)
        randomize_array(matrix[i], N, min, max);
}

void randomize_matrix_s(int M, int N, int matrix[M][N], int min, int max)
{
    for (int i = 0; i < M; ++i)
        randomize_array(matrix[i], N, min, max);
}

// * ///////////////

#define default_min 10
#define default_max 99

void input_array(int *array, int length)
{
    const v = scan_variant("Вариант заполнения: ",
                           (char *[]){
                               "заполнение случайными числами [10,99]",
                               "заполнение случайными числами в заданном интервале",
                               "ручной ввод"},
                           3);

    switch (v)
    {
    case 0:
        randomize_array(array, length, default_min, default_max);
        break;
    case 1:
        int min = scan_int("Минимум: ");
        int max = scan_int_limit("Максимум", min, __INT_MAX__);
        randomize_array(array, length, min, max);
        break;
    case 2:
        scan_array(array, length);
        break;
    }
}

void input_matrix(int **matrix, int M, int N)
{
    int v = scan_variant("Вариант заполнения: ",
                         (char *[]){
                             "заполнение случайными числами [10,99]",
                             "заполнение случайными числами в заданном интервале",
                             "ручной ввод"},
                         3);

    switch (v)
    {
    case 0:
        randomize_matrix(matrix, M, N, default_min, default_max);
        break;
    case 1:
        int min = scan_int("Минимум: ");
        int max = scan_int_limit("Максимум: ", min, __INT_MAX__);
        randomize_matrix(matrix, M, N, min, max);
        break;
    case 2:
        scan_matrix(matrix, M, N);
        break;
    }
}

void input_matrix_s(int M, int N, int matrix[M][N])
{
    const v = scan_variant("Вариант заполнения: ",
                           (char *[]){
                               "заполнение случайными числами [10,99]",
                               "заполнение случайными числами в заданном интервале",
                               "ручной ввод"},
                           3);

    switch (v)
    {
    case 0:
        randomize_matrix_s(M, N, matrix, default_min, default_max);
        break;
    case 1:
        int min = scan_int("Минимум: ");
        int max = scan_int_limit("Максимум", min, __INT_MAX__);
        randomize_matrix_s(M, N, matrix, min, max);
        break;
    case 2:
        scan_matrix_s(M, N, matrix);
        break;
    }
}

// * ///////////////

int random(int min, int max)
{
    return (rand() % (max + 1 - min)) + min;
}

void swap(int *a, int *b)
{
    int a2 = *a;
    *a = *b;
    *b = a2;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}