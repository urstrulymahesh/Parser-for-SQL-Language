#include <ctype.h>
#include <string.h>

#include "utils/defs.h"
#include "utils/ip.c"
#include "utils/utils.c"
#include "utils/parser.c"

char lexeme[MAX_LEXEME] ;
int lexeme_length = 0 ;

bool is_id(char* s)
{
	if(s == NULL || (!isalpha(*s) &&  *s != '_'))
		return false ;
	while(*s != 0)
	{
		if(!isalpha(*s) && !isdigit(*s) && *s != '_')
			return false ;
		s++ ;
	}
	return true ;
}

bool is_num(char* s)
{
	if(s == NULL || (!isdigit(*s) && *s != '.'))
		return false ;
	while(*s != 0 && *s != '.')
	{
		if(!isdigit(*s))
			return false ;
		s++ ;
	}
	if(*s == '.')
		s++ ;
	while(*s != 0)
	{
		if(!isdigit(*s))
			return false ;
		s++ ;
	}
	return true ;
}

int is_keyword(char* s)
{
	int i = 0 ;
	for(i = 0 ; i < NUM_KEYWORDS ; i++)
	{
		if(strcmp_i(s , keyword_values[i]))
			return i ;
	}
	return -1 ;
}

token* create_token(int type)
{
	token* r = (token*) malloc(sizeof (token)) ;
	r -> type = type ;
	if(type < NUM_KEYWORDS)
		r -> value = keyword_values[type] ;
	else
		r -> value = clone(lexeme , lexeme_length) ;
	return r ;
}

bool blank(char c)
{
	return c == ' ' || c == '\t' || c == '\n' || c == '\r' ;
}

token* scan()
{
	static int a = 1 ;
	a++ ;
	lexeme_length = 0 ;
	while(blank(cur))
	{
		if(cur == '\n')
		{
			line_no++ ;
			ch_read = 0 ;
		}
		read_char() ;
	}
	char temp ;
	switch(cur)
	{
		case EOF :
			return NULL ;
		case '+' :
		case '*' :
		case '/' :
		case ',' :
		case ';' :
		case '(' :
		case ')' :
		case '-' :
		case '\'' :
			lexeme[0] = cur ;
			lexeme[1] = '\0' ;
			lexeme_length = 1 ;
			read_char() ;
			break ;
		case '<' :
		case '>' :
		case '=' :
		case '!' :
			temp = cur ;
			lexeme[0] = temp ;
			if(read_this('='))
			{
				lexeme[1] = '=' ;
				lexeme[2] = '\0' ;
				lexeme_length = 2 ;
				read_char() ;
			}
			else
			{
				lexeme[1] = '\0' ;
				lexeme_length = 1 ;
				read_char() ;
			}
			break ;
		case '.' :
			lexeme[0] = cur ;
			lexeme[1] = '\0' ;
			lexeme_length = 1 ;
			read_char() ;
			if(!isdigit(cur))
				break ;
		default :
			if(isdigit(cur) || cur == '.')
			{
				while(isalpha(cur) || isdigit(cur) || cur == '.')
				{
					lexeme[lexeme_length++] = cur ;
					read_char() ;
				}
			}
			else
			{
				if(isalpha(cur) || cur == '_')
				{
					while(isalpha(cur) || isdigit(cur) || cur == '_')
					{
						lexeme[lexeme_length++] = cur ;
						read_char() ;
					}
				}
			}
	}
	lexeme[lexeme_length] = 0 ;
	// printf("%s\n", lexeme);
	int ret = is_keyword(lexeme) ;
	if(ret != -1)
	{
		return create_token(ret) ;
	}
	if(is_id(lexeme))
	{
		return create_token(ID) ;
	}
	else if(is_num(lexeme))
	{
		return create_token(NUM) ;
	}
	else
	{
		if(lexeme_length != 0)
			printf("Unrecognized token '%s' on line no %d and colno %d \n", lexeme , line_no , ch_read - lexeme_length);
		else
			printf("Unrecognized token '%c' on line no %d and colno %d \n", cur , line_no , ch_read - 1);
		return NULL ;
	}
}

char* get_type(int type)
{
	if(type < NUM_OPERATORS)
		return operator_names[type] ;
	else if(type >= NUM_KEYWORDS)
		return keyword_values[type] ;
	else
		return "Keyword" ;
}

void print_token(token* i)
{
	printf("%s %s\n", get_type(i -> type) , i -> value);
}


//////////////////////////////////////////////////////////////////SELECT//////////////////////////////////////////////////////////////////
bool select_(){
	//SELECT
	if(num_tokens >ptr){
		if(tok[ptr]->type == 24){
			ptr ++;
		}
		else return 0;
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}

	//ARGUMENTS
	if(!arguments())
		return 0;

	//FROM
	if(!from()){
		expectederror("FROM",tok[ptr-1]);
		return 0;
	}

	//CHECK for LEFT BRACKET (NESTED SELECT)
	if(lb()){
		bcount ++;
		printf("%d\n",bcount);
		if(!select_())
			return 0;
	}

	//CHECK FOR RIGHT BRACKET ( NESTED SELECT )
	if(rb()){
		bcount--;
		if(!semicolon())
			return 0;
		return 1;
	}

	//TABLE NAME
	if(!multiid())
		return 0;

	//SEMICOLON or CONDITIONS
	if(semicolon()){
		if(bcount == 0)
			return 1;
		else {
			printf("Brackets not balanced\n");
			return 0;
		}
	}

	//WHERE
	if(!where()){
		expectederror("WHERE",tok[ptr-1]);
		return 0;
	}

	//CONDITIONS
	if(!conditions())
		return 0;

	return 1;
}

