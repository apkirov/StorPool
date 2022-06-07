#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <time.h>


// struct Chunk {
// 	char *path;
// 	int partPosition;
// 	int state;
// 	int version;
// 	struct Chunk *next;
// };

// 	long maxObject = 0;
// 	long masVersion = 0;

struct Route {
	struct Route  **pushRoute;
	unsigned short *versionsCount;
	unsigned int *versions;



};




struct Result {
	struct Route *route;
	char *versionId;
	char *objectId ;
	struct Result *next;

};




int read_off_memory_status() {
	unsigned char *buffer;
	unsigned char *vmPos;
	int vmSize = 0;
	long size = 0;

	FILE *f = fopen("/proc/self/status","r");
	if(f == NULL) {
    	printf("Cant open file !!!!\n");
    	return 0;
    }
	size = 300;
	buffer = (unsigned char *)malloc(size+1);
	fread(buffer, size, 1, f);
    fclose(f);
    vmPos = strstr(buffer, "VmSize:");
    vmSize = atoi(vmPos+7);
    free(buffer);

    return vmSize;
}



char *find_chunk (char *data){
	return strchr(data, '}');
}


struct Result *appendChunk(struct Route *thisRoute, long version, struct Result *result , char *versionId, char * objectId) {
	if (thisRoute->versionsCount == NULL) {
		if (thisRoute->versions == NULL) {
			thisRoute->versions = (unsigned int *)malloc(sizeof (unsigned int));
			*(thisRoute->versions) =  version;
		}
		else {
			if (version != *(thisRoute->versions)) {
				unsigned int *tmpVersions;
				tmpVersions = thisRoute->versions;
				thisRoute->versions =  (unsigned int *)malloc(sizeof (unsigned int)*2);
				*(thisRoute->versions) =  *tmpVersions;
				*(thisRoute->versions+1) = version;
				thisRoute->versionsCount = (unsigned short *)malloc(sizeof (unsigned short));
				*(thisRoute->versionsCount) = 1;
				free(tmpVersions);
				result->next = (struct Result *)malloc(sizeof(struct Result));
				result = result->next;
				result->next = NULL;
				result->versionId = (char *)malloc(18);
				result->objectId = (char *)malloc(6);
				strcpy(result->versionId, versionId);
				strcpy(result->objectId, objectId);
				result->route = thisRoute;
			}

		}
	}
	else {
		char exists = 0;
		unsigned int *tmpVersions;
		for(int uh1 = 0; uh1 <= *(thisRoute->versionsCount); uh1++) {
			if (*(thisRoute->versions+uh1) == version) {
				exists = 1;
				break;
			}
		}
		if (!exists) {
			tmpVersions = thisRoute->versions;
			thisRoute->versions = (unsigned int *)malloc(sizeof (unsigned int)* (*(thisRoute->versionsCount) + 1) ) ;
			for(int uh1 = 0; uh1 < *(thisRoute->versionsCount); uh1++) {
				*(thisRoute->versions+uh1) = *(tmpVersions + uh1);
			}
			*( thisRoute->versions+*(thisRoute->versionsCount) ) = version;
			*(thisRoute->versionsCount) = *(thisRoute->versionsCount) + 1;		
			free(tmpVersions);
		}
	}
	return result;
/*	
	long *tmpVersions;
	tmpVersions = (long *)malloc(*((thisRoute->versionsCount) + 1)* sizeof(long));
	if (thisRoute->versionsCount != NULL && *(thisRoute->versionsCount) > 0) {
		for(int uh1 = 0; uh1 < *(thisRoute->versionsCount); uh1++) {
			*(tmpVersions+uh1) = *(thisRoute->versions+uh1);
		}
		free(thisRoute->versions);
	}
	*(tmpVersions + *(thisRoute->versionsCount) = version;
	thisRoute->versions = tmpVersions;
	*(thisRoute->versionsCount)++;
	if (thisRoute->versionsCount > maxObject) {
		maxObject = thisRoute->versionsCount;
		printf("%u\n", maxObject);
	}
	return NULL;
	3 338 366 543
    2 147 483 648
*/
}


struct Result *find_structure(char *prev, char *this, struct Route *firstRoute, struct Result *thisResult, unsigned long *objectsCount) {
	char *found;
	char routeVolume[] = "0000000000000000000";
	char routeObjects[] = "000000";
	int state;
	long version;
	*objectsCount += 1;
	if ( (found  = strstr(prev, "\"state\":") ) != NULL) {
		if (found < this) {
			state = atoi(found + 8);
		}
	}
	// if ( (found  = strstr(prev, "\"version\":") ) != NULL) {
	// 	if (found < this) {
	// 		long obj_id = atol(found + 11);
	// 		if (obj_id > maxObject) {
	// 			maxObject = obj_id;
	// 			printf("%u\n", maxObject);

