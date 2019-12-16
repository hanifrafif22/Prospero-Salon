#define NCURSES_MOUSE_VERSION
#include<stdio.h>
#include<math.h>
#include<windows.h>
#include<stdlib.h>
#include <time.h>
#include <curses.h>

struct baris{
  char nama[50];
  char umur[4];
  char telp[20];
  char alamat[50];
  char gender[3];
  int bagian;
  int bayar;
  struct baris *nextwash;
};
typedef struct baris wash;
typedef wash *washpoint;

washpoint head = NULL;
washpoint tail = NULL;
washpoint head2 = NULL;
washpoint tail2 = NULL;

int main()
{
    disclaimer();
}
int color()
{
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_CYAN);
    init_pair(7, COLOR_WHITE, COLOR_RED);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);
}
int disclaimer()
{
    initscr();
    WINDOW *in;
    in = newwin(1, 1, 0, -1);
    refresh();
    start_color();
    color();

    char* choices[] = {"Accept and Continue", "Exit"};
    // Length of Array, bukan Size of Array
    int n = sizeof(choices) / sizeof(choices[0]);
    int choice;
    int highlight = 0;

    //Mengambil informasi ukuran layar komputer
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    //Watermark
    char mesg[] = {"PROSPERO SALON"};
    mvprintw(1,(xMax-strlen(mesg))/2,"%s", mesg);

    //Window Konten
    WINDOW * content_win = newwin(yMax-8, xMax-10, 3, 5);
    box(content_win, 30, 30);
    bkgd(COLOR_PAIR(7));
    refresh();

    //Disclaimer
    int clock;
    char* disc[] = {"PERMISSION", "This app may request access to","", "1. Microphone                      ","    -record audio                    ",
                    "2. Storage                         ","    -Read the content of your disk  ","    -Modify the content of your disk ",
                    "3. Location                        ","  -Access this device's location ","while you're using this app"};

    int s = sizeof(disc) / sizeof(disc[0]);
    for (clock=0; clock < s; clock++)
    {
        mvwprintw(content_win, (yMax/2)-s+clock,(xMax-strlen(disc[clock])-11)/2,"%s", disc[clock]);
    }
    wrefresh(content_win);

    //Buat window khusus untuk input
    WINDOW * menuwin = newwin(3, xMax/2-5, yMax-4, 5);
    mvwprintw(menuwin, 1, 18, choices[0]);
    refresh();
    wrefresh(menuwin);

    WINDOW * menuwin1 = newwin(3, xMax/2-5, yMax-4, 60);
    mvwprintw(menuwin1, 1, 25, choices[1]);
    refresh();
    wrefresh(menuwin);

    //Fungsi untuk mengambil input arrow key
    keypad(in, true);
    cbreak();
    noecho();
    // Enables keypad mode. This makes (at least for me) mouse events getting
    // reported as KEY_MOUSE, instead as of random letters.
    keypad(stdscr, TRUE);
    // Don't mask any mouse events
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
        while(1)
        {
                if(highlight==0)
                {
                    wbkgd(menuwin1, COLOR_PAIR(2));
                    wbkgd(menuwin, COLOR_PAIR(6));
                }
                else if(highlight==1)
                {
                    wbkgd(menuwin, COLOR_PAIR(2));
                    wbkgd(menuwin1, COLOR_PAIR(6));
                }

            wrefresh(menuwin);
            wrefresh(menuwin1);
            choice = wgetch(in);
            switch(choice)
            {
                case KEY_LEFT:
                    highlight--;
                    if(highlight == -1)
                        highlight = 0;
                    break;
                case KEY_RIGHT:
                    highlight++;
                    if(highlight == n);
                        highlight = n-1;
                    break;
                default:
                    break;
            }
            if(choice==10 || choice==13)
                break;


        char buffer[512];
        size_t max_size = sizeof(buffer);
        if (choice == KEY_MOUSE) {
          MEVENT event;
          if (getmouse(&event) == OK)
          {
            if (event.x>= 5 &&event.x<= 60 &&event.y>=25)
            {
                menu_utama(xMax,yMax);
            }
            else if (event.x>= 63 &&event.x<= 110 &&event.y>=25)
            {
                return 0;
            }
          }
        }
        }
        if(highlight==0)
        {
            menu_utama(xMax,yMax);
        }
        else if(highlight==1)
        {
            exit(0);
        }
}


