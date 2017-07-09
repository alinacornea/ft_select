#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>

#define MAXBUFSIZE (10000U)
#define DEL (127)

int main(void) {
    char buf[MAXBUFSIZE];
    char c;
    size_t top;
    struct termios curterm;

    tcgetattr(STDIN_FILENO, &curterm);
    curterm.c_lflag &= ~(ICANON| ECHO);
    curterm.c_cc[VTIME] = 0;
    curterm.c_cc[VMIN] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW, &curterm);

    top = 0;
    while (read(STDIN_FILENO, &c, sizeof c) == 1) {
        switch (c) {
            case DEL:
                if (top) {
                    --top;
                    const char delbuf[] = "\b \b";
                    write(STDOUT_FILENO, delbuf, strlen(delbuf));
                }
                break;
            case '\n':
                write(STDOUT_FILENO, &c, sizeof c);
                write(STDOUT_FILENO, buf, top);
                top = 0;
                break;
            default:
                buf[top++] = c;
                write(STDOUT_FILENO, &c, sizeof c);
                break;
         }
    }

    return 0;
}


// int main(int arg, char **argv)
// {
// 	struct winsize win;

// 	ioctl(0, TIOCGWINSZ, &win);
// 	printf("Screen width: %d\nScreen height: %d\n", win.ws_col, win.ws_row);
// 	printf("Screen hor pixels: %d\nScreen ver pixels: %d\n", win.ws_xpixel, win.ws_ypixel);
// 	return (0);

// }

