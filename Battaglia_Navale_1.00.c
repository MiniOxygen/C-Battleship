//Davide Quartieri

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define ANSI_BACKGROUND_GREEN   "\x1b[42m"
#define ANSI_BACKGROUND_RED     "\x1b[41m"
#define ANSI_BACKGROUND_YELLOW  "\x1b[43m"
#define ANSI_BACKGROUND_BLUE    "\x1b[44m"
#define ANSI_BACKGROUND_RESET   "\x1b[49m"

#define N 10
int i, j, k;                    //indici
int nav2, nav3, nav4;           //navi disponibili > sia per giocatore 1 sia giocatore 2

void setutf();
void clear();
void stampa_matrice(int mat[][N], int mat_backup[][N]);
void undo(int mat[][N], int mat_backup[][N]);
void nave_inserita(int lenght);
void inserimenti();
void setup(int mat[][N], int mat_backup[][N]);
void cpusetup(int mat[][N], int mat_backup[][N]);
void battle(int campo_giocatore_1[][N], int campo_missili_1[][N], int campo_giocatore_2[][N], int campo_missili_2[][N]);
void autobattle(int campo_giocatore_1[][N], int campo_missili_1[][N], int campo_giocatore_2[][N], int campo_missili_2[][N]);
void printGame(int mat[][N], int mat2[][N]);
void setcampo(int mat[][N], int mat2[][N]);
void test();

//funzioni per grafiche
void menu();
void PLAYER1();
void PLAYER2();
void CPU();
void salvataggi();
void listfiles();

int main(){
	system("mkdir Salvataggi");
    system("mode con:cols=72 lines=35");
    setutf();
    srand(time(NULL));
    int opt = 0;
    int campo_p1[N][N];               			    //campo di gioco giocatore 1
    int campo_backup_p1[N][N];					    //campo di backup giocatore 1
    int campo_missili_p1[N][N];
    int campo_p2[N][N];							    //campo di gioco giocatore 2
    int campo_backup_p2[N][N];					    //campo di gioco giocatore 2

    int campo_missili_p2[N][N];
    char let;
    FILE *fp;
	
	inizio:
    setcampo(campo_missili_p1, campo_missili_p2);

    do{
        clear();
        menu();
        if(opt < 0 || opt > 4){
    		printf("Errore: inserisci un'opzione valida!\n");
		}
        printf("> ");
        scanf("%d", &opt);
    }while(opt < 1 || opt > 4);


	clear();
	switch(opt){
		case 1:
			//user vs user
            setup(campo_p1, campo_backup_p1);       //inserimenti giocatore 1
			setup(campo_p2, campo_backup_p2);    //inserimenti cpu
			battle(campo_p1, campo_missili_p1, campo_p2, campo_missili_p2);
			
			fp = fopen("Salvataggi/Giocatore1_campo.txt", "w");
            for(i = 0; i < N; i++){
                for(j = 0; j < N; j++){
                    fprintf(fp, "%d ", campo_p1[i][j]);
                }
            }
            fclose(fp);
			
			fp = fopen("Salvataggi/Giocatore1_missili.txt", "w");
            for(i = 0; i < N; i++){
                for(j = 0; j < N; j++){
                    fprintf(fp, "%d ", campo_missili_p1[i][j]);
                }
            }
            fclose(fp);
            
            fp = fopen("Salvataggi/Giocatore2_campo.txt", "w");
            for(i = 0; i < N; i++){
                for(j = 0; j < N; j++){
                    fprintf(fp, "%d ", campo_p2[i][j]);
                }
            }
            fclose(fp);
			
			fp = fopen("Salvataggi/Giocatore2_missili.txt", "w");
            for(i = 0; i < N; i++){
                for(j = 0; j < N; j++){
                    fprintf(fp, "%d ", campo_missili_p2[i][j]);
                }
            }
            fclose(fp);
            system("pause");
            goto inizio;
			break;
		case 2:
			//user vs user
			cpusetup(campo_p1, campo_backup_p1);	    //inserimenti giocatore 1
    		cpusetup(campo_p2, campo_backup_p2);	    //inserimenti giocatore 2
            autobattle(campo_p1, campo_missili_p1, campo_p2, campo_missili_p2);
            clear();
            printGame(campo_p1, campo_missili_p1);
            printf("\n");
            printGame(campo_p2, campo_missili_p2);
            
            fp = fopen("Salvataggi/Giocatore1_campo.txt", "w");
            for(i = 0; i < N; i++){
                for(j = 0; j < N; j++){
                    fprintf(fp, "%d ", campo_p1[i][j]);
                }
            }
            fclose(fp);
			
			fp = fopen("Salvataggi/Giocatore1_missili.txt", "w");
            for(i = 0; i < N; i++){
                for(j = 0; j < N; j++){
                    fprintf(fp, "%d ", campo_missili_p1[i][j]);
                }
            }
            fclose(fp);
            
            fp = fopen("Salvataggi/Giocatore2_campo.txt", "w");
            for(i = 0; i < N; i++){
                for(j = 0; j < N; j++){
                    fprintf(fp, "%d ", campo_p2[i][j]);
                }
            }
            fclose(fp);
			
			fp = fopen("Salvataggi/Giocatore2_missili.txt", "w");
            for(i = 0; i < N; i++){
                for(j = 0; j < N; j++){
                    fprintf(fp, "%d ", campo_missili_p2[i][j]);
                }
            }
            fclose(fp);
            system("pause");
            goto inizio;
			break;
		case 3:
            //salvataggio
            salvataggi();
            fp = fopen("Salvataggi/Giocatore1_campo.txt", "r");
            for(i = 0; i < N; i++){
                for(j = 0; j < N; j++){
                    fscanf(fp, "%d ", &campo_p1[i][j]);
                }
            }
            fclose(fp);
			
			fp = fopen("Salvataggi/Giocatore1_missili.txt", "r");
            for(i = 0; i < N; i++){
                for(j = 0; j < N; j++){
                    fscanf(fp, "%d ", &campo_missili_p1[i][j]);
                }
            }
            fclose(fp);
            
            fp = fopen("Salvataggi/Giocatore2_campo.txt", "r");
            for(i = 0; i < N; i++){
                for(j = 0; j < N; j++){
                    fscanf(fp, "%d ", &campo_p2[i][j]);
                }
            }
            fclose(fp);
			
			fp = fopen("Salvataggi/Giocatore2_missili.txt", "r");
            for(i = 0; i < N; i++){
                for(j = 0; j < N; j++){
                    fscanf(fp, "%d ", &campo_missili_p2[i][j]);
                }
            }
            fclose(fp);
            
            printGame(campo_p1, campo_missili_p1);
            printf("\n");
            printGame(campo_p2, campo_missili_p2);
            
            system("pause");
            goto inizio;
			break;
		case 4:
			break;
	}
    return 0;
}

