# **pipex with multiple pipes**
Handling [pipes](https://www.geeksforgeeks.org/pipe-system-call/) and processes in shell. 

Run:
------
- **make**

- **/pipex file1 cmd1 cmd2 file2**   *(for two commands and one pipe)*
  - *file1 and file2 are file names.cmd1 and cmd2 are shell commands with their parameters*
  - *behaves the same as the shell command: < file1 cmd1 | cmd2 > file2*

- **./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2**   *(for multiple pipes)*
  - *behaves the same as the shell command: < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2*

Examples:
---------
./pipex infile "ls -l" "wc -l" outfile
  - Should behave like: < infile ls -l | wc -l > outfile

./pipex infile "grep a1" "wc -w" outfile
  - Should behave like: < infile grep a1 | wc -w > outfile

Usefull info:
---
- [File descriptors](https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/)
- [Fork](https://www.geeksforgeeks.org/fork-system-call/?ref=gcse)
- [Pipe](https://www.geeksforgeeks.org/pipe-system-call/) 
