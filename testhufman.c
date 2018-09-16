#include <stdio.h>
#include "hufmanTree.h"

int main(int argc,char *argv[]){
	if(argc == 2){
		HufmanList hufl = {NULL,0,0};

		InitHufmanList(&hufl, argv[1]);
		CreateHufmanTree(&hufl);
		CreateHufmanCode(&hufl);
		for(mySize i = 0; i < hufl.leaves; ++i){
			printf("%s:\t%s\n", hufl.huftree[i].key, hufl.huftree[i].hufmanCode);
		}
	}

	return 0;
}