void listfiles(){
	system("dir /b Salvataggi");
}

void setutf(){
  	#if defined(_WIN32)
	system ("CHCP 65001");
	clear();
  	#endif
}

void clear(){
  #if defined(_WIN32)
    system ("cls");
  #elif defined(__linux__)
    system("clear");
  #endif
}

void stampa_matrice(int mat[][N], int mat_backup[][N]){
    clear();
    printf("   1 2 3 4 5 6 7 8 9 10\n");
    for(i = 0; i < N; i++){
        if(i == 9){
            printf("%d ", i + 1);
        }
        else{
            printf("%d  ", i + 1);
        }
        for(j = 0; j < N; j++){
            switch(mat[i][j]){
                case 0:
                    printf(ANSI_BACKGROUND_BLUE);
                    break;
                default:
                    printf(ANSI_BACKGROUND_YELLOW);
            }
            printf("%d " ANSI_BACKGROUND_RESET, mat[i][j]);
            mat_backup[i][j] = mat[i][j];
        }
        printf("\n");
    }
}

void nave_inserita(int lenght){
    switch(lenght){
        case 2:
            nav2 = 1;
            break;
        case 3:
            nav3 = 1;
            break;
        case 4:
            nav4 = 1;
            break;
    }
}

void undo(int mat[][N], int mat_backup[][N]){
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            mat[i][j] = mat_backup[i][j];
        }
    }
}

