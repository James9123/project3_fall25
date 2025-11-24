# Project3: Writing your own shell interpreter

You are working for a company that hires interns regularly and develops software in Linux. You are their favorite employee, and they asked you to write a **restricted** shell interpreter to be used by the interns. In this project, you are going to implement **rsh**, the **r**estricted **sh**ell, which will allow only a handful of commands to be executed from the shell prompt. To be precise, there are twelve commands that can be executed:

1: cp  
2: touch  
3: mkdir  
4: ls  
5: pwd  
6: cat  
7: grep  
8: chmod  
9: diff  
10: cd  
11: exit  
12: help  

The *help* command should print the list of commands as they appear above with the following header line added as the first line (in the standard output):

The allowed commands are:

You can see the exact behavior of the *help* command wuth the help of the provided solution executable or inspecting the output of the second test case. The first 9 commands are programs that you are going to **spawn** as separate processes using the **posix_spawnp()** system call. An **example** program that spawns an echo command is provided in the repository: **myspawn.c**. You are going to write your own shell interpreter in the file **rsh.c** that can execute the commands above. Commands 10, 11, and 12 can be considered as built-in shell commands, which will **not** spawn a separate process. The handling of commands 11 and 12 by your program is trivial: return from the main function and print a list of commands, respectively. For the "cd" command, you are going to use the **chdir()** system call to change the directory to a target directory. However, if the user specifies more than one argument to the cd command, similar to bash, you should print the following error message (**in standard output**) and **do not perform any cd action**:

-rsh: cd: too many arguments

Note that you must print this error message in **standard output** instead of standard error for autograding purposes. The shell prompt is printed in standard error and standard error is **ignored** when autograding your output. You can use the following approach to compare your output with the expected output of a test case:

```
./rsh < test_cases/test05.in 2>/dev/null > mytest5.out
diff mytest5.out test_cases/test05.out
```

The diff command should not print anything if your output is identical to the expected output.

For all the commands you will be implementing, you can assume that the maximum number of command line arguments provided will be 20 -- so that you can use a fixed sized static array for your command line arguments.

When the program is run, the shell prompt "rsh>" should be displayed. The shell should be in an infinite loop until the command **exit** is entered at which point the shell program should be terminated with a "return 0".

If the user enters any dissallowed command or try to execute some other program, you should display the following message (in standard output) and return to the prompt:

NOT ALLOWED!

Similar to project2, a sample executable, which is compiled on isengard, is provided for convenience in the solution_executable folder.

You are not expected to support background processes, piping, or input/output redirection in this project.

You can use the starter code rsh.c to complete the project. A Makefile is also provided for convenience.

**Note:** All output (other than the "rsh>" prompt) produced by the "rsh" program should be made to the standard output. You do not need to control the outputs of the spawned processes, i.e., they can print to stdout or stderr.

**Useful tips:**
 - You can use fgets() to get a line of input from the rsh prompt. Note that, fgets() also retains the end of line character at the end of the string. You can get rid of that by simply line[strlen(line)-1]='\0'.
 - You need to create and argument vector (argv in the sample program myspawn.c) to be passed to the posix_spawn() call. That argument vector is an array of strings terminated with a NULL pointer, which are basically the individual strings that the user enters from the command prompt separated by space. For example, if the user enters "mkdir a b c d", argv should be {"mkdir","a","b","c","d",NULL}. If you want to dynamically resize the argv array while parsing the input, you can use the realloc() function to do so. You can also assume that the argument vector will not contain more than 20 arguments in it.
 - strtok() destroys/modifies the original string as it tokenizes it. If you want to restart strtok() a second time on the same string from the beginning, you should first make a separate copy of that string before running strtok() the first time and start strtok() on the copied string the second time.

### Github Repo Setup and Gradescope Submission Instructions

The setup of the git repo is similar to the one for Project 2. Refer to those instructions for your github repo setup.

For Project 3, create a separate private repository specific for this project under your own user name. For example, I created a private repo named **csci210_project3** and my github username is tolgacan. A private repo can be created from the GitHub web site by going to your repositories after clicking on your profile picture (e.g., https://github.com/tolgacan?tab=repositories) and clicking on the "New" button in the top right corner. After that, you can enter a command sequence similar to the one below to clone the starter repo and copy it to your private repo to work with. The **project3** repo under the organization **CSCI210Mines** is the public repository that contains the starter code.

```
git clone git@github.com:CSCI210Mines/project3_fall25.git
cd project3_fall25
git remote remove origin
git remote add origin git@github.com:tolgacan/csci210_project3.git  # this is my private repo. replace it with your own private repo
git branch -M main
git push -u origin main
```

After these commands, you should have a copy of your starter code in your own repo and you can update the **rsh.c** with your solution code and execute the following git commands to push your updates to your own repo:

```
git add rsh.c
git commit -m "your commit message here"
git push -u origin main
```

You can also clone your repo and work on it and push the updates from different machines if you add the ssh public keys for these machines to your github profile.

**Submission on Gradescope:**

After you are logged in to your github account in a browser, if you follow the Gradescope assignment page for this project from Canvas and try to upload a submission, you will be able to select the Github submission options and select your private repository for this project to submit your solution on Gradescope.
# project3_fall25
