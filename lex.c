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
bool select_(int level){
	//SELECT
	if(num_tokens >ptr){
		if(tok[ptr]->type == 24){
			create_node(tok[ptr]->value,level);
			ptr ++;
		}
		else return 0;
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}

	//ARGUMENTS
	create_node(" * | ARGUMENTS",level);
	if(!arguments(level+1))
		return 0;

	//FROM
	if(!from(level)){
		expectederror("FROM",tok[ptr-1]);
		return 0;
	}

	//CHECK for LEFT BRACKET (NESTED SELECT)
	if(lb(level)){
		bcount ++;
		printf("%d\n",bcount);
		if(!select_(level+1))
			return 0;
	}

	//CHECK FOR RIGHT BRACKET ( NESTED SELECT )
	if(rb(level)){
		bcount--;
		if(!semicolon(level))
			return 0;
		return 1;
	}

	//TABLE NAME
	if(!id(level))
		return 0;

	if(rb(level)){
		bcount--;
	}

	//SEMICOLON or CONDITIONS
	create_node(" ; | WHERE conditions",level);
	if(semicolon(level+1)){
		if(bcount == 0 )
			return 1;
		else {
			printf("Brackets not balanced\n");
			return 0;
		}
	}

	//WHERE
	if(!where(level+1)){
		expectederror("WHERE",tok[ptr-1]);
		return 0;
	}

	//CONDITIONS
	if(!conditions(level+1))
		return 0;

	return 1;
}

