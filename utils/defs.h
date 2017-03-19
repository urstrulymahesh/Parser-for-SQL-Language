#define STACK_SIZE 256

typedef int bool ;
#define true 1
#define false 0

#define MAX_SIZE 100
#define MAX_STATES 100
#define MAX_LEXEME 20

// Token types
enum tokens
{
	LB , RB , LT , GT , LTE , GTE , EQ , COMMA , STAR , SC , APS , DOT ,
	PLUS , MINUS , DIV ,
	// keywords
	CREATE , TABLE , INTEGER , REAL , VARCHAR , PRIMARY , KEY , FOREIGN , REFERENCES , //related to create
	SELECT , FROM , WHERE , GROUP , BY , HAVING , JOIN , ON , //related to select
	INSERT , INTO , VALUES , //related to insert
	UPDATE , SET , //related to update
	DELETE , DROP , ALTER , ADD , COLUMN , IN ,
	ID , NUM //others
} ;

char* keyword_values[] = {"(" , ")" , "<" , ">" , "<=" , ">=" , "=" , "," , "*" , ";" , "'" , "." ,
				"+" , "-" , "/" ,
				"CREATE" , "TABLE" , "INTEGER" , "REAL" , "VARCHAR" , "PRIMARY" , "KEY" , "FOREIGN" , "REFERENCES" , //related to create
				"SELECT" , "FROM" , "WHERE" , "GROUP" , "BY" , "HAVING" , "JOIN" , "ON" , //related to select
				"INSERT" , "INTO" , "VALUES" , //related to insert
				"UPDATE" , "SET" , //related to update
				"DELETE" , "DROP" , "ALTER" , "ADD" , "COLUMN" , "IN" ,
				"ID" , "NUM"} ;
char* operator_names[] = {"LB" , "RB" , "LT" , "GT" , "LTE" , "GTE" , "EQ" , "COMMA" , "STAR" , "SC" , "APS" , "DOT" ,
				"PLUS" , "MINUS" , "DIV"} ;
#define NUM_KEYWORDS 43
#define NUM_OPERATORS 15

typedef struct token
{
	int type ;
	char* value ;
}token ;

int bcount = 0;
token *tok[MAX_SIZE];
int num_tokens = 0;
int ptr = 0;
int flag = 0;
