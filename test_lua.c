
#include <stdlib.h>
#include <stdio.h>

/* Include the Lua API header files. */
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

int main(void)
{


	/* Declare a Lua State, open the Lua State and load the libraries (see above). */
	lua_State *l;
	l = luaL_newstate();
    luaL_openlibs(l);

	/* You can do what you want here. Note: Remember to update the libraries used (see above) */
	/* if you add to your program and use new Lua libraries. */
	/* In the lines below, I load and run the Lua code contained in the file */
	/* "script.lua". */
	/* Plus print some text directly from C. */
    char *command[100];
	printf("This line in directly from C\n\n");

    while(1) {
        printf(">> ");
        if (gets(command) == NULL)
            break;
        luaL_loadstring(l, command);
        lua_pcall(l, 0, 0, 0);
    }

	printf("\nBack to C again\n\n");

	/* Remember to destroy the Lua State */
	lua_close(l);

	return 0;
}
