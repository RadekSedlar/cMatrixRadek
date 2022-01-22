#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int row, col;
int kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

char random_printable(){
    return (rand() % 93) + 33;
}

void printable_override(char *arr, int current_row, int current_col, char to_print){
    if (arr[(col * current_row) + current_col] != ' ')
    {
        attron(COLOR_PAIR(1));
        mvprintw(current_row, current_col, "%c", to_print);
        attron(COLOR_PAIR(2));
    }
}



void extend_by_one(int current_row, int current_col, char *arr){

    if (arr[(col * current_row) + current_col] != ' ')
    {
        if (current_row == row - 1)
            return;
        
        if (arr[(col * (current_row + 1)) + current_col] == ' ')
        {
            arr[(col * (current_row + 1)) + current_col] = random_printable();
        }
    }
}

void erase_highest(int current_row, int current_col, char *arr){

    int count = 0;

    do
    {
        if ( (current_row + count) > (row - 1) ){ // posledni row
            if (arr[(col * (current_row - 1)) + current_col] == ' ')
            {
                arr[(col * current_row) + current_col] = ' ';
            }
            
            return;
        }

        if (arr[(col * (current_row + count)) + current_col] == ' ')
        {
            break;
        }
        count++;

    } while (true);
    
    if (count > 7)
    {
        arr[(col * current_row) + current_col] = ' ';
    }
}


int main()
{
    srand(time(NULL));
    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(0);

    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }

    start_color();

    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(2));

    getmaxyx(stdscr, row, col);
    char char_matrix[row][col];
    for (unsigned x = 0; x < row; x++)
    {
        for (unsigned y = 0; y < col; y++)
        {
            char_matrix[x][y] = ' ';
        }
    }

    while(true)
    {
        if (kbhit()){
            endwin();
            return 0;
        }

        for (int x = row - 1; x >= 0; x--)
        {
            
            
            for (int y = col; y >= 0; y--)
            {
                if (x == 0)
                {
                    if ((rand() % 100) < 2)
                    {
                        char_matrix[x][y] = random_printable();
                    }
                    
                }

                extend_by_one(x, y, char_matrix[0]);
                erase_highest(x, y, char_matrix[0]);
                mvprintw(x, y, "%c", char_matrix[x][y]);
                
                
            }
        }

        int nth_char = col/10;
        int half_row = row/2;
        printable_override(char_matrix[0], half_row, 0, 83);
        printable_override(char_matrix[0], half_row, nth_char, 69);
        printable_override(char_matrix[0], half_row, nth_char*2, 78);
        printable_override(char_matrix[0], half_row, nth_char*3, 68);

        printable_override(char_matrix[0], half_row, nth_char*4, 78);
        printable_override(char_matrix[0], half_row, nth_char*5, 85);
        printable_override(char_matrix[0], half_row, nth_char*6, 68);
        printable_override(char_matrix[0], half_row, nth_char*7, 69);
        printable_override(char_matrix[0], half_row, nth_char*8, 83);

        refresh();
        usleep(100000);
    }
}