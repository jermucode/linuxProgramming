#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <ctype.h>
#include <sys/types.h>
#include <dirent.h>

/* 
 * Write a program that lists the process ID
 * and command name for all processes being run
 * by the user named in the program's command-line argument.
 * This can be done by inspecting the Name and Uid: lines of all
 * the /proc/PID/status files on the system
 * Walking through all of the /proc/PID directories on the system
 * requires the use of readdir. Make sure your
 * program correctly handles the possibility that a /proc/PID directory
 * disappears between the time that the program determines that the directory
 * exists and the time that is tries to open the corresponding /proc/PID/status file*/


char *
userNameFromId(uid_t uid)
{
	struct passwd *pwd;
	pwd = getpwuid(uid);
	if(pwd == NULL)
	{
		printf("No such user ID\n");
		exit(EXIT_FAILURE);

	}
	else
	{
		return(pwd->pw_name);

	}
}

uid_t
userIdFromName(const char *name)
{
	struct passwd *pwd;
	uid_t u;
	char *endptr;
	if(name == NULL || *name == '\0')
	{
		printf("%s\n", strerror(errno));

	}
	u = strtol(name, &endptr, 10);
	if(*endptr == '\0')
	{
		return u;
	}
	pwd = getpwnam(name);
	if(pwd == NULL)
	{
		printf("%s\n", strerror(errno));

	}
	return(pwd->pw_uid);

}

uid_t userIdFromFile(FILE *fp)
{
	int c;
	char *line;
	int lineLength=0;
	uid_t uId;
	char matchUid[4];
	while(fgets(matchUid, 4, fp) != NULL)
	{ 
		if(strncmp(matchUid, "Uid", 3) == 0)
		{
			fseek(fp, 2, SEEK_CUR);
			while((c=fgetc(fp)!='\t'))
			{
				lineLength++;
			}
			fseek(fp, -(lineLength+1), SEEK_CUR);
			line = calloc(lineLength+1, sizeof(char));
			fgets(line, lineLength+1, fp);
			break;
		}

	}
	uId = atoi(line);
	free(line);
	return(uId);
}

char* processNameFromFile(FILE *fp)
{
	int c;
	char *line;
	int lineLength=0;
	char matchName[5];
	while(fgets(matchName, 5, fp) != NULL)
	{ 
		if(strncmp(matchName, "Name", 4) == 0)
		{
			fseek(fp, 2, SEEK_CUR);
			while((c=fgetc(fp)!='\t'))
			{
				lineLength++;
			}
			fseek(fp, -(lineLength+1), SEEK_CUR);
			line = calloc(lineLength+1, sizeof(char));
			fgets(line, lineLength+1, fp);
			break;

		}

	}
	return(line);
}




int main(int argc, char* argv[])
{
	/* command-line argument is just the username*/
	if(argc == 1)
	{
		printf("Provide a username.\n");
		exit(EXIT_FAILURE);
	}
	char *userName = argv[1];
	DIR *folder = opendir("/proc/");
	struct dirent *entry;
	struct dirent *process;
	char filenam[256];
	FILE *fp;
	uid_t userId;
	char *commandName;
	while((entry=readdir(folder)))
	{
		char startdir[512]; 
		strcpy(startdir, "/proc/\0");
		strcpy(filenam, entry->d_name);
		if(strcmp(filenam, ".") == 0 || strcmp(filenam, "..") == 0)
		{
			continue;
		}
		strcat(startdir, filenam);
		DIR *processDirectory = opendir(startdir);
		if(processDirectory == NULL)
		{
			continue;
		}
		while((process = readdir(processDirectory)))
		{
			if(strcmp(process->d_name, "status") == 0)
			{
				strcat(startdir, "/");
				strcat(startdir, process->d_name);
				fp = fopen(startdir, "r");
				userId = userIdFromFile(fp);
				fclose(fp);
				fp = fopen(startdir, "r");
				commandName = processNameFromFile(fp);
				fclose(fp);
				

				if(strcmp(userNameFromId(userId),  userName) == 0)
				{
					printf("Pid:\t%-10s\t\t: %s", filenam, commandName);

				}

			free(commandName);
			}

		}
		closedir(processDirectory);



	}
	closedir(folder);
}

