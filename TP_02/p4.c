#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_LEN 50

#define MAX_NAME_LEN 100
#define MAX_NUM_STUDENTS 10
#define MAX_NUM_LEN 15

typedef struct Student {
	char name[MAX_NAME_LEN];
	int grade;
} Student;

int main(int argc, char *argv[]){
    struct termios term, oldterm;
    int i,fd;
    char ch;
    Student students[MAX_NUM_STUDENTS];
    if (argc != 2) {
        printf("Usage: %s <destination>\n", argv[0]);
        return 1;
    }
    write(STDOUT_FILENO, "\nEnter 10 names and classifications\n", 36);

    tcgetattr(STDIN_FILENO, &oldterm);
    term = oldterm;
    term.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);

    //i=0;
    fd=open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0644);
    if (fd == -1) {
        perror(argv[1]); 
        return 2;  
    }
    /*
    while (i < MAX_LEN && read(STDIN_FILENO, &ch, 1) && ch != '\t') {
    write(fd, &ch, 1);
    write(STDOUT_FILENO,&ch,1);
    }
    */

   Student s;
	for (i=0 ; i<MAX_NUM_STUDENTS ; i++) {
		// Read the name
		printf("\nName: ");
		fgets(s.name , MAX_NAME_LEN , stdin);

		// Read the grade
		printf("Grade: ");
		scanf("%d" , &s.grade);
		getchar();	// Ignore \n from input stream

		// Store the student in the array
		students[i] = s;
	}
    // Write them to a file
	for (i=0 ; i<MAX_NUM_STUDENTS ; i++) {
		write(fd , &students[i] , sizeof(Student));
	}

    tcsetattr(STDIN_FILENO, TCSANOW, &oldterm);
    write(STDOUT_FILENO, "\n\nDone! ", 8);
    write(STDOUT_FILENO, "\n", 1);
    close(fd);

    return 0;
}