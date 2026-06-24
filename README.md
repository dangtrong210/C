# Cấu trúc Dữ liệu và Giải thuật — Tài liệu Thực hành (C/C++)
(Code được tổng hợp từ các bài của giáo viên trên lớp)
---

## Bài số 1: Tìm kiếm, Sắp xếp

```c
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int a[100], b[100], c[100], n;

void hoanvi(int &x, int &y) {
    int t = x; x = y; y = t;
}

void nhap(int a[], int n) {
    for (int i = 1; i <= n; i++) {
        printf("a[%d]=", i);
        scanf("%d", &a[i]);
    }
}

void xuat(int a[], int n) {
    for (int i = 1; i <= n; i++)
        printf("%4d", a[i]);
}

int LinearSearch(int a[], int n, int x) {
    int i;
    for (i = 1; (a[i] != x); i++);
    if (i <= n) return i;
    return -1;
}

int BinarySearch(int a[], int n, int x) {
    int left = 1, right = n, midle;
    while (left <= right) {
        midle = (left + right) / 2;
        if (x == a[midle]) return midle;
        if (x < a[midle]) right = midle - 1;
        else left = midle + 1;
    }
    return -1;
}

void selectionsort(int a[], int n) {
    int min;
    for (int i = 1; i < n; i++) {
        min = i;
        for (int j = i + 1; j <= n; j++)
            if (a[j] < a[min]) min = j;
        hoanvi(a[min], a[i]);
    }
}

void insertionsort(int a[], int n) {
    int pos, x;
    for (int i = 1; i <= n; i++) {
        x = a[i]; pos = i - 1;
        while ((pos >= 0) && (a[pos] > x)) {
            a[pos + 1] = a[pos];
            pos--;
        }
        a[pos + 1] = x;
    }
}

void interchangeSort(int a[], int n) {
    int i, j;
    for (i = 1; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (a[j] < a[i]) hoanvi(a[i], a[j]);
}

void BubleSort(int a[], int n) {
    int i, j;
    for (i = 1; i < n; i++)
        for (j = n; j > i; j--)
            if (a[j] < a[j - 1]) hoanvi(a[j], a[j - 1]);
}

void ShakeSort(int a[], int n) {
    int i, j, left, right, k;
    left = 0; right = n - 1; k = n - 1;
    while (left < right) {
        for (j = right; j > left; j--)
            if (a[j] < a[j - 1]) { hoanvi(a[j], a[j - 1]); k = j; }
        left = k;
        for (j = left; j < right; j++)
            if (a[j] > a[j + 1]) { hoanvi(a[j], a[j - 1]); k = j; }
        right = k;
    }
}

void Shift(int a[], int left, int right) {
    int x, curr, joint;
    curr = left; joint = 2 * curr;
    x = a[curr];
    while (joint <= right) {
        if (joint < right)
            if (a[joint] < a[joint + 1]) joint = joint + 1;
        if (a[joint] < x) break;
        else {
            a[curr] = a[joint];
            curr = joint;
            joint = 2 * curr;
        }
        a[curr] = x;
    }
}

void CreateHeap(int a[], int N) {
    int left;
    for (left = (N) / 2; left >= 1; left--)
        Shift(a, left, N);
}

void Heapsort(int a[], int N) {
    int right;
    CreateHeap(a, N);
    right = N;
    while (right > 1) {
        hoanvi(a[1], a[right]);
        right--;
        Shift(a, 1, right);
    }
}

void Sellsort(int a[], int n) {
    int h[] = {5, 3, 1};
    int k = 3, step, i, j, x, len;
    for (step = 0; step < k; step++) {
        len = h[step];
        for (i = len; i <= n; i++) {
            x = a[i]; j = i - len;
            while ((x < a[j]) && (j >= 1)) { a[j + len] = a[j]; j = j - len; }
            a[j + len] = x;
        }
    }
}

void Quicksort(int a[], int l, int r) {
    int i, j, x;
    x = a[(l + r) / 2];
    i = l; j = r;
    do {
        while (a[i] < x) i++;
        while (a[j] > x) j--;
        if (i <= j) { hoanvi(a[i], a[j]); i++; j--; }
    } while (i < j);
    if (l < j) Quicksort(a, l, j);
    if (i < r) Quicksort(a, i, r);
}

int min(int a, int b) { return a < b ? a : b; }

void Merge(int a[], int nb, int nc, int k) {
    int p, pb, pc, ib, ic, kb, kc;
    p = pb = pc = 0; ib = ic = 0;
    while ((0 < nb) && (0 < nc)) {
        kb = min(k, nb); kc = min(k, nc);
        if (b[pb + ib] <= c[pc + ic]) {
            a[p++] = b[pb + ib]; ib++;
            if (ib == kb) {
                for (; ic < kc; ic++) a[p++] = c[pc + ic];
                pb += kb; pc += kc; ib = ic = 0;
                nb -= kb; nc -= kc;
            }
        } else {
            a[p++] = c[pc + ic]; ic++;
            if (ic == kc) {
                for (; ib < kb; ib++) a[p++] = b[pb + ib];
                pb += kb; pc += kc; ib = ic = 0;
                nb -= kb; nc -= kc;
            }
        }
    }
}

void mergesort(int a[], int n) {
    int p, pb, pc, i, k = 1;
    do {
        p = pb = pc = 0;
        while (p < n) {
            for (i = 0; (p <= n) && (i < k); i++) b[pb++] = a[p++];
            for (i = 0; (p <= n) && (i < k); i++) c[pc++] = a[p++];
        }
        Merge(a, pb, pc, k);
        k *= 2;
    } while (k <= n);
}

int main() {
    int x, vitri;
    printf("\n nhap so phan tu:"); scanf("%d", &n);
    nhap(a, n);
    printf("\n day so da nhap la:"); xuat(a, n);
    printf("\n nhap khoa can tim:"); scanf("%d", &x);
    vitri = LinearSearch(a, n, x);
    if (vitri == -1) printf("Khong tim thay %d", x);
    else printf("%d xuat hien tai vi tri %d", x, vitri);
    getch();
}
```

