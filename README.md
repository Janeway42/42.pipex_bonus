# **42.pipex**

Run:
------
- **make**

- **/pipex file1 cmd1 cmd2 file2**   *(for two commands and one pipe)*
  - *file1 and file2 are file names.cmd1 and cmd2 are shell commands with their parameters*
  - *behaves the same as the shell command: < file1 cmd1 | cmd2 > file2*

- **./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2**   *(for multiple pipes)*
  - *behaves the same as the shell command: < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2*
 
-------------------------------------------------------------------

[42 The Network](https://www.42network.org/) Assignment:
-----------
Handling [pipes](https://www.geeksforgeeks.org/pipe-system-call/) and processes in [shell](https://en.wikipedia.org/wiki/Unix_shell).   

Examples:
---------
./pipex infile "ls -l" "wc -l" outfile
  - Should behave like: < infile ls -l | wc -l > outfile

./pipex infile "grep a1" "wc -w" outfile
  - Should behave like: < infile grep a1 | wc -w > outfile  
---
- Allowed external functions: open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid, [ft_printf](https://github.com/Janeway42/42.printf) 

-------------------------------------------------------------------

Code format: 
------------
The code must be written in accordance to the 42 set of norms.  
These include for example a maximum of 25 lines per function, at most 80 columns per line, comments included and a maximum of five functions per file. 

-------------------------------------------------------------------

Usefull info:
---
- [File descriptors](https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/)
- [Fork](https://www.geeksforgeeks.org/fork-system-call/?ref=gcse)
- [Pipe](https://www.geeksforgeeks.org/pipe-system-call/) 

-------------------------------------------------------------------
