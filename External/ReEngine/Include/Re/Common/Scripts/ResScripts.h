#pragma once
// module include file



// Data scripts are used to save & load constant data to files
// No logic or any if statements should be included
#include <Re\Common\Scripts\ResDataScriptLoader.h>
#include <Re\Common\Scripts\ResDataScriptSaver.h>


// ISerialisable interface
#include <Re\Common\Scripts\ResISerialisable.h>





/*support for multi line statements like:
<initial >
	< sub line 1 >
	< sub line 2 >
	// ect
<\>
*/
#define DATA_SCRIPT_MULTILINE(file, loader) \
while( loader.nextLine(file), loader.getLine() != "\\" )


/* DATA_SCRIPT_MULTILINE save version
*/

#define DATA_SCRIPT_MULTILINE_SAVE(file, saver, b)	\
while(saver.nextLine(file) , b);					\
saver.setEndLine();									\
/*
small example of how to use this
brackets looks strange, but probably there is no other way

void load( ostream& file, DataScriptSaver& saver)
{
	list<int> v;
	for(auto it : v){
		saver.save("vi", it);
	DATA_SCRIPT_MULTILINE_SAVE(file, saver)
}
*/