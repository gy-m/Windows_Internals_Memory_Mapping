// argv[1] = dst path
// argv[2] = amount of bytes read or write
// argv[3] = offset


#include <windows.h>						// for using winAPI functions
#include <stdio.h>							// for using std I/O functions
#include <stdlib.h>							// for converting user input string to numeric

#define MAX_NAME 256						// max name of a file
#define MAX_PATH 512						// path of the source or destination file
#define MAPPED_OBJ_NAME "my_mapped_obj"		// must be known to the process, because this name of the mapped object

int main(int argc, char *argv[])
{
	/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	1. get the object from named obj - process which created the mapped object defined a name to the object. we use is here (MAPPED_OBJ_NAME)
	   and this way recognize the desired object
	2. creating a file view, from the obj, which represents the start address of the string, on the virtual memory
	3. creating a file view, from the obj, which represents the start address of the string, on the virtual memory
	   note: although we created file_view_start_address, we won"t use it, because we want to create here a file view according to user's offset
	4. create a dest file - where we will copy the data
	5. write data - to the dst file we created, using file view
	6. close all - file handles, mapped objects, file views
	7. note: the responsibily to close the mapped object is for the process that uses it, in other words: this process
	8. note: MAPPED_OBJ_NAME cannot be changed without changing this value in other processes and the process which created the mapped object
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

	int fh_dst = 0;									// file habdle for destination file	
	int mapped_obj_src = 0;							// obj on the RAM - fh_src mapped to the disk and creates this obj
	char*  file_view_start_address_user_process;	// file view - will be created from the mapped object in step 1

	char path_dst[MAX_PATH] = { 0 };
	int bytes_to_copy = atoi(argv[2]);
	int offset_bytes = atoi(argv[3]);
	char mapped_obj_name[MAX_NAME] = { 0 };

	strcpy(path_dst, argv[1]);				// get the dst path argument
	strcpy(mapped_obj_name, MAPPED_OBJ_NAME);
	
	// we will use the same main so i do not need this function
	// note: mapped_obj_src should be a name and if i want to get it from the handle
	mapped_obj_src = OpenFileMapping(FILE_MAP_ALL_ACCESS,		// read/write access
									TRUE,						// do not inherit the name
									mapped_obj_name);			// name of the object from which we will create a file view later

	// check valid obj
	if (mapped_obj_src == NULL)
	{
		printf("cannot map the source file\n");
		exit(1);
	}
	

	file_view_start_address_user_process = (LPTSTR)MapViewOfFile(mapped_obj_src,						// handle to map object
																FILE_MAP_ALL_ACCESS,					// read/write permission
																0,
																0,
																bytes_to_copy);							// number of bytes we need to map  
	// check valid file view
	if (file_view_start_address_user_process == NULL)
	{
		printf("could not mapp the File View for the process\n");
		exit(1);
	}

	// open the destination file and get the handle to the file
	fh_dst = CreateFile(path_dst, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// check valid file handle to dst file
	if (fh_dst == INVALID_HANDLE_VALUE)
	{
		printf("cannot open the destination file\n");
		exit(1);
	}

	// write to dst file and check if was done
	char *ptr_end = NULL;		// we must have this ptr according to MSDN
	if (WriteFile(fh_dst, file_view_start_address_user_process + offset_bytes, bytes_to_copy, ptr_end, NULL) == NULL)
	{
		printf("cannot copy to the destinatin file\n");
		exit(1);
	}

	// close dst file
	CloseHandle(fh_dst);
	// unmapped file view
	UnmapViewOfFile(file_view_start_address_user_process);
	// close the mapped object
	CloseHandle(mapped_obj_src);
}