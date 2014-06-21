
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ZuPuTree.h"

#define MAXOFCHILD 10 //���������ӵ����ֵ


enum boolean {False,True};//����ö������

typedef struct Date {
	
	int year;//��

	int month;//��

	int date;//��

} Date;


/*
 *���׵Ľ�����Ϣ
 **/
typedef struct member {

	int id;//����������Ψһ��ʾĳ����Ա

	char name[20];//����
	
	char address[50];//סַ

	enum boolean isExist;//�Ƿ��ڣ������True��ʾ���ڣ������ǲ�����

	Date birthday;//��������

	Date dieDay;//��������

	enum boolean isManage;//��������True��ʾ�Ѿ�����ˣ�Faliseû��

	char zuPuName;//����������;

	int parent;//��ĸ�ı��ֵ
}Member;

Member member[50];
int length = 0;

/*
 *�������Ĵ洢�ṹ
 *ʹ���˺��ӱ�ʾ��
 */
typedef struct ZuPuTree{
	
	Member data;//��ǰ��������
	
	struct ZuPuTree *children;

	int numberOfChild;

}ZuPuTree;



typedef struct ZuPu {
	
	int id;//���׵�id

	char name[20];//���׵�����

	ZuPuTree tree;//���г�Ա���ɵ���

	

}ZuPu;


/*
 *����һ�������ļ���
 */
void createZuPu(ZuPu *zuPu) 
{
	int id;
	char name[20];
	FILE *fp;
	Member m;
	printf("�������׵ı��:");
	scanf("%d",&id);
	printf("\n");

	printf("�������׵�����");
	scanf("%s",name);
	printf("\n");
	
	zuPu->id = id ;
	strcpy(zuPu->name,name);
	
	strcat(name,".txt");
	
	printf("���׵�������%s\n",zuPu->name);

	fp = fopen(name,"wb");//����һ��dat�ļ�
	
	
	m.id = 0;
	strcpy(m.name,"root");

	zuPu->tree.data = m;//����һ��root���
	
	fclose(fp);
}

/*�������׳�Ա����Ϣ,����Ϣ������ʱ����member*/
void scanfZuPuMember(int *flag) {
	scanf("%d%d%s",&member[length].id,&member[length].parent,&member[length].name);
	*flag = member[length].id;
	if(*flag == -1)
	{
		return;
	}
	length++;
}

/*
 *��ӡ��ʱ����������±�Ϊi��member����Ϣ
 */
void printfZuPuMember(int i) {
	printf("%-4d%-4d%10s",member[i].id,member[i].parent,member[i].name);
}


/*
 *@param f Ŀ���ļ���ָ��
 */
void writeInfoToFile(FILE *f) {
	
	int j;
	for( j = 0;j < length;j++)
	{
		if(fwrite(&member[j],sizeof(Member),1,f) != 1) {
			printf("file write error");
			exit(0);
		}
	}
}



/*
 *�������׹�ϵ��
 *@param tree 
 *@param parentId 
 */
void createTree(ZuPuTree *tree,int parentId) {
	int i;
	int j;
	tree->children = (ZuPuTree *)malloc(sizeof(ZuPuTree)*MAXOFCHILD); //�����洢���ӵĿռ䣬ֻ���������жԿռ��е��˷�
	/*�������У�Ȼ���ҵ�*/
	tree->numberOfChild = 0;
	for(i = 0 ,j = 0;i < length; i++) {
		if(member[i].parent == parentId)
		{	
			tree->children[j].data = member[i]; 
			tree->numberOfChild++;
			createTree(&(tree->children[j]),tree->children[j].data.id);
			j++;
		}
	}
}

/*
 *�������ı���
 */
void travalZuPuTree(ZuPuTree *z) {
	/*�����ǰ������Ϣ*/
	int i = 0;
	printf("%-4d%10s%4d\n",z->data.id,z->data.name,z->data.parent);
	for(;i < z->numberOfChild; i++) {
		travalZuPuTree(&(z->children[i]));
	}
}



/*
 *���׵�չʾ
 */
void displayZuPu(ZuPu *zuPu) { 

	ZuPuTree z = zuPu->tree;
	printf("��������%s\n",zuPu->name);
	printf("���ױ�ţ�%d\n",zuPu->id);
	travalZuPuTree(&z);
	printf("\n");
}



/*
 *���������ϵ
 *�Ȱ����ݴ����ļ����棬Ȼ���ٰ�ͨ���������ڴ潨��������
 */
void createZuPuTree(ZuPu *zuPu) {
	
	int i =0;
	FILE *f;
	char fileName[20];

	/*�����Ա����Ϣ
	 *�����и�Ҫ������һ�����ݵĵ�һ���ֶ���-1(��Ϊ������־)
	 */
	int flag=1;
	while(flag != -1) 
	{	
		
		scanfZuPuMember(&flag);
		printf("the flag is %d\n",flag);
	}

	/*����Ա����Ϣд���ļ�����*/
	strcpy(fileName,zuPu->name);
	strcat(fileName,".txt");
	f = fopen(fileName,"wb");
	writeInfoToFile(f);
	
	createTree(&zuPu->tree,0);//���ڴ����湹���ϵ��
}


int main()
{
	ZuPu zuPu; 

	while(1) 
	{
		/*����һ���յ����ף���ʵ�Ǵ�����һ���ļ�*/
		createZuPu(&zuPu);
		createZuPuTree(&zuPu);
		displayZuPu(&zuPu);
	}
}