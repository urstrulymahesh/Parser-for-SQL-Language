char cur = ' ' ;
int line_no = 1 ;
int ch_read = 0 ;

char read_char()
{
	cur = fgetc(stdin) ;
	ch_read++ ;
	return cur ;
}

bool read_this(char c)
{
	cur == read_char() ;
	if(cur != c)
		return false ;
	cur = ' ' ;
	return true ;
}