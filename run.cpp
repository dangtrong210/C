#include "stdio.h"
#include "conio.h"
int p, n;
void tao_file(void)
{
    // Tao file co n phan tu
    int i, x;
    FILE *fp;
    fp = fopen("D:\\Bang.txt", "wb");
    printf("Cho biet so phan tu : ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Nhap so thu %d : ", i + 1);
        scanf("%d", &x);
        fprintf(fp, "%3d", x);
    }
    fclose(fp);
}
void xuat_file(void)
{
    // Hien thi noi dung file len man hinh
    int x;
    FILE *fp;
    fp = fopen("D:\\Bang.txt", "rb");
    int i = 0;
    while (i < n)
    {
        fscanf(fp, "%d", &x);
        printf("%3d", x);
        i++;
    }
    fclose(fp);
}
void chia(FILE *a, FILE *b, FILE *c, int p)
{
    // Chia xoay vong file a cho file b va file c moi lan p phan tu cho
    // den khi het file a.
    int dem, x;
    a = fopen("D:\\Bang.txt", "rb");
    b = fopen("D:\\Bang1.txt", "wb");
    c = fopen("D:\\Bang2.txt", "wb");
    while (!feof(a))
    {
        // Chia p phan tu cho b
        dem = 0;
        while ((dem < p) && (!feof(a)))
        {
            fscanf(a, "%3d", &x);
            fprintf(b, "%3d", x);
            dem++;
        }
        // Chia p phan tu cho c
        dem = 0;
        while ((dem < p) && (!feof(a)))
        {
            fscanf(a, "%3d", &x);
            fprintf(c, "%3d", x);
            dem++;
        }
    }
    fclose(a);
    fclose(b);
    fclose(c);
}
void tron(FILE *b, FILE *c, FILE *a, int p)
{
    // Tron p phan tu tren b voi p phan tu tren c thanh 2*p phan tu tren a cho den khi
    // file b hoac c het
    int stop, x, y, l, r;
    a = fopen("D:\\Bang.txt", "wb");
    b = fopen("D:\\Bang1.txt", "rb");
    c = fopen("D:\\Bang2.txt", "rb");
    while ((!feof(b)) && (!feof(c)))
    {
        l = 0; // so phan tu cua b da ghi het len a
        r = 0; // so phan tu cua c da ghi het len a
        fscanf(b, "%3d", &x);
        fscanf(c, "%3d", &y);
        stop = 0;
        while ((l != p) && (r != p) && (!stop))
        {
            if (x < y)
            {
                fprintf(a, "%3d", x);
                l++;
                if ((l < p) && (!feof(b)))
                    fscanf(b, "%3d", &x); // chua du p phan tu va chua het file b
                else
                {
                    fprintf(a, "%3d", y);
                    r++;
                    if ((feof(b)))
                        stop = 1;
                }
            }
            else
            {
                fprintf(a, "%3d", y);
                r++;
                if ((r < p) && (!feof(c)))
                    fscanf(c, "%3d", &y); // chua du p phan tu va chua het file c
                else
                {
                    fprintf(a, "%3d", x);
                    l++;
                    if ((feof(c)))
                        stop = 1;
                }
            }
        }
        // chep phan tu con lai cua p phan tu tren b len a
        while ((!feof(b)) && (l < p))
        {
            fscanf(b, "%3d", &x);
            fprintf(a, "%3d", x);
            l++;
        }
        // chep phan tu con lai cua p phan tu tren c len a
        while ((!feof(c)) && (r < p))
        {
            fscanf(c, "%3d", &y);
            fprintf(a, "%3d", y);
            r++;
        }
    }
    if (!feof(b))
    {
        // chep phan tu con lai cua b len a
        while (!feof(b))
        {
            fscanf(b, "%3d", &x);
            fprintf(a, "%3d", x);
        }
    }
    if (!feof(c))
    {
        // chep phan tu con lai cua c len a
        while (!feof(c))
        {
            fscanf(c, "%3d", &x);
            fprintf(a, "%3d", x);
        }
    }
    fclose(a);
    fclose(b);
    fclose(c);
}
int main(void)
{
    FILE *a, *b, *c;
    tao_file();
    printf("\n Tap tin nhap:");
    xuat_file();
    p = 1;
    while (p < n)
    {
        chia(a, b, c, p);
        tron(b, c, a, p);
        p = 2 * p;
    }
    printf("\n Tap tin da sap xep:");
    xuat_file();
    getch();
}