---

## Bài số 2: Sắp xếp ngoài

### Phương pháp trộn Run

```c
#include "stdio.h"
#include "conio.h"

int p, n;

void tao_file(void) {
    int i, x; FILE *fp;
    fp = fopen("D:\\Bang.txt", "wb");
    printf("Cho biet so phan tu : "); scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Nhap so thu %d : ", i + 1); scanf("%d", &x);
        fprintf(fp, "%3d", x);
    }
    fclose(fp);
}

void xuat_file(void) {
    int x; FILE *fp;
    fp = fopen("D:\\Bang.txt", "rb");
    int i = 0;
    while (i < n) { fscanf(fp, "%d", &x); printf("%3d", x); i++; }
    fclose(fp);
}

void chia(FILE *a, FILE *b, FILE *c, int p) {
    int dem, x;
    a = fopen("D:\\Bang.txt", "rb");
    b = fopen("D:\\Bang1.txt", "wb");
    c = fopen("D:\\Bang2.txt", "wb");
    while (!feof(a)) {
        dem = 0;
        while ((dem < p) && (!feof(a))) { fscanf(a, "%3d", &x); fprintf(b, "%3d", x); dem++; }
        dem = 0;
        while ((dem < p) && (!feof(a))) { fscanf(a, "%3d", &x); fprintf(c, "%3d", x); dem++; }
    }
    fclose(a); fclose(b); fclose(c);
}

void tron(FILE *b, FILE *c, FILE *a, int p) {
    int stop, x, y, l, r;
    a = fopen("D:\\Bang.txt", "wb");
    b = fopen("D:\\Bang1.txt", "rb");
    c = fopen("D:\\Bang2.txt", "rb");
    while ((!feof(b)) && (!feof(c))) {
        l = 0; r = 0;
        fscanf(b, "%3d", &x); fscanf(c, "%3d", &y); stop = 0;
        while ((l != p) && (r != p) && (!stop)) {
            if (x < y) {
                fprintf(a, "%3d", x); l++;
                if ((l < p) && (!feof(b))) fscanf(b, "%3d", &x);
                else { fprintf(a, "%3d", y); r++; if (feof(b)) stop = 1; }
            } else {
                fprintf(a, "%3d", y); r++;
                if ((r < p) && (!feof(c))) fscanf(c, "%3d", &y);
                else { fprintf(a, "%3d", x); l++; if (feof(c)) stop = 1; }
            }
        }
        while ((!feof(b)) && (l < p)) { fscanf(b, "%3d", &x); fprintf(a, "%3d", x); l++; }
        while ((!feof(c)) && (r < p)) { fscanf(c, "%3d", &y); fprintf(a, "%3d", y); r++; }
    }
    if (!feof(b)) while (!feof(b)) { fscanf(b, "%3d", &x); fprintf(a, "%3d", x); }
    if (!feof(c)) while (!feof(c)) { fscanf(c, "%3d", &x); fprintf(a, "%3d", x); }
    fclose(a); fclose(b); fclose(c);
}

int main(void) {
    FILE *a, *b, *c;
    tao_file();
    printf("\n Tap tin nhap:"); xuat_file();
    p = 1;
    while (p < n) { chia(a, b, c, p); tron(b, c, a, p); p = 2 * p; }
    printf("\n Tap tin da sap xep:"); xuat_file();
    getch();
}
```

