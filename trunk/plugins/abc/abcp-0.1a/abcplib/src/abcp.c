#include "abcp.h"

typedef enum {
  ERR_FIRST=0,
  ERR_NONE,  ERR_UNKNOWN, ERR_UNKTOKEN,
  ERR_NOLUA, ERR_ARGS, ERR_SCAN,
  ERR_LAST
} Errors;

#ifdef LUA

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

static lua_State *L = NULL;

static const luaL_reg lualibs[] = {
  {"base", luaopen_base},
  {"table", luaopen_table},
  {"io", luaopen_io},
  {"string", luaopen_string},
  {"math", luaopen_math},
  {"debug", luaopen_debug},
  {"loadlib", luaopen_loadlib},
  {NULL, NULL}
};

static int init_lua()
{
  luaL_reg *lib = lualibs;

  L = lua_open();  /* create state */
  if (L) {
    for (; lib->func; lib++) {
      lib->func(L);  /* open library */
      lua_settop(L, 0);  /* discard any results */
    }
  }

  return (L == NULL);
}
#endif

int myhandler(abcHandle h)
{
  int t; char *s;char *f;USHORT l; USHORT c;
  char *x; char*y;
  
  t=abcToken(h);
  s=abcString(h);
  f=abcFilename(h);
  l=abcLine(h);
  c=abcColumn(h);
  x=abcStateName(abcState(h));
  
#ifdef LUA  
  if (L) {
    lua_getglobal(L,"abcHandler");
    lua_pushstring(L,x);
    lua_pushstring(L,abcTokenName(t));
    lua_pushstring(L,s);
    lua_pushstring(L,f);
    lua_pushnumber(L,l);
    lua_pushnumber(L,c);
    lua_call(L,6,1);
    return(0);
/*    return(lua_pcall(L,6,1,0));*/
  }
  else
#endif
  {
    printf("%s %03d,%03d:%s %s\n",x,l,c,abcTokenName(t),s);
    
    y=abcParsedString(h);
    
    if (*y && *y != '?') printf("%s\n",y); 
    return 0;
  }
}

char *test="X:2\nK:Am \\\n =A\nABC D| (3EFg,\\ \n gG'";

int main(int argc,char *argv[])
{
  static Errors err=ERR_NONE;
 
  if (argc < 2) {
    
    abcScanString(test,myhandler);
    
    fprintf(stderr,"Usage: abcp file.abc [handlers.lua]\n");
    err=ERR_ARGS;
  }
  else if (argc > 2) { 
    #ifdef LUA
    if (init_lua()) {
      fprintf(stderr,"ERROR! Cannot initialize Lua\n");
      err=ERR_NOLUA;
    }
    if (err == ERR_NONE) {
      lua_dofile(L,argv[2]);
    }
    #endif
  }

  if (err == ERR_NONE) {   
    if (abcScanFile(argv[1],myhandler)) {
      fprintf(stderr,"ERROR! cannot scan %s\n",argv[1]);
      err=ERR_SCAN;
    }
  }
#ifdef LUA  
  if (L) lua_close(L);
  L=NULL;
#endif
  return(err);
}