int menu_antri(xMax, yMax)
{
    erase();
    WINDOW * judul;
    WINDOW * content_win;
    WINDOW * win;
    WINDOW * win1;
    WINDOW * win2;
    WINDOW *in;
    in = newwin(1, 1, 0, -1);
    refresh();

    start_color();
    color();
    bkgd(COLOR_PAIR(6));


    //Window Judul
    judul = newwin(3, xMax/2, 1, xMax/3-10);
    mvwprintw(judul, 1, 25, "Login Menu");
    wbkgd(judul, COLOR_PAIR(5));
    refresh();
    wrefresh(judul);



    char* choices[] = {"ANTRI PELANGGAN", "BATAL ANTRI", "MAIN MENU"};

    //Buat window khusus untuk input
    win = newwin(6, xMax/3-2, 6, xMax/3);
    mvwprintw(win, 3, 12, choices[0]);
    refresh();
    win1 = newwin(6, xMax/3-2, 13, xMax/3);
    mvwprintw(win1, 3, 13, choices[1]);
    refresh();
    win2 = newwin(6, xMax/3-2, 20, xMax/3);
    mvwprintw(win2, 3, 14, choices[2]);
    refresh();

    //Fungsi untuk mengambil input arrow key
    keypad(in, true);

    // Length of Array, bukan Size of Array
    int n = sizeof(choices) / sizeof(choices[0]);
    int choice;
    int highlight=0;

        //Fungsi untuk mengambil input arrow key
    keypad(in, true);
    cbreak();
    noecho();
    // Enables keypad mode. This makes (at least for me) mouse events getting
    // reported as KEY_MOUSE, instead as of random letters.
    keypad(stdscr, TRUE);
    // Don't mask any mouse events
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    while(1)
    {
            if(highlight==0)
            {
                wbkgd(win2, COLOR_PAIR(2));
                wbkgd(win1, COLOR_PAIR(2));
                wbkgd(win, COLOR_PAIR(1));
            }
            else if(highlight==1)
            {
                wbkgd(win, COLOR_PAIR(2));
                wbkgd(win2, COLOR_PAIR(2));
                wbkgd(win1, COLOR_PAIR(1));
            }
            else if(highlight==2)
            {
                wbkgd(win1, COLOR_PAIR(2));
                wbkgd(win, COLOR_PAIR(2));
                wbkgd(win2, COLOR_PAIR(1));
            }

        wrefresh(win);
        wrefresh(win1);
        wrefresh(win2);

        choice = wgetch(in);

        switch(choice)
        {
            case KEY_UP:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == 3)
                    highlight = 2;
                    break;
            default:
                break;
        }
        if(choice==10 || choice==13)
            break;

        char buffer[512];
        size_t max_size = sizeof(buffer);

        if (choice == KEY_MOUSE) {
          MEVENT event;
          if (getmouse(&event) == OK)
          {
            if (event.y>=5&&event.y<=10)
            {
                erase();
                bkgd(COLOR_PAIR(9));
                antri(&head,&tail);
            }
            else if (event.y>= 12&&event.y<=17)
            {
                erase();
                bkgd(COLOR_PAIR(9));
                bat(&head,&tail);
            }
            else if (event.y>= 22&&event.y<=27)
            {
                erase();
                bkgd(COLOR_PAIR(7));
                menu_utama(xMax,yMax);
            }
          }
        }
    }
            if(highlight==0)
        {
            erase();
            bkgd(COLOR_PAIR(9));
            antri(&head,&tail);
        }
        else if(highlight==1)
        {
            erase();
            bkgd(COLOR_PAIR(9));
            bat(&head,&tail);
        }
        else if(highlight==2)
        {
            erase();
            bkgd(COLOR_PAIR(7));
            menu_utama(xMax,yMax);
        }

       char buffer[512];
        size_t max_size = sizeof(buffer);
        if (choice == KEY_MOUSE) {
          MEVENT event;
          if (getmouse(&event) == OK)
          {
            if (event.x>= 5 &&event.x<= 60 &&event.y>=25)
            {
                menu_utama(xMax,yMax);
            }
            else if (event.x>= 63 &&event.x<= 110 &&event.y>=25)
            {
                return 0;
            }
          }
        }

        if(highlight==0)
        {
            erase();
            bkgd(COLOR_PAIR(9));
            antri(&head,&tail);
        }
        else if(highlight==1)
        {
            erase();
            bkgd(COLOR_PAIR(9));
            bat(&head,&tail);
        }
        else if(highlight==2)
        {
            erase();
            bkgd(COLOR_PAIR(7));
            menu_utama(xMax,yMax);
        }

}
int menu_utama(int xMax, int yMax)
{
    WINDOW * menuwin;
    WINDOW * menuwin1;
    WINDOW * menuwin2;
    WINDOW * menuwin3;
    WINDOW * menuwin4;
    WINDOW * win;
    WINDOW *in;
    in = newwin(1, 1, 0, -1);
    refresh();


    bkgd(COLOR_PAIR(7));

    //Watermark
    char mesg[] = {"PROSPERO SALON"};
    mvprintw(1,(xMax-strlen(mesg))/2,"%s", mesg);

    //Buat window khusus untuk Konten
    win = newwin(30, xMax, 4, 10);
    refresh();

    wrefresh(win);

    char* choices[] = {"ANTRIAN PELANGGAN", "PELANGGAN MASUK", "DAFTAR ANTRIAN", "KAS", "EXIT"};
    // Length of Array, bukan Size of Array
    int n = sizeof(choices) / sizeof(choices[0]);
    int choice;
    int highlight=0;

    //Buat window khusus untuk input
    menuwin = newwin(7, 22, yMax-8, 5);
    mvwprintw(menuwin, 3, 3, choices[0]);
    refresh();

    menuwin1 = newwin(7, 22, yMax-8, 27);
    mvwprintw(menuwin1, 3, 4, choices[1]);
    refresh();

    menuwin2 = newwin(7, 22, yMax-8, 49);
    mvwprintw(menuwin2, 3, 3, choices[2]);
    refresh();

    menuwin3 = newwin(7, 22, yMax-8, 71);
    mvwprintw(menuwin3, 3, 9, choices[3]);
    refresh();

    menuwin4 = newwin(7, 22, yMax-8, 93);
    mvwprintw(menuwin4, 3, 9, choices[4]);
    refresh();


    keypad(in, true);
    cbreak();
    noecho();
    // Enables keypad mode. This makes (at least for me) mouse events getting
    // reported as KEY_MOUSE, instead as of random letters.
    keypad(stdscr, TRUE);
    // Don't mask any mouse events
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
while(1)
    {
            if(highlight==0)
            {
                wbkgd(menuwin4, COLOR_PAIR(2));
                wbkgd(menuwin3, COLOR_PAIR(2));
                wbkgd(menuwin2, COLOR_PAIR(2));
                wbkgd(menuwin1, COLOR_PAIR(2));
                wbkgd(menuwin, COLOR_PAIR(1));
            }
            else if(highlight==1)
            {
                wbkgd(menuwin, COLOR_PAIR(2));
                wbkgd(menuwin4, COLOR_PAIR(2));
                wbkgd(menuwin3, COLOR_PAIR(2));
                wbkgd(menuwin2, COLOR_PAIR(2));
                wbkgd(menuwin1, COLOR_PAIR(1));
            }
            else if(highlight==2)
            {
                wbkgd(menuwin1, COLOR_PAIR(2));
                wbkgd(menuwin, COLOR_PAIR(2));
                wbkgd(menuwin4, COLOR_PAIR(2));
                wbkgd(menuwin3, COLOR_PAIR(2));
                wbkgd(menuwin2, COLOR_PAIR(1));
            }
            else if(highlight==3)
            {
                wbkgd(menuwin2, COLOR_PAIR(2));
                wbkgd(menuwin1, COLOR_PAIR(2));
                wbkgd(menuwin, COLOR_PAIR(2));
                wbkgd(menuwin4, COLOR_PAIR(2));
                wbkgd(menuwin3, COLOR_PAIR(1));
            }
            else if(highlight==4)
            {
                wbkgd(menuwin3, COLOR_PAIR(2));
                wbkgd(menuwin2, COLOR_PAIR(2));
                wbkgd(menuwin1, COLOR_PAIR(2));
                wbkgd(menuwin, COLOR_PAIR(2));
                wbkgd(menuwin4, COLOR_PAIR(1));
            }

        wrefresh(menuwin);
        wrefresh(menuwin1);
        wrefresh(menuwin2);
        wrefresh(menuwin3);
        wrefresh(menuwin4);

        choice = wgetch(in);

        switch(choice)
        {
            case KEY_LEFT:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_RIGHT:
                highlight++;
                if(highlight == n)
                    highlight = n-1;
                break;
            default:
                break;
        }
        if(choice==10 || choice==13)
            break;

        char buffer[512];
        size_t max_size = sizeof(buffer);

        if (choice == KEY_MOUSE) {
          MEVENT event;
          if (getmouse(&event) == OK)
          {
            if (event.x>=5&&event.x<=25)
            {
                erase();
                bkgd(COLOR_PAIR(9));
                menu_antri(xMax,yMax);
            }
            else if (event.x>=27&&event.x<=45)
            {
                erase();
                bkgd(COLOR_PAIR(9));
                masuk(&head,&tail,&head2,&tail2);
            }
            else if (event.x>=47&&event.x<=65)
            {
                erase();
                bkgd(COLOR_PAIR(9));
                display(head);
            }
            else if (event.x>=67&&event.x<=85)
            {
                erase();
                bkgd(COLOR_PAIR(9));
                cash(head2);
            }
            else if (event.x>=87)
            {
                return 0;
            }
          }
        }
    }

    if(highlight == 3)
    {
        erase();
        bkgd(COLOR_PAIR(9));
        cash(head2);
    }

    else if(highlight == 2)
      {
        erase();
        bkgd(COLOR_PAIR(9));
        display(head);
      }

    else if(highlight == 1)
    {
        erase();
        bkgd(COLOR_PAIR(9));
        masuk(&head,&tail,&head2,&tail2);
    }


    else if(highlight == 0)
    {
        erase();
        bkgd(COLOR_PAIR(9));
        menu_antri(xMax,yMax);
    }
}

