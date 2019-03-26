#include <stdio.h>
#include <string.h>

/*
    EOF =   End of file - Se utiliza para identificar el final del
    archivo de lectura.
    , (44)= Se utiliza para identificar el final de una palabra.
*/

void cargarTablaDeTransiciones(short pos[7][6]) {
//   0          [1-7]        [8-9]     [a-f]U[A-F]      x,X          otro
pos[0][0]=2; pos[0][1]=1; pos[0][2]=1; pos[0][3]=6; pos[0][4]=6; pos[0][5]=6;
pos[1][0]=1; pos[1][1]=1; pos[1][2]=1; pos[1][3]=6; pos[1][4]=6; pos[1][5]=6;
pos[2][0]=4; pos[2][1]=4; pos[2][2]=6; pos[2][3]=6; pos[2][4]=3; pos[2][5]=6;
pos[3][0]=5; pos[3][1]=5; pos[3][2]=5; pos[3][3]=5; pos[3][4]=6; pos[3][5]=6;
pos[4][0]=4; pos[4][1]=4; pos[4][2]=6; pos[4][3]=6; pos[4][4]=6; pos[4][5]=6;
pos[5][0]=5; pos[5][1]=5; pos[5][2]=5; pos[5][3]=5; pos[5][4]=6; pos[5][5]=6;
pos[6][0]=6; pos[6][1]=6; pos[6][2]=6; pos[6][3]=6; pos[6][4]=6; pos[6][5]=6;
}

short verificarEstado(short caracter, short estadoActual, short estado[7][6]) {
    if (caracter == 48)                             // == 0
        return estado[estadoActual][0];
    else if (caracter >= 49 && caracter <= 55)      // >= 1 y <= 7
        return estado[estadoActual][1];
    else if (caracter == 56 || caracter == 57)      // 8 o 9
        return estado[estadoActual][2];
    else if ((caracter>=65 && caracter<=70) ||      // >= A y <= F o
             (caracter>=97 && caracter<=102))       // >= a y <= f
        return estado[estadoActual][3];
    else if (caracter == 88 || caracter == 120)     // X o x
        return estado[estadoActual][4];
    else
        return estado[estadoActual][5];
}

void definirSistemaNumerico(short estado, char sistema[]) {
    switch (estado) {
        case 1:
            strcpy(sistema, "Decimal");
            break;
        case 2:
        case 4:
            strcpy(sistema, "Octal");
            break;
        case 5:
            strcpy(sistema, "Hexadecimal");
            break;
        default:
            strcpy(sistema, "No Reconocido");
    }
}

void agregarEspacio(short longitud, FILE* archivoSalida) {
    int i;
    for (i=0; i<(8-longitud); i++) {
        putc(32,archivoSalida);
    }
}

void identificarPalabras(short tabla[7][6]) {
    FILE* archivoEntrada = fopen("ENTRADA.txt","r");
    FILE* archivoSalida = fopen("SALIDA.txt", "w");
    short caracter, estadoActual, longitud;
    char sistema[13];
	
	
    while ((caracter = fgetc(archivoEntrada)) != EOF) {
        longitud = 0;
        estadoActual = 0;
        while (caracter!=44 && caracter!= EOF){
                putc(caracter, archivoSalida);
                estadoActual = verificarEstado(caracter, estadoActual, tabla);
                longitud ++;
                caracter = fgetc(archivoEntrada);
        }
		
        agregarEspacio(longitud, archivoSalida);
        definirSistemaNumerico(estadoActual, sistema);
        fprintf(archivoSalida, "%s\n", &sistema[0]);
        if (!caracter)
            break;
    }
	
    fclose(archivoEntrada);
    fclose(archivoSalida);
}

int main() {
    short automata[7][6];

    cargarTablaDeTransiciones(automata);
    identificarPalabras(automata);

    return 0;
}