### Phương pháp trộn tự nhiên

```c
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

typedef int DataType;
FILE *F0, *F1, *F2;
int M, N, Eor;
DataType X1, X2, X, Y;

void CreatFile(FILE *Ft, int Num) {
    srand(time(NULL));
    Ft = fopen("e:\\bang.txt", "wb");
    for (int i = 0; i < Num; i++) { X = rand() % (30); fprintf(Ft, "%3d", X); }
    fclose(Ft);
}

void ListFile(FILE *Ft) {
    DataType X, I = 0;
    Ft = fopen("e:\\bang.txt", "rb");
    while (!feof(Ft)) { fscanf(Ft, "%3d", &X); printf("%3d", X); I++; }
    printf("\n\n"); fclose(Ft);
}

void Copy(FILE *Fi, FILE *Fj) {
    fscanf(Fi, "%3d", &X); fprintf(Fj, "%3d", X);
    if (!feof(Fi)) {
        fscanf(Fi, "%3d", &Y);
        long curpos = ftell(Fi) - 2;
        fseek(Fi, curpos, SEEK_SET);
    }
    if (feof(Fi)) Eor = 1;
    else Eor = (X > Y) ? 1 : 0;
}

void CopyRun(FILE *Fi, FILE *Fj) { do Copy(Fi, Fj); while (!Eor); }

void Distribute() {
    do {
        CopyRun(F0, F1);
        if (!feof(F0)) CopyRun(F0, F2);
    } while (!feof(F0));
    fclose(F0); fclose(F1); fclose(F2);
}

void MergeRun() {
    do {
        fscanf(F1, "%3d", &X1); long curpos = ftell(F1) - 2; fseek(F1, curpos, SEEK_SET);
        fscanf(F2, "%3d", &X2); curpos = ftell(F2) - 2; fseek(F2, curpos, SEEK_SET);
        if (X1 <= X2) { Copy(F1, F0); if (Eor) CopyRun(F2, F0); }
        else { Copy(F2, F0); if (Eor) CopyRun(F1, F0); }
    } while (!Eor);
}

void Merge() {
    while ((!feof(F1)) && (!feof(F2))) { MergeRun(); M++; }
    while (!feof(F1)) { CopyRun(F1, F0); M++; }
    while (!feof(F2)) { CopyRun(F2, F0); M++; }
    fclose(F0); fclose(F1); fclose(F2);
}

int main() {
    printf(" Nhap so phan tu: "); scanf("%d", &N);
    CreatFile(F0, N);
    printf("\n Noi dung file goc:"); ListFile(F0);
    do {
        F0 = fopen("e:\\bang.txt", "rb"); F1 = fopen("e:\\bang1.txt", "wb"); F2 = fopen("e:\\bang2.txt", "wb");
        Distribute();
        F0 = fopen("e:\\bang.txt", "wb"); F1 = fopen("e:\\bang1.txt", "rb"); F2 = fopen("e:\\bang2.txt", "rb");
        M = 0; Merge();
    } while (M != 1);
    printf("\n Noi dung file da sap xep:"); ListFile(F0);
    getch(); return 0;
}
```

---

## Bài số 3: Danh sách liên kết

