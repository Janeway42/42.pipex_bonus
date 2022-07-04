# pipex_bonus

Pipex - Usage of pipe in shell. 

Program will be executed as follows:
./pipex file1 cmd1 cmd2 file2

It must take 4 arguments:

• file1 and file2 are file names.
• cmd1 and cmd2 are shell commands with their parameters.

It must behave exactly the same as the shell command below:
$> < file1 cmd1 | cmd2 > file2


Handle multiple pipes.
This example:
$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
Should behave like:
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2

Pipex Examples
$> ./pipex infile "ls -l" "wc -l" outfile
Should behave like: < infile ls -l | wc -l > outfile
$> ./pipex infile "grep a1" "wc -w" outfile
Should behave like: < infile grep a1 | wc -w > outfile
