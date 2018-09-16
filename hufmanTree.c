#include <stdlib.h>
#include <string.h>
#include "hufmanTree.h"

/********************************辅助函数***************************************/
//选择一个较小结点位置
mySize selectOneMinElem(HufmanTree *ht,mySize stopPos,mySize *exclude){
	int setMin = 0;
	mySize result;

	for(mySize i = 0; i < stopPos; ++i){
		if(!ht[i].parent){
			if(!setMin && !exclude){
				setMin = 1;
				result = i;
			}else{
				if( !exclude ){
					if(ht[i].frequency < ht[result].frequency){
						result = i;
					}
				}else{
					if(*exclude != i){
						if( !setMin ){
							setMin = 1;
							result = i;
						}else if(ht[i].frequency<=ht[result].frequency){
							result = i;
						}
					}
				}
			}
		}
	}

	return result;
}

//选择两个较小结点位置
void selectTwoMinElem(HufmanTree *ht,mySize stopPos,mySize *pos1,mySize *pos2){
	*pos1 = selectOneMinElem(ht, stopPos, NULL);
	*pos2 = selectOneMinElem(ht, stopPos, pos1);
}
/**********************************end******************************************/

void InitHufmanList(HufmanList *hfl,char *str){
	size_t slen = strlen(str);
	mySize count = 0,
		   curPos = 0;
	char seperator1[] = ",",
		 seperator2[] = ":",
		 *seperatorStr;

	//统计有多少个结点
	for(size_t i = 0; i < slen; ++i){
		if(str[i] == seperator2[0]){
			count++;
		}
	}
	
	//初始化叶子结点
	if(count){
		hfl->huftree = (HufmanTree*)malloc((2*count-1) * sizeof(HufmanTree));

		if(hfl->huftree){
			hfl->leaves = count;
			hfl->nodes = 2 * count - 1;
			memset(hfl->huftree,0,(hfl->nodes*sizeof(HufmanTree)));

			char *seperatorStr = strtok(str, seperator1);
			while( seperatorStr ){
				char *num = strstr(seperatorStr, seperator2) + 1;

				if(num){
					hfl->huftree[curPos].frequency = strtoul(num,NULL,10);
					hfl->huftree[curPos].key = strndup( seperatorStr, num-seperatorStr-1);
					++curPos;
				}
				seperatorStr = strtok(NULL, seperator1);
			}
		}
	}
}

void CreateHufmanTree(HufmanList *hfl){
	mySize min1 = 0,						//选取的最小两个结点序号
		   min2 = 0,
		   curPos = hfl->leaves;			//选取的结点限制的位置
	
	for( ; curPos < hfl->nodes; ++curPos){
		selectTwoMinElem(hfl->huftree, curPos, &min1, &min2);
		hfl->huftree[curPos].frequency = hfl->huftree[min1].frequency + hfl->huftree[min2].frequency;
		hfl->huftree[curPos].lchild = hfl->huftree + min1;
		hfl->huftree[curPos].rchild = hfl->huftree + min2;
		hfl->huftree[min1].parent = hfl->huftree + curPos;
		hfl->huftree[min2].parent = hfl->huftree + curPos;
	}
}

void CreateHufmanCode(HufmanList *hfl){
	for(mySize i = 0; i < hfl->leaves; ++i){
		hfl->huftree[i].hufmanCode = (char*)malloc(1*sizeof(char));
		if( hfl->huftree[i].hufmanCode ){
			HufmanTree *pre = hfl->huftree + i,
					   *temp = hfl->huftree[i].parent;

			while( temp ){
				if( pre == temp->lchild ){
					strcat(hfl->huftree[i].hufmanCode,"0");
				}else if( pre == temp->rchild ){
					strcat(hfl->huftree[i].hufmanCode,"1");
				}
				pre = temp;
				temp = temp->parent;
			}
		}
	}
}