```cpp
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

typedef struct sinhvien { char maso[10]; char hoten[50]; int tuoi; } sinhvien;
typedef struct node { sinhvien data; node *pnext; } node;
typedef struct list { node *phead; node *ptail; } list;

void khoitao(list &l) { l.phead = l.ptail = NULL; }

node *taonut() {
    node *p; sinhvien sv;
    p = new(node);
    if (p != NULL) {
        printf("\nNhap ma so:"); fflush(stdin); gets(sv.maso);
        printf("\nNhap ho ten:"); fflush(stdin); gets(sv.hoten);
        printf("\nNhap tuoi:"); scanf("%d", &sv.tuoi);
        p->data = sv; p->pnext = NULL; return p;
    }
    return NULL;
}

void addtail(list &l, node *new_ele) {
    if (l.phead == NULL) { l.phead = new_ele; l.ptail = l.phead; }
    else { l.ptail->pnext = new_ele; l.ptail = new_ele; }
}

void addfirst(list &l, node *new_ele) {
    if (l.phead == NULL) { l.phead = new_ele; l.ptail = l.phead; }
    else { new_ele->pnext = l.phead; l.phead = new_ele; }
}

node *timvitri(list l) {
    char ma[10]; node *q;
    printf("\nNhap ma so can tim :"); fflush(stdin); gets(ma);
    q = l.phead;
    while (q != NULL) {
        if (strcmp(ma, q->data.maso) == 0) return q;
        else q = q->pnext;
    }
    return NULL;
}

void addafter(list &l, node *q, node *new_ele) {
    if (q != NULL) {
        new_ele->pnext = q->pnext; q->pnext = new_ele;
        if (q == l.ptail) l.ptail = new_ele;
    } else addfirst(l, new_ele);
}

void taods(list &l) {
    int n; node *p;
    printf("\nnhap so phan tu:"); scanf("%d", &n);
    for (int i = 1; i <= n; i++) { p = taonut(); addfirst(l, p); }
}

void duyetds(list l) {
    node *p = l.phead;
    printf("\nMa so  || Ho ten ||Tuoi");
    while (p != NULL) { printf("\n %s %s %d", p->data.maso, p->data.hoten, p->data.tuoi); p = p->pnext; }
}

sinhvien removehead(list &l) {
    node *p; sinhvien x;
    if (l.phead != NULL) {
        p = l.phead; x = p->data; l.phead = l.phead->pnext; delete p;
        if (l.phead == NULL) l.ptail = NULL;
    }
    return x;
}

void removeafter(list &l, node *q) {
    node *p;
    if (q != NULL) {
        p = q->pnext;
        if (p != NULL) { if (p == l.ptail) l.ptail = q; q->pnext = p->pnext; delete p; }
    } else removehead(l);
}

void remove(list &l, char ma[]) {
    node *p, *q; p = l.phead;
    while ((p != NULL) && (strcmp(p->data.maso, ma) != 0)) { q = p; p = p->pnext; }
    if (p == NULL) printf("\n Sinh vien khong co trong danh sach");
    else if (p == l.phead) { l.phead = p->pnext; delete(p); }
    else { q->pnext = p->pnext; delete(p); }
}

void Interchange(list &l) {
    for (node *p = l.phead; p != l.ptail; p = p->pnext)
        for (node *q = p->pnext; q != NULL; q = q->pnext)
            if (p->data.tuoi > q->data.tuoi) { sinhvien a; a = p->data; p->data = q->data; q->data = a; }
}

void noids(list &l, list &l2) {
    if (l2.phead == NULL) return;
    if (l.phead == NULL) { l.phead = l2.phead; l.ptail = l2.ptail; }
    else { l.ptail->pnext = l2.phead; l.ptail = l2.ptail; }
    khoitao(l2);
}

void quicksort(list &l) {
    node *x, *p; list l1, l2;
    if (l.phead == l.ptail) return;
    khoitao(l1); khoitao(l2);
    x = l.phead; l.phead = x->pnext; x->pnext = NULL;
    while (l.phead != NULL) {
        p = l.phead; l.phead = p->pnext;
        if (atoi(p->data.maso) < atoi(x->data.maso)) addtail(l1, p);
        else addtail(l2, p);
    }
    quicksort(l1); quicksort(l2);
    noids(l, l1); addtail(l, x); noids(l, l2);
}

int main() {
    list l; node *q, *new_ele; char ma[10];
    khoitao(l); taods(l);
    printf("\n Danh nhap la:"); duyetds(l);
    getch();
}
```

---

## Bài 4: Cấu trúc ngăn xếp (Stack)

### Stack cài đặt bằng mảng

```cpp
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define N 20

typedef struct node { long maso; char hoten[40]; char diachi[100]; } node;
typedef struct stack { int top; node list[N]; } stack;

void khoitao(stack &s) { s.top = -1; }
int empty(stack s) { return s.top == -1 ? 1 : 0; }
int full(stack s) { return s.top == N - 1 ? 1 : 0; }
void push(stack &s, node x) { if (!full(s)) s.list[++s.top] = x; }
node pop(stack &s) { node x; if (!empty(s)) x = s.list[s.top--]; return x; }

int main() {
    int n; stack s; node x;
    printf("\n nhap vao so phan tu:"); scanf("%d", &n);
    khoitao(s);
    for (int i = 0; i < n; i++) {
        printf("\n nhap ma so:"); scanf("%d", &x.maso);
        printf("\n nhap ho ten:"); fflush(stdin); gets(x.hoten);
        printf("\n nhap dia chi :"); fflush(stdin); gets(x.diachi);
        push(s, x);
    }
    while (!empty(s)) {
        x = pop(s);
        printf("\nMa so:%d Ho ten:%s Dia chi:%s", x.maso, x.hoten, x.diachi);
    }
}
```

