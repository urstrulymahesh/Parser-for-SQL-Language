char* clone(char* s , int length)
{
	if(s == NULL)
		return NULL ;
	char* res = (char*) malloc(length) ;
	int i = 0 ;
	while(i < length)
		res[i] = s[i++] ;
	res[i] = 0 ;
	return res ;
}

bool strcmp_i(char* a , char* b)
{
	while(*a != 0 && * b != 0)
	{
		if((*a == *b) || (isalpha(*a) && isalpha(*b) && toupper(*a) == toupper(*b)))
		{
			a++ ;
			b++ ;
			continue ;
		}
		else
			return false ;
	}
	if(*a == 0 && *b == 0)
		return true ;
	return false ;
}
