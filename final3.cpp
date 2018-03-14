#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

class evaluate{
	public:
		string eq;
		string priority;

		void get_eq(){
			cout << "     -> Enter the equation :         |	";
			cin >> eq;
			cout << " |                                                                                                                             |\n";
			cout << " *******************************************************************************************************************************\n\n";

			for(int i=0;i<=eq.size()-1;i++)
				priority.push_back('0');
		}
		void replace_x(float value){
			int pos=1;
			string val=to_string(value);
			while(pos!=-1){
				pos=eq.find('x');
				if(pos==-1)
					break;
				eq.replace(pos,1,val);
			}
		}
		void replace_cosec(){
			int pos=1;
			while(pos!=-1){
				pos=eq.find("cosec");
				if(pos==-1)
					break;
				eq.replace(pos,5,"csc");
			}
		}
		int max_priority(){
			int l=eq.size();
			int max=0;
			for(int i=0;i<=l-1;i++)
				if(max<(int)priority[i])
					max=(int)priority[i];
		}
		void set_priority(){
			int l=eq.size();
			int count_parenthesis=0;
			priority="";
			for(int i=0;i<=l-1;i++){
				priority.push_back(char(count_parenthesis+48));
				if(eq[i]=='(') count_parenthesis++;
				if(eq[i]==')') {
					count_parenthesis--;
					priority[i]=(char)(count_parenthesis+48);
				}
			}
		}
		void display(){
			int l=eq.size();
			for(int i=0;i<=l-1;i++){
				//cout<<eq[i];
			}
			//cout<<endl;
			for(int i=0;i<=l-1;i++){
				//cout<<priority[i];
			}
			//cout<<endl;
		}
		int string_size(){ 
			//blah blah
			return eq.size(); 
		}
};
int max_p;
bool is_n(string s){
	int l=s.size();
	for(int i=0;i<=l-1;i++){
		if(!isdigit(s[i]))
			return false;
	}
	return true;
}
bool is_f(string s){
	int l=s.size();
	for(int i=0;i<=l-1;i++){
		if((!isdigit(s[i]))&&s[i]!='.')
			return false;
	}
	return true;
}
bool is_negetive(string s){
	string num=s.substr(1,s.size()-1);
	if(is_f(num)||is_n(num))
		return true;
	return false;
}
int prec(char c){
    if(c == '^')
    	return 3;
    else if(c == '*' || c == '/')
    	return 2;
    else if(c == '+' || c == '-')
    	return 1;
    else
    	return -1;
}
string infix_postfix(string s){
    std::stack<char> st;
    st.push('N');
    int l = s.length();
    string ns;
    for(int i=0;i<=l-1;i++)
    {
        if((s[i] >= 'A' && s[i] <= 'Z'))	ns+=s[i];
        else if(s[i]=='(')	st.push('(');
        else if(s[i]==')'){
            while(st.top() != 'N' && st.top() != '('){
				char c = st.top();
				st.pop();
				ns += c;
            }
            if(st.top() == '('){
                char c = st.top();
                st.pop();
            }
        }else{
            while(st.top()!='N' && prec(s[i])<=prec(st.top())){
                char c = st.top();
                st.pop();
                ns += c;
            }
            st.push(s[i]);
        }
    }
    while(st.top()!='N'){
        char c = st.top();
        st.pop();
        ns += c;
    } 
    //cout << ns << endl;
    return ns;
}
string evaluate_postfix(string exp, string alphabet[26],string numbers[26]){
    stack<float>result;
    int i;
    for(i=0;i<=(exp.size()-1);i++){
        if (isalpha(exp[i])){
      		int index=exp[i]-'A';
      		string temp=numbers[index];
      		if(temp.size()==2){
      			continue;
      		}
      		int size_temp=temp.size();
      		temp=temp.substr(1,size_temp-1);
      		temp=temp.substr(0,size_temp-2);
        	result.push(stof(temp));
        }else{
            float val1=result.top();
            result.pop();
            float val2=result.top();
            result.pop();
            switch (exp[i]){
				case '+': result.push(val2+val1); break;
				case '^': result.push(pow(val2,val1)); break;
				case '-': result.push(val2-val1); break;
				case '*': result.push(val2*val1); break;
				case '/': result.push(val2/val1);  break;
            }
        }
    }
    float res=result.top();
    result.pop();
    return to_string(res);
}

