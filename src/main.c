#include <stdio.h>
#include <stdlib.h>

/*
    *place_for_task*
*/

#define task_name "lab #1"
#define welcome_message "\
Дана матрица MxN. \
Вывести количество похожих строк. \
Строки похожи, если множества их элементов эквивалентны. \
"

int main()
{
    localize();
    welcome(task_name, welcome_message);

    getchar();
}