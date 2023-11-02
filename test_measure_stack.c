#include <stdio.h>

char *sb, *sp;

void init_sb_sp()
{
    char x;
    sb = &x;
    sp = &x;
}

int f(int x)
{
    if ((char*)&x < sp)
        sp = (char*)&x;

    if (x <= 0)
        return 0;
    else
        return f(x - 1);
}

int main()
{
    init_sb_sp();

    f(100);

    printf("sb - sp = %ld bytes\n", (sb - sp) / 8);

#ifdef HW
    printf("Hello, World!\n");
#endif
}