string solve(string eqn){
	int function_flag=1;
	string evaluated_string="";

	//cout<<"BHAHAHAH   "<<eqn<<endl;

	if(eqn.find("--")!=-1||eqn.find("-(-")!=-1){
		int pos_double=eqn.find("-(-");
		if(pos_double!=-1){
			int close_parn=eqn.find(")");
			int size=close_parn-(pos_double+3);
			string temp=eqn.substr(pos_double+3,size);
			//cout<<temp<<" THE SABOIR"<<endl;
			eqn.replace(pos_double,close_parn-pos_double+1,"+"+temp);
		}

		int pos_double_negetive=eqn.find("--");
		if(pos_double_negetive!=-1){
			if(pos_double_negetive==0)
				eqn.replace(pos_double_negetive,2,"");
			else if(isdigit(eqn[pos_double_negetive+2]))
				eqn.replace(pos_double_negetive,2,"+");
		}
	}
	if(eqn.find("-+")!=-1){
		int pos_double_negetive=eqn.find("-+");
		if(isdigit(eqn[pos_double_negetive+2]))
			eqn.replace(pos_double_negetive,2,"-");
	}
	if(eqn.find("+-")!=-1){
		int pos_double_negetive=eqn.find("+-");
		if(isdigit(eqn[pos_double_negetive+2]))
			eqn.replace(pos_double_negetive,2,"-");
	}
	if(eqn.find("++")!=-1){
		int pos_double_negetive=eqn.find("++");
		if(isdigit(eqn[pos_double_negetive+2]))
			eqn.replace(pos_double_negetive,2,"+");
	}

	/*if there is only number*/{
		if(is_n(eqn)||is_f(eqn)||is_negetive(eqn))
			return eqn;
	}
	/*if there is a numbr in TOTAL equation*/{
		int flag=1;
		string variable="";
		int len_eqn=eqn.size();
		int i;
		int negation_flag=0;
		//cout<<"ljejnfrjeknjkfdm;nv;kmc ds "<<eqn<<endl;
		for(i=0;i<=eqn.size()-1;i++){
			variable.push_back(eqn[i]);
			if((eqn[i]=='+'||eqn[i]=='-'||eqn[i]=='*'||eqn[i]=='/'||eqn[i]=='^')){
				if(i==0){
					negation_flag=1;
					continue;
				}
				if(eqn[i-1]=='('){
					negation_flag=1;
					continue;
				}
				if(eqn[i-1]=='/'||eqn[i-1]=='*'||eqn[i-1]=='+'||eqn[i-1]=='^'||eqn[i-1]=='-')
					continue;
				//cout<<endl<<"fl3k4f "<<variable<<endl;
				variable.pop_back();
				if(variable.size()!=0){
					if(is_n(variable)||is_f(variable)||is_negetive(variable)){
						int len_variable=variable.size();
						//cout<<variable<<" wow magic "<<endl;
						variable="("+variable+")";
						eqn.replace(i-len_variable,len_variable,variable);
						//cout<<endl<<"HAHAHAHA"<<variable<<endl;
						//eqn="("+eqn+")";

						i=i+2;
					}
				}
				//cout<<"rlrie: "<<variable<<endl;
				variable="";
			}
		}
		if(is_negetive(variable)||is_f(variable)||is_f(variable)){
			int len_variable=variable.size();
			variable="("+variable+")";
			eqn.replace(i-len_variable,len_variable,variable);
			//cout<<endl<<"HAHAHAHA"<<variable<<endl;
			variable="";
		}
		//cout<<endl<<eqn<<" madod3 "<<endl;
	}
	/*Functions*/
	while(function_flag==1){
		function_flag=0;

		if(eqn.find("ep")!=-1||eqn.find("-ep")!=-1){
		//	//cout<<"hello1"<<endl;
			int negation_flag=0;
			function_flag=1;
			int pos_fun=eqn.find("ep");
			if(pos_fun>0){
				if(eqn[pos_fun-1]=='-'){
					if(pos_fun>2){
						char temp=eqn[pos_fun-2];
						if(temp!=')'){
							negation_flag=1;
							pos_fun--;
							eqn=eqn.substr(1,eqn.size());
						}
					}
					else{
						negation_flag=1;
						pos_fun--;
						eqn=eqn.substr(1,eqn.size());	
					}
				}
			}
			int l=eqn.size();
			string temp="";
			int flag=0,j=0,strt_float=0;
			float nos;
			//cout<<"kaha "<<nos<<endl;
			for(int i=pos_fun;i<=l-1;i++){
				if(isdigit(eqn[i])||eqn[i]=='.'||eqn[i]=='-'){
					temp.push_back(eqn[i]);
					flag=1;
					strt_float=i;
				}
				else if(!isdigit(eqn[i])&&flag==1){
					nos=stof(temp);
					break;
				}
			}
			//cout<<"Negetopm flag "<<negation_flag<<endl;
			float res=pow(2.71828,nos);
			if(isnan(res))
				return "INFINITY";
			if(negation_flag==1)
				res*=-1;
			string result=to_string(res);
			//cout<<"fjwrkef: "<<result<<endl;
			int length_to_be_added=result.size();
			int num_parenthesis=1; 
			int i;
			for(i=pos_fun+2;;i++){
				if(eqn[i]==')') break;
			}
			result="("+result+")";
			//cout<<"cwljvle: "<<result<<"pos: "<<pos_fun<<" "<<i<<endl;
			int length_to_be_removed=i-pos_fun+1;
			eqn.replace(pos_fun,length_to_be_removed,result);
		}

		if(eqn.find("sqrt")!=-1||eqn.find("-sqrt")!=-1){
			//cout<<"hello1"<<endl;
			int negation_flag=0;
			function_flag=1;
			int pos_fun=eqn.find("sqrt");
			if(pos_fun>0){
				if(eqn[pos_fun-1]=='-'){
					if(pos_fun>2){
						char temp=eqn[pos_fun-2];
						if(temp!=')'){
							negation_flag=1;
							pos_fun--;
							eqn=eqn.substr(1,eqn.size());
						}
					}
					else{
						negation_flag=1;
						pos_fun--;
						eqn=eqn.substr(1,eqn.size());	
					}
				}
			}
			int l=eqn.size();
			string temp="";
			int flag=0,j=0,strt_float=0;
			float nos;
			for(int i=pos_fun;i<=l-1;i++){
				if(isdigit(eqn[i])||eqn[i]=='.'||eqn[i]=='-'){
					temp.push_back(eqn[i]);
					flag=1;
					strt_float=i;
				}
				else if(!isdigit(eqn[i])&&flag==1){
					nos=stof(temp);
					break;
				}
			}
			//cout<<"Negetopm flag "<<negation_flag<<endl;
			float res=sqrt(nos);
			if(isnan(res))
				return "INFINITY";
			if(negation_flag==1)
				res*=-1;
			string result=to_string(res);
			//cout<<"fjwrkef: "<<result<<endl;
			int length_to_be_added=result.size();
			int num_parenthesis=1; 
			int i;
			for(i=pos_fun+5;;i++){
				if(eqn[i]==')') break;
			}
			result="("+result+")";
			//cout<<"cwljvle: "<<result<<"pos: "<<pos_fun<<" "<<i<<endl;
			int length_to_be_removed=i-pos_fun+1;
			eqn.replace(pos_fun,length_to_be_removed,result);
			//return result;
		}

		if(eqn.find("abs")!=-1||eqn.find("-abs")!=-1){
		//	//cout<<"hello1"<<endl;
			int negation_flag=0;
			function_flag=1;
			int pos_fun=eqn.find("abs");
			if(pos_fun>0){
				if(eqn[pos_fun-1]=='-'){
					if(pos_fun>2){
						char temp=eqn[pos_fun-2];
						if(temp!=')'){
							negation_flag=1;
							pos_fun--;
							eqn=eqn.substr(1,eqn.size());
						}
					}
					else{
						negation_flag=1;
						pos_fun--;
						eqn=eqn.substr(1,eqn.size());	
					}
				}
			}
			int l=eqn.size();
			string temp="";
			int flag=0,j=0,strt_float=0;
			float nos;
			for(int i=pos_fun;i<=l-1;i++){
				if(isdigit(eqn[i])||eqn[i]=='.'||eqn[i]=='-'){
					temp.push_back(eqn[i]);
					flag=1;
					strt_float=i;
				}
				else if(!isdigit(eqn[i])&&flag==1){
					nos=stof(temp);
					break;
				}
			}
			//cout<<"Negetopm flag "<<negation_flag<<endl;
			float res=abs(nos);
			if(negation_flag==1)
				res*=-1;
			string result=to_string(res);
			//cout<<"fjwrkef: "<<result<<endl;
			int length_to_be_added=result.size();
			int num_parenthesis=1; 
			int i;
			for(i=pos_fun+4;;i++){
				if(eqn[i]==')') break;
			}
			result="("+result+")";
			//cout<<"cwljvle: "<<result<<"pos: "<<pos_fun<<" "<<i<<endl;
			int length_to_be_removed=i-pos_fun+1;
			eqn.replace(pos_fun,length_to_be_removed,result);
			//return result;
		}

		if(eqn.find("csc")!=-1||eqn.find("-csc")!=-1){
			//cout<<"hello1"<<endl;
			int negation_flag=0;
			function_flag=1;
			int pos_fun=eqn.find("csc");
			if(pos_fun>0){
				if(eqn[pos_fun-1]=='-'){
					if(pos_fun>2){
						char temp=eqn[pos_fun-2];
						if(temp!=')'){
							negation_flag=1;
							pos_fun--;
							eqn=eqn.substr(1,eqn.size());
						}
					}
					else{
						negation_flag=1;
						pos_fun--;
						eqn=eqn.substr(1,eqn.size());	
					}
				}
			}
			//cout<<"wah wah  "<<eqn<<endl;
			int l=eqn.size();
			string temp="";
			int flag=0,j=0,strt_float=0;
			float nos;
			for(int i=pos_fun;i<=l-1;i++){
				if(isdigit(eqn[i])||eqn[i]=='.'||eqn[i]=='-'){
					temp.push_back(eqn[i]);
					flag=1;
					strt_float=i;
				}
				else if(!isdigit(eqn[i])&&flag==1){
					nos=stof(temp);
					break;
				}
			}
			//cout<<"Negetopm flag "<<negation_flag<<endl;
			float res=1.0/sin(nos);
			if(negation_flag==1)
				res=(-1)*res;
			string result=to_string(res);
			//cout<<"fjwrkef: "<<result<<endl;
			int length_to_be_added=result.size();
			int num_parenthesis=1; 
			int i;
			for(i=pos_fun+4;;i++){
				if(eqn[i]==')') break;
			}
			result="("+result+")";
			//cout<<"cwljvle: "<<result<<"pos: "<<pos_fun<<" "<<i<<endl;
			int length_to_be_removed=i-pos_fun+1;
			eqn.replace(pos_fun,length_to_be_removed,result);
			//cout<<"od: "<<eqn<<endl;
			//cout<<"od2: "<<result<<endl;
			//return result;
		}
		if(eqn.find("cos")!=-1||eqn.find("-cos")!=-1){
			//cout<<"hello2"<<endl;
			function_flag=1;
			int pos_fun=eqn.find("cos");
			int negation_flag=0;
			if(pos_fun>0){
				if(eqn[pos_fun-1]=='-'){
					if(pos_fun>2){
						char temp=eqn[pos_fun-2];
						if(temp!=')'){
							negation_flag=1;
							pos_fun--;
							eqn=eqn.substr(1,eqn.size());
						}
					}
					else{
						negation_flag=1;
						pos_fun--;
						eqn=eqn.substr(1,eqn.size());	
					}
				}
			}
			int l=eqn.size();
			string temp="";
			int flag=0,j=0,strt_float=0;
			float nos;
			for(int i=pos_fun;i<=l-1;i++){
				if(isdigit(eqn[i])||eqn[i]=='.'||eqn[i]=='-'){
					temp.push_back(eqn[i]);
					flag=1;
					strt_float=i;
				}
				else if(!isdigit(eqn[i])&&flag==1){
					nos=stof(temp);
					//cout<<"mweljfwel: "<<temp<<endl;
					break;
				}
			}
			float res=cos(nos);
			if(negation_flag==1)
				res*=(-1);
			string result=to_string(res);
			int length_to_be_added=result.size();
			int num_parenthesis=1; 
			int i;
			for(i=pos_fun+4;num_parenthesis!=0 && i<=l-1;i++){
				if(eqn[i]=='(')	num_parenthesis++;
				if(eqn[i]==')')	num_parenthesis--;
			}	
			result="("+result+")";
			//cout<<"chorljvle: "<<result<<"pos: "<<pos_fun<<" "<<"Madarc"<<i<<endl;
			int length_to_be_removed=i-1-pos_fun+1;
			eqn.replace(pos_fun,length_to_be_removed,result);
			//cout<<"mhod: "<<eqn<<endl;			
		}
		if(eqn.find("sin")!=-1||eqn.find("-sin")!=-1){
			//cout<<"Hello"<<endl;
			function_flag=1;
			int pos_fun=eqn.find("sin");
			int negation_flag=0;
			if(pos_fun>0){
				if(eqn[pos_fun-1]=='-'){
					if(pos_fun>2){
						char temp=eqn[pos_fun-2];
						if(temp!=')'){
							negation_flag=1;
							pos_fun--;
							eqn=eqn.substr(1,eqn.size());
						}
					}
					else{
						negation_flag=1;
						pos_fun--;
						eqn=eqn.substr(1,eqn.size());	
					}
				}
			}
			//cout<<"MD yeh kya h: "<<pos_fun<<endl;
			int l=eqn.size();
			string temp="";
			int flag=0,j=0,strt_float=0;
			float nos;
			for(int i=pos_fun;i<=l-1;i++){
				if(isdigit(eqn[i])||eqn[i]=='.'||eqn[i]=='-'){
					temp.push_back(eqn[i]);
					flag=1;
					strt_float=i;
				}
				else if(!isdigit(eqn[i])&&flag==1){
					nos=stof(temp);
					break;
				}
			}
			float res=sin(nos);
			if(negation_flag==1)
				res*=(-1);
			string result=to_string(res);
			//cout<<"fjwrkef: "<<result<<endl;
			int length_to_be_added=result.size();
			int num_parenthesis=1; 
			int i;
			for(i=pos_fun+4;;i++){
				if(eqn[i]==')') break;
			}
			result="("+result+")";
			//cout<<"cwljvle: "<<result<<" pos: "<<pos_fun<<" "<<i<<endl;
			int length_to_be_removed=i-pos_fun+1;
			eqn.replace(pos_fun,length_to_be_removed,result);
			//cout<<"mod2: "<<result<<endl;
			//return result;
		}
		if(eqn.find("sec")!=-1||eqn.find("-sec")!=-1){
			//cout<<"hello3"<<endl;
			function_flag=1;
			int pos_fun=eqn.find("sec");
			int negation_flag=0;
			if(pos_fun>0){
				if(eqn[pos_fun-1]=='-'){
					if(pos_fun>2){
						char temp=eqn[pos_fun-2];
						if(temp!=')'){
							negation_flag=1;
							pos_fun--;
							eqn=eqn.substr(1,eqn.size());
						}
					}
					else{
						negation_flag=1;
						pos_fun--;
						eqn=eqn.substr(1,eqn.size());	
					}
				}
			}
			int l=eqn.size();
			string temp="";
			int flag=0,j=0,strt_float=0;
			float nos;
			for(int i=pos_fun;i<=l-1;i++){
				if(isdigit(eqn[i])||eqn[i]=='.'||eqn[i]=='-'){
					temp.push_back(eqn[i]);
					flag=1;
					strt_float=i;
				}
				else if(!isdigit(eqn[i])&&flag==1){
					nos=stof(temp);
					break;
				}
			}
			float res=1/cos(nos);
			if(negation_flag==1)
				res*=(-1);
			string result=to_string(res);
			//cout<<"fjwrkef: "<<result<<endl;
			int length_to_be_added=result.size();
			int num_parenthesis=1; 
			int i;
			for(i=pos_fun+4;;i++){
				if(eqn[i]==')') break;
			}
			result="("+result+")";
			//cout<<"cwljvle: "<<result<<"pos: "<<pos_fun<<" "<<i<<endl;
			int length_to_be_removed=i-pos_fun+1;
			eqn.replace(pos_fun,length_to_be_removed,result);
		
			//return result;
		}
		if(eqn.find("tan")!=-1||eqn.find("-tan")!=-1){
			//cout<<"hello4"<<endl;
			function_flag=1;
			int pos_fun=eqn.find("tan");int negation_flag=0;
			if(pos_fun>0){
				if(eqn[pos_fun-1]=='-'){
					if(pos_fun>2){
						char temp=eqn[pos_fun-2];
						if(temp!=')'){
							negation_flag=1;
							pos_fun--;
							eqn=eqn.substr(1,eqn.size());
						}
					}
					else{
						negation_flag=1;
						pos_fun--;
						eqn=eqn.substr(1,eqn.size());	
					}
				}
			}
			int l=eqn.size();
			string temp="";
			int flag=0,j=0,strt_float=0;
			float nos;
			for(int i=pos_fun;i<=l-1;i++){
				if(isdigit(eqn[i])||eqn[i]=='.'||eqn[i]=='-'){
					temp.push_back(eqn[i]);
					flag=1;
					strt_float=i;
				}
				else if(!isdigit(eqn[i])&&flag==1){
					nos=stof(temp);
					break;
				}
			}
			float res=sin(nos)/cos(nos);
			if(negation_flag==1)
				res*=(-1);
			string result=to_string(res);
			//cout<<"fjwrkef: "<<result<<endl;
			int length_to_be_added=result.size();
			int num_parenthesis=1; 
			int i;
			for(i=pos_fun+4;;i++){
				if(eqn[i]==')') break;
			}
			result="("+result+")";
			//cout<<"cwljvle: "<<result<<"pos: "<<pos_fun<<" "<<i<<endl;
			int length_to_be_removed=i-pos_fun+1;
			eqn.replace(pos_fun,length_to_be_removed,result);
			//return result;
		}
		if(eqn.find("cot")!=-1||eqn.find("-cot")!=-1){
			//cout<<"hello5"<<endl;
			function_flag=1;
			int pos_fun=eqn.find("cot");
			int negation_flag=0;
			if(pos_fun>0){
				if(eqn[pos_fun-1]=='-'){
					if(pos_fun>2){
						char temp=eqn[pos_fun-2];
						if(temp!=')'){
							negation_flag=1;
							pos_fun--;
							eqn=eqn.substr(1,eqn.size());
						}
					}
					else{
						negation_flag=1;
						pos_fun--;
						eqn=eqn.substr(1,eqn.size());	
					}
				}
			}
			int l=eqn.size();
			string temp="";
			int flag=0,j=0,strt_float=0;
			float nos;
			for(int i=pos_fun;i<=l-1;i++){
				if(isdigit(eqn[i])||eqn[i]=='.'||eqn[i]=='-'){
					temp.push_back(eqn[i]);
					flag=1;
					strt_float=i;
				}
				else if(!isdigit(eqn[i])&&flag==1){
					nos=stof(temp);
					break;
				}
			}
			float res=cos(nos)/sin(nos);
			if(negation_flag==1)
				res*=-1;
			string result=to_string(res);
			//cout<<"fjwrkef: "<<result<<endl;
			int length_to_be_added=result.size();
			int num_parenthesis=1; 
			int i;
			for(i=pos_fun+4;;i++){
				if(eqn[i]==')') break;
			}
			result="("+result+")";
			//cout<<"cwljvle: "<<result<<"pos: "<<pos_fun<<" "<<i<<endl;
			int length_to_be_removed=i-pos_fun+1;
			eqn.replace(pos_fun,length_to_be_removed,result);
			//return result;
		}

		if(eqn.find("log")!=-1||eqn.find("-log")!=-1){
			//cout<<"hello log"<<endl;
			function_flag=1;
			int pos_fun=eqn.find("log");
			int negation_flag=0;
			if(pos_fun>0){
				if(eqn[pos_fun-1]=='-'){
					if(pos_fun>2){
						char temp=eqn[pos_fun-2];
						if(temp!=')'){
							negation_flag=1;
							pos_fun--;
							eqn=eqn.substr(1,eqn.size());
						}
					}
					else{
						negation_flag=1;
						pos_fun--;
						eqn=eqn.substr(1,eqn.size());	
					}
				}
			}
			int l=eqn.size();
			string temp="";
			int flag=0,j=0,strt_float=0;
			float nos;
			int temp_break=0;
			for(int i=pos_fun;i<=l-1;i++){
				if(isdigit(eqn[i])||eqn[i]=='.'||eqn[i]=='-'){
					temp.push_back(eqn[i]);
					flag=1;
					strt_float=i;
				}
				else if(!isdigit(eqn[i])&&flag==1){
					nos=stof(temp);
					temp_break=i;
					break;
				}
			}
			string temp1="";
			flag=0;
			float nos1;
			for(int i=temp_break+1;i<=l-1;i++){
				if(isdigit(eqn[i])||eqn[i]=='.'||eqn[i]=='-'){
					temp1.push_back(eqn[i]);
					flag=1;
					strt_float=i;
				}
				else if(!isdigit(eqn[i])&&flag==1){
					//cout<<"THIS IS TEMP1 "<<temp1<<endl;
					nos1=stof(temp1);
					break;
				}
			}
			//cout<<"This is temp in log: "<<temp<<" "<<eqn[temp_break]<<endl;
			if(nos<0)
				return "INFINITY";
			if(nos1<0)
				return "INFINITY";
			float res=log(nos1)/log(nos);
			if(negation_flag==1)
				res*=-1;
			string result=to_string(res);
			//cout<<"fjwrkef: "<<result<<endl;
			int length_to_be_added=result.size();
			int num_parenthesis=1; 
			int i;
			for(i=pos_fun+4;;i++){
				if(eqn[i]==')') break;
			}
			result="("+result+")";
			//cout<<"cwljvle: "<<result<<"pos: "<<pos_fun<<" "<<i<<endl;
			int length_to_be_removed=i-pos_fun+1;
			eqn.replace(pos_fun,length_to_be_removed,result);
			//return result;
		}
	}

	/*Expression Evaluation*/{
		if((eqn.find(")+(")!=-1 ||eqn.find(")-(")!=-1 ||
		   eqn.find(")/(")!=-1 ||eqn.find(")*(")!=-1||
		   eqn.find("^")!=-1)){

			float result=0;
			string temp="";
			string numbers[26];
			string alphabet[26];
			for(int i=0;i<=25;i++){
				char w='A'+i;
				alphabet[i].push_back(w);
			}
			int l=eqn.size();
			int k=0;
			for(int i=0;i<=eqn.size()-1;i++){
				if(eqn[i]=='('){
					int close_paren=eqn.find(')');
					//cout<<"chya: "<<i<<endl;
					numbers[k++]=eqn.substr(i,close_paren-i+1);
					eqn.replace(i,close_paren-i+1,alphabet[k-1]);

				}
			}
			//cout<<eqn<<endl;
			string post=infix_postfix(eqn);
			evaluated_string=evaluate_postfix(post,alphabet,numbers);
			return evaluated_string;
		}
	}
	int size_eqn=eqn.size();
	string temp_equation=eqn;
	int negation_flag_final=0;
	if(eqn.find("-(")!=-1){
		negation_flag_final=1;
	}
	if(negation_flag_final==1){
		temp_equation=temp_equation.substr(2,size_eqn-1);
	}
	else
		temp_equation=temp_equation.substr(1,size_eqn-1);

	temp_equation=temp_equation.substr(0,size_eqn-2);

	if(negation_flag_final)
		temp_equation="-"+temp_equation;


	return temp_equation;
}
string travel(evaluate &equation){
	int l=equation.string_size();
	string result;
	string part="";
	int i,j;
	for(j=max_p;j>=0;j--){
		part="";
		int flag=0;
		for(i=0;i<=equation.string_size()-1;i++){
			if((int)(equation.priority[i])-48>=j){
				//cout<<equation.eq[i];
				
				int pri=(int)(equation.priority[i]);
				pri--;
			//	//cout<<"fuck thos : "<<pri <<endl;
				equation.priority[i]=(char)(pri);
				//cout<<"fuck thos : "<<equation.priority[i]<<endl;
				part.push_back(equation.eq[i]);
				flag=1;
			}
			else if(flag==1&& ((int)equation.priority[i]-48)<j){
				//cout<<"Hello od: "<<endl<<endl;
				result=solve(part);
				if(result.find("inf")!=-1)
					continue;
				if(result.find("nan")!=-1)
					continue;
				if(result=="INFINITY")
					return "nan";
				//cout<<result<<" result of this part "<<part<<endl;
				string wow=equation.eq;
				int w=0;
				here: wow=equation.eq.substr(w,equation.eq.size());
				int pos=wow.find(part);
				if(((int)equation.priority[w+pos]-48)+1!=j){
					//cout<<"this is w: "<<w<<" "<<wow<<" "<<pos<<" "<<j<<endl;
					//cout<<" "<<(int)((int)equation.priority[pos+w]-48)+1<<endl;
					w=w+1;
					goto here;
				//	//cout<<"kwefmwelkjlk3ncelfcnerknfvenfergnvengfvagvbrnfvuinrgfvu4hnfr4g"<<endl;
					//continue;
				}
				//cout<<"here: "<<w+pos<<endl;
				int size_to_be_removed=0;
				if(equation.eq[pos-1]=='*'||equation.eq[pos-1]=='+'||
					equation.eq[pos-1]=='/'||equation.eq[pos-1]=='-'||
					equation.eq[pos-1]=='^')
					size_to_be_removed=part.size();
				else
					size_to_be_removed=part.size();
				 
				equation.eq.replace(w+pos,size_to_be_removed,result);
				//for(int k=0;k<=())
				//equation.priority.replace(w+pos,size_to_be_removed,priority_result);
				equation.set_priority();
				//cout<<equation.priority;
				flag=0;
				//cout<<endl<<equation.eq<<" after a loop"<<endl;
				//cout<<equation.priority<<endl;
				i=i+(result.size()-part.size());
				part="";
			}
			else if(flag==1){
				part="";
				flag=0;
			}
		}
	}
//	//cout<<"choyal: "<<part<<endl;
//	//cout<<"yeh "<<solve(part)<<endl;
	return solve(part);
}