void inserimenti(){
    printf("\nTipo nave\tnav2\tnav3\tnav4\n");
    printf("Disponibile?\t");
    if(nav2 == 0){
        printf(ANSI_BACKGROUND_GREEN " si \t");
    }
    else{
        printf(ANSI_BACKGROUND_RED" no \t");
    }

    if(nav3 == 0){
        printf(ANSI_BACKGROUND_GREEN" si \t");
    }
    else{
        printf(ANSI_BACKGROUND_RED" no \t");
    }

    if(nav4 == 0){
        printf(ANSI_BACKGROUND_GREEN" si \t");
    }
    else{
        printf(ANSI_BACKGROUND_RED" no \t");
    }
    printf(ANSI_BACKGROUND_RESET"\t\t. \n");
}


void setup(int mat[][N], int mat_backup[][N]){    
    //DICHIARAZIONI_________________________________________________
    int dir, dest, len, r, c;       //dati necessari
    int err;                        //stato di errore del programma (bool)
    //INIZIALIZZAZIONI______________________________________________
    printf("   1 2 3 4 5 6 7 8 9 10\n");
    for(i = 0; i < N; i++){
        if(i == 9){
            printf("%d ", i + 1);
        }
        else{
            printf("%d  ", i + 1);
        }
        for(j = 0; j < N; j++){
            mat[i][j] = 0;
            printf(ANSI_BACKGROUND_BLUE "%d " ANSI_BACKGROUND_RESET, mat[i][j]);
        }
        printf("\n");
    }
    nav2 = 0;
	nav3 = 0;
	nav4 = 0;
    //______________________________________________________________
    while(nav2 != 1 || nav3 != 1 || nav4 != 1){
        inserimenti();
        printf("\nInserisci:\nCoordinate del punto 1\n");
        do{
            printf("Riga: ");
            scanf("%d", &r);
            printf("Colonna: ");
            scanf("%d", &c);
            if((r < 1 || r > N || c < 1 || c > N) || (mat[r-1][c-1] != 0)){
                printf("\nErrore: inserisci coordinate valide\n");
            }
        }while((r < 1 || r > N || c < 1 || c > N) || (mat[r-1][c-1] != 0));
        c = c - 1;
        r = r - 1;
        do{
            printf("Lunghezza nave: ");
            scanf("%d", &len);
            if(len < 2 || len > 4){
                printf("\nErrore: inserisci una dimensione valida\n");
            }
            if((len == 2 && nav2 == 1) || (len == 3 && nav3 == 1) || (len == 4 && nav4 == 1)){
                printf("\nErrore: nave gia' inserita\n");
            }
        }while(len < 2 || len > 4 || (len == 2 && nav2 == 1) || (len == 3 && nav3 == 1) || (len == 4 && nav4 == 1));

        nave_inserita(len);
        //______________________________________________________________
        error:
        if(err == 1){
            printf("\n\nErrore: c'e' gia' una nave, cambia direzione!\n\n");
        }
        k = 0;
        err = 0;
        do{
            printf("Direzione nave:\n1) Verticale\n2) Orizzontale\n3) Diagonale\n> ");
            scanf("%d", &dir);
            if(dir < 1 || dir > 3){
                printf("\nErrore: inserisci una direzione valida\n");
            }
        }while(dir < 1 || dir > 3);

        switch(dir){
            case 1:
                //verticale
                do{
                    printf("\t1) Verticale-Alto\n\t2) Verticale-basso\n> ");
                    scanf("%d", &dest);
                    if(dest < 1 || dest > 2){
                        printf("\nErrore: inserisci una destinazione valida\n");
                    }
                    if(((r - len + 1) < 0 && dest == 1)||((r + len - 1 ) > 9 && dest == 2)){
                        printf("\nErrore: Non e' possibile inserire la nave\n");
                    }
                }while((dest < 1 || dest > 2)||(((r - len + 1) < 0 && dest == 1)||((r + len - 1 ) > 9 && dest == 2)));
                switch(dest){
                    case 1:	//verticale-alto
                        for(i = r; k < len; i--){
                            if(mat[i][c] == 0){
                                mat[i][c] = len;
                                k++;
                            }
                            else{
                                err = 1;
                            }
                        }
                        if(err == 1){
                            undo(mat, mat_backup);
                            goto error;
                        }
                        break;
                    case 2: //verticale basso
                        for(i = r; i < len + r; i++){
                            if(mat[i][c] == 0){
                                mat[i][c]= len;
                            }
                            else{
                                err = 1;
                            }
                        }
                        if(err == 1){
                            undo(mat, mat_backup);
                            goto error;
                        }
                        break;
                }
                break;
            case 2:
                //orizzontale
                do{
                    printf("\t1) Orizzontale-sinistra\n\t2) Orizzontale-destra\n> ");
                    scanf("%d", &dest);
                    if(dest < 1 || dest > 2){
                        printf("\nErrore: inserisci una destinazione valida\n");
                    }
                    if(((c - len + 1) < 0 && dest == 1)||((c + len - 1 ) > 9 && dest == 2)){
                        printf("\nErrore: Non e' possibile inserire la nave\n");
                    }
                }while((dest < 1 || dest > 2)||(((c - len + 1) < 0 && dest == 1)||((c + len - 1 ) > 9 && dest == 2)));
                switch(dest){
                    case 1:	//orizzontale-sinistra
                        for(i = c; k < len; i--){
                            if(mat[r][i] == 0){
                                mat[r][i] = len;
                                k++;
                            }
                            else{
                                err = 1;
                            }
                        }
                        if(err == 1){
                            undo(mat, mat_backup);
                            goto error;
                        }
                        break;
                    case 2:	//orizzontale-destra
                        for(i = c; k < len; i++){
                            if(mat[r][i] == 0){
                                mat[r][i] = len;
                                k++;
                            }
                            else{
                                err = 1;
                            }
                        }
                        if(err == 1){
                            undo(mat, mat_backup);
                            goto error;
                        }
                        break;
                }
                break;
            case 3:
                //diagonale
                do{
                    printf("\t1) Diagonale-Alto-destra\n\t2) Diagonale-Alto-sinistra\n\t3) Diagonale-basso-destra\n\t4) Diagonale-basso-sinistra\n> ");
                    scanf("%d", &dest);
                    if(dest < 1 || dest > 4){
                        printf("\nErrore: inserisci una destinazione valida\n");
                    }
                    if(((r - len - 1) < 0 && (dest == 1 || dest == 2))||((r + len - 1 ) > 9 && (dest == 3 || dest == 4))||((((c - len - 1) < 0 && (dest == 2 || dest == 4))||((c + len - 1 ) > 9 && (dest == 1 || dest == 3))))){
                        printf("\nErrore: Non e' possibile inserire la nave\n");
                    }

                }while((dest < 1 || dest > 4) || (((r - len - 1) < 0 && (dest == 1 || dest == 2))||((r + len - 1 ) > 9 && (dest == 3 || dest == 4))||((((c - len - 1) < 0 && (dest == 2 || dest == 4))||((c + len - 1 ) > 9 && (dest == 1 || dest == 3))))));
                switch(dest){
                    case 1:	//diagonale-alto-destra
                        j = c;
                        for(i = r; k < len; i--){
                            if(mat[i][j] == 0){
                                mat[i][j++] = len;
                                k++;
                            }
                            else{
                                err = 1;
                            }
                        }
                        if(err == 1){
                            undo(mat, mat_backup);
                            goto error;
                        }
                        break;
                    case 2: //diagonale-alto-sinistra
                        j = c;
                        for(i = r; k < len; i--){
                            if(mat[i][j] == 0){
                                mat[i][j--] = len;
                                k++;
                            }
                            else{
                                err = 1;
                            }
                        }
                        if(err == 1){
                            undo(mat, mat_backup);
                            goto error;
                        }
                        break;
                    case 3: //diagonale-basso-destra
                        j = c;
                        for(i = r; k < len; i++){
                            if(mat[i][j] == 0){
                                mat[i][j++] = len;
                                k++;
                            }
                            else{
                                err = 1;
                            }
                        }
                        if(err == 1){
                            undo(mat, mat_backup);
                            goto error;
                        }
                        break;
                    case 4: //diagonale-basso-sinistra
                        j = c;
                        for(i = r; k < len; i++){
                            if(mat[i][j] == 0){
                                mat[i][j--] = len;
                                k++;
                            }
                            else{
                                err = 1;
                            }
                        }
                        if(err == 1){
                            undo(mat, mat_backup);
                            goto error;
                        }
                        break;
                    }
                break;
            default:
            printf("\nErrore sconosciuto\n");
                break;
        }
        clear();
        stampa_matrice(mat, mat_backup);
    }
}
void cpusetup(int mat[][N], int mat_backup[][N]){
    //DICHIARAZIONI_________________________________________________
    int dir, dest, len, r, c;       //dati necessari
    len = 1;
    int err;                        //stato di errore del programma (bool)
    //INIZIALIZZAZIONI______________________________________________
    printf("   1 2 3 4 5 6 7 8 9 10\n");
    for(i = 0; i < N; i++){
        if(i == 9){
            printf("%d ", i + 1);
        }
        else{
            printf("%d  ", i + 1);
        }
        for(j = 0; j < N; j++){
            mat[i][j] = 0;
            printf(ANSI_BACKGROUND_BLUE "%d " ANSI_BACKGROUND_RESET, mat[i][j]);
        }
        printf("\n");
    }
    nav2 = 0;
	nav3 = 0;
	nav4 = 0;
    //______________________________________________________________
    while(nav2 != 1 || nav3 != 1 || nav4 != 1){
        inserimenti();
        do{
            r = (rand() % N) + 1;
            c = (rand() % N) + 1;
        }while((r < 1 || r > N || c < 1 || c > N) || (mat[r-1][c-1] != 0));
        c = c - 1;
        r = r - 1;
        do{
            len++;
        }while(len < 2 || len > 4 || (len == 2 && nav2 == 1) || (len == 3 && nav3 == 1) || (len == 4 && nav4 == 1));

        nave_inserita(len);
        //______________________________________________________________
        error:
        k = 0;
        err = 0;
        do{
            dir = (rand() % 3) + 1;
        }while(dir < 1 || dir > 3);

        switch(dir){
            case 1:
                //verticale
                do{
                    dest = (rand() % 2) + 1;
                }while((dest < 1 || dest > 2)||(((r - len + 1) < 0 && dest == 1)||((r + len - 1 ) > 9 && dest == 2)));
                switch(dest){
                    case 1:	//verticale-alto
                        for(i = r; k < len; i--){
                            if(mat[i][c] == 0){
                                mat[i][c] = len;
                                k++;
                            }
                            else{
                                err = 1;
                            }
                        }
                        if(err == 1){
                            undo(mat, mat_backup);
                            goto error;
                        }
                        break;
                    case 2: //verticale basso
                        for(i = r; i < len + r; i++){
                            if(mat[i][c] == 0){
                                mat[i][c]= len;
                            }
                            else{
                                err = 1;
                            }
                        }
                        if(err == 1){
                            undo(mat, mat_backup);
                            goto error;
                        }
                        break;
                }
                break;
            case 2:
                //orizzontale
                do{
                    dest = (rand() % 2) + 1;
                }while((dest < 1 || dest > 2)||(((c - len + 1) < 0 && dest == 1)||((c + len - 1 ) > 9 && dest == 2)));
                switch(dest){
                    case 1:	//orizzontale-sinistra
                        for(i = c; k < len; i--){
                            if(mat[r][i] == 0){
                                mat[r][i] = len;
                                k++;
                            }
                            else{
                                err = 1;
                            }
                        }
                        if(err == 1){
                            undo(mat, mat_backup);
                            goto error;
                        }
                        break;
                    case 2:	//orizzontale-destra
                        for(i = c; k < len; i++){
                            if(mat[r][i] == 0){
                                mat[r][i] = len;
                                k++;
                            }
                            else{
                                err = 1;
                            }
                        }
                        if(err == 1){
                            undo(mat, mat_backup);
                            goto error;
                        }
                        break;
                }
                break;
            case 3:
                //diagonale
                do{
                    dest = (rand() % 4) + 1;
                }while((dest < 1 || dest > 4) || (((r - len - 1) < 0 && (dest == 1 || dest == 2))||((r + len - 1 ) > 9 && (dest == 3 || dest == 4))||((((c - len - 1) < 0 && (dest == 2 || dest == 4))||((c + len - 1 ) > 9 && (dest == 1 || dest == 3))))));
                switch(dest){
                    case 1:	//diagonale-alto-destra
                        j = c;
                        for(i = r; k < len; i--){
                            if(mat[i][j] == 0){
                                mat[i][j++] = len;
                                k++;
                            }
                            else{
                                err = 1;
                            }
                        }
                        if(err == 1){
                            undo(mat, mat_backup);
                            goto error;
                        }
                        break;
                    case 2: //diagonale-alto-sinistra
                        j = c;
                        for(i = r; k < len; i--){
                            if(mat[i][j] == 0){
                                mat[i][j--] = len;
                                k++;
                            }
                            else{
                                err = 1;
                            }
                        }
                        if(err == 1){
                            undo(mat, mat_backup);
                            goto error;
                        }
                        break;
                    case 3: //diagonale-basso-destra
                        j = c;
                        for(i = r; k < len; i++){
                            if(mat[i][j] == 0){
                                mat[i][j++] = len;
                                k++;
                            }
                            else{
                                err = 1;
                            }
                        }
                        if(err == 1){
                            undo(mat, mat_backup);
                            goto error;
                        }
                        break;
                    case 4: //diagonale-basso-sinistra
                        j = c;
                        for(i = r; k < len; i++){
                            if(mat[i][j] == 0){
                                mat[i][j--] = len;
                                k++;
                            }
                            else{
                                err = 1;
                            }
                        }
                        if(err == 1){
                            undo(mat, mat_backup);
                            goto error;
                        }
                        break;
                    }
                break;
            default:
            printf("\nErrore sconosciuto\n");
                break;
        }
        clear();
        stampa_matrice(mat, mat_backup);
    }
}

