#include <linux/linkage.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>

char *all_var_names[20];
int *p[20];
int place_holder = 0;

struct set_to{
	char *name;
	char *def;};


asmlinkage int SaveVariable(char *varname, char * vardef){
		
		int status = -1;
		
		struct set_to variable;  
		
		variable.name = varname;
		variable.def= vardef;

		char *kernel_ptr = kmalloc(sizeof(variable), GFP_USER);		

		copy_from_user(kernel_ptr, &variable, sizeof(variable));
		
		if(copy_from_user == 0){
			status = 0;
			all_var_names[place_holder] = varname;
			place_holder ++;}
		
		return status;
}

asmlinkage int GetVariable(char *varname, char *vardef, int deflen){

		char buff[deflen];

		int status = -1;

		for(int i = 0; i < sizeof(all_var_names); i++){
			
			if(strcmp(all_var_names[i], varname)){
				copy_to_user(&buff, p[i], deflen);
				status = 0;}}
		
		vardef = buff;

}

asmlinkage int NextVariable(char *prevname, char *varname, int namelen, char *vardef, int deflen){
		
		char tmp_name[namelen];
		char tmp_def[deflen];

		int status = -1;
		int i = 0;
		while(strcmp(all_var_names[i], prevname) == 0 && i <21){i++;}

		copy_to_user(&tmp_def, p[i+1], deflen);	
		varname = all_var_names[i+1];
		vardef = tmp_def;

		prevname = varname;
}
