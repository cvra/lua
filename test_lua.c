
#include <stdlib.h>
#include <stdio.h>

/* Include the Lua API header files. */
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

static int test_func(lua_State *l)
{

    lua_pushinteger(l, strlen(lua_tostring(l, -1)));
    return 1;
}


int main(void)
{


	/* Declare a Lua State, open the Lua State and load the libraries (see above). */
	lua_State *l;
	l = luaL_newstate();
    luaL_openlibs(l);

    lua_pushcfunction(l, test_func);
    lua_setglobal(l, "mylen");

	/* You can do what you want here. Note: Remember to update the libraries used (see above) */
	/* if you add to your program and use new Lua libraries. */
	/* In the lines below, I load and run the Lua code contained in the file */
	/* "script.lua". */
	/* Plus print some text directly from C. */
    char command[100];
    char real_command[100];
    int ret;

    while(1) {
        printf(">> ");

        if (fgets(command, 100, stdin) == NULL)
            break;

        sprintf(real_command, "print(%s)", command);

        luaL_loadstring(l, real_command);
        ret = lua_pcall(l, 0, LUA_MULTRET, 0);
        if (ret) {
            lua_pop(l, 1);
            luaL_loadstring(l, command);
            ret = lua_pcall(l, 0, LUA_MULTRET, 0);
            if (ret) {
                printf("ERROR %d : %s\n", ret, lua_tostring(l, -1));
                lua_pop(l, 1);
            }
        }

        printf("top of stack : %d\n", lua_gettop(l));
    }

	/* Remember to destroy the Lua State */
	lua_close(l);

	return 0;
}