///////////////////////////////////////////////////////////DELETE/////////////////////////////////////////////////////////////////////
bool delete(){
	//DELETE
	if(num_tokens >ptr){
		if(tok[ptr]->type == 37){
			ptr ++;
		}
		else return 0;
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}

	//FROM
	if(!from()){
		expectederror("FROM",tok[ptr-1]);
		return 0;
	}

	//TABLE NAME
	if(!id()){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

	//WHERE
	if(!where()){
		expectederror("WHERE",tok[ptr-1]);
		return 0;
	}

	//CONDITIONS
	if(!conditions())
		return 0;

	return 1;
}

///////////////////////////////////////////////////////////////////////CREATE//////////////////////////////////////////////////////////////////////////
bool create(){
  //CREATE
	if(num_tokens >ptr){
		if(tok[ptr]->type == 15){
			ptr ++;
		}
		else return 0;
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}

	//TABLE
	if(!table()){
		expectederror("TABLE",tok[ptr-1]);
		return 0;
	}

	//ID
	if(!id()){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

	//LEFT BRACKET
	if(!lb()){
		expectederror("(",tok[ptr-1]);
		return 0;
	}

	//ATTRIBUTES
	if(!attributes())
		return 0;

	//RIGHT BRACKET
	if(!rb()){
		expectederror(")",tok[ptr-1]);
		return 0;
	}

	//SEMICOLON
	if(!semicolon()){
		expectederror(";",tok[ptr-1]);
	}

	return 1;
}

////////////////////////////////////////////////////////////////////////INSERT///////////////////////////////////////////////////////////////////////
bool insert(){
  //INSERT
	if(num_tokens >ptr){
		if(tok[ptr]->type == 32){
			ptr ++;
		}
		else return 0;
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}

	//INTO
	if(!into())
		return 0;

	//TABLE NAME
	if(!id()){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

	//OPTIONAL ATTRIBUTES
	if(lb()){
		if(!multicolumn())
			return 0;
		if(!rb()){
			expectederror(")",tok[ptr-1]);
			return 0;
		}
	}

	//VALUES
	if(!values())
		return 0;

	//LEFT BRACKET
	if(!lb()){
		expectederror("(",tok[ptr-1]);
		return 0;
	}

	//MULTIPLE VALUES
	if(!multivalues())
		return 0;

	//RIGHT BRACKET
	if(!rb()){
		expectederror(")",tok[ptr-1]);
		return 0;
	}

	//SEMICOLON
	if(!semicolon())
		return 0;

	return 1;
}

////////////////////////////////////////////////////////////////////UPDATE//////////////////////////////////////////////////////////////////////////////////////
bool update(){
  //UPDATE
	if(num_tokens >ptr){
		if(tok[ptr]->type == 35){
			ptr ++;
		}
		else return 0;
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}

	//TABLE NAME
	if(!id()){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

	//SET
	if(!set())
		return 0;

	//SET ATTRIBUTES
	if(!equalcondition())
		return 0;

	if(semicolon())
		return 1;

	//WHERE
	if(!where())
 		return 1;

	if(!conditions())
		return 0;

	return 1;
}

//////////////////////////////////////////////////////////////////////////////DROP/////////////////////////////////////////////////////////////////////////////////////
bool drop(){
	//DROP
	if(num_tokens >ptr){
		if(tok[ptr]->type == 38){
			ptr ++;
		}
		else return 0;
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}

	//TABLE OR COLUMN
	if(!table() && !column()){
		expectederror("TABLE or COLUMN",tok[ptr-1]);
		return 0;
	}

	//TABLE NAME OR COLUMN NAME
	if(!id()){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

	//SEMICOLON
	if(!semicolon()){
		expectederror(";",tok[ptr-1]);
		return 0;
	}

	return 1;
}

/////////////////////////////////////////////////////////////////////////ALTER////////////////////////////////////////////////////////////////////////////////////////
int alter(){

	//ALTER
	if(num_tokens >ptr){
		if(tok[ptr]->type == 39){
			ptr ++;
		}
		else return 0;
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}

	//TABLE
	if(!table()){
		expectederror("TABLE",tok[ptr-1]);
		return 0;
	}

	//TABLE NAME
	if(!id()){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

	//DROP OR ADD
	if(!drop() && !add()){
		return 0;
	}

	return 1;
}



void parse(){
  switch(tok[0]->type){
    case 24:
      if(select_()) flag = 1;
      break;
    case 37:
      if(delete()) flag = 1;
      break;
    case 15:
      if(create()) flag = 1;
      break;
    case 32:
      if(insert()) flag = 1;
      break;
    case 35:
      if(update()) flag = 1;
      break;
    case 38:
      if(drop()) flag = 1;
      break;
    case 39:
      if(alter()) flag = 1;
      break;
    default:
			//error("Invalid Input\n");
      return;
  }
	if(flag == 1){
		printf("Printing Parse Tree\n");
	}
}
