#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE (1024)
#define MAX_SIZE (128)

typedef struct {
    char ime[MAX_SIZE];
    char prezime[MAX_SIZE];
    double bodovi;
}student;

int broj_studenata(char *ime_datoteke)
{
    int br=0;
    FILE* fp = NULL;
    char buffer[MAX_LINE] = {0};

    fp=fopen(ime_datoteke, "r");

    if(!fp)
    {
        printf("Greska");
        return -1;
    }
    while(!feof(fp))
    {
        fgets(buffer, MAX_LINE, fp);
        br++;
    }

    fclose(fp);

    return br;
}

student* alokacija_memorije(int br_studenata, char* ime_datoteke)
{
    int i=0;
    FILE* fp = NULL;
    student* studenti = NULL;

    studenti=(student*)malloc(br_studenata * sizeof(student));
    fp=fopen(ime_datoteke, "r");

    if(!fp)
    {
        printf("Greska");
        free(studenti);
        return NULL;
    }
    while(!feof(fp))
    {
        fscanf(fp, " %s %s %lf", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
        i++;
    }
    fclose(fp);
    return studenti;
}

double maksimalan_broj_bodova(char* ime_datoteke)
{
     int brojStudenata = 0, i = 0;
     double max=0;
     student* studenti = NULL;

     brojStudenata=broj_studenata(ime_datoteke);
     studenti=alokacija_memorije(brojStudenata, ime_datoteke);
     max = studenti[0].bodovi;

     for(i = 0 ; i < brojStudenata; i++)
     {
        if(studenti[i].bodovi>=max)
            {
                max=studenti[i].bodovi;
            }
     }
     return max;
}

double relativan_broj_bodova(char* ime_datoteke, int index)
{
    student* studenti = NULL;
    int brojStudenata = 0;
    double relativanBroj = 0, max = 0;

    brojStudenata=broj_studenata(ime_datoteke);
    studenti=alokacija_memorije(brojStudenata, ime_datoteke);

    max=maksimalan_broj_bodova(ime_datoteke);
    relativanBroj = studenti[index].bodovi/max*100;
    return relativanBroj;
}

int ispis(char* ime_datoteke)
{
    int brojStudenata = 0, i = 0;
    student* studenti = NULL;
    FILE* fp = NULL;

    fp = fopen(ime_datoteke, "r");
    brojStudenata = broj_studenata(ime_datoteke);
    studenti=alokacija_memorije(brojStudenata, ime_datoteke);
    for(i=0; i < brojStudenata; i++)
   {
        fscanf(fp," %s %s %lf", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
   }
   for(i=0; i< brojStudenata; i++)
   {
        printf("IME: %s \t PREZIME: %s \t BODOVI: %lf \t", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi);
        printf("RELATIVNI BODOVI: %lf \n", relativan_broj_bodova(ime_datoteke, i));
   }
   fclose(fp);
   return 0;
}

int main()
{
    ispis("studenti.txt");
    return 0;
}