void masuk(washpoint *head, washpoint *tail, washpoint *head2, washpoint *tail2)
{
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

	washpoint tem;

    WINDOW * judul;
    WINDOW * content_win;
    WINDOW * win;
    WINDOW * win1;
    WINDOW * win2;
    WINDOW * emp;
    WINDOW *in;
    in = newwin(1, 1, 0, -1);
    refresh();

    start_color();
    color();
    bkgd(COLOR_PAIR(5));


    //Window Judul
    char* choices[] = {"MANICURE & PEDICURE", "FACIAL", "SMOOTHING"};

    	if(kosong(*head))
	{
        emp = newwin(3, xMax/2, 1, xMax/3-10);
        mvwprintw(emp, 1, 25, "Tidak Ada Pasien Antri");
        wrefresh(emp);
        Sleep(2000);

	}
	else{
    judul = newwin(3, xMax/2, 1, xMax/3-10);
    mvwprintw(judul, 1, 25, "NAME : %s",(*head)->nama);
    wbkgd(judul, COLOR_PAIR(5));
    refresh();
    wrefresh(judul);

    win = newwin(6, xMax/3-2, 6, xMax/3);
    mvwprintw(win, 3, 12, choices[0]);
    refresh();
    win1 = newwin(6, xMax/3-2, 13, xMax/3);
    mvwprintw(win1, 3, 11, choices[1]);
    refresh();
    win2 = newwin(6, xMax/3-2, 20, xMax/3);
    mvwprintw(win2, 3, 16, choices[2]);
    refresh();

    keypad(in, true);

    int n = sizeof(choices) / sizeof(choices[0]);
    int choice;
    int highlight=0;

        keypad(in, true);
    cbreak();
    noecho();
    // Enables keypad mode. This makes (at least for me) mouse events getting
    // reported as KEY_MOUSE, instead as of random letters.
    keypad(stdscr, TRUE);
    // Don't mask any mouse events
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    while(1)
    {
            if(highlight==0)
            {
                wbkgd(win2, COLOR_PAIR(2));
                wbkgd(win1, COLOR_PAIR(2));
                wbkgd(win, COLOR_PAIR(1));
            }
            else if(highlight==1)
            {
                wbkgd(win, COLOR_PAIR(2));
                wbkgd(win2, COLOR_PAIR(2));
                wbkgd(win1, COLOR_PAIR(1));
            }
            else if(highlight==2)
            {
                wbkgd(win1, COLOR_PAIR(2));
                wbkgd(win, COLOR_PAIR(2));
                wbkgd(win2, COLOR_PAIR(1));
            }

        wrefresh(win);
        wrefresh(win1);
        wrefresh(win2);

        choice = wgetch(in);

        switch(choice)
        {
            case KEY_UP:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == 3)
                    highlight = 2;
                    break;
            default:
                break;
        }
        if(choice==10 || choice==13)
            break;

        char buffer[512];
        size_t max_size = sizeof(buffer);

        if (choice == KEY_MOUSE) {
          MEVENT event;
          if (getmouse(&event) == OK)
          {

            if (event.y>=5&&event.y<=10)
            {
                erase();
            bkgd(COLOR_PAIR(9));
            (*head)->bagian==1;
            (*head)->bayar=100000;
            }
            else if (event.y>= 12&&event.y<=17)
            {
                erase();
                bkgd(COLOR_PAIR(9));
                (*head)->bagian==2;
                (*head)->bayar=50000;
            }
            else if (event.y>= 22&&event.y<=27)
            {
                erase();
                bkgd(COLOR_PAIR(9));
                (*head)->bagian==3;
                (*head)->bayar=40000;
            }
          }
        }
    }
            if(highlight==0)
        {
            erase();
            bkgd(COLOR_PAIR(9));
            (*head)->bagian==1;
            (*head)->bayar=100000;
        }
        else if(highlight==1)
        {
            erase();
            bkgd(COLOR_PAIR(9));
            (*head)->bagian==2;
            (*head)->bayar=50000;
        }
        else if(highlight==2)
        {
            erase();
            bkgd(COLOR_PAIR(9));
            (*head)->bagian==3;
            (*head)->bayar=40000;
        }
        washpoint new;
		new = malloc(sizeof(wash));
		if (new != NULL)
		{
			strcpy(new->nama,(*head)->nama);
            strcpy(new->umur,(*head)->umur);
			strcpy(new->telp,(*head)->telp);
			strcpy(new->alamat,(*head)->alamat);
			strcpy(new->gender,(*head)->gender);
			strcpy(new->telp,(*head)->telp);
			strcpy(new->alamat,(*head)->alamat);
			new->bagian = (*head)->bagian;
			new->bayar = (*head)->bayar;
			new->nextwash = NULL;
			if (kosong(*head2))
			{
				*head2 = new;
			}
			else
			{
				(*tail2)->nextwash = new;
			}
			*tail2 = new;
		}
		else
		{
			printw("MEMORI PENUH");
		}

		tem = *head;
		*head = (*head)->nextwash;
		if (*head == NULL)
		{
			*tail = NULL;
		}
		free(tem);
	}
    menu_utama(xMax,yMax);
}
int popup_window (xMax, yMax)
{
       int save;
       //Window Pop-Up pemberitahuan
        WINDOW * ask_win = newwin(5, xMax/2.5, 3, xMax/3.3);
        wbkgd(ask_win, COLOR_PAIR(2));
        refresh();
        mvwprintw(ask_win, 1, xMax/7, "Confirm Booking ?");
        wrefresh(ask_win);

    //Window Pop-Up waiting request

        //Fungsi untuk mengambil input arrow key
    keypad(ask_win, true);

    char *choices[]={"Antri", "Edit Antrian","Cancel"};
    int n = sizeof(choices) / sizeof(choices[0]);
    int choice;
    int highlight = 0;

    while(1)
    {
        for(int i = 0; i < n; i++)
        {
            if(i==highlight)
                wattron(ask_win, A_REVERSE);
                mvwprintw(ask_win, 3, 3+16*i, choices[i]);
                wattroff(ask_win, A_REVERSE);
        }
        choice = wgetch(ask_win);

        switch(choice)
        {
            case KEY_LEFT:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_RIGHT:
                highlight++;
                if(highlight == n)
                    highlight = n-1;
                break;
            default:
                break;
        }
        if(choice==10 || choice==13)
            break;
    }

    if(highlight == 0)
    {
        erase();
        menu_utama(xMax,yMax);
    }

    else if(highlight == 1)
    {
        erase();
        menu_utama(xMax,yMax);
    }
}
void display(washpoint now)
{
	int ang=1;

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW * win;
    WINDOW * content_win;
    WINDOW * ghost_win;
    WINDOW *in;
    in = newwin(1, 1, 0, -1);


    bkgd(COLOR_PAIR(4));
    mvprintw(7, 6, "ANTRIAN");

    //Watermark
    char mesg[] = {"PROSPERO SALON"};
    mvprintw(1,(xMax-strlen(mesg))/2,"%s", mesg);


    //Window Konten
    content_win = newwin(yMax-13, xMax-10, 8, 5);
    wbkgd(content_win, COLOR_PAIR(9));
    refresh();
    wrefresh(content_win);

	if (now == NULL)
	{
		mvprintw(9,6,"Kosong");
        bkgd(COLOR_PAIR(5));
        erase();

	}
	else
	{
	    wrefresh(content_win);
	    wprintw(content_win,"Antrian pasien : \n\n");
		while (now != NULL)
		{
			wprintw(content_win,"\t %i. %s \n",ang,now->nama);
			ang++;
			now = now->nextwash;
		}
		wrefresh(content_win);
	}
	system("pause");
	menu_utama(xMax,yMax);
}
void cash(washpoint now)
{
	int ang=1;
	int tot=0;

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW * win;
    WINDOW * content_win;
    WINDOW * ghost_win;
    WINDOW *in;
    in = newwin(1, 1, 0, -1);


    bkgd(COLOR_PAIR(4));
    mvprintw(7, 6, "KAS");

    char mesg[] = {"PROSPERO SALON"};
    mvprintw(1,(xMax-strlen(mesg))/2,"%s", mesg);

    content_win = newwin(yMax-13, xMax-10, 8, 5);
    wbkgd(content_win, COLOR_PAIR(9));
    refresh();
    wrefresh(content_win);


	if (now == NULL)
	{
		wprintw(content_win,"Belum ada Pelanggan yang di data");
		wrefresh(content_win);
	}
	else
	{

		wprintw(content_win,"Data Pelanggan : \n\n");
		while (now != NULL)
		{
			wprintw(content_win,"\t %i. %s",ang,now->nama);
			wprintw(content_win,"\t gender : %s",now->gender);
			wprintw(content_win,"\t Nomor telepon : %s",now->telp);
			wprintw(content_win,"\t Alamat        : %s",now->alamat);
			wprintw(content_win,"\t Service   : ");
			if(now->bagian==1)
			{
				wprintw(content_win,"1. Manicure dan Pedicure");
			}
			if(now->bagian==2)
			{
				wprintw(content_win,"2. Facial\n");
			}
			if(now->bagian==3)
			{
				wprintw(content_win,"3. Smoothing");
			}
			wprintw(content_win,"\n \t Biaya : %i \n\n",now->bayar);
			ang++;
			tot+=now->bayar;
			now = now->nextwash;
		}
		wprintw(content_win,"Total pendapatan Prospero Salon = %i \n",tot);
		wrefresh(content_win);
	}
	getchar(); getchar();
	erase();
	menu_utama(xMax,yMax);

}

