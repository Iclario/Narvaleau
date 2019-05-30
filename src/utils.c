#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int scanint ()
{
	char answer[10];

	scanf ("%s", answer);

	return strtol (answer, NULL, 10);
}