//_____________________________________________________________________________________________________________________
void setcampo(int mat[][N], int mat2[][N]){
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            mat[i][j] = 0;
        }
        for(j = 0; j < N; j++){
            mat2[i][j] = 0;
        }
    }
}
void printGame(int mat[][N], int mat2[][N]){
	printf("   1 2 3 4 5 6 7 8 9 10\t\t   1 2 3 4 5 6 7 8 9 10\n");
    for(i = 0; i < N; i++){
        if(i == 9){
            printf("%d ", i + 1);
        }
        else{
            printf("%d  ", i + 1);
        }
        for(j = 0; j < N; j++){
            switch(mat[i][j]){
                case 0:
                    printf(ANSI_BACKGROUND_BLUE);
                    break;
                case 1:
                    printf(ANSI_BACKGROUND_RED);
                    break;
                default:
                    printf(ANSI_BACKGROUND_YELLOW);
                    break;
            }
            printf("%d " ANSI_BACKGROUND_RESET, mat[i][j]);
        }
        printf("\t\t");
         if(i == 9){
            printf("%d ", i + 1);
        }
        else{
            printf("%d  ", i + 1);
        }
        for(j = 0; j < N; j++){
            switch(mat2[i][j]){
                case 0:
                    printf(ANSI_BACKGROUND_BLUE);
                    break;
                case 1:
                    printf(ANSI_BACKGROUND_RED);
                    break;
                default:
                    printf(ANSI_BACKGROUND_YELLOW);
                    break;
            }
            printf("%d " ANSI_BACKGROUND_RESET, mat2[i][j]);
        }
        printf(" .\n");
    }
}

