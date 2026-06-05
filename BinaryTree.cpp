#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node *right;
	struct node *left;
}node;

node *create(int value){
	node *newnode=((node*)malloc(sizeof(node)));
	if(newnode!=NULL){
		newnode->data=value;
		newnode->right=newnode->left=NULL;
	}
	return newnode;
}

node *insert(node *newnode,int value){
	if (newnode==NULL){
		newnode=create(value);
	}else{
		if(newnode->data>value){
			newnode->left=insert(newnode->left,value);
		}else{
			newnode->right=insert(newnode->right,value);
		}
	}
	return newnode;
}

void LNR(node *root){
	if (root!=NULL){
		LNR(root->left);
		printf("%d",root->data);
		LNR(root->right);
	}
}

void NLR(node *root){
	if (root!=NULL){
		printf("%d",root->data);
		NLR(root->left);
		NLR(root->right);
	}
}

void LRN(node *root){
	if (root!=NULL){
		LRN(root->left);
		LRN(root->right);
		printf("%d",root->data);
	}
}

int countnode(node *root){
	if(root!=NULL){
		return 1 + countnode(root->left) + countnode(root->right);
	}
	return 0;
}

int treeheight(node *root){
	if(root==NULL){
		return 0;
	}
	int leftheight=treeheight(root->left);
	int rightheight=treeheight(root->right);
	if(leftheight>rightheight){
		return leftheight+1;
	}else{
		return rightheight+1;
	}
}

int CountLeaves(node *root){
	if(root==NULL){
		return 0;
	}
	if(root->left==NULL&&root->right==NULL){
		return 1;
	}
	return CountLeaves(root->left) + CountLeaves(root->right);
}

node *findnode(node *root){
	if(root->left==NULL){
		return root;
	}
	return findnode(root->left);
}


node *del(node *root, int x){
	if(root==NULL){
		return root;
	}
	if(x<root->data){
		root->left=del(root->left, x);
	}else{
		if(x>root->data){
			root->right=del(root->right, x);
		}else{
			if(root->left==NULL){
				node *temp=root->right;
				free (root);
				return temp;
			}else{
				if(root->right==NULL){
					node *temp=root->left;
					free (root);
					return temp;
				}
			}
			node *temp=findnode(root->right);
			root->data=temp->data;
			root->right=del(root->right,temp->data);
		}
	}
	return root;
}

void thaotac(node *root){
	LNR(root);
	printf("\n");
	NLR(root);
	printf("\n");
	LRN(root);
	printf("\n");
	printf("Co %d node trong cay\n",countnode(root));
	printf("Cay nhi phan co bac la %d\n",treeheight(root));
	printf("Cay co %d nut la\n",CountLeaves(root));
}

int main(){
	int n, m, x, value;
	node *root=NULL;
	printf("Nhap n: ");
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&value);
		root=insert(root,value);
	}
	printf("Cay nhi phan ban dau:\n");
	thaotac(root);
	
	printf("Nhap so node can xoa: ");
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		printf("Nhap gia tri thu %d can xoa: ",i);
		scanf("%d",&x);
		root=del(root,x);
		printf("Cay nhi phan sau khi xoa lan %d\n",i);
		thaotac(root);
		printf("\n");
	}
	
	return 0;
}
