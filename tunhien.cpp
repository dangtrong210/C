#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

typedef int DataType;
FILE *F0, *F1, *F2;
int M, N, Eor;
/*
Bien eor dung de kiem tra ket thuc Run hoac File
*/
DataType X1, X2, X, Y;

void CreatFile(FILE *Ft, int Num)
/*Tao file co ngau nhien n phan tu* */
{
    srand(time(NULL));
    Ft = fopen("e:\\bang.txt", "wb");
    for (int i = 0; i < Num; i++)
    {
        X = rand() % (30);
        fprintf(Ft, "%3d", X);
    }
    fclose(Ft);
}
void ListFile(FILE *Ft)
/*Hien thi noi dung cua file len man hinh */
{
    DataType X, I = 0;
    Ft = fopen("e:\\bang.txt", "rb");
    while (!feof(Ft))
    {
        fscanf(Ft, "%3d", &X);
        printf("%3d", X);
        I++;
    }
    printf("\n\n");
    fclose(Ft);
}
/**/
void Copy(FILE *Fi, FILE *Fj)
{
    // Doc phan tu X tu Tap tin Fi, ghi X vao Fj
    // Eor==1, Neu het Run(tren Fi) hoac het File Fi
    fscanf(Fi, "%3d", &X);
    fprintf(Fj, "%3d", X);
    if (!feof(Fi))
    {
        fscanf(Fi, "%3d", &Y);
        long curpos = ftell(Fi) - 2;
        fseek(Fi, curpos, SEEK_SET);
    }
    if (feof(Fi))
        Eor = 1;
    else
        Eor = (X > Y) ? 1 : 0;
}

void CopyRun(FILE *Fi, FILE *Fj)
/*Chep 1 Run tu Fi vao Fj */
{
    do
        Copy(Fi, Fj);
    while (!Eor);
}
void Distribute()
/*Phan bo luan phien cac Run tu nhien tu F0 vao F1 va F2*/
{
    do
    {
        CopyRun(F0, F1);
        if (!feof(F0))
            CopyRun(F0, F2);
    } while (!feof(F0));
    fclose(F0);
    fclose(F1);
    fclose(F2);
}
void MergeRun()
/*Tron 1 Run cua F1 va F2 vao F0*/
{
    do
    {
        fscanf(F1, "%3d", &X1);
        long curpos = ftell(F1) - 2;
        fseek(F1, curpos, SEEK_SET);
        fscanf(F2, "%3d", &X2);
        curpos = ftell(F2) - 2;
        fseek(F2, curpos, SEEK_SET);
        if (X1 <= X2)
        {
            Copy(F1, F0);
            if (Eor)
                CopyRun(F2, F0);
        }
        else
        {
            Copy(F2, F0);
            if (Eor)
                CopyRun(F1, F0);
        }
    } while (!Eor);
}
void Merge()
/*Tron cac run tu F1 va F2 vao F0*/
{
    while ((!feof(F1)) && (!feof(F2)))
    {
        MergeRun();
        M++;
    }
    while (!feof(F1))
    {
        CopyRun(F1, F0);
        M++;
    }
    while (!feof(F2))
    {
        CopyRun(F2, F0);
        M++;
    }
    fclose(F0);
    fclose(F1);
    fclose(F2);
}
// Ham main
int main()
{
    printf(" Nhap so phan tu: ");
    scanf("%d", &N);
    CreatFile(F0, N);
    printf("\n Noi dung file goc:");
    ListFile(F0);
    do
    {
        F0 = fopen("e:\\bang.txt", "rb");
        F1 = fopen("e:\\bang1.txt", "wb");
        F2 = fopen("e:\\bang2.txt", "wb");
        Distribute();
        F0 = fopen("e:\\bang.txt", "wb");
        F1 = fopen("e:\\bang1.txt", "rb");
        F2 = fopen("e:\\bang2.txt", "rb");
        M = 0;
        Merge();
    } while (M != 1);

    printf("\n Noi dung file da sap xep:");
    ListFile(F0);
    getch();
    return 0;
}
