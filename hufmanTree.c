#include <stdlib.h>
#include <string.h>
#include "hufmanTree.h"

/********************************辅助函数***************************************/
void selectTwoMinElem(HufmanTree *ht,mySize stopPos,mySize *pos1,mySize *pos2){
	
}
/**********************************end******************************************/

void InitHufmanList(HufmanList *hfl,char *str){
	size_t slen = strlen(str);
	mySize count = 0,
		   curPos = 0;
	char seperator1 = ',',
		 seperator2 = ':',
		 *seperatorStr;

	//统计有多少个节点
	for(size_t i = 0; i < slen; ++i){
		if(str[i] == seperator1){
			count++;
		}
	}
	
	//初始化叶子节点
	if(count){
		hfl->huftree = (HufmanTree*)malloc((2*count-1) * sizeof(HufmanTree));

		if(hfl->huftree){
			hfl->leaves = count;
			hfl->nodes = 2 * count - 1;
			memset(hfl->huftree,0,(hfl->nodes*sizeof(HufmanTree)));

			seperatorStr = strtok(str, seperator1);
			while( seperatorStr ){
				char *num = strstr(seperatorStr, seperator2);

				if(num){
					hfl->huftree[curPos].frequency = strtoul(num);
					hfl->key = strndup( seperatorStr, num-seperatorStr);
					++curPos;
				}
				sepetatorStr = strtok(NULL, seperator1);
			}
		}
	}
}

void CreateHufmanTree(HufmanList *hfl){
	mySize min1 = 0,min2 = 0,curPos = 0;
}

void CreateHufmanCode(HufmanList *hfl){
}
