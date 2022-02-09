#include <stdio.h>

void welcome(char *task_name, char *description)
{
    red_print(task_name);
    printf("\nЗадание: ");
    red_print(description);
    printf("\n");
}

int red_print(char* message)
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
        {
            if (message[0] != '\n')
                printf("\n");
            printf(message);
        }
        scanf("%d", &buff);

        if (buff < min)
            printf("\nЗначение должно быть не меньше %d", min);
        if (buff > max)
            printf("\nЗначение должно быть не больше %d", max);
    } while (buff < min || max < buff);

    return buff;
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
        print_array(matrix[i], N);
}

void print_matrix_s(int M, int N, int matrix[M][N])
{
    for (int i = 0; i < M; ++i)
        print_array(matrix[i], N);
}

// * ///////////////

void zeromize_array(int *array, int length)
{
    for (int i = 0; i < length; ++i)
        array[i] = 0;
}

void zeromize_matrix(int** matrix, int M, int N, int min, int max)
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

void randomize_matrix(int** matrix, int M, int N, int min, int max)
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