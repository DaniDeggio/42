#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int ft_putstr(char *str, int fd){
	int i = 0;

	while(str[i]){
		write(fd, &str[i], 1);
		i++;
	}
	return(1);
}

int cd(char **av, int i){
	if(i != 2)
		return (ft_putstr("error: cd: bad arguments\n", 2));
	if (chdir(av[1]) == -1)
		return ft_putstr("error: cd: cannot change directory to ", 2), ft_putstr(av[1], 2), ft_putstr("\n", 2);
	return 0;
}

void set_pipe(int pipes, int *fd, int end){
	if (pipes && (dup2(fd[end], end) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
		ft_putstr("error: fatal\n", 2), exit(1);
}

int exec(char **av, int i, char**env){
	int fd[2];
	int pid;
	int status;
	int pipes = av[i] && !strcmp(av[i], "|");

	if(!pipes && !strcmp(*av, "cd"))
		return (cd(av, i));
	if(pipes && pipe (fd) == -1)
		ft_putstr("error: fatal\n", 2), exit(1);
	if((pid = fork()) == -1)
		ft_putstr("error: fatal\n", 2), exit(1);
	if (!pid)
	{
		av[i] = 0;
		set_pipe(pipes, fd, 1);
		if(!strcmp(*av, "cd"))
			return(cd(av, i));
		execve(*av, av, env);
		ft_putstr("error: cannot execute ", 2), ft_putstr(av[0], 2), ft_putstr("\n", 2);
		exit(1);
	}
	waitpid(pid, &status, 0);
	set_pipe(pipes, fd, 0);
	return WIFEXITED(status) && WEXITSTATUS(status);
}

int main(int ac, char **av, char **env){
	int i = 0;
	int status = 0;

	if (ac == 1)
		return 0;
	while (av[i]){
		av += i + 1;
		i = 0;

		while(av[i] && strcmp(av[i], "|") && strcmp(av[i], ";"))
			i++;
		if(i)
			status = exec(av, i , env);
	}
	return status;
}