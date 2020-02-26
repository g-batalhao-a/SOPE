#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_LEN 50

int main(int argc, char *argv[]){
    struct termios term, oldterm;
    int i,fd;
    char ch;

    write(STDOUT_FILENO, "\nName and classification(TAB to exit): ", 39);

    tcgetattr(STDIN_FILENO, &oldterm);
    term = oldterm;
    term.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);

    i=0;
    fd=open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0644);
    if (fd == -1) {
        perror(argv[1]); 
        return 2;  
    }

    while (i < MAX_LEN && read(STDIN_FILENO, &ch, 1) && ch != '\t') {
    write(fd, &ch, 1);
    write(STDOUT_FILENO,&ch,1);
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldterm);
    write(STDOUT_FILENO, "\n\nDone! ", 8);
    write(STDOUT_FILENO, "\n", 1);

    return 0;
}