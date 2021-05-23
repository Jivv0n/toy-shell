# toy-shell

OS Environment : Linux

So that my shell looks like real shell, I included username, hostname and print working directory and modified each color.

// Built-in command

1) cd : If input is "cd [directory path]", you can change directory. 

2) exit : If input is "exit", shell is terminated.

// External command

1) ls [ ] -> print list with option [ ]
2) pwd -> print working directory
3) date -> show current time
4) echo -> echo [...] : print ...
5) vi -> vi [file name] : open file
6) cat -> cat [file name] : print file on shell
7) clear -> clear shell

<Limitations & Problems>

1) Home directory of real shell shows "~", but can't hide home directory. (for me, /home/jiwon)

2) In command of "cd", just typing "cd" can't go home directory.

3) echo prints just one word without word spacing.

4) "clear" operates normally, but it can work through not exec system call but system function. When I used exec system, there was a error like "TERM environment variable not set." 


