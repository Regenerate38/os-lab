#include <dirent.h>
#include <stdio.h>

int main() {

	DIR *dir_stream;
	struct dirent *dir_read;

	dir_stream = opendir(".");

	if (dir_stream == NULL) {
		printf("ERROR: error while trying to open directory. \n");
	return 1;
	}

	while((dir_read = readdir(dir_stream))!= NULL) {
		if(dir_read->d_type ==DT_DIR)
		{
			printf("\033[0;32m%s \t", dir_read->d_name);
		}
		else if(dir_read->d_type==DT_REG) 
		{
			printf("\033[0m %s \t", dir_read->d_name);
		}
		else {
		}
	}
	printf("\n");
//IMP: dir close is essential
	if(closedir(dir_stream)== -1) {
	printf("ERROR: Cannot close the directory. \n");
	return -1;
}

return 0;
}
