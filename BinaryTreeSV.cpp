#include <stdio.h>
#include <stdlib.h>

typedef struct sinhvien{
	char mssv[20];
	char hoten[50];
	int tuoi;
}sinhvien;

typedef struct node{
	sinhvien *data;
	struct node *left;
	struct node *right; 
}node;

sinhvien *nhap(){
	sinhvien *newdata=((sinhvien*)malloc(sizeof(sinhvien)));
	if(newdata==NULL){
		exit (0);
	}
	printf("Nhap mssv: ");
	gets(newdata->mssv);
	printf("Nhap ho va ten: ");
	gets(newdata->hoten);
	printf("Nhap tuoi: ");
	scanf("%d",&newdata->tuoi);
	printf("\n");
	return newdata;
}

node *create(sinhvien *value){
	node *newnode=((node*)malloc(sizeof(node)));
	if (newnode==NULL){
		exit (0);
	}
	newnode->data=value;
	newnode->left=newnode->right=NULL;
	return newnode;
}

node *insert(node *root, sinhvien *value){
	if(root == NULL){
		return create(value);
	}else{
		if((atoi(value->mssv)) < atoi(root->data->mssv)){
			root->left=insert(root->left,value);
		}else{
			if((atoi(value->mssv)) > atoi(root->data->mssv)){
				root->right=insert(root->right,value);
			}
		}
		return root;
	}
}

void LNR(node *root){
	if (root!=NULL){
		sinhvien *p=root->data;
		LNR(root->left);
		printf("%s	%s	%d\n",p->mssv,p->hoten,p->tuoi);
		LNR(root->right);
	}
}

node *findnode(node *root){
	node *cur=root;
	while(cur && cur->left!=NULL){
		cur=cur->left;
	}
	return cur;
}

node *del(node *root, const char *x){
	if (root == NULL){
		return root;
	}else{
		if((atoi(x)) < atoi(root->data->mssv)){
			root->left=del(root->left,x);
		}else{
			if((atoi(x)) > atoi(root->data->mssv)){
				root->right=del(root->right,x);
			}else{
				if(root->left == NULL){
					node *temp=root->right;
					free(root->data);
					free(root);
					return temp;
				}else{
					if(root->right == NULL){
						node *temp=root->left;
						free(root->data);
						free(root);
						return temp;
					}
				}
				
				node *temp=findnode(root->right);
				root->data=temp->data;
				root->right = del(root->right,temp->data->mssv);
			}
		}
	}
	return root;
}


int main(){
	int n,m;
	char z[20];
	sinhvien *data=NULL;
	node *root=NULL;

	printf("Nhap so sinh vien: ");
	scanf("%d",&n);
	
	for (int i=0; i<n; i++){
		fflush(stdin);
		data = nhap();
		root = insert(root, data);
	}
	LNR(root);
	printf("\n");
	
	printf("Nhap so sinh vien can xoa: ");
	scanf("%d",&m);
	printf("\n");
	for (int i=0;i<m;i++){
		fflush(stdin);
		printf("Nhap mssv can xoa: ");
		gets(z);
		root = del(root, z);
		LNR(root);
		printf("\n");	
	}
	return 0;
}
