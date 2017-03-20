void create_node(char *value,int level){
	tree[num_nodes].value = value;
	tree[num_nodes].level = level;
	num_nodes++;
}

void error(token *msg){
	printf("Syntax error near %s\n",msg->value);
}

void expectederror(char *msg,token *loc){
	printf("expected %s near %s\n",msg,loc->value);
}

bool table(int level){
	if(num_tokens > ptr){
		if(tok[ptr]->type == 16 ){
			create_node(tok[ptr]->value,level);
			ptr++;
			return 1;
		}
		else return 0;
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}
}

bool from(int level){
	if(num_tokens >ptr){
		if(tok[ptr]->type == 25){
			create_node(tok[ptr]->value,level);
			ptr++;
			return 1;
		}
		else{
			expectederror("FROM",tok[ptr-1]);
			return 0;
		}
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}
}

bool star(int level){
	if(num_tokens >ptr){
		if(tok[ptr]->type == 8){
			create_node(tok[ptr]->value,level);
			ptr++;
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}
}

bool where(int 	level){
	if(num_tokens >ptr){
		if(tok[ptr]->type == 26){
			create_node(tok[ptr]->value,level);
			ptr++;
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}
}

bool id(int level){
	if(num_tokens >ptr){
		if(tok[ptr]->type == 43){
			create_node(tok[ptr]->value,level);
			ptr++;
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}
}

bool semicolon(int level){
	if(num_tokens > ptr){
		if(tok[ptr]->type == 9){
			create_node(tok[ptr]->value,level);
			ptr++;
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		return 0;
	}
}

bool equal(int level){
	if(num_tokens > ptr){
		if(tok[ptr]->type == 6){
			create_node(tok[ptr]->value,level);
			ptr++;
			return 1;
		}
		else{
			expectederror("=",tok[ptr-1]);
			return 0;
		}
	}
	else{
		expectederror(";",tok[ptr-1]);
		return 0;
	}
}

bool dot(int level){
  if(num_tokens > ptr){
		if(tok[ptr]->type == 11){
			create_node(tok[ptr]->value,level);
			ptr++;
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}

bool aps(int level){
  if(num_tokens > ptr){
		if(tok[ptr]->type == 10){
			create_node(tok[ptr]->value,level);
			ptr++;
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}

bool comma(int level){
  if(num_tokens > ptr){
		if(tok[ptr]->type == 7){
			create_node(tok[ptr]->value,level);
			ptr++;
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}

bool lb(int level){
	if(num_tokens > ptr){
		if(tok[ptr]->type == 0){
			create_node(tok[ptr]->value,level);
			ptr++;
			return 1;
		}
		else{
			//expectederror("(",tok[ptr-1]);
			return 0;
		}
	}
	else{
		expectederror("(",tok[ptr-1]);
		return 0;
	}
}

bool rb(int level){
	if(num_tokens > ptr){
		if(tok[ptr]->type == 1){
			create_node(tok[ptr]->value,level);
			ptr++;
			return 1;
		}
		else{
			//expectederror(")",tok[ptr-1]);
			return 0;
		}
	}
	else{
		expectederror(")",tok[ptr-1]);
		return 0;
	}
}

bool into(int level){
	if(num_tokens > ptr){
		if(tok[ptr]->type == 33){
			create_node(tok[ptr]->value,level);
			ptr++;
			return 1;
		}
		else{
			expectederror("INTO",tok[ptr-1]);
			return 0;
		}
	}
	else{
		expectederror("INTO",tok[ptr-1]);
		return 0;
	}
}

bool values(int level){
	if(num_tokens > ptr){
		if(tok[ptr]->type == 34){
			create_node(tok[ptr]->value,level);
			ptr++;
			return 1;
		}
		else{
			expectederror("VALUES",tok[ptr-1]);
			return 0;
		}
	}
	else{
		expectederror("VALUES",tok[ptr-1]);
		return 0;
	}
}

bool set(int level){
	if(num_tokens > ptr){
		if(tok[ptr]->type == 36){
			create_node(tok[ptr]->value,level);
			ptr++;
			return 1;
		}
		else{
			expectederror("VALUES",tok[ptr-1]);
			return 0;
		}
	}
	else{
		expectederror("VALUES",tok[ptr-1]);
		return 0;
	}
}

bool num(int level){
  if(num_tokens > ptr){
		if(tok[ptr]->type == 44){
			create_node(tok[ptr]->value,level);
			ptr++;
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}

bool column(int level){
	if(num_tokens > ptr){
		if(tok[ptr]->type == 41 ){
			create_node(tok[ptr]->value,level);
			ptr++;
			return 1;
		}
		else return 0;
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}
}

bool definition(int level){
	if(num_tokens > ptr){
		if(tok[ptr]->type == 17 || tok[ptr]->type == 18 ){
			create_node(tok[ptr]->value,level);
			ptr++;
			return 1;
		}
		else if( tok[ptr]->type == 19){
			create_node(tok[ptr]->value,level);
			ptr++;
			if(!lb(level)){
				expectederror("(",tok[ptr-1]);
				return 0;
			}
			if(!num(level))
				return 0;
			if(!rb(level)){
				expectederror(")",tok[ptr-1]);
				return 0;
			}
			return 1;
		}
		else{
			expectederror("COLUMN Definition",tok[ptr-1]);
			return 0;
		}
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}
}

bool operator(int level){
	if(num_tokens >ptr){
		if(tok[ptr]->type == 2 || tok[ptr]->type == 3 || tok[ptr]->type == 4 || tok[ptr]->type == 5 || tok[ptr]->type == 6){
			create_node(tok[ptr]->value,level);
			ptr++;
			return 1;
		}
		else{
			expectederror("OPERATOR",tok[ptr-1]);
			return 0;
		}
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}
}

bool lhand(int level){
  //ID
  if(!id(level)){
    expectederror("ID",tok[ptr-1]);
    return 0;
  }

  //DOT
	create_node(" E | .ID",level);
  if(!dot(level+1))
    return 1;

  //ID
  if(!id(level+1)){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

  return 1;
}

bool rhand(int level){
	create_node("NUM | 'MULTIPLE ID'",level);
  if(!aps(level+1)){
    if(!id(level+2) && !num(level+2)){
      expectederror("rhand",tok[ptr-1]);
      return 0;
    }
    return 1;
  }
  else{
    while(id(level+1)){
      continue;
    }
    if(!aps(level+1)){
      expectederror("'",tok[ptr-1]);
      return 0;
    }
  }

  return 1;
}

bool normal(int level){
	//ID
	if(!id(level)){
		//expectederror("ID",tok[ptr-1]);
		return 0;
	}

	//COLUMN DEGINITIONS
	if(!definition(level))
		return 0;

	//REFERENCES
	if(num_tokens >ptr){
		if(tok[ptr]->type == 23 ){
			create_node(tok[ptr]->value,level+1);
			ptr++;
		}
		else{
			return 1;
		}
	}
	else{
		return 0;
	}

	//ID
	if(!id(level)){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

	//LB
	if(!lb(level)){
		expectederror("(",tok[ptr-1]);
		return 0;
	}

	//ID
	if(!id(level)){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

	//RB
	if(!rb(level)){
		expectederror(")",tok[ptr-1]);
		return 0;
	}

}

bool primary(int level){
	//PRIMARY
	if(num_tokens >ptr){
		if(tok[ptr]->type == 20 ){
			create_node(tok[ptr]->value,level);
			ptr++;
		}
		else{
			return 0;
		}
	}
	else{
		return 0;
	}

	//KEY
	if(num_tokens >ptr){
		if(tok[ptr]->type == 21 ){
			create_node(tok[ptr]->value,level);
			ptr++;
		}
		else{
			expectederror("KEY",tok[ptr-1]);
			return 0;
		}
	}
	else{
		error(tok[ptr-1]);
		return 0;
	}

	//LB
	if(!lb(level)){
		expectederror("(",tok[ptr-1]);
		return 0;
	}

	//ID
	if(!id(level)){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

	//RB
	if(!rb(level)){
		expectederror(")",tok[ptr-1]);
		return 0;
	}

}

bool multiid(int level){
	//ID
	if(!id(level)){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

	//COMMA
	if(comma(level)){
		if(!multiid(level+1))
			return 0;
	}

	return 1;
}

bool multivalues(int level){
	if(!rhand(level))
		return 0;

	if(comma(level)){
		create_node("MUTLIPLE VALUES",level);
		if(!multivalues(level+1))
			return 0;
	}

	return 1;
}

bool multicolumn(int level){
	//columns
	if(!lhand(level))
		return 0;

	if(comma(level)){
		create_node("MULTIPLE COLUMNS",level);
		if(!multicolumn(level+1))
			return 0;
	}

	return 1;
}

bool arguments(int level){
	//* or COLUMN NAMES
	if(star(level)){
		return 1;
	}

	if(!multicolumn(level)){
		return 0;
	}

	return 1;
}

bool attributes(int level){
	create_node("GENERAL | PRIMARY KEY",level);
	if(!normal(level+1) && !primary(level+1)){
		return 0;
	}

	if(comma(level)){
		create_node("ATTRIBUTES",level);
		if(!attributes(level+1))
			return 0;
	}
	return 1;
}

bool conditions(int level){

	//ID
	if(!lhand(level))
		return 0;

	//operator
	create_node(" < | > | <= | >= | =",level);
	if(!operator(level+1))
		return 0;

	create_node("(SELECT STATEMENT) | VALUE",level);
	if(lb(level+1)){
		bcount++;
		if(!select_(level+1))
			return 0;

		return 1;
	}

	//ID
	if(!rhand(level+1))
		return 0;

	if(rb(level+1)){
		bcount--;
		if(bcount == 0){
			if(!semicolon(level+1)){
				expectederror(";",tok[ptr-1]);
				return 0;
			}
		}
		return 1;
	}

	//SEMICOLON or CONDITIONS
	create_node(" ; | , conditions",level);
	if(!semicolon(level+1)){
      if(!comma(level+1)){
				expectederror(",",tok[ptr-1]);
				return 0;
			}
      else{
				create_node(" conditions ",level+1);
        if(!conditions(level+2))
          return 0;
      }
  }

	if(bcount == 0)
	 return 1;
	else{
		printf("Brackets not balanced\n");
		return 0;
	}

	return 1;
}

bool equalcondition(int level){
	//ID
	if(!lhand(level))
		return 0;

	//operator
	if(!equal(level))
		return 0;

	//ID
	if(!rhand(level))
		return 0;

	if(comma(level)){
		create_node("MULTIPLE ATTRIBUTE = VALUE",level);
		if(!equalcondition(level+1))
			return 0;
	}


	return 1;
}

bool add(int level){
	//ADD
	if(num_tokens >ptr){
		if(tok[ptr]->type == 40){
			create_node(tok[ptr]->value,level);
			ptr ++;
		}
		else return 0;
	}
	else{
		return 0;
	}

  //COLUMN NAME
	if(!id(level)){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

  //COLUMN DEFINITION
  if(!definition(level))
    return 0;

  //SEMICOLON
	if(!semicolon(level)){
    expectederror(";",tok[ptr-1]);
		return 0;
	}

  return 1;
}
