#include <stdio.h>
#include <stdlib.h>

#include "lex.c"

int main()
{
	int i = 0;
	while(1)
	{
		token* t = scan() ;
		tok[i++] = t;
		if(t == NULL)
			break ;
		num_tokens++;
		print_token(t) ;
	}
	parse();
	return 0 ;
}
