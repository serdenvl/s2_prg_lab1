#include <stdio.h>
#include <stdlib.h>

/*
    *place_for_task*
*/

#define task_name "lab #N"
#define welcome_message "\
*description* \
"

int main()
{
    localize();
    welcome(task_name, welcome_message);
    
    getchar();
}