///////////////////////////////////////////////////////////DELETE/////////////////////////////////////////////////////////////////////
bool delete(int level){
	//DELETE
	if(num_tokens >ptr){
		if(tok[ptr]->type == 37){
			create_node(tok[ptr]->value,level);
			ptr ++;
		}
		else return 0;
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}

	//FROM
	if(!from(level)){
		expectederror("FROM",tok[ptr-1]);
		return 0;
	}

	//TABLE NAME
	if(!id(level)){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

	create_node(" ; | WHERE conditions",level);
	if(semicolon(level+1))
		return 1;

	//WHERE
	if(!where(level+1)){
		expectederror("WHERE",tok[ptr-1]);
		return 0;
	}

	//CONDITIONS
	if(!conditions(level+1))
		return 0;

	return 1;
}

///////////////////////////////////////////////////////////////////////CREATE//////////////////////////////////////////////////////////////////////////
bool create(int level){
  //CREATE
	if(num_tokens >ptr){
		if(tok[ptr]->type == 15){
			create_node(tok[ptr]->value,level);
			ptr ++;
		}
		else return 0;
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}

	//TABLE
	if(!table(level)){
		expectederror("TABLE",tok[ptr-1]);
		return 0;
	}

	//ID
	if(!id(level)){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

	//LEFT BRACKET
	if(!lb(level)){
		expectederror("(",tok[ptr-1]);
		return 0;
	}

	//ATTRIBUTES
	create_node("ATTRIBUTES",level);
	if(!attributes(level+1))
		return 0;

	//RIGHT BRACKET
	if(!rb(level)){
		expectederror(")",tok[ptr-1]);
		return 0;
	}

	//SEMICOLON
	if(!semicolon(level)){
		expectederror(";",tok[ptr-1]);
	}

	return 1;
}

////////////////////////////////////////////////////////////////////////INSERT///////////////////////////////////////////////////////////////////////
bool insert(int level){
  //INSERT
	if(num_tokens >ptr){
		if(tok[ptr]->type == 32){
			create_node(tok[ptr]->value,level);
			ptr ++;
		}
		else return 0;
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}

	//INTO
	if(!into(level))
		return 0;

	//TABLE NAME
	if(!id(level)){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

	//OPTIONAL ATTRIBUTES
	create_node("E | Optional Attributes",level);
	if(lb(level+1)){
		if(!multicolumn(level+1))
			return 0;
		if(!rb(level+1)){
			expectederror(")",tok[ptr-1]);
			return 0;
		}
	}

	//VALUES
	if(!values(level))
		return 0;

	//LEFT BRACKET
	if(!lb(level)){
		expectederror("(",tok[ptr-1]);
		return 0;
	}

	//MULTIPLE VALUES
	create_node("MULTIPLE VALUES",level);
	if(!multivalues(level+1))
		return 0;

	//RIGHT BRACKET
	if(!rb(level)){
		expectederror(")",tok[ptr-1]);
		return 0;
	}

	//SEMICOLON
	if(!semicolon(level))
		return 0;

	return 1;
}

////////////////////////////////////////////////////////////////////UPDATE//////////////////////////////////////////////////////////////////////////////////////
bool update(int level){
  //UPDATE
	if(num_tokens >ptr){
		if(tok[ptr]->type == 35){
			create_node(tok[ptr]->value,level);
			ptr ++;
		}
		else return 0;
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}

	//TABLE NAME
	if(!id(level)){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

	//SET
	if(!set(level))
		return 0;

	//SET ATTRIBUTES
	create_node("MULTIPLE ATTRIBUTE = VALUE",level);
	if(!equalcondition(level+1))
		return 0;

	if(semicolon(level+1))
		return 1;

	//WHERE
	if(!where(level))
 		return 1;

	create_node("CONDITIONS",level);
	if(!conditions(level+1))
		return 0;

	return 1;
}

//////////////////////////////////////////////////////////////////////////////DROP/////////////////////////////////////////////////////////////////////////////////////
bool drop(int level){
	//DROP
	if(num_tokens >ptr){
		if(tok[ptr]->type == 38){
			create_node(tok[ptr]->value,level);
			ptr ++;
		}
		else return 0;
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}

	//TABLE OR COLUMN
	create_node("TABLE  | COLUMN ",level);
	if(!table(level+1) && !column(level+1)){
		expectederror("TABLE or COLUMN",tok[ptr-1]);
		return 0;
	}

	//TABLE NAME OR COLUMN NAME
	if(!id(level)){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

	//SEMICOLON
	if(!semicolon(level)){
		expectederror(";",tok[ptr-1]);
		return 0;
	}

	return 1;
}

/////////////////////////////////////////////////////////////////////////ALTER////////////////////////////////////////////////////////////////////////////////////////
int alter(int level){

	//ALTER
	if(num_tokens >ptr){
		if(tok[ptr]->type == 39){
			create_node(tok[ptr]->value,level);
			ptr ++;
		}
		else return 0;
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}

	//TABLE
	if(!table(level)){
		expectederror("TABLE",tok[ptr-1]);
		return 0;
	}

	//TABLE NAME
	if(!id(level)){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

	//DROP OR ADD
	create_node("DROP | ADD",level);
	if(!drop(level+1) && !add(level+1)){
		return 0;
	}

	return 1;
}

void print(char *msg,int level){
	int i;
	if(level == 1){
		printf("|--> %s\n",msg);
		return;
	}
	for(i=0;i<level-1;i++){
		printf("\t");
	}
	printf("|--> %s\n",msg);
}

void printparse(){
	int i;
	for(i=0;i<num_nodes;i++){
		//printf("%s %d\n",tree[i].value,tree[i].level);
		print(tree[i].value,tree[i].level);
	}
}

void parse(){
  switch(tok[0]->type){
    case 24:
      if(select_(level)) flag = 1;
      break;
    case 37:
      if(delete(level)) flag = 1;
      break;
    case 15:
      if(create(level)) flag = 1;
      break;
    case 32:
      if(insert(level)) flag = 1;
      break;
    case 35:
      if(update(level)) flag = 1;
      break;
    case 38:
      if(drop(level)) flag = 1;
      break;
    case 39:
      if(alter(level)) flag = 1;
      break;
    default:
			//error("Invalid Input\n");
      return;
  }
	if(flag == 1){
		printf("Printing Parse Tree\n");
		printparse();
	}
}
