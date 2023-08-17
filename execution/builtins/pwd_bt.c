#include <stdio.h>
#include <unistd.h>

typedef enum e_excode
{
	EX_SUCCESS = 0,
	EX_FAILURE = 1,
	EX_BT_FAIL = 2,
	EX_CNOT_EXEC = 126,
	EX_CNOT_FIND = 127,
	EX_BY_SIGNAL = 128,
	EX_OUTOF_RANGE = 255
}	t_excode;

int	pwd(void)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	printf("%s\n", pwd);
	free (pwd);
	return (EX_SUCCESS);
}