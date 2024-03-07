#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void Json_Pack_Example(void)
{
	json_t *array, *integer,*string,*str;
	
	char *output;
	/* JSON-OBJECT */
	json_t *obj = json_object(); 								// Define a new json obj.
	

	size_t obj_size = json_object_size(obj); 		// Get the size of the json obj.
	printf("The size of obj:%d\n",obj_size);
	
	char *key = "name:";
	string = json_string("Code Boy"); // Set the value of integer json obj.
	int ret = json_object_set(obj,key,string); // Setup a new obj named "Hello" and the mapped value is 52.
	
	key = "location:";
	ret = json_object_set(obj,key,json_string("China-Beijing")); // Setup a new obj named "Hello" and the mapped value is 52.
	
	key = "company:";
	ret = json_object_set(obj,key,json_string("Feitianchegnxin")); // Setup a new obj named "Hello" and the mapped value is 52.

	output = json_dumps(obj, JSON_ENCODE_ANY);
	
	printf("\r\n\r\n\r\n\r\nout:%s\r\n", output);
	
	
	str = json_object_get(obj,"company");  
	
	printf("\r\n\r\n%s",json_string_value(str));   
	
	free(obj);
	free(output);
	
}
