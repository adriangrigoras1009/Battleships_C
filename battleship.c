#include<ncurses.h>

#include<stdlib.h>

#include<time.h>

#include<unistd.h>

void creare_meniu(WINDOW * cursor, int * optiune) {
  char * MENIU[] = {
    "New Game",
    "Resume Game",
    "Exit"
  };
  int i, luminat = 0, c;
  cursor = newwin(5, 20, 9, 25); //fereastra pentru posibilitatile din meniu
  keypad(cursor, TRUE); //posibilitatea functionarii tastaturii
  box(cursor, 0, 0);
  for (i = 0; i < 3; i++) {
    if (luminat == i) {
      start_color();
      init_pair(1, COLOR_RED, COLOR_BLACK);
      wattron(cursor, COLOR_PAIR(1)); //sa coloreze prima optiune
      mvwprintw(cursor, 1 + i, 2, "%s", MENIU[i]);
      wattroff(cursor, COLOR_PAIR(1));
    } else
      mvwprintw(cursor, 1 + i, 2, "%s", MENIU[i]); //restu neluminate
  }
  * optiune = 0;
  while ((c = wgetch(cursor)) != 10) //cat timp nu dau enter
  {
    if (c == KEY_UP) {
      if (luminat == 0)
        luminat = 2; //prima optiune devine ultima daca dau in sus
      else
        luminat--;
    }
    if (c == KEY_DOWN) {
      if (luminat == 2)
        luminat = 0; //ultima devine prima daca dau in sus
      else
        luminat++;
    }
    for (i = 0; i < 3; i++) {
      if (luminat == i) {
        start_color();
        wattron(cursor, COLOR_PAIR(1)); //stabilesc culoarea
        mvwprintw(cursor, 1 + i, 2, "%s", MENIU[i]); //colorez optiunea pe care o vreau
        wattroff(cursor, COLOR_PAIR(1));
        ( * optiune) = i; //optiunea colorata devine optiunea pentru cand apasa enter
      } else
        mvwprintw(cursor, 1 + i, 2, "%s", MENIU[i]); //restul apar neluminate
      wrefresh(cursor);
    }
  }
}
void generat_nava_4(int matrice[10][10], int * contor_4, int * linie, int * coloana, int * pozitie) {
  int i, contor = 0;
  * linie = rand() % 7; //mai mic decat 7 pentru ca are 4 pozitii de umplut
  * coloana = rand() % 7;
  * pozitie = rand() % 2; //daca este verticala sau orizontala
  if (( * pozitie) == 1) //verticala
  {
    for (i = ( * linie) - 1; i <= ( * linie) + 4; i++) //verific sa nu fie deja 1 in jurul ei
    {
      if (matrice[i][( * coloana) - 1] == 1 || matrice[i][( * coloana) + 1] == 1 || matrice[i][( * coloana)] == 1)
        contor++;
    }
    if (contor == 0) //daca nu a fost 
    {
      for (i = ( * linie); i < ( * linie) + 4; i++)
        matrice[i][( * coloana)] = 1; //pun o barca in locul ala
      ( * contor_4) ++;
    }
  }
  if (( * pozitie) == 0)  { //daca este orizontala fac asemenea
    for (i = ( * coloana) - 1; i <= ( * coloana) + 4; i++) {
      if (matrice[( * linie) - 1][i] == 1 || matrice[( * linie) + 1][i] == 1 || matrice[( * linie)][i] == 1)
        contor++;
    }
    if (contor == 0) {
      for (i = ( * coloana); i < ( * coloana) + 4; i++)
        matrice[( * linie)][i] = 1;
      ( * contor_4) ++;
    }
  }
}
void generat_1nava_4(int matrice[10][10]) {
  int contor_4 = 0, linie, coloana, pozitie;
  while (contor_4 < 1) { //sa generez o singura nava
    generat_nava_4(matrice, & contor_4, & linie, & coloana, & pozitie);
  }
}
void generat_nava_3(int matrice[10][10], int * contor_3, int * linie, int * coloana, int * pozitie) {
  int i, contor;
  contor = 0;
  * linie = rand() % 8; //sa fie mai mic decat 8 deoarece e pe 3 pozitii
  * coloana = rand() % 8;
  * pozitie = rand() % 2;
  if (( * pozitie) == 1) {
    for (i = ( * linie) - 1; i <= ( * linie) + 3; i++) { //acelasi lucru ca la 4 casute
      if (matrice[i][( * coloana) - 1] == 1 || matrice[i][( * coloana) + 1] == 1 || matrice[i][( * coloana)] == 1)
        contor++;
    }
    if (contor == 0) {
      for (i = ( * linie); i < ( * linie) + 3; i++)
        matrice[i][( * coloana)] = 1;
      ( * contor_3) ++;
    }
  }
  if (( * pozitie) == 0) {
    for (i = ( * coloana) - 1; i <= ( * coloana) + 3; i++)
      if (matrice[( * linie) - 1][i] == 1 || matrice[( * linie) + 1][i] == 1 || matrice[( * linie)][i] == 1)
        contor++;
    if (contor == 0) {
      for (i = ( * coloana); i < ( * coloana) + 3; i++)
        matrice[( * linie)][i] = 1;
      ( * contor_3) ++;
    }
  }
}
void generat_2nava_3(int matrice[10][10]) {
  int contor_3 = 0, linie, coloana, pozitie;
  while (contor_3 < 2) { //sa generez doar 2 barci de 3 casute
    generat_nava_3(matrice, & contor_3, & linie, & coloana, & pozitie);
  }
}
void generat_nava_2(int matrice[10][10], int * contor_2, int * linie, int * coloana, int * pozitie) {
  int i, contor;
  contor = 0;
  * linie = rand() % 9; //sa fie mai mic decat 9 deoarece e pe 2 pozitii
  * coloana = rand() % 9;
  * pozitie = rand() % 2;
  if (( * pozitie) == 1) {
    for (i = ( * linie) - 1; i <= ( * linie) + 2; i++) { //repet operatia pentru fiecare tip de barca
      if (matrice[i][( * coloana) - 1] == 1 || matrice[i][( * coloana) + 1] == 1 || matrice[i][( * coloana)] == 1)
        contor++;
    }
    if (contor == 0) {
      for (i = ( * linie); i < ( * linie) + 2; i++)
        matrice[i][( * coloana)] = 1;
      ( * contor_2) ++;
    }
  }
  if (( * pozitie) == 0) {
    for (i = ( * coloana) - 1; i <= ( * coloana) + 2; i++)
      if (matrice[( * linie) - 1][i] == 1 || matrice[( * linie) + 1][i] == 1 || matrice[( * linie)][i] == 1)
        contor++;
    if (contor == 0) {
      for (i = ( * coloana); i < ( * coloana) + 2; i++)
        matrice[( * linie)][i] = 1;
      ( * contor_2) ++;
    }
  }
}
void generat_3nava_2(int matrice[10][10]) {
  int contor_2 = 0, linie, coloana, pozitie;
  while (contor_2 < 3) { //construiesc doar 3 barci de 2
    generat_nava_2(matrice, & contor_2, & linie, & coloana, & pozitie);
  }
}
void generat_nava_1(int matrice[10][10], int * contor_1, int * linie, int * coloana, int * pozitie) {
  int i, contor;
  contor = 0;
  * linie = rand() % 10;
  * coloana = rand() % 10;
  * pozitie = rand() % 2;
  if (( * pozitie) == 1) {
    for (i = ( * linie) - 1; i <= ( * linie) + 1; i++) {
      if (matrice[i][( * coloana) - 1] == 1 || matrice[i][( * coloana) + 1] == 1 || matrice[i][( * coloana)] == 1)
        contor++;
    }
    if (contor == 0) {
      for (i = ( * linie); i < ( * linie) + 1; i++)
        matrice[i][( * coloana)] = 1;
      ( * contor_1) ++;
    }
  }
  if (( * pozitie) == 0) {
    for (i = ( * coloana) - 1; i <= ( * coloana) + 1; i++)
      if (matrice[( * linie) - 1][i] == 1 || matrice[( * linie) + 1][i] == 1 || matrice[( * linie)][i] == 1)
        contor++;
    if (contor == 0) {
      for (i = ( * coloana); i < ( * coloana) + 1; i++)
        matrice[( * linie)][i] = 1;
      ( * contor_1) ++;
    }
  }
}
void generat_4nava_1(int matrice[10][10]) {
  int contor_1 = 0, linie, coloana, pozitie;
  while (contor_1 < 4) { //construiesc 4 barci de o casuta
    generat_nava_1(matrice, & contor_1, & linie, & coloana, & pozitie);
  }
}
void afisare_matrice_bot(int * luminat_linie, int * luminat_coloana, WINDOW * joc, WINDOW * patratica1, WINDOW * patratica) {
  int i, j;
  ( * luminat_linie) = 0;
  ( * luminat_coloana) = 0;
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      if (( * luminat_linie) == i && ( * luminat_coloana) == j) { //daca aleg o optiune
        start_color();
        init_pair(1, COLOR_BLUE, COLOR_RED); // sa o lumineze
        WINDOW * patratica1 = newwin(3, 3, 3 * i, 3 * j); // sa construiasca o fereastra mica
        box(patratica1, 0, 0);
        mvwprintw(patratica1, 1, 1, "b"); //afiseaza b in mijlocul ei
        wbkgd(patratica1, COLOR_PAIR(1));
        wrefresh(joc);
        wrefresh(patratica1);
      } else {
        WINDOW * patratica = newwin(3, 3, 3 * i, 3 * j); //altfel construieste fereastra incolora
        box(patratica, 0, 0);
        mvwprintw(patratica, 1, 1, "b"); //afiseaza b in mijlocul ei
        wrefresh(joc);
        wrefresh(patratica);
      }
    }
  }
}
void afisare_matrice_random(WINDOW * joc, WINDOW * patratica1, WINDOW * patratica, int matrice[10][10], int optiune_incercata_bot[10][10]) {
  int i, j;
  for (i = 0; i < 10; i++)
    for (j = 0; j < 10; j++) {
      if (matrice[i][j] == 1 && optiune_incercata_bot[i][j] == 1) { //daca am nimerit deja casuta cu 1,
        WINDOW * patratica1 = newwin(3, 3, 3 * i, 3 * j + 50); //construiesc ferestrele
        box(patratica1, 0, 0);
        mvwprintw(patratica1, 1, 1, "1"); //pun 1 pentru ca a fost deja mierita
        wrefresh(joc);
        wrefresh(patratica1);
      } else {
        WINDOW * patratica = newwin(3, 3, 3 * i, 3 * j + 50); //restul doar le afisez
        box(patratica, 0, 0);
        mvwprintw(patratica, 1, 1, "b"); // afisez b in mijlocul lor
        wrefresh(joc);
        wrefresh(patratica);
      }
    }
}
void afisare_matrice_resume_jucator(WINDOW * joc, WINDOW * patratica1, WINDOW * patratica, int matrice[10][10], int optiune_incercata_bot[10][10]) {
  int i, j;
  for (i = 0; i < 10; i++)
    for (j = 0; j < 10; j++) {
      if (optiune_incercata_bot[i][j] == 1) { //daca a fost nimerita
        WINDOW * patratica1 = newwin(3, 3, 3 * i, 3 * j + 50);
        box(patratica1, 0, 0);
        if (matrice[i][j] == 1) //daca am nimerit casuta si era 1
          mvwprintw(patratica1, 1, 1, "1"); // sa afiseze 1
        if (matrice[i][j] == 0) //daca nu
          mvwprintw(patratica1, 1, 1, "0"); // sa o lase neghicita
        wrefresh(joc);
        wrefresh(patratica1);
      }
      if (optiune_incercata_bot[i][j] == 0) { //daca nu a fost nimerita acea casuta
        WINDOW * patratica = newwin(3, 3, 3 * i, 3 * j + 50);
        box(patratica, 0, 0);
        mvwprintw(patratica, 1, 1, "b"); //sa afiseze b in mijlocul ei
        wrefresh(joc);
        wrefresh(patratica);
      }
    }
}
void afisare_matrice_resume_bot(WINDOW * joc, WINDOW * patratica1, WINDOW * patratica, int matrice[10][10], int optiune_incercata_bot[10][10]) {
  int i, j;
  for (i = 0; i < 10; i++)
    for (j = 0; j < 10; j++) {
      if (optiune_incercata_bot[i][j] == 1) { //daca a fost incercata
        WINDOW * patratica1 = newwin(3, 3, 3 * i, 3 * j);
        start_color();
        box(patratica1, 0, 0);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        if (matrice[i][j] == 1) { //daca am nimerit si era 1
          wattron(patratica1, COLOR_PAIR(2)); //sa o coloreze
          mvwprintw(patratica1, 1, 1, "1"); //sa puna 1
          wattroff(patratica1, COLOR_PAIR(2));
        } if (matrice[i][j] == 0)
          mvwprintw(patratica1, 1, 1, "0"); //sa puna 0 daca era 0
        wrefresh(joc);
        wrefresh(patratica1);
      }
      if (optiune_incercata_bot[i][j] == 0) { //daca nu a fost incercata
        WINDOW * patratica = newwin(3, 3, 3 * i, 3 * j);
        box(patratica, 0, 0);
        mvwprintw(patratica, 1, 1, "b");
        wrefresh(joc);
        wrefresh(patratica);
      }
    }
}
void afisare_matrice_jucator(WINDOW * joc, WINDOW * patratica) {
  int i, j;
  for (i = 0; i < 10; i++) 
  {
    for (j = 0; j < 10; j++) {
      WINDOW * patratica = newwin(3, 3, 3 * i, 3 * j + 50); //sa imi construiasca harta
      box(patratica, 0, 0);
      mvwprintw(patratica, 1, 1, "b");
      wrefresh(joc);
      wrefresh(patratica);
    }
  }
}
void mers_in_sus(int optiune_incercata[10][10], int * luminat_linie, int * luminat_coloana, int matrice[10][10], WINDOW * patratica, WINDOW * joc) {
  if (( * luminat_linie) == 0) { //daca e pe prima linie casuta pe care sunt
    ( * luminat_linie) = 9; // sa se duca pe ultima
    WINDOW * patratica = newwin(3, 3, 3 * 0, 3 * ( * luminat_coloana));
    box(patratica, 0, 0);
    if (optiune_incercata[0][( * luminat_coloana)] == 1) { //daca a fost ghicita
      if (matrice[0][( * luminat_coloana)] == 1) {
        wattron(patratica, COLOR_PAIR(2)); //sa fie colorata cand merg prin ea
        mvwprintw(patratica, 1, 1, "1"); //sa apara 1
        wattroff(patratica, COLOR_PAIR(2));
      } else //daca nu
        mvwprintw(patratica, 1, 1, "%d", matrice[0][( * luminat_coloana)]); //sa apara 0
    } else
      mvwprintw(patratica, 1, 1, "b"); //daca nu a fost ghicita sa apara b
    wrefresh(joc);
    wrefresh(patratica);
  } else { //daca nu e pe prima linie casuta care e selectata
    ( * luminat_linie) --; //sa se duca pe linia de sus
    WINDOW * patratica = newwin(3, 3, 3 * (( * luminat_linie) + 1), 3 * ( * luminat_coloana));
    box(patratica, 0, 0);
    if (optiune_incercata[( * luminat_linie) + 1][( * luminat_coloana)] == 1) { //daca a fost incercata
      if (matrice[( * luminat_linie) + 1][( * luminat_coloana)] == 1) { //daca e parte dintr-o nava
        wattron(patratica, COLOR_PAIR(2));
        mvwprintw(patratica, 1, 1, "1"); //sa afiseze 1 daca a fost nimerita
        wattroff(patratica, COLOR_PAIR(2));
      } else
        mvwprintw(patratica, 1, 1, "%d", matrice[( * luminat_linie) + 1][( * luminat_coloana)]);
    } else
      mvwprintw(patratica, 1, 1, "b");
    wrefresh(joc);
    wrefresh(patratica);
  }
} //analog pentru toate functiile mers
void mers_in_jos(int optiune_incercata[10][10], int * luminat_linie, int * luminat_coloana, int matrice[10][10], WINDOW * patratica, WINDOW * joc) {
  if (( * luminat_linie) == 9) {
    ( * luminat_linie) = 0;
    WINDOW * patratica = newwin(3, 3, 3 * 9, 3 * ( * luminat_coloana));
    box(patratica, 0, 0);
    if (optiune_incercata[9][( * luminat_coloana)] == 1) {
      if (matrice[9][( * luminat_coloana)] == 1) {
        wattron(patratica, COLOR_PAIR(2));
        mvwprintw(patratica, 1, 1, "1");
        wattroff(patratica, COLOR_PAIR(2));
      } else
        mvwprintw(patratica, 1, 1, "%d", matrice[9][( * luminat_coloana)]);
    } else
      mvwprintw(patratica, 1, 1, "b");
    wrefresh(joc);
    wrefresh(patratica);
  } else {
    ( * luminat_linie) ++;
    WINDOW * patratica = newwin(3, 3, 3 * (( * luminat_linie) - 1), 3 * ( * luminat_coloana));
    box(patratica, 0, 0);
    if (optiune_incercata[( * luminat_linie) - 1][( * luminat_coloana)] == 1)
      if (matrice[( * luminat_linie) - 1][( * luminat_coloana)] == 1) {
        wattron(patratica, COLOR_PAIR(2));
        mvwprintw(patratica, 1, 1, "1");
        wattroff(patratica, COLOR_PAIR(2));
      }
    else
      mvwprintw(patratica, 1, 1, "%d", matrice[( * luminat_linie) - 1][( * luminat_coloana)]);
    else
      mvwprintw(patratica, 1, 1, "b");
    wrefresh(joc);
    wrefresh(patratica);
  }
}
void mers_in_stanga(int optiune_incercata[10][10], int * luminat_linie, int * luminat_coloana, int matrice[10][10], WINDOW * patratica, WINDOW * joc) {
  if (( * luminat_coloana) == 0) {
    ( * luminat_coloana) = 9;
    WINDOW * patratica = newwin(3, 3, 3 * ( * luminat_linie), 3 * 0);
    box(patratica, 0, 0);
    if (optiune_incercata[( * luminat_linie)][0] == 1) {
      if (matrice[( * luminat_linie)][0] == 1) {
        wattron(patratica, COLOR_PAIR(2));
        mvwprintw(patratica, 1, 1, "1");
        wattroff(patratica, COLOR_PAIR(2));
      } else
        mvwprintw(patratica, 1, 1, "%d", matrice[( * luminat_linie)][0]);
    } else
      mvwprintw(patratica, 1, 1, "b");
    wrefresh(joc);
    wrefresh(patratica);
  } else {
    ( * luminat_coloana) --;
    WINDOW * patratica = newwin(3, 3, 3 * ( * luminat_linie), 3 * (( * luminat_coloana) + 1));
    box(patratica, 0, 0);
    if (optiune_incercata[( * luminat_linie)][( * luminat_coloana) + 1] == 1) {
      if (matrice[( * luminat_linie)][( * luminat_coloana) + 1] == 1) {
        wattron(patratica, COLOR_PAIR(2));
        mvwprintw(patratica, 1, 1, "1");
        wattroff(patratica, COLOR_PAIR(2));
      } else
        mvwprintw(patratica, 1, 1, "%d", matrice[( * luminat_linie)][( * luminat_coloana) + 1]);
    } else
      mvwprintw(patratica, 1, 1, "b");
    wrefresh(joc);
    wrefresh(patratica);
  }
}
void mers_in_dreapta(int optiune_incercata[10][10], int * luminat_linie, int * luminat_coloana, int matrice[10][10], WINDOW * patratica, WINDOW * joc) {
  if (( * luminat_coloana) == 9) {
    ( * luminat_coloana) = 0;
    WINDOW * patratica = newwin(3, 3, 3 * ( * luminat_linie), 3 * 9);
    box(patratica, 0, 0);
    if (optiune_incercata[( * luminat_linie)][9] == 1) {
      if (matrice[( * luminat_linie)][9] == 1) {
        wattron(patratica, COLOR_PAIR(2));
        mvwprintw(patratica, 1, 1, "1");
        wattroff(patratica, COLOR_PAIR(2));
      } else
        mvwprintw(patratica, 1, 1, "%d", matrice[( * luminat_linie)][9]);
    } else
      mvwprintw(patratica, 1, 1, "b");
    wrefresh(joc);
    wrefresh(patratica);
  } else {
    ( * luminat_coloana) ++;
    WINDOW * patratica = newwin(3, 3, 3 * ( * luminat_linie), 3 * (( * luminat_coloana) - 1));
    box(patratica, 0, 0);
    if (optiune_incercata[( * luminat_linie)][( * luminat_coloana) - 1] == 1) {
      if (matrice[( * luminat_linie)][( * luminat_coloana) - 1] == 1) {
        wattron(patratica, COLOR_PAIR(2));
        mvwprintw(patratica, 1, 1, "1");
        wattroff(patratica, COLOR_PAIR(2));
      } else
        mvwprintw(patratica, 1, 1, "%d", matrice[( * luminat_linie)][( * luminat_coloana) - 1]);
    } else
      mvwprintw(patratica, 1, 1, "b");
    wrefresh(joc);
    wrefresh(patratica);
  }
}
void coloreaza_patratica(int * luminat_linie, int * luminat_coloana, int optiune_incercata[10][10], WINDOW * patratica_col, WINDOW * joc, int matrice[10][10]) {
  int i, j;
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      if (( * luminat_linie) == i && ( * luminat_coloana) == j) { //pentru casuta selectata
        start_color();
        init_pair(1, COLOR_BLUE, COLOR_RED); //selectez rosu
        WINDOW * patratica_col = newwin(3, 3, 3 * ( * luminat_linie), 3 * ( * luminat_coloana));
        box(patratica_col, 0, 0);
        if (optiune_incercata[( * luminat_linie)][( * luminat_coloana)] == 1) //daca e 1 sau 0 si a fost nimerita
          mvwprintw(patratica_col, 1, 1, "%d", matrice[( * luminat_linie)][( * luminat_coloana)]); //sa ramana 1 sau 0
        else //daca nu
          mvwprintw(patratica_col, 1, 1, "b"); //afiseaza b
        wbkgd(patratica_col, COLOR_PAIR(1)); //o coloreaza pe cea selectata
        wrefresh(joc);
        wrefresh(patratica_col);
        break;
      }
    }
  }
}
void nimerit_matrice(int matrice[10][10], int matricea_mea[10][10], int * luminat_linie, int * luminat_coloana, WINDOW * patratica, int * incercare_mea, WINDOW * patratica_col, WINDOW * joc, int optiune_incercata_bot[10][10], int optiune_incercata[10][10], int * incercare_bot) {
  int linie, coloana;
  if (matrice[ * luminat_linie][ * luminat_coloana] == 1) { //daca nimeresc pe harta botului o casuta si e 1
    delwin(patratica_col);
    start_color();
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    patratica = newwin(3, 3, 3 * ( * luminat_linie), 3 * ( * luminat_coloana)); //construiesc o alta fereastra si pun 1
    wattron(patratica, COLOR_PAIR(2));
    box(patratica, 0, 0);
    mvwprintw(patratica, 1, 1, "1");//pun verde
    wattroff(patratica, COLOR_PAIR(2));
    ( * incercare_mea) ++; //creste numarul de casute
    mvwprintw(joc, 20, 120, "incercarea mea: %d", ( * incercare_mea)); //afisez numarul de casute daca e una nimerita
    wrefresh(joc);
    wrefresh(patratica);
    optiune_incercata[ * luminat_linie][ * luminat_coloana] = 1; //casuta de optiune devine incercata
  }
  if (matrice[ * luminat_linie][ * luminat_coloana] == 0) {
    delwin(patratica_col);
    patratica = newwin(3, 3, 3 * ( * luminat_linie), 3 * ( * luminat_coloana));
    box(patratica, 0, 0);
    mvwprintw(patratica, 1, 1, "0"); //daca pe harta botului e 0 sa apara 0 dupa ce incerc o casuta
    wrefresh(joc);
    wrefresh(patratica);
    optiune_incercata[ * luminat_linie][ * luminat_coloana] = 1; //casuta de optiune devine 1
    do {
      linie = rand() % 10; //incercarea botului de a cauta o linie si o coloana
      coloana = rand() % 10;
    } while (optiune_incercata_bot[linie][coloana] != 0); //cat timp nu a fost deja incercata
    while (matricea_mea[linie][coloana] == 1) { //daca locul de pe harta mea e 1
      WINDOW * patratica = newwin(3, 3, 3 * linie, 3 * coloana + 50);
      box(patratica, 0, 0);
      sleep(1); //sa astept o secunda pentru a vedea miscarea lui
      mvwprintw(patratica, 1, 1, "1"); //sa afiseze 1
      optiune_incercata_bot[linie][coloana] = 1; //casuta de optiune devine incercata
      ( * incercare_bot) ++; //creste numaru; de casute ghicite de bot
      mvwprintw(joc, 23, 120, "incercare bot: %d", ( * incercare_bot));
      wrefresh(joc);
      wrefresh(patratica);
      if (optiune_incercata_bot[linie + 1][coloana] == 0 && linie != 9) //sa incerce o optiune de pe langa daca a nimerit un 1
        linie = linie + 1;
      else {
        if (optiune_incercata_bot[linie][coloana + 1] == 0 && coloana != 9)
          coloana = coloana + 1;
        else {
          if (optiune_incercata_bot[linie - 1][coloana] == 0 && linie != 0)
            linie = linie - 1;
          else {
            if (optiune_incercata_bot[linie][coloana - 1] == 0 && coloana != 0)
              coloana = coloana - 1;
            else { //daca nu gaseste pe langa una neincercata inca, da random
              do {
                linie = rand() % 10;
                coloana = rand() % 10;
              } while (optiune_incercata_bot[linie][coloana] != 0);
            }
          }
        }
      }
    }
    if (matricea_mea[linie][coloana] == 0) { //daca cea incercata nu e casuta cu o parte dintr-o nava
      WINDOW * patratica = newwin(3, 3, 3 * linie, 3 * coloana + 50);
      box(patratica, 0, 0);
      sleep(1);
      mvwprintw(patratica, 1, 1, "0"); // sa o faca 0
      optiune_incercata_bot[linie][coloana] = 1; //casuta de optiune devine 1(incercata)
      wrefresh(joc);
      wrefresh(patratica);
    }
  }
}
void randomize_o_nava(int optiune_incercata_bot[10][10], int matricea_mea[10][10], int optiune_incercata_bot_random[10][10], int matrice_aux_random[10][10]) {
  int i, j, contor, contor_nava_buna, contor_transfer, poz_veche, linie, coloana, pozitie, t;
  for (i = 0; i < 10; i++) { 
    for (j = 0; j < 10; j++) {
      matrice_aux_random[i][j] = matricea_mea[i][j]; //transfer toata harta mea la alta matrice secundara
      matricea_mea[i][j] = 0; //harta mea devine 0 pe fiecare pozitie
      if (matrice_aux_random[i][j] == 0 && optiune_incercata_bot[i][j] == 1) //daca a fost ghicita dar era 0
        optiune_incercata_bot[i][j] = 0; //devine 0
      optiune_incercata_bot_random[i][j] = 0;
    }
  }
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      contor = 0;
      contor_nava_buna = 0;
      contor_transfer = 0;
      if (matrice_aux_random[i][j] == 1) { //daca a fost ghicita si era 1
        contor++;
        matrice_aux_random[i][j] = 0;
        if (matrice_aux_random[i + 1][j] == 1) { //daca pe linia de mai jos se afla tot 1
          poz_veche = 0; //pozitia veche este verticala
          contor++;
          matrice_aux_random[i + 1][j] = 0; //locul ala devine 0
          for (t = i + 2; t < 10; t++) { 
            if (matrice_aux_random[t][j] == 1) { //daca mai sunt parti din barca mai jos
              contor++; //contorul de care parti are barca creste
              matrice_aux_random[t][j] = 0; //optiunile pe care era 1 devin 0
            } else
              break;
          }
        }
        if (matrice_aux_random[i][j + 1] == 1) { //daca pe urmatoare coloana se afla tot 1
          poz_veche = 1; //inseamna ca poz veche era orizontala
          contor++; //contorul de cate parti sunt creste
          matrice_aux_random[i][j + 1] = 0; //locul initial devine 0
          for (t = j + 2; t < 10; t++) {
            if (matrice_aux_random[i][t] == 1) { //verificam daca mai exista
              contor++; //contorul de parti creste
              matrice_aux_random[i][t] = 0; //locul ala devine 0
            } else
              break;
          }
        }
      }
      if (contor == 1) { //daca e o barca din o casuta
        while (contor_nava_buna == 0) { //generez o barca de una
          generat_nava_1(matricea_mea, & contor_nava_buna, & linie, & coloana, & pozitie);
        }
        if (optiune_incercata_bot[i][j] == 1) { //daca a fost ghicita de robot
          optiune_incercata_bot_random[linie][coloana] = 1; //cea noua devine ghicita
          optiune_incercata_bot[i][j] = 0;//cea veche nu mai e
        }
      }
      if (contor == 2) {
        while (contor_nava_buna == 0) { //generez o barca de doua casute
          generat_nava_2(matricea_mea, & contor_nava_buna, & linie, & coloana, & pozitie);
        }
        if (poz_veche == 0) { //daca a fost verticala pozitia
          for (t = i; t <= i + 1; t++) { //pentru fiecare casuta
            contor_transfer++; //cresc un contor pentru a face doua casute
            if (pozitie == 1) { //daca noua pozitie e verticala
              if (optiune_incercata_bot[t][j] == 1) { //daca era incercata
                optiune_incercata_bot_random[linie + contor_transfer - 1][coloana] = 1; //devine incercata
                optiune_incercata_bot[t][j] = 0; //cea dinainte se transforma in 0
              }
            }
            if (pozitie == 0) { //daca noua pozitie e orizontala
              if (optiune_incercata_bot[t][j] == 1) { //si daca a fost incercata
                optiune_incercata_bot_random[linie][coloana + contor_transfer - 1] = 1; //devine incercata in noua harta
                optiune_incercata_bot[t][j] = 0; //se transforma in 0 pe vechea optiune
              }
            }
          }
        }
        if (poz_veche == 1) { //daca pozitia veche era orizontala
          for (t = j; t <= j + 1; t++) { //pentru fiecare casuta
            contor_transfer++; //cresc un contor pentru a face doua casute
            if (pozitie == 1) { //daca noua pozitie e verticala
              if (optiune_incercata_bot[i][t] == 1) { //si optiunea incercata e 1
                optiune_incercata_bot_random[linie + contor_transfer - 1][coloana] = 1; //devine ghicita pe nou harta
                optiune_incercata_bot[i][t] = 0; //pe vechea devine 0
              }
            }
            if (pozitie == 0) { //daca noua poz e orizontala
              if (optiune_incercata_bot[i][t] == 1) { //daca a fost incercata
                optiune_incercata_bot_random[linie][coloana + contor_transfer - 1] = 1; //devine incercata pe noua harta
                optiune_incercata_bot[i][t] = 0; //si pe vechea 0 pentru a elibera locul pentru a putea pune orice in locul ei
              }
            }
          }
        }
      }
      if (contor == 3) { //analog pentru cazurile contor==3 si contor==4 ca la cazul cu barca cu 2 casute
        while (contor_nava_buna == 0) {
          generat_nava_3(matricea_mea, & contor_nava_buna, & linie, & coloana, & pozitie);
        }
        if (poz_veche == 0) {
          for (t = i; t <= i + 2; t++) {
            contor_transfer++;
            if (pozitie == 1) {
              if (optiune_incercata_bot[t][j] == 1) {
                optiune_incercata_bot_random[linie + contor_transfer - 1][coloana] = 1;
                optiune_incercata_bot[t][j] = 0;
              }
            }
            if (pozitie == 0) {
              if (optiune_incercata_bot[t][j] == 1) {
                optiune_incercata_bot_random[linie][coloana + contor_transfer - 1] = 1;
                optiune_incercata_bot[t][j] = 0;
              }
            }
          }
        }
        if (poz_veche == 1) {
          for (t = j; t <= j + 2; t++) {
            contor_transfer++;
            if (pozitie == 1) {
              if (optiune_incercata_bot[i][t] == 1) {
                optiune_incercata_bot_random[linie + contor_transfer - 1][coloana] = 1;
                optiune_incercata_bot[i][t] = 0;
              }
            }
            if (pozitie == 0) {
              if (optiune_incercata_bot[i][t] == 1) {
                optiune_incercata_bot_random[linie][coloana + contor_transfer - 1] = 1;
                optiune_incercata_bot[i][t] = 0;
              }
            }
          }
        }
      }
      if (contor == 4) {
        while (contor_nava_buna == 0) {
          generat_nava_4(matricea_mea, & contor_nava_buna, & linie, & coloana, & pozitie);
        }
        if (poz_veche == 0) {
          for (t = i; t <= i + 3; t++) {
            contor_transfer++;
            if (pozitie == 1) {
              if (optiune_incercata_bot[t][j] == 1) {
                optiune_incercata_bot_random[linie + contor_transfer - 1][coloana] = 1;
                optiune_incercata_bot[t][j] = 0;
              }
            }
            if (pozitie == 0) {
              if (optiune_incercata_bot[t][j] == 1) {
                optiune_incercata_bot_random[linie][coloana + contor_transfer - 1] = 1;
                optiune_incercata_bot[t][j] = 0;
              }
            }
          }
        }
        if (poz_veche == 1) {
          for (t = j; t <= j + 3; t++) {
            contor_transfer++;
            if (pozitie == 1) {
              if (optiune_incercata_bot[i][t] == 1) {
                optiune_incercata_bot_random[linie + contor_transfer - 1][coloana] = 1;
                optiune_incercata_bot[i][t] = 0;
              }
            }
            if (pozitie == 0) {
              if (optiune_incercata_bot[i][t] == 1) {
                optiune_incercata_bot_random[linie][coloana + contor_transfer - 1] = 1;
                optiune_incercata_bot[i][t] = 0;
              }
            }
          }
        }
      }
    }
  }
  for (i = 0; i < 10; i++)
    for (j = 0; j < 10; j++) {
      optiune_incercata_bot[i][j] = optiune_incercata_bot_random[i][j]; //refac optiunile incercate pentru noua harta
    }
}
void destroy(WINDOW * joc, WINDOW * patratica_col, WINDOW * patratica, int optiune_incercata_bot[10][10], int optiune_incercata[10][10], int * incercare_mea, int * incercare_bot, int matricea_mea[10][10], int matrice[10][10]) {
  int contor, linie, coloana;
  contor = 0;
  while (contor < 10) {
    do {
      linie = rand() % 10; //botul cauta pozitii care nu au fost incercate
      coloana = rand() % 10;
    } while (optiune_incercata_bot[linie][coloana] != 0);
    if (matricea_mea[linie][coloana] == 1) { //daca au fost parti de nava
      WINDOW * patratica = newwin(3, 3, 3 * linie, 3 * coloana + 50);
      box(patratica, 0, 0);
      mvwprintw(patratica, 1, 1, "1");
      optiune_incercata_bot[linie][coloana] = 1; //devine incercata
      ( * incercare_bot) ++; //creste numarul de casute nimerite
      mvwprintw(joc, 23, 120, "incercare bot: %d", * incercare_bot);
      wrefresh(joc);
      wrefresh(patratica);
    }
    if (matricea_mea[linie][coloana] == 0) { //daca erau 0
      WINDOW * patratica = newwin(3, 3, 3 * linie, 3 * coloana + 50);
      box(patratica, 0, 0);
      mvwprintw(patratica, 1, 1, "0");
      optiune_incercata_bot[linie][coloana] = 1;
      wrefresh(joc);
      wrefresh(patratica);
    }
    do {
      linie = rand() % 10; //eu caut pozitie neincercata
      coloana = rand() % 10;
    } while (optiune_incercata[linie][coloana] != 0);
    if (matrice[linie][coloana] == 1) { //daca e parta de barca
      delwin(patratica_col);
      patratica = newwin(3, 3, 3 * linie, 3 * coloana);
      start_color();
      init_pair(2, COLOR_GREEN, COLOR_BLACK);
      box(patratica, 0, 0);
      wattron(patratica, COLOR_PAIR(2));
      mvwprintw(patratica, 1, 1, "1"); //o notez corspunzator
      wattroff(patratica, COLOR_PAIR(2));
      ( * incercare_mea) ++; //cersc numarul de casute ghicit
      mvwprintw(joc, 20, 120, "incercarea mea: %d", * incercare_mea);
      wrefresh(joc);
      wrefresh(patratica);
      optiune_incercata[linie][coloana] = 1; //devine incercata
    }
    if (matrice[linie][coloana] == 0) { //daca nu
      delwin(patratica_col);
      patratica = newwin(3, 3, 3 * linie, 3 * coloana);
      box(patratica, 0, 0);
      mvwprintw(patratica, 1, 1, "0"); //o notez
      wrefresh(joc);
      wrefresh(patratica);
      optiune_incercata[linie][coloana] = 1; //devine incercata
    }
    contor++;
  }
}
int scor_jucator_pierde(WINDOW * joc, int matrice_aux_random[10][10], int optiune_incercata[10][10], int matrice[10][10]) {
  int i, j, t, s, contor;
  s = 0;
  mvwprintw(joc, 10, 120, "Botul a castigat");
  wrefresh(joc);
  for (i = 0; i < 10; i++)
    for (j = 0; j < 10; j++) {
      if (optiune_incercata[i][j] == 1 && matrice[i][j] == 1) { //daca a fost parte de barca si a fost nimerita
        matrice_aux_random[i][j] = 2; //devine 2 pe o harta secundara
      } else
        matrice_aux_random[i][j] = matrice[i][j]; //altfel ramane 1 sau 0
    }
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      contor = 0;
      if (matrice_aux_random[i][j] == 1) { //daca e 1(nu a fost nimerita dar era parte de nava)
        contor = 0;//contoru devine 0
        for (t = j + 1; t < 10; t++) { //pentru fiecare casuta care a fost nimerita din acea barca daca e pe orizontala
          if (matrice_aux_random[i][t] == 0)
            break;
          if (matrice_aux_random[i][t] == 2)
            matrice_aux_random[i][t] = 0; //devine 0 pe harta secundara
        }
        for (t = i + 1; t < 10; t++) { //analog daca e pe verticala
          if (matrice_aux_random[t][j] == 0)
            break;
          if (matrice_aux_random[t][j] == 2)
            matrice_aux_random[t][j] = 0;
        }
      }
      if (matrice_aux_random[i][j] == 2) { //daca prima parte din barca gasita e nimerita
        contor = 1;
        for (t = j + 1; t < 10; t++) { //verificam sa fie toate nimerite pe orizontala
          if (matrice_aux_random[i][t] == 1) { //daca e una negasita
            contor = 0; //contorul devine 0
          }
          if (matrice_aux_random[i][t] == 0)
            break;
          if (matrice_aux_random[i][t] == 2) //daca e nimerita devine 0 sa nu mai dam de ea
            matrice_aux_random[i][t] = 0;
        }
        for (t = i + 1; t < 10; t++) {
          if (matrice_aux_random[t][j] == 1) //analog daca e pe verticala
            contor = 0;
          if (matrice_aux_random[t][j] == 0)
            break;
          if (matrice_aux_random[t][j] == 2)
            matrice_aux_random[t][j] = 0;
        }
      }
      if (contor == 1)
        s = s + 1; //daca a fost o barca distrusa in intregime o adaugam
    }
  }
  return s;
}//analog daca botul pierde
int scor_bot_pierde(WINDOW * joc, int matrice_aux_random[10][10], int optiune_incercata_bot[10][10], int matricea_mea[10][10]) {
  int i, j, t, s, contor;
  s = 0;
  mvwprintw(joc, 10, 120, "Ai castigat");
  wrefresh(joc);
  for (i = 0; i < 10; i++)
    for (j = 0; j < 10; j++) {
      if (optiune_incercata_bot[i][j] == 1 && matricea_mea[i][j] == 1) {
        matrice_aux_random[i][j] = 2;
      } else
        matrice_aux_random[i][j] = matricea_mea[i][j];
    }
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      contor = 0;
      if (matrice_aux_random[i][j] == 1) {
        contor = 0;
        for (t = j + 1; t < 10; t++) {
          if (matrice_aux_random[i][t] == 0)
            break;
          if (matrice_aux_random[i][t] == 2)
            matrice_aux_random[i][t] = 0;
        }
        for (t = i + 1; t < 10; t++) {
          if (matrice_aux_random[t][j] == 0)
            break;
          if (matrice_aux_random[t][j] == 2)
            matrice_aux_random[t][j] = 0;
        }
      }
      if (matrice_aux_random[i][j] == 2) {
        contor = 1;
        for (t = j + 1; t < 10; t++) {
          if (matrice_aux_random[i][t] == 1) {
            contor = 0;
          }
          if (matrice_aux_random[i][t] == 0)
            break;
          if (matrice_aux_random[i][t] == 2)
            matrice_aux_random[i][t] = 0;
        }
        for (t = i + 1; t < 10; t++) {
          if (matrice_aux_random[t][j] == 1)
            contor = 0;
          if (matrice_aux_random[t][j] == 0)
            break;
          if (matrice_aux_random[t][j] == 2)
            matrice_aux_random[t][j] = 0;
        }
      }
      if (contor == 1)
        s = s + 1;
    }
  }
  return s;
}
int main(int argc, char * argv[]) {
  WINDOW * cursor, * joc, * patratica_col, * patratica0, * patratica1, * patratica;
  int luminat = 0, i, alegere, j, luminat_linie = 0, luminat_coloana = 0;
  int contor_nave, s = 0, t1;
  int c, optiune, incercare_mea = 0, incercare_bot = 0, contor = 0, t, contor_nava_buna = 0, contor_transfer, poz_veche;
  int matricea_mea[10][10], matrice_aux_random[10][10], matrice[10][10];
  int optiune_incercata[10][10], optiune_incercata_bot[10][10], optiune_incercata_bot_random[10][10];
  FILE * harta, * resume, * fisier;
  harta = fopen(argv[1], "r");
  if(harta == NULL)
    fprintf(stderr, "Eroare! Nu am putut deschide fisierul!");
  else {
    initscr();
    clear();
    cbreak();
    noecho();
    mvprintw(1, 10, "BATTLESHIP");
    refresh();
    creare_meniu( & ( * cursor), & optiune);
    for (i = 0; i < 10; i++) {
      for (j = 0; j < 10; j++) {
        fscanf(harta, "%d", & matricea_mea[i][j]); //citesc harta din fisier
        //wrefresh(joc);
      }
    }
    if (optiune == 2) { //daca am ales exit
      refresh();
      endwin();
    }
    if (optiune == 0) { //daca am ales new game
      delwin(cursor);
      int linie, coloana, pozitie;
      joc = newwin(0, 0, 0, 0); //initializeaza noua harta
      for(i=0;i<10;i++)
        for(j=0;j<10;j++)
          mvwprintw(joc,35+i,100+j,"%d",matricea_mea[i][j]);
      wrefresh(joc);
      wattroff(joc, COLOR_PAIR(1));
      mvwprintw(joc, 20, 120, "incercarea mea: %d", incercare_mea);
      mvwprintw(joc, 23, 120, "incercare bot: %d", incercare_bot);
      mvwprintw(joc, 30, 120, "press r for randomize"); //adaug optiunile scrise
      mvwprintw(joc, 31, 120, "press d for destroy in advance");
      mvwprintw(joc, 32, 120, "press s for save");
      wrefresh(joc);
      for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
          matrice[i][j] = 0;
          optiune_incercata[i][j] = 0;
          optiune_incercata_bot[i][j] = 0;
        }
      }
      srand(time(0));
      generat_1nava_4(matrice); //generez navele
      generat_2nava_3(matrice);
      generat_3nava_2(matrice);
      generat_4nava_1(matrice);
      afisare_matrice_bot( & luminat_linie, & luminat_coloana, joc, patratica1, patratica);
      afisare_matrice_jucator(joc, patratica);
      keypad(joc, TRUE);
      while (incercare_mea < 20 && incercare_bot < 20) { //cat timp pe ambele harti exista casute nedistruse
        c = wgetch(joc);
        if (c == KEY_UP)
          mers_in_sus(optiune_incercata, & luminat_linie, & luminat_coloana, matrice, patratica, joc);
        if (c == KEY_DOWN)
          mers_in_jos(optiune_incercata, & luminat_linie, & luminat_coloana, matrice, patratica, joc);
        if (c == KEY_LEFT)
          mers_in_stanga(optiune_incercata, & luminat_linie, & luminat_coloana, matrice, patratica, joc);
        if (c == KEY_RIGHT)
          mers_in_dreapta(optiune_incercata, & luminat_linie, & luminat_coloana, matrice, patratica, joc);
        keypad(joc, TRUE);
        coloreaza_patratica( & luminat_linie, & luminat_coloana, optiune_incercata, patratica_col, joc, matrice);
        if (c == 10 && optiune_incercata[luminat_linie][luminat_coloana] == 0)
          nimerit_matrice(matrice, matricea_mea, & luminat_linie, & luminat_coloana, patratica, & incercare_mea, patratica_col, joc, optiune_incercata_bot, optiune_incercata, & incercare_bot);
        if (c == 'r') { //r sa dau random la propria harta
          randomize_o_nava(optiune_incercata_bot, matricea_mea, optiune_incercata_bot_random, matrice_aux_random);
          afisare_matrice_random(joc, patratica1, patratica, matricea_mea, optiune_incercata_bot);
        }
        if (c == 'd') //d pentru destroy
          destroy(joc, patratica_col, patratica, optiune_incercata_bot, optiune_incercata, & incercare_mea, & incercare_bot, matricea_mea, matrice);
        if (c == 's') { //salvez statusul jocului pentru resume, sa pot juca doar din punctul din care am salvat
          resume = fopen("resume", "w"); //transfer toate datele de pana acum in fisiere
          putwin(joc, resume);
          fisier = fopen("fisier", "w");
          for (i = 0; i < 10; i++)
            for (j = 0; j < 10; j++) {
              fprintf(fisier, "%d ", matricea_mea[i][j]);
              fprintf(fisier, "%d ", matrice[i][j]);
              fprintf(fisier, "%d ", optiune_incercata[i][j]);
              fprintf(fisier, "%d ", optiune_incercata_bot[i][j]);
            }
          fprintf(fisier, "%d ", incercare_bot);
          fprintf(fisier, "%d ", incercare_mea);
          fclose(fisier);
          fclose(resume);
        }
        if (c == 'q') { //daca apas pe q in timpul jocului sa iasa
          refresh();
          endwin();
          break;
        }
      }
      //wrefresh(joc);
    }
    if (optiune == 1) { //daca aleg resume
      resume = fopen("resume", "r"); //citesc din fisierele in care am salvat datele
      fisier = fopen("fisier", "r");
      for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++) {
          fscanf(fisier, "%d", & matricea_mea[i][j]);
          fscanf(fisier, "%d", & matrice[i][j]);
          fscanf(fisier, "%d", & optiune_incercata[i][j]);
          fscanf(fisier, "%d", & optiune_incercata_bot[i][j]);
        }
      fscanf(fisier, "%d", & incercare_bot);
      fscanf(fisier, "%d", & incercare_mea);
      joc = newwin(0, 0, 0, 0); //reincarc hartile in functie de matrici
      wrefresh(joc);
      wattroff(joc, COLOR_PAIR(1));
      mvwprintw(joc, 20, 120, "incercarea mea: %d", incercare_mea);
      mvwprintw(joc, 23, 120, "incercare bot: %d", incercare_bot);
      mvwprintw(joc, 30, 120, "press r for randomize");
      mvwprintw(joc, 31, 120, "press d for destroy in advance");
      mvwprintw(joc, 32, 120, "press s for save");
      wrefresh(joc);
      fclose(resume);
      fclose(fisier);
      afisare_matrice_resume_jucator(joc, patratica1, patratica, matricea_mea, optiune_incercata_bot);
      afisare_matrice_resume_bot(joc, patratica1, patratica, matrice, optiune_incercata);
      keypad(joc, TRUE); //de aici e analog ca la new game
      while (incercare_mea < 20 && incercare_bot < 20) {
        c = wgetch(joc);
        if (c == KEY_UP)
          mers_in_sus(optiune_incercata, & luminat_linie, & luminat_coloana, matrice, patratica, joc);
        if (c == KEY_DOWN)
          mers_in_jos(optiune_incercata, & luminat_linie, & luminat_coloana, matrice, patratica, joc);
        if (c == KEY_LEFT)
          mers_in_stanga(optiune_incercata, & luminat_linie, & luminat_coloana, matrice, patratica, joc);
        if (c == KEY_RIGHT)
          mers_in_dreapta(optiune_incercata, & luminat_linie, & luminat_coloana, matrice, patratica, joc);
        keypad(joc, TRUE);
        coloreaza_patratica( & luminat_linie, & luminat_coloana, optiune_incercata, patratica_col, joc, matrice);
        if (c == 10 && optiune_incercata[luminat_linie][luminat_coloana] == 0)
          nimerit_matrice(matrice, matricea_mea, & luminat_linie, & luminat_coloana, patratica, & incercare_mea, patratica_col, joc, optiune_incercata_bot, optiune_incercata, & incercare_bot);
        if (c == 'r') {
          randomize_o_nava(optiune_incercata_bot, matricea_mea, optiune_incercata_bot_random, matrice_aux_random);
          afisare_matrice_random(joc, patratica1, patratica, matricea_mea, optiune_incercata_bot);
        }
        if (c == 'd')
          destroy(joc, patratica_col, patratica, optiune_incercata_bot, optiune_incercata, & incercare_mea, & incercare_bot, matricea_mea, matrice);
        if (c == 's') {
          resume = fopen("resume", "w");
          fisier = fopen("fisier", "w");
          putwin(joc, resume);
          for (i = 0; i < 10; i++)
            for (j = 0; j < 10; j++) {
              putw(matricea_mea[i][j], fisier);
              putw(matrice[i][j], fisier);
              putw(optiune_incercata[i][j], fisier);
              putw(optiune_incercata_bot[i][j], fisier);
            }
          fclose(resume);
          fclose(fisier);
        }
        if (c == 'q') {
          refresh();
          endwin();
          break;
        }
      }
      //wrefresh(joc);
    }
    do { //scorul la final
      if (incercare_bot == 20 && incercare_mea != 20) { //daca botul a castigat
        mvwprintw(joc, 12, 120, "Ai doborat %d nave", scor_jucator_pierde(joc, matrice_aux_random, optiune_incercata, matrice));
        mvwprintw(joc, 13, 120, "Botul a doborat 10 nave");
        wrefresh(joc);
      }
      if (incercare_mea == 20 && incercare_bot != 20) { //daca eu am castigat
        mvwprintw(joc, 12, 120, "Ai doborat 10 nave");
        mvwprintw(joc, 13, 120, "Botul a doborat %d nave", scor_bot_pierde(joc, matrice_aux_random, optiune_incercata_bot, matricea_mea));
        wrefresh(joc);
      }
      if (incercare_bot == 20 && incercare_mea == 20) { //daca a fost remiza
        mvwprintw(joc, 10, 120, "remiza");
        mvwprintw(joc, 13, 120, "ati doborat 10 nave");
        wrefresh(joc);
      }
    } while ((c = wgetch(joc)) != KEY_BACKSPACE); //cu backspace inchid jocul
    delwin(joc);
    clrtoeol();
    refresh();
    endwin();
    return 1;
  }
}