### Stack cài đặt bằng danh sách liên kết

```cpp
#include <stdio.h>
#include<conio.h>

typedef struct sinhvien { char hoten[40]; int tuoi; } sinhvien;
typedef struct node { sinhvien data; node *link; } node;
typedef struct stack { node *top; } stack;

void khoitao(stack &s) { s.top = NULL; }
int empty(stack s) { return s.top == NULL ? 1 : 0; }

void push(stack &s, sinhvien x) {
    node *p = new(node);
    p->data = x; p->link = s.top; s.top = p;
}

sinhvien pop(stack &s) {
    node *p;
    if (!empty(s)) p = s.top;
    s.top = p->link;
    return p->data;
}

int main() {
    int n; stack s; sinhvien x;
    printf("\nnhap vao so phan tu:"); scanf("%d", &n);
    khoitao(s);
    for (int i = 0; i < n; i++) {
        printf("\nnhap ho ten:"); fflush(stdin); gets(x.hoten);
        printf("\nnhap tuoi:"); scanf("%d", &x.tuoi);
        push(s, x);
    }
    while (!empty(s)) {
        x = pop(s);
        printf("\nho ten :%s", x.hoten);
        printf("\ntuoi:%d", x.tuoi);
    }
    getch();
}
```

---

## Bài 5: Cấu trúc hàng đợi (Queue)

### Queue cài đặt bằng mảng

```cpp
#include"stdio.h"
#include"conio.h"
#define N 20

typedef struct node { char hoten[40]; int tuoi; } node;
typedef struct Queu { int front, rear; node list[N]; } Queu;

void khoitao(Queu &q) { q.front = q.rear = -1; }
int empty(Queu q) { return (q.front == -1 && q.rear == -1) ? 1 : 0; }
int full(Queu q) {
    if (q.front == 0 && q.rear == N - 1) return 1;
    if (q.front == q.rear + 1) return 1;
    return 0;
}

void enqueu(Queu &q, node x) {
    if (!full(q)) {
        if (empty(q)) q.front = q.rear = 0;
        else if (q.rear == N - 1) q.rear = 0;
        else q.rear = q.rear + 1;
        q.list[q.rear] = x;
    }
}

node dequeu(Queu &q) {
    if (!empty(q)) {
        node t = q.list[q.front];
        if (q.front == q.rear) khoitao(q);
        else if (q.front == N - 1) q.front = 0;
        else q.front = q.front + 1;
        return t;
    }
}

int main() {
    int n; node x; Queu q;
    printf("nhap so phan tu:"); scanf("%d", &n);
    khoitao(q);
    for (int i = 1; i <= n; i++) {
        printf("nhap ho ten:"); fflush(stdin); gets(x.hoten);
        printf("nhap tuoi:"); scanf("%d", &x.tuoi);
        enqueu(q, x);
    }
    while (!empty(q)) {
        x = dequeu(q);
        printf("\n hoten:%s", x.hoten);
        printf("\n tuoi:%d", x.tuoi);
    }
    getch();
}
```

### Queue cài đặt bằng danh sách liên kết

```cpp
#include<stdio.h>
#include<conio.h>
#define N 20

typedef struct sinhvien { char hoten[40]; int tuoi; } sinhvien;
typedef struct node { sinhvien data; node *link; } node;
typedef struct queu { node *front; node *rear; } queu;

void khoitao(queu &q) { q.front = q.rear = NULL; }
int empty(queu q) { return q.front == NULL ? 1 : 0; }

void enqueu(queu &q, node *new_ele) {
    if (q.front == NULL) { q.front = new_ele; q.rear = q.front; }
    else { q.rear->link = new_ele; q.rear = new_ele; }
}

sinhvien dequeu(queu &q) {
    node *p; sinhvien x;
    if (!empty(q)) { p = q.front; x = p->data; q.front = p->link; delete(p); }
    return x;
}

int main() {
    int n; sinhvien x; queu q; node *new_ele;
    printf("\n nhap so phan tu:"); scanf("%d", &n);
    khoitao(q);
    for (int i = 1; i <= n; i++) {
        printf("\n nhap hoten:"); fflush(stdin); gets(x.hoten);
        printf("\n nhap tuoi:"); scanf("%d", &x.tuoi);
        new_ele = new(node); new_ele->data = x; new_ele->link = NULL;
        enqueu(q, new_ele);
    }
    while (!empty(q)) {
        x = dequeu(q);
        printf("\n hoten:%s", x.hoten);
        printf("\n tuoi:%d", x.tuoi);
    }
    getch();
}
```

