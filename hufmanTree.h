typedef unsigned long int mySize;

typedef struct hufmanTree{
	char *key;
	char *hufmanCode;
	mySize frequency;
	struct hufmanTree *parent,*lchild,*rchild;
}HufmanTree;

typedef struct hufmanList{
	HufmanTree *huftree;
	mySize leaves;
	mySize nodes;
}HufmanList;

//初始化霍夫曼列表
void InitHufmanList(HufmanList *hfl,char *str);

//构建霍夫曼树
void CreateHufmanTree(HufmanList *hfl);

//构建霍夫曼编码
void CreateHufmanCode(HufmanList *hfl);