void battle(int campo_giocatore_1[][N], int campo_missili_1[][N], int campo_giocatore_2[][N], int campo_missili_2[][N]){
    int r, c;
    int turno = 0;
    int active;
    int win = 0;
    int p1_count = 0;
    int p2_count = 0;
    int err = 0;
    clear();
    while(win == 0){
        turno++;
        if(turno % 2 == 0){
            active = 2;                     //giocatore 2
        }
        else {
            active = 1;                     //giocatore 1
        }
        switch(active){
            case 1://giocatore1
                clear();
                PLAYER1();
                printGame(campo_giocatore_1, campo_missili_1);
                printf("\n");
                printGame(campo_giocatore_2, campo_missili_2);
                do{
                    err = 0;
                    printf("\nInserisci le coordinate\n");
                    do{
                        printf("Riga: ");
                        scanf("%d", &r);
                        printf("Colonna: ");
                        scanf("%d", &c);
                        if((r < 1 || r > N || c < 1 || c > N)){
                            printf("\nErrore: inserisci coordinate valide\n");
                        }
                    }while((r < 1 || r > N || c < 1 || c > N));
                    c = c - 1;
                    r = r - 1;
                    if(campo_missili_1[r][c] == 1 || campo_missili_1[r][c] == 2 || campo_missili_1[r][c] == 3 || campo_missili_1[r][c] == 4){
                        err = 1;
                    }
                }while(err == 1);

                if(campo_giocatore_2[r][c] != 0){
                    p1_count += 1;
                    campo_missili_1[r][c] = campo_giocatore_2[r][c];
                }
                else{
                    campo_missili_1[r][c] = 1;
                }
                if(p1_count == 9){
                    win = 1;
                }

                break;
            case 2://giocatore2
                clear();
                PLAYER2();
                printGame(campo_giocatore_2, campo_missili_2);
                printf("\n");
                printGame(campo_giocatore_1, campo_missili_1);
                do{
                    err = 0;
                    printf("\nInserisci le coordinate\n");
                    do{
                        printf("Riga: ");
                        scanf("%d", &r);
                        printf("Colonna: ");
                        scanf("%d", &c);
                        if((r < 1 || r > N || c < 1 || c > N)){
                            printf("\nErrore: inserisci coordinate valide\n");
                        }
                    }while((r < 1 || r > N || c < 1 || c > N));
                    c = c - 1;
                    r = r - 1;
                    if(campo_missili_2[r][c] == 1 || campo_missili_2[r][c] == 2 || campo_missili_2[r][c] == 3 || campo_missili_2[r][c] == 4){
                        err = 1;
                    }
                }while(err == 1);

                if(campo_giocatore_1[r][c] != 0){
                    p2_count += 1;
                    campo_missili_2[r][c] = campo_giocatore_1[r][c];
                }
                else{
                    campo_missili_2[r][c] = 1;
                }
                if(p2_count == 9){
                    win = 1;
                }
                break;
        }
    }
    if(p1_count > p2_count){
    	printf("\nGiocatore 1 vince la partita!\n");
    	system("pause");
	}
	else{
		printf("\nGiocatore 2 vince la partita!\n");
    	system("pause");
	}
}