---

## Bài 6: Cấu trúc cây nhị phân

```cpp
#include"stdio.h"
#include"conio.h"
#include"string.h"

typedef struct sv { char hoten[40]; int tuoi; } sv;
typedef struct node { sv data; node *left; node *right; } node;
typedef struct node *TREE;
TREE root;

void taocay(TREE &root) {
    sv x;
    printf("\n nhap ho ten:"); fflush(stdin); gets(x.hoten);
    if (strcmp(x.hoten, "n") != 0) { printf("\n nhap tuoi:"); scanf("%d", &x.tuoi); }
    if (strcmp(x.hoten, "n") != 0) {
        root = new(node); root->data = x;
        printf("\n cay con trai cua:%s", x.hoten); taocay(root->left);
        printf("\n cay con phai cua:%s", x.hoten); taocay(root->right);
    } else root = NULL;
}

void NLR(TREE root) {
    if (root != NULL) {
        printf("\n ho ten:%s", root->data.hoten); printf("\n tuoi:%d", root->data.tuoi);
        NLR(root->left); NLR(root->right);
    }
}

void LRN(TREE root) {
    if (root != NULL) { LRN(root->left); LRN(root->right); printf("\n ho ten:%s tuoi:%d", root->data.hoten, root->data.tuoi); }
}

void LNR(TREE root) {
    if (root != NULL) { LNR(root->left); printf("\n ho ten:%s tuoi:%d", root->data.hoten, root->data.tuoi); LNR(root->right); }
}

int max(int a, int b) { return a > b ? a : b; }
int chieucao(TREE root) { return root == NULL ? 0 : max(chieucao(root->left), chieucao(root->right)) + 1; }

int demla(TREE r) {
    int dem = 0;
    if (r == NULL) return 0;
    if ((r->left == NULL) && (r->right == NULL)) dem++;
    return (demla(r->left) + demla(r->right) + dem);
}

int main() {
    TREE t; taocay(t);
    printf("\n duyet cay theo thu tu truoc:"); NLR(t);
    printf("\n duyet cay theo thu tu sau:"); LRN(t);
    printf("\n duyet cay theo thu tu giua:"); LNR(t);
    printf("\n So nut la: %d", demla(t));
    getch();
}
```

---

## Bài 7: Cây nhị phân tìm kiếm (BST)

```cpp
#include"stdio.h"
#include"conio.h"
#include"string.h"

typedef struct sinhvien { char hoten[40]; int tuoi; } sv;
typedef struct node { sv data; node *left; node *right; } node;
typedef struct node *TREE;
TREE root;

void khoitao(TREE &root) { root = NULL; }

void chennode(TREE &root, sv x) {
    if (root != NULL) {
        if (strcmp(root->data.hoten, x.hoten) == 0) return;
        if (root->data.tuoi > x.tuoi) chennode(root->left, x);
        else chennode(root->right, x);
    } else {
        root = new(node); root->data = x; root->left = root->right = NULL;
    }
}

void taocay(TREE &root) {
    int n; sv x;
    printf("\n nhap so sv:"); scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        printf("\n nhap ho ten:"); fflush(stdin); gets(x.hoten);
        printf("\n nhap tuoi:"); scanf("%d", &x.tuoi);
        chennode(root, x);
    }
}

void NLR(TREE root) { if (root != NULL) { printf("\n ho ten:%s tuoi:%d", root->data.hoten, root->data.tuoi); NLR(root->left); NLR(root->right); } }
void LRN(TREE root) { if (root != NULL) { LRN(root->left); LRN(root->right); printf("\n ho ten:%s tuoi:%d", root->data.hoten, root->data.tuoi); } }
void LNR(TREE root) { if (root != NULL) { LNR(root->left); printf("\n ho ten:%s tuoi:%d", root->data.hoten, root->data.tuoi); LNR(root->right); } }

int max(int a, int b) { return a > b ? a : b; }
int chieucao(TREE root) { return root == NULL ? 0 : max(chieucao(root->left), chieucao(root->right)) + 1; }

node *tim(TREE root, sv x) {
    if (root != NULL) {
        if (root->data.tuoi == x.tuoi) return root;
        if (root->data.tuoi > x.tuoi) return tim(root->left, x);
        return tim(root->right, x);
    }
    return NULL;
}

void timthaythe(TREE &p, TREE &q) {
    if (q->right != NULL) timthaythe(p, q->right);
    else { p->data = q->data; p = q; if (q->left != NULL) q = q->left; else q = q->right; }
}

void huy(TREE &root, sv x) {
    if (root == NULL) return;
    if (root->data.tuoi > x.tuoi) huy(root->left, x);
    if (root->data.tuoi < x.tuoi) huy(root->right, x);
    if (root->data.tuoi == x.tuoi) {
        node *p = root;
        if (root->left == NULL) root = root->right;
        else if (root->right == NULL) root = root->left;
        else timthaythe(p, root->left);
        delete(p);
    }
}

int main() {
    TREE t; sv x, y, z;
    khoitao(t); taocay(t);
    printf("\n duyet cay theo thu tu truoc:"); NLR(t);
    printf("\n duyet cay theo thu tu sau:"); LRN(t);
    printf("\n duyet cay theo thu tu giua:"); LNR(t);
    printf("\n chieu cao cay la:%d", chieucao(t));
    printf("\n sv can xoa co tuoi la: "); scanf("%d", &z.tuoi);
    huy(t, z);
    printf("\n cay sau khi xoa:"); NLR(t);
    getch();
}
```