int kosong(washpoint head)
{
	return head == NULL;
}

int antri(washpoint *head, washpoint *tail)
{
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW * passwin;
    WINDOW * accountwin;
    WINDOW * userwin;
    WINDOW * ask_win;
    WINDOW * inputwin;
    WINDOW * content_win;
    WINDOW *in;
    in = newwin(1, 1, 0, -1);
    refresh();

	washpoint new;
	new = malloc(sizeof(wash));

    ask_win = newwin(5, xMax/2.5, 3, xMax/3.3);
    wbkgd(ask_win, COLOR_PAIR(2));
    refresh();
    char *string[]=
    {"NAME : ",
     "AGE : ",
     "GENDER (M/F):",
     "Mobile Number : ",
     "EMAIL : "};

    char mesg[] = {"PROSPERO SALON"};
    mvprintw(1,(xMax-strlen(mesg))/2,"%s", mesg);

    	if (new != NULL)
	{
    content_win = newwin(yMax-13, xMax-10, 8, 5);
    wbkgd(content_win, COLOR_PAIR(4));
    refresh();
    wrefresh(content_win);

    WINDOW *jdl = newwin(1, 14, 5, 5);
    mvwprintw(jdl, 0, 1, "ANTRI");
    wbkgd(jdl, COLOR_PAIR(2));
    refresh();
    wrefresh(jdl);

    inputwin = newwin(3, xMax-10, yMax-5, 5);
    wbkgd(inputwin, COLOR_PAIR(2));
    refresh();

        mvwprintw(inputwin, 1, 1, string[0]);
        wrefresh(inputwin);
        wgetstr(inputwin, new->nama);
        strlwr(new->nama);
        mvwprintw(content_win, 1, 1, "Summary");
        mvwprintw(content_win, 3, 1, "Name: %s", new->nama);
        wrefresh(content_win);

        wclear(inputwin);
        mvwprintw(inputwin, 1, 1, string[1]);
        wrefresh(inputwin);
        wgetstr(inputwin, new->umur);
        strlwr(new->umur);
        mvwprintw(content_win, 4, 1, "AGE: %s", new->umur);
        wrefresh(content_win);

        wclear(inputwin);
        mvwprintw(inputwin, 1, 1, string[2]);
        wrefresh(inputwin);
        wgetstr(inputwin, new->gender);
        strlwr(new->gender);
        mvwprintw(content_win, 5, 1, "GENDER (M/F): %s", new->gender);
        wrefresh(content_win);

        wclear(inputwin);
        mvwprintw(inputwin, 1, 1, string[3]);
        wrefresh(inputwin);
        wgetstr(inputwin, new->telp);
        strlwr(new->telp);
        mvwprintw(content_win, 6, 1, "NOMOR TELEPON : %s", new->telp);
        wrefresh(content_win);

        wclear(inputwin);
        mvwprintw(inputwin, 1, 1, string[4]);
        wrefresh(inputwin);
        wgetstr(inputwin, new->alamat);
        strlwr(new->alamat);
        mvwprintw(content_win, 7, 1, "ALAMAT : %s", new->alamat);
        wrefresh(content_win);
        new->nextwash = NULL;

        if (kosong(*head))
        {
			*head = new;
		}
		else
		{
			(*tail)->nextwash = new;
		}
		*tail = new;
	}
	else
	{
		printw("Tidak dapat memasukkan");
	}
	popup_window(xMax,yMax);
    menu_utama(xMax,yMax);
}
void bat(washpoint *head, washpoint *tail)
{
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW * passwin;
    WINDOW * accountwin;
    WINDOW * userwin;
    WINDOW * ask_win;
    WINDOW * inputwin;
    WINDOW * content_win;
    WINDOW *in;
	washpoint now, bef, bef2;
	now = *head;
    content_win = newwin(yMax-13, xMax-10, 8, 5);
    wbkgd(content_win, COLOR_PAIR(5));
    refresh();
    wrefresh(content_win);

    WINDOW *jdl = newwin(1, 14, 5, 5);
    mvwprintw(jdl, 0, 1, "ANTRI");
    wbkgd(jdl, COLOR_PAIR(1));
    refresh();
    wrefresh(jdl);

    inputwin = newwin(3, xMax-10, yMax-5, 5);
    wbkgd(inputwin, COLOR_PAIR(1));
    refresh();

    	if (kosong(*head))
	{
		wprintw(content_win,"TIDAK ADA PASIEN ANTRI\n\n");
		wrefresh(content_win);
	}
	else
	{
		bef=NULL;;
		while(now != NULL)
		{
			bef2 = bef;
			bef = now;
			now = now->nextwash;
		}
		wprintw(content_win,"MENGHAPUS DATA SEBELUMNYA");
		wrefresh(content_win);
        if (bef2==NULL)
        {
            *head=NULL;
            *tail=NULL;
        }
        else
        {
            *tail = bef2;
            (*tail)->nextwash = NULL;
        }
		free(bef);
	}

    getchar();
    menu_utama(xMax,yMax);
}
