https://teaching.csse.uwa.edu.au/units/CITS2002/past-projects/p2022-2/summary.php <br />
# CITS2002 Systems Programming - Project 2 2022 

# Background 
In recent years, computer disk sizes and densities have increased dramatically, with costs dropping to 4c/gigabyte (HDD) and 12c/gigabyte (SSD). As a consequence, we store an enormous number of files on our computers' disks, and finding required information is increasingly difficult. Historically, the names of files and directories alone reminded us of the location of information; today we require software tools to find information based on the content of files. In addition to file-system metadata storing information about our files and directories, we require an index of the content of our files. <br />
As examples, the macOS operating system provides the Spotlight utility to index the contents of files, and there are a number of similar utilities developed for Linux.

The goal of this project is to design and develop a command-line utility program, named trove, to build and search a compressed index of the contents of files.
 
Successful completion of the project will develop and enhance your understanding of advanced features of the C11 programming language, core Linux and macOS system-calls, POSIX function calls, and the use of the make utility. <br />

(Some of) the contents of all required files are to be stored in a trove-file. A trove-file will contain the absolute pathnames of the files that have been indexed, and each of the 'words' found in those files.

The words indexed by trove, are minimum-length sequences of alphanumeric characters. Some example words are:    main, Australia, and GTHO351. The character sequence COVID-19 contains 2 words, but the second word might not be stored if indexed words must be at least 3 characters long.

Naturally, if many files are indexed, or if many words are found, the trove-file has the potential to become very large. Thus, the trove-file will be compressed when stored on disk.


# Program invocation

From the command-line, the trove utility may be invoked in one of two ways, with command-line options indicating the actions to be performed.

prompt.1>  ./trove  [-f trovefile]  word <br />
The first invocation requests trove to list the absolute pathname of files containing the indicated word. Filenames are simply listed one-per-line (their order is not important).

If any file does not exist at the time of the search (it may have been deleted since the trove-file was built), then the file is not listed.

If any files containing the requested word are found, then trove will exit with success; otherwise with failure.

prompt.2>  ./trove  [-f trovefile]  [-b  |  -r  |  -u]  [-l length]  filelist <br />
The second invocation requests trove to build a new index, to remove information from an existing index, or to update an existing index.

A filelist is a sequence of one-or-more filenames or directory names. The contents of each named file should be indexed, and each named directory (and its subdirectories) should be traversed to locate files to be indexed.

Note that the files do not have to be text-files - they could equally be, for example, executable programs or object files.

If the requested action can be performed successfully, then trove will exit with success; otherwise with failure.

The following command-line options are to be supported:

-b	build a new trove-file from the contents of a filelist. The new trove-file will replace an existing trove-file of the same name. <br />
-f trovefile	provide the name of the trove-file to be built or searched. If the -f option is not provided, the default name of the trove-file is /tmp/trove <br />
-l length	only words of at least the indicated length should be added to the trove-file. length must be a positive integer, for example: -l 6.    If the -l option is not provided, the default length is 4. <br />
-r	if any of the files from the filelist appear in the trove-file, remove all of their information from the trove-file. <br />
-u	update the trove-file with the contents of all files in the filelist. If the information from any of the files already exists in the trove-file, then that (old) information is first removed. <br />

# The trove-file format

While there is no required format for the trove-file your design should consider some important factors: <br />
the filenames stored in the trove-file should be absolute pathnames - see man realpath <br />
to reduce the size of the trove-file (and, thus, the time to read it), each indexed word and each absolute filename should (ideally) be stored only once. <br />
the trove-file may, but does not have to be, a text-file. <br />

# Getting started

There is no required sequence of steps to undertake the project, and no sequence of steps will guarantee success. However, the following sequence is strongly recommended (and this is how the sample solution was built). It is assumed (considered essential for success!) that each step: <br />
is extensively tested before you proceed to the next step, and <br />
if any errors are found, the first error should be reported to stderr, and the program should immediately terminate. <br />

The recommended initial steps: <br />

find a project partner. <br />
determine what activities are to be performed by the program. Determine what data needs to be stored during the execution of the program. Design one of more data types and data structures to store this long-term data, and create a new trove.h header file to define these constructs. These definitions will certainly evolve as your project develops. <br />
break up the activities into fairly independent sets. Write a number of "empty" C files, each of which #includes your trove.h header file. Ensure that your main() function is implemented in a file named trove.c <br />
write a Makefile to compile and link your C files, each of which will be dependent on the header file. <br />
write the main() function, whose primary task is simply to receive and validate the command-line options and arguments. Write a usage() function to report the program's synopsis, should command-line processing detect any errors. <br />
determine if trove is required to build/modify a trove-file, or to search an existing trove-file. <br />
if building/modifying a trove-file, (recursively) traverse the filelist to find all of the files to be indexed. At this stage (as a debugging aid) just print each filename as it is found. <br />
open each file found, and find all 'words' of at least the required length. At this stage (as a debugging aid) just print each word as it is found. Remember that the files do not have to be text-files. <br />
store each word and each filename in which it is found in your data-structure(s). <br />
.... <br />
initially, store your trove-file on disk without any compression. <br />
learn how to compress files using the /usr/bin/gzip utility, and how to read the contents of a compressed file (without decompressing it) using the /usr/bin/zcat utility. Both utilities are available under macOS and Linux. When confident that your program works as required, add code to compress the file - see man gzip
.... <br />

It is anticipated that a successful project will very likely use (most of) the following Linux system-calls, and standard C11 & POSIX functions: 

getopt(), malloc(), realloc(), strdup(), free();   opendir(), readdir(), closedir(), stat(), perror();   realpath();   access(), open(), read(), write(), close();   fork(), execl(), dup2(), wait().<br />

# Project requirements and fine print
Your project must be developed in multiple C11 source files and (at least one) header file. <br />
Your submission will be compiled with the C11 compiler arguments -std=c11 -Wall -Werror, and marks will not be awarded if your submission does not compile. <br />
Compilation and linking of your project must be supported by a Makefile, employing approriate variable definitions and automatic variables. <br />
The default target of your Makefile must be named trove, and invocation of the make command must produce an executable program named trove. <br />
The default name of the trove-file must be /tmp/trove, and the default minimum length of each indexed word must be 4 <br />
Each trove-file must be stored on, and read from, disk using the /usr/bin/gzip and /usr/bin/zcat utilities. <br />
When performing a search, the names of files containing the required word should be listed one-per-line (commencing in the first column). You may leave 'debug printing' in your submitted program, but all debug printing should be indented with one-or-more space or tab characters. <br />