float solver(float a, evaluate equation){
    float val=(float)a;
    equation.replace_x(val);
    equation.set_priority();
    max_p=equation.max_priority();
    string ans=travel(equation);
    if(ans=="nan")
    	ans="0";
    float y=stof(ans);
    return y;
}


int tp,btm,lef,righ,height,width;
void init2D(float r, float g, float b){
    glClearColor(r,g,b,0.0);  
    glMatrixMode (GL_PROJECTION);
    cout << "     -> Enter the xRangeMin :        |	";
	cin >> lef;
    cout << " |_____________________________________________________________________________________________________________________________|\n";
	cout << " |                                                                                                                             |\n";


	cout << "     -> Enter the xRangeMax :        |	";
	cin >> righ;
	cout << " |_____________________________________________________________________________________________________________________________|\n";
	cout << " |                                                                                                                             |\n";

	cout << "     -> Enter the yRangeMin :        |	";
	cin >> btm;
	cout << " |_____________________________________________________________________________________________________________________________|\n";
	cout << " |                                                                                                                             |\n";

	cout << "     -> Enter the yRangeMax :        |	";
	cin >> tp;
	cout << " |_____________________________________________________________________________________________________________________________|\n";
	cout << " |                                                                                                                             |\n";

    gluOrtho2D (lef,righ, btm, tp); //co-ordinate of view-port
    float scale=0.1*height;
    float scale_x=0.0001*width;
}