	// 		}

	// 	}
	// }
	// return;



	if (state != 1) {
		return thisResult;
	}

	if ( (found  = strstr(prev, "\"volumeId\":") ) != NULL) {
		if (found < this) {
			found += 11;
			int uh1 = 0;
			while (*(found+uh1) == ' ') {
				uh1++;
			}

			if (*(found+uh1) == '-') {
				return thisResult;
			}
			found += uh1;
			uh1 = 0;
			while (*(found+uh1) >= '0' && *(found+uh1) <= '9') {
				uh1++;
			}
			int routePosition = 18;
			// char show[1200];
			// strncpy(show, found-20, 1000);
			do {
				routeVolume[routePosition--] = *(found+uh1-1);
			}while (--uh1 >= 1);
		}
	}
	if ( (found  = strstr(prev, "\"objectId\":") ) != NULL) {
		if (found < this) {
			found += 11;
			int uh1 = 0;
			while (*(found+uh1) == ' ') {
				uh1++;
			}

			if (*(found+uh1) == '-') {
				return thisResult;
			}
			found += uh1;
			uh1 = 0;
			while (*(found+uh1) >= '0' && *(found+uh1) <= '9') {
				uh1++;
			}
			int routePosition = 5;
			do {
				routeObjects[routePosition--] = *(found+uh1-1);
			}while (--uh1 >= 1);
		}

	}
	// if (atoi(routeObjects) == 0) {
	// 	char show[1200];
	// 	strncpy(show, prev, 1000);
	// 	printf("%s\n\n\n", show);
	// }
	if ( (found  = strstr(prev, "\"version\":") ) != NULL) {
		if (found < this) {
			version = atol(found + 10);
		}
	}
	struct Route *thisVolume;
	thisVolume = firstRoute;
	for (int uh1 = 0; uh1 < 18; uh1++) {

		if (*(thisVolume->pushRoute + routeVolume[uh1] - 48) == NULL) {
			*(thisVolume->pushRoute + routeVolume[uh1] - 48) = (struct Route *) malloc(sizeof(struct Route));
			thisVolume = *(thisVolume->pushRoute + routeVolume[uh1] - 48);
			thisVolume->versions = NULL;
			thisVolume->versionsCount = NULL;
			thisVolume->pushRoute = (struct Route **) malloc(10 * sizeof(struct Route *));
			for (int uh2 = 0; uh2 < 10; uh2++) {
				*(thisVolume->pushRoute+uh2) = NULL;
			}
		}
		else {
			thisVolume = *(thisVolume->pushRoute + routeVolume[uh1] - 48);
		}
	}

	for (int uh1 = 0; uh1 < 6; uh1++) {

		if (*(thisVolume->pushRoute + routeObjects[uh1] - 48) == NULL) {
			*(thisVolume->pushRoute + routeObjects[uh1] - 48) = (struct Route *) malloc(sizeof(struct Route));
			thisVolume = *(thisVolume->pushRoute + routeObjects[uh1] - 48);
			thisVolume->versions = NULL;
			thisVolume->versionsCount = NULL;
			thisVolume->pushRoute = (struct Route **) malloc(10 * sizeof(struct Route *));
			for (int uh2 = 0; uh2 < 10; uh2++) {
				*(thisVolume->pushRoute+uh2) = NULL;
			}
		}
		else {
			thisVolume = *(thisVolume->pushRoute + routeObjects[uh1] - 48);
		}
	}
	// if (thisVolume->versionsCount != NULL && *(thisVolume->versionsCount) >= 10000) {
	// 	printf("%s %s %d", routeVolume, routeObjects, version);
	// }

	return appendChunk(thisVolume, version, thisResult, routeVolume, routeObjects);
// void appendChunk(struct Route *thisRoute, int state, int version, char *path, int partPosition ) {

		// printf("VolumeID: %s, objectId: %s , state: %d, volume : %d \n",  routeVolume, routeObjects, state, volume);
}

char *search_for_begin (char *data){
	unsigned int iter = 0;
	char searchString[] = "\"objects\":";
	char *found;
	if ( (found  = strstr(data, searchString) ) != NULL) {
		return found + strlen(searchString);
	}
	else {
		return 0;
	}
}


struct Result *read_file (char *path, struct Route *firstVolumeRoute, struct Result *incomeResult, unsigned long *objectsCount) {
	FILE *in;
	unsigned long routeLastPosition = 0;
	unsigned char *buffer, *begin, *currentPart, *prevPart;
    unsigned int parts = 0;
    struct Result *thisResult;
    thisResult = incomeResult;