void autobattle(int campo_giocatore_1[][N], int campo_missili_1[][N], int campo_giocatore_2[][N], int campo_missili_2[][N]){
    int r = 0, c = 0;
    int r2 = 0, c2 = 0;
    int turno = 0;
    int active;
    int win = 0;
    int p1_count = 0;
    int p2_count = 0;
    int err = 0;
    clear();
    while(win == 0){
        turno++;
        if(turno % 2 == 0){
            active = 2;                     //giocatore 2
        }
        else {
            active = 1;                     //giocatore 1
        }
        switch(active){
            case 1://giocatore1
                if(c == 10){
                	r++;
                	c = 0;
				}

                if(campo_giocatore_2[r][c] != 0){
                    p1_count += 1;
                    campo_missili_1[r][c] = campo_giocatore_2[r][c];
                }
                else{
                    campo_missili_1[r][c] = 1;
                }
                if(p1_count == 9){
                    win = 1;
                }
				c++;
                break;
            case 2://giocatore2
                if(c2 == 10){
                	r2++;
                	c2 = 0;
				}

                if(campo_giocatore_1[r2][c2] != 0){
                    p2_count += 1;
                    campo_missili_2[r2][c2] = campo_giocatore_1[r2][c2];
                }
                else{
                    campo_missili_2[r2][c2] = 1;
                }
                if(p2_count == 9){
                    win = 1;
                }
                c2++;
                break;
        }
    }
    if(p1_count > p2_count){
    	printf("\nGiocatore 1 vince la partita!\n");
    	system("pause");
	}
	else{
		printf("\nGiocatore 2 vince la partita!\n");
    	system("pause");
	}
}


//FUNZIONI PER GRAFICHE
void menu(){
    printf("\n------------------------------------------------------------------------\n                           BATTAGLIA NAVALE C\n------------------------------------------------------------------------\n\n");
    printf("1) Player1 vs Player2\n");
    printf("2) Test (CPU vs CPU)\n");
    printf("3) Salvataggi\n");
    printf("4) Esci\n\n");
}

void salvataggi(){
	printf("------------------------------------------------------------------------\n                              SALVATAGGI\n------------------------------------------------------------------------\n\n");
}
void PLAYER1(){
    printf("------------------------------------------------------------------------\n");
    printf("                                PLAYER 1\n");
    printf("------------------------------------------------------------------------\n\n");
}
void PLAYER2(){
    printf("------------------------------------------------------------------------\n");
    printf("                                PLAYER 2\n");
    printf("------------------------------------------------------------------------\n\n");
}
void CPU(){
    printf("-----------------------------------------------------------------------\n");
    printf("                                  CPU\n");
    printf("-----------------------------------------------------------------------\n\n");
}