float tranform_x(float x){
	float numer;
	float denom;

	numer=(righ-lef)*(x-0);
	denom=width;

	return (float)lef+numer/(denom*1.0);
}

float tranform_y(float y){
	float numer,denom;

	numer=(tp-btm)*(y-1000);
	denom=-height;

	return (float)btm+numer/(denom*1.0);
}

void printtext(float x, float y, string String)
{
//(x,y) is from the bottom left of the window
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(lef,righ,btm,tp);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    glRasterPos2f(x,y);
    for (int i=0; i<String.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
    }
    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

float mousex,mousey;
void mouse(int button, int state, int x, int y)
{
   // Save the mouse position
   mousex = x;
   mousey = y;

   mousex=tranform_x(x);
   mousey=tranform_y(y);

   //..std:://cout<<"WOWOWOWOWOWOWO"<<" "<<mousex<<" "<<mousey<<endl;

   char strin[64];

   string cordinate=to_string(mousex);
 //  for(int p=0;p<=cordinate.size();p++)	
 //  		strin[p]=cordinate[p];
  // printtext(mousex,mousey,cordinate);
}


static int x_zoom=0;
static int y_zoom=0;
static int move_x=0;
static int move_y=0;
static int flag_get_eq=0;
//evaluate equation;
evaluate equation;
int coubt_x=0;
int coubt_y=0;

void display2(){
	if(flag_get_eq==0)
		equation.get_eq();
	equation.replace_cosec();

 //   printtext(5,5,"The Graph of The equation: "+ equation.eq);

	
	flag_get_eq=1;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

	glScaled(1+x_zoom/100.0,1+y_zoom/100.0,0);
	glTranslated(move_x/10.0,move_y/10.0,0);

    /*Drawing the axes and blocks*/{
    	//x-axis
	    glBegin(GL_LINES);
	        glColor3f(1.0, 1.0, 1.0);
	        glVertex2i(-999999,0);
	        glVertex2i(999999,0);
	    glEnd();
	    //y-axis
	    glBegin(GL_LINES);
	        glColor3f(1.0, 1.0, 1.0);
	        glVertex2i(0,-999999);
	        glVertex2i(0,999999);
	    glEnd();

	    //m=inf lines lines along x-axis;
	    for(int i=-999; i<=999;i++){
	    	if(i==0)	
	    		continue;
	    	glBegin(GL_LINES);
		        glColor3f(0.2, 0.2 , 0.2);
		        glVertex2i(i,-999999);
		        glVertex2i(i,999999);
	    	glEnd();
	    }

	    //m=0 lines along the y-axis
	    for(int i=-999; i<=999;i++){
	    	if(i==0)	
	    		continue;
	    	glBegin(GL_LINES);
		        glColor3f(0.2, 0.2 , 0.2);
		        glVertex2i(-999999,i);
		        glVertex2i(999999,i);
	    	glEnd();
	    }
	}

    glColor3f(1.0, 1.0, 0.0); //color of the graph

    float y,y1;
	//evaluate equation;
    //equation.replace_cosec();

    float scale=width/(righ-lef);
    float scale_y=height/(tp-btm);

    for(int i=lef;i<=righ;i++){
    	for(float k=0;k<=1;k+=(1/scale)){
    		float x=i+k;
    		y=solver(x,equation);
	        y1=solver(x+1/scale,equation);

	        if(isnan(y))	continue;
	        if(isnan(y1))	continue;
	        if(isinf(y))	continue;
	        if(isinf(y1))	continue;

	       

	        /*Rounding off y to 0.5*/
	        if(y>0){	if((int)y<(int)(y+0.5*(1/scale_y)))		y+=1/scale_y;	}
			else{	 if((int)y>(int)(y-0.5*(1/scale_y)))	y-=1/scale_y;	}

			/*Rounding off y1 to 0.5*/
			if(y1>0){	if((int)y1<(int)(y1+0.5*(1/scale_y)))		y1+=1/scale_y;	}
			else{	 if((int)y1>(int)(y1-0.5*(1/scale_y)))	y1-=1/scale_y;	}


	        glBegin(GL_LINES);
	            glVertex2f(x,y);
	            glVertex2f(x+1/scale,y1);
	        glEnd(); 
    	}
    }
    glFlush();
}

void keyPressed(unsigned char key, int x, int y){
	//cout<<"maaaa"<<endl;
	/*Map*/

	/*Zoom-in Zoom-out x*/
	if(key=='w'){//zoom in
		x_zoom=1;
		y_zoom=0;
		move_y=0;
		move_x=0;
		glutPostRedisplay();
	}
	else if(key=='s'){//zoom out
		x_zoom=-1;
		y_zoom=0;
		move_y=0;
		move_x=0;
		glutPostRedisplay();
	}
	/*traversing x*/
	else if(key=='a'){//to +inf
		x_zoom=0;
		y_zoom=0;
		move_y=0;
		move_x=1;
		glutPostRedisplay();
	}
	else if(key=='d'){//to -inf
		x_zoom=0;
		y_zoom=0;
		move_y=0;
		move_x=-1;
		glutPostRedisplay();
	}

	/*Zoom-in Zoom out y*/
	else if(key=='p'){//zoom in
		x_zoom=0;
		y_zoom=1;
		move_y=0;
		move_x=0;
		glutPostRedisplay();
	}
	else if(key=='l'){//zoom out
		x_zoom=0;
		y_zoom=-1;
		move_y=0;
		move_x=0;
		glutPostRedisplay();
	}

	/*traversing y*/
	else if(key=='o'){//to +inf
		x_zoom=0;
		y_zoom=0;
		move_y=1;
		move_x=0;
		glutPostRedisplay();
	}
	else if(key=='k'){//to -inf
		x_zoom=0;
		y_zoom=0;
		move_y=-1;
		move_x=0;
		glutPostRedisplay();
	}
}

/*int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    cin>>height;
    cin>>width;
    glutInitWindowSize (height, width);
    glutCreateWindow ("Hello Graph");
    glutKeyboardFunc(keyPressed);
    glutMouseFunc(mouse);
    init2D(0.0,0.0,0.0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}*/