---

## Bài 8: Cấu trúc cây đa phân (B-Cây)

```c
#include <stdio.h>
#include <conio.h>
#define M 5

struct node {
    int n;
    int keys[M-1];
    struct node *p[M];
} *root = NULL;

enum KeyStatus { Duplicate, SearchFailure, Success, InsertIt, LessKeys };

void insert(int key);
void display(struct node *root, int);
void DelNode(int x);
void search(int x);
enum KeyStatus ins(struct node *r, int x, int *y, struct node **u);
int searchPos(int x, int *key_arr, int n);
enum KeyStatus del(struct node *r, int x);

int main() {
    int key, choice;
    printf("TAO B CAY BAC %d:\n", M);
    while (choice != 5) {
        printf("1.Chen nut\n2.Xoa nut\n3.Tim khoa\n4.Duyet cay\n5.Thoat\n");
        printf("Chon chuc nang:"); scanf("%d", &choice);
        switch (choice) {
            case 1: printf("Nhap vao khoa:"); scanf("%d", &key); insert(key); break;
            case 2: printf("Nhap vao khoa:"); scanf("%d", &key); DelNode(key); break;
            case 3: printf("Nhap vao khoa:"); scanf("%d", &key); search(key); break;
            case 4: printf("B cay da nhap:\n"); display(root, 0); break;
            case 5: break;
            default: printf("Nhap sai chuc nang!\n");
        }
    }
}

// (Các hàm insert, ins, display, search, searchPos, DelNode, del — xem mã nguồn đầy đủ trong tài liệu gốc)
```

---

## Bài 9: Cấu trúc bảng băm

### Băm tuyến tính

```c
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "time.h"
#define TRUE 1
#define FALSE 0
#define NULLKEY -1
#define M 10

struct node { int key; };
struct node hashtable[M];
int N;

int hashfunc(int key) { return (key % M); }
void initialize() { for (int i = 0; i < M; i++) hashtable[i].key = NULLKEY; N = 0; }
int empty() { return (N == 0 ? TRUE : FALSE); }
int full() { return (N == M - 1 ? TRUE : FALSE); }

int search(int k) {
    int i = hashfunc(k);
    while (hashtable[i].key != k && hashtable[i].key != NULLKEY) {
        i = i + 1; if (i >= M) i = i - M;
    }
    return hashtable[i].key == k ? i : M;
}

int insert(int k) {
    if (full()) { printf("Bang bam bi day"); return 0; }
    if (search(k) < M) { printf("So nay da co trong bang bam"); return 0; }
    int i = hashfunc(k);
    while (hashtable[i].key != NULLKEY) { i++; if (i >= M) i -= M; }
    hashtable[i].key = k; N++; return i;
}

void viewtable() { for (int i = 0; i < M; i++) printf("\nTable[%2d] : %4d", i, hashtable[i].key); }

int main() {
    int key, chucnang;
    initialize();
    do {
        printf("\n1.Them nut\n2.Them ngau nhien\n3.Xoa nut\n4.Xoa bang\n5.Xem bang\n6.Tim kiem\n0.Ket thuc\n");
        printf("Chuc nang: "); scanf("%d", &chucnang);
        switch (chucnang) {
            case 1: printf("Khoa moi: "); scanf("%d", &key); insert(key); break;
            case 5: viewtable(); break;
            case 6: printf("Khoa can tim: "); scanf("%d", &key);
                if (search(key) == M) printf("\nKhong tim thay");
                else printf("Tim thay tai dia chi %d", search(key)); break;
        }
    } while (chucnang != 0);
}
```

