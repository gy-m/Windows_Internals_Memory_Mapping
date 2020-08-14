# Windows_Internals_Memory_Mapping

This project demonstrates how OS (windows) deals with large files, that bigger than the physical memory. For that purpose, we manually will create a tool, using winAPI functions (so you must use windows for this project) to create a "File Mapping Object" that maps different parts of that large file. Those parts will be called "File Views" and only they are loaded to the physical memory. We will access those File Views using "File Mapping object" that has handles to the "File Views"


The project itself will create a tool that has the below functionality:
the user will supply an input file, an offset from the beginning, amount of bytes to read/write and an output path, and you will copy the bytes from the input file in the given offset to the output file (given the bytes to read/write).


### Prerequisites

You must use Windows x64,  because we demonstrating the way Windows OS works, using WinAPI functions.
For creating the large sized file, download python and run the provided script.

### Creating File to be copied

Run the python script. To change the size of the file created, you can change the code (The  desired size is a variable hardcoded named TOTAL_FILE_SIZE_IN_GB).
Run the Solutions (VS), which consists of 2 projects, with the following arguments:

for project 1 - <path to the large sized file<path to the large sized file>>
 
for project 2 - <size of the desired file to be created, desired offset, destination path> (without commas)
 

### Check the created file

Check the size of the created file by using "properties"
Open the created file and check the offset and the amount of bytes were coppied
note:every character in Win64 OS is 1 byte


you can find more detailed instructions in the file "detailed_instructions" 
