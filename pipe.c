#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
    int READ = 0;
    int WRITE = 1;

    int f;

    int c_wr[2];
    int c_rd[2];
    pipe(c_wr);
    pipe(c_rd);
    f = fork();

    if (f == 0) {
        close(c_wr[READ]);
        close(c_rd[WRITE]);

        int i = 0;
        read(c_rd[READ], &i, sizeof(i));
        printf("Child read from parent: %d\n", i);

        i *= 12;
        write(c_wr[WRITE], &i, sizeof(i));
        printf("Child wrote num %d to parent.\n", i);

        return 0;
    } else {
        close(c_rd[READ]);
        close(c_wr[WRITE]);

        int x = 10;
        int y;

        printf("Parent writing %d to child.\n", x);
        write(c_rd[WRITE], &x, sizeof(x));

        read(c_wr[READ], &y, sizeof(y));
        printf("Parent read %d from child.\n", y);
    }

    return 0;
}