### Băm kép

```c
// Tương tự băm tuyến tính, thêm hàm băm thứ hai:
int hashfunc2(int key) { return (M - (key % M)); }

// Trong search và insert, thay i = i + 1 bằng:
// i = (i + j) % M;  (với j = hashfunc2(k))
```

### Băm nối kết (Từ điển)

```c
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#define M 26

typedef struct tudien { char tu[10]; char nghia[100]; } tudien;
typedef struct node { tudien data; node *link; } node;
node bucket[M];

int hambam(char tu[]) { char ch = toupper(tu[0]); return ((ch - 65) % M); }
void khoitao(node bucket[]) { for (int i = 0; i < M; i++) bucket[i].link = NULL; }

void themtu(tudien x) {
    node *p; int i = hambam(x.tu);
    p = new(node); p->data = x; p->link = bucket[i].link; bucket[i].link = p;
}

node *timtu(char tu[]) {
    int i = hambam(tu); node *p = bucket[i].link;
    while (p != NULL) { if (strcmp(p->data.tu, tu) == 0) return p; p = p->link; }
    return NULL;
}

void intudien() {
    for (int i = 0; i < M; i++) {
        node *p = bucket[i].link;
        printf("\nDanh muc tu %c:", i + 65);
        while (p != NULL) { printf("\n Tu: %s  nghia: %s", p->data.tu, p->data.nghia); p = p->link; }
    }
}
```

---

## Bài 10: Ứng dụng giải thuật

### Ứng dụng sắp xếp ngoài (Quản lý sinh viên từ file)

```c
// Quản lý file SinhVien.Dat với cấu trúc:
typedef struct { char Maso[10]; char HoTen[40]; } SinhVien;

// Các chức năng:
// WriteFile  — nhập và ghi sinh viên vào file
// ReadFile   — đọc và hiển thị danh sách
// Search     — tìm kiếm theo mã số
// Delete     — xóa sinh viên theo mã số
// sort       — sắp xếp file theo mã số (trộn tự nhiên)
```

### Ứng dụng Stack tính tổ hợp C(n, k)

```cpp
#include <stdio.h>
#include <conio.h>

typedef struct Trangthai { int n; int k; } Trangthai;
typedef struct node { Trangthai data; node *link; } node;
typedef struct stack { node *top; } stack;

void Init(stack &s) { s.top = NULL; }
int Empty(stack s) { return s.top == NULL ? 1 : 0; }

void Push(stack &s, Trangthai x) {
    node *p = new(node); p->data = x; p->link = s.top; s.top = p;
}

Trangthai Pop(stack &s) {
    node *p;
    if (!Empty(s)) p = s.top;
    s.top = p->link;
    return p->data;
}

long Combo(int n, int k) {
    stack st; long TH = 0;
    Trangthai tt, tt1, tt2;
    Init(st); tt = {n, k}; Push(st, tt);
    while (!Empty(st)) {
        tt = Pop(st);
        if (tt.k == 0 || tt.n == tt.k) TH++;
        if (tt.k > 0 && tt.n > tt.k) {
            tt1 = {tt.n - 1, tt.k - 1}; Push(st, tt1);
            tt2 = {tt.n - 1, tt.k};     Push(st, tt2);
        }
    }
    return TH;
}

int main() {
    int n, k;
    printf("\n Nhap vao n:"); scanf("%d", &n);
    printf("\n Nhap vao k:"); scanf("%d", &k);
    printf("\n Ket qua:%ld", Combo(n, k));
    getch();
}
```

### Ứng dụng Queue phân loại sinh viên theo giới tính

```cpp
// Đọc file sinhvien.dat, phân vào 2 queue theo trường Phai ("nu" / khác)
// Ghi kết quả ra:
//   sinhviennu.dat  — sinh viên nữ
//   sinhviennam.dat — sinh viên nam
```

---

## Ghi chú

- Compiler: **Turbo C++ / Dev-C++** (cần `conio.h`, `getch()`)
- Đường dẫn file (`D:\`, `E:\`) cần chỉnh lại cho phù hợp máy thực tế
- Hàm `gets()` và `fflush(stdin)` là phong cách C cũ, có thể thay bằng `fgets()` cho an toàn hơn