	in = fopen(path, "r");
    if (NULL == in) {
        printf("file can't be opened %s \n", path);
        return 0;
    }
	fseek(in, 0, SEEK_END);
	size_t size = ftell(in);
	fseek(in, 0, SEEK_SET);  /* same as rewind(f); */
	buffer = (unsigned char *)malloc(size+1);
	fread(buffer, size, 1, in);
	begin = buffer;
	buffer[size] = 0;
    fclose(in);
    buffer = search_for_begin(buffer);
    prevPart = NULL;
	while( (currentPart = find_chunk( buffer ) ) != NULL) {
		if (prevPart != NULL) {
			thisResult = find_structure(prevPart, currentPart, firstVolumeRoute, thisResult, objectsCount);
		}
		prevPart = currentPart+1;
		buffer = currentPart+1;
		parts++;
		
	}

    // printf("In file %s found %d chunks \n", path, parts);
    free(begin);
    return thisResult;
}




void clearData (struct Route *this) {
	for (int uh1 = 0; uh1 < 10; uh1++) {
		if (*(this->pushRoute + uh1) != NULL) {
			clearData(*(this->pushRoute + uh1));
			free( *(this->pushRoute + uh1) );
		}
	}
	if (this->versionsCount != NULL) {
		free(this->versionsCount);
	}
	if (this->versions != NULL) {
		free(this->versions);
	}
	if (this->pushRoute != NULL) {
		free(this->pushRoute);
	}
}


int main(int argc, char  **argv) {
	DIR *folder;
	struct dirent *entry;
	int files = 0, allFiles =0;;

	char *full_path;
	size_t maxSize = 0;

	struct Route firstRoute;
	struct Result *firstResult;
	struct Result *currentResult;
	firstResult = (struct Result *)malloc(sizeof(struct Result));
	currentResult = firstResult;
    firstRoute.pushRoute = (struct Route **) malloc(10 * sizeof(struct Route));
    firstRoute.versionsCount = NULL;
    firstRoute.versions = NULL;
    clock_t start, end;
    start = clock();




	folder = opendir(argv[1]);
	int uCount = 0;
	unsigned long objectsCount = 0;

	if(folder == NULL) {
        printf ("ERROR !!! : Unable to read directory %s. First param of program must be dir with files ", argv[1]);
        return(1);
    }
    else {
		while( ( entry=readdir(folder) ) ) {
			if (entry->d_name[0] == '.') {
				continue;
			}
			files++;
		}
		allFiles = files;
		char *allPaths[files];
		rewinddir(folder);
		files = 0;
		while( ( entry=readdir(folder) ) ) {
			allPaths[files] = (char *)malloc(strlen(argv[1]) + 5);;
			 full_path = *(allPaths+files);
			if (entry->d_name[0] == '.') {
				continue;
			}
    		strcpy(full_path, argv[1]);
        	if ( *(full_path+strlen(full_path)-1) != '/') {
        		strcat(full_path, "/");
			}
    		strcat(full_path, entry->d_name);
    		printf("Start reading %d file from %d files  - %s \n", files+1, allFiles, full_path);
    		currentResult = read_file(full_path, &firstRoute, currentResult, &objectsCount);
    		printf("After complition of %d file - used memory: %.2f GB, time:  %.2f sec\n", files+1, ((float)read_off_memory_status())/(1024*1024), ((double) (clock() - start)) / CLOCKS_PER_SEC ) ;
        	files++;
	    }   
	    for (int uh1 = 0; uh1 < files; uh1++) {
	    	free(allPaths[uh1]);
	    }
	     	
    }
    closedir(folder);	
	currentResult = firstResult;
	unsigned long found = 0;
	FILE *out;
	out = fopen("output.txt", "w");

	struct Result *prevResult;
    do {
    	found++;
    	prevResult = currentResult;
    	currentResult = currentResult->next;
    	fprintf(out, "%s\t%s\t%d:", currentResult->versionId, currentResult->objectId, *(currentResult->route->versionsCount)+1);
    	for (int uh1 = 0; uh1 <= *(currentResult->route->versionsCount); uh1++) {
    		fprintf(out, "\t%d", *(currentResult->route->versions+uh1));
    	}
    	fprintf(out, "\n");
    	free(prevResult);


    }while(currentResult->next != NULL);

    fclose(out);
	printf ("Done Everything. In %d files found %lu objects that match on conditions from %lu objects at all. The result is witten into \"output.txt\" \n" , files, found, objectsCount);
	printf("Start cleaning memory....\n");
	clearData(&firstRoute);
	printf("Operation complete used memory: %.2f GB, time:  %.2f sec\n",((float)read_off_memory_status())/(1024*1024), ((double) (clock() - start)) / CLOCKS_PER_SEC ) ;

	return 0;
}





