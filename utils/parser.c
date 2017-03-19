
void error(token *msg){
	printf("Syntax error near %s\n",msg->value);
}

void expectederror(char *msg,token *loc){
	printf("expected %s near %s\n",msg,loc->value);
}

bool table(){
	if(num_tokens > ptr){
		if(tok[ptr]->type == 16 ){
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

bool from(){
	if(num_tokens >ptr){
		if(tok[ptr]->type == 25){
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

bool star(){
	if(num_tokens >ptr){
		if(tok[ptr]->type == 8){
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

bool where(){
	if(num_tokens >ptr){
		if(tok[ptr]->type == 26){
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

bool id(){
	if(num_tokens >ptr){
		if(tok[ptr]->type == 43){
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

bool semicolon(){
	if(num_tokens > ptr){
		if(tok[ptr]->type == 9){
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

bool equal(){
	if(num_tokens > ptr){
		if(tok[ptr]->type == 6){
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

bool dot(){
  if(num_tokens > ptr){
		if(tok[ptr]->type == 11){
			ptr++;
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}

bool aps(){
  if(num_tokens > ptr){
		if(tok[ptr]->type == 10){
			ptr++;
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}

bool comma(){
  if(num_tokens > ptr){
		if(tok[ptr]->type == 7){
			ptr++;
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}

bool lb(){
	if(num_tokens > ptr){
		if(tok[ptr]->type == 0){
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

bool rb(){
	if(num_tokens > ptr){
		if(tok[ptr]->type == 1){
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

bool into(){
	if(num_tokens > ptr){
		if(tok[ptr]->type == 33){
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

bool values(){
	if(num_tokens > ptr){
		if(tok[ptr]->type == 34){
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

bool set(){
	if(num_tokens > ptr){
		if(tok[ptr]->type == 36){
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

bool num(){
  if(num_tokens > ptr){
		if(tok[ptr]->type == 44){
			ptr++;
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}

bool column(){
	if(num_tokens > ptr){
		if(tok[ptr]->type == 41 ){
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

bool definition(){
	if(num_tokens > ptr){
		if(tok[ptr]->type == 17 || tok[ptr]->type == 18 ){
			ptr++;
			return 1;
		}
		else if( tok[ptr]->type == 19){
			ptr++;
			if(!lb()){
				expectederror("(",tok[ptr-1]);
				return 0;
			}
			if(!num())
				return 0;
			if(!rb()){
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

bool operator(){
	if(num_tokens >ptr){
		if(tok[ptr]->type == 2 || tok[ptr]->type == 3 || tok[ptr]->type == 4 || tok[ptr]->type == 5 || tok[ptr]->type == 6){
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

bool lhand(){
  //ID
  if(!id()){
    expectederror("ID",tok[ptr-1]);
    return 0;
  }

  //DOT
  if(!dot())
    return 1;

  //ID
  if(!id()){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

  return 1;
}

bool rhand(){

  if(!aps()){
    if(!id() && !num()){
      expectederror("rhand",tok[ptr-1]);
      return 0;
    }
    return 1;
  }
  else{
    while(id()){
      continue;
    }
    if(!aps()){
      expectederror("'",tok[ptr-1]);
      return 0;
    }
  }

  return 1;
}

bool normal(){

	//ID
	if(!id()){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

	//COLUMN DEGINITIONS
	if(!definition())
		return 0;

	//REFERENCES
	if(num_tokens >ptr){
		if(tok[ptr]->type == 23 ){
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
	if(!id()){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

	//LB
	if(!lb()){
		expectederror("(",tok[ptr-1]);
		return 0;
	}

	//ID
	if(!id()){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

	//RB
	if(!rb()){
		expectederror(")",tok[ptr-1]);
		return 0;
	}

}

bool primary(){
	//PRIMARY
	if(num_tokens >ptr){
		if(tok[ptr]->type == 20 ){
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
	if(!lb()){
		expectederror("(",tok[ptr-1]);
		return 0;
	}

	//ID
	if(!id()){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

	//RB
	if(!rb()){
		expectederror(")",tok[ptr-1]);
		return 0;
	}

}

bool multiid(){
	//ID
	if(!id()){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

	//COMMA
	if(comma()){
		if(!multiid())
			return 0;
	}

	return 1;
}

bool multivalues(){
	if(!rhand())
		return 0;

	if(comma()){
		if(!multivalues())
			return 0;
	}

	return 1;
}

bool multicolumn(){
	//columns
	if(!lhand())
		return 0;

	if(comma()){
		if(!multicolumn())
			return 0;
	}

	return 1;
}

bool arguments(){
	//* or COLUMN NAMES
	if(star()){
		return 1;
	}

	if(!multicolumn()){
		return 0;
	}

	return 1;
}

bool attributes(){

	if(!normal() && !primary()){
		return 0;
	}

	if(comma()){
		if(!attributes())
			return 0;
	}
	return 1;
}

bool conditions(){

	//ID
	if(!lhand())
		return 0;

	//operator
	if(!operator())
		return 0;

	if(lb()){
		bcount++;
		if(!select_())
			return 0;

		// if(!rb()){
		// 	//expectederror(")",tok[ptr-1]);
		// 	return 0;
		// }

		// if(!semicolon()){
		// 	expectederror(";",tok[ptr-1]);
		// 	return 0;
		// }
		return 1;
	}

	//ID
	if(!rhand())
		return 0;

	if(rb()){
		bcount--;
		if(bcount == 0){
			if(!semicolon()){
				expectederror(";",tok[ptr-1]);
				return 0;
			}
		}
		return 1;
	}

	//SEMICOLON or CONDITIONS
	if(!semicolon()){
      if(!comma()){
				expectederror(",",tok[ptr-1]);
				return 0;
			}
      else{
        if(!conditions())
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

bool equalcondition(){
	//ID
	if(!lhand())
		return 0;

	//operator
	if(!equal())
		return 0;

	//ID
	if(!rhand())
		return 0;

	if(comma()){
		if(!equalcondition())
			return 0;
	}


	return 1;
}

bool add(){
	//ADD
	if(num_tokens >ptr){
		if(tok[ptr]->type == 40){
			ptr ++;
		}
		else return 0;
	}
	else{
		return 0;
	}

  //COLUMN NAME
	if(!id()){
		expectederror("ID",tok[ptr-1]);
		return 0;
	}

  //COLUMN DEFINITION
  if(!definition())
    return 0;

  //SEMICOLON
	if(!semicolon()){
    expectederror(";",tok[ptr-1]);
		return 0;
	}

  return 1;
}
