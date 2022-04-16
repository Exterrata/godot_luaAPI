#ifndef LUA_H
#define LUA_H

#include "core/object/ref_counted.h"
#include "core/core_bind.h"

#include "luasrc/lua.hpp"
#include <string>
#include <thread>
#include <mutex>

class Lua : public RefCounted {
  GDCLASS(Lua, RefCounted);

protected:
  static void _bind_methods();

public:
  Lua();
  ~Lua();
  
  void exposeFunction(Callable func, String name);
  void doFile( String fileName, bool protected_call = true , Object* CallbackCaller = nullptr , String callback = String() );
  void doString( String code, bool protected_call = true , Object* CallbackCaller = nullptr , String callback = String() );
  void setThreaded(bool thread);
  void killAll();

  Callable getCallable(int index);

  static void runLua( lua_State *L , String code, bool protected_call , Object* CallbackCaller , String callback, bool *executing );

  bool pushVariant(Variant var);
  bool pushGlobalVariant(Variant var, String name);
  bool luaFunctionExists(String function_name);
  
  Variant pullVariant(String name);
  Variant getVariant(int index = -1);
  Variant callFunction( String function_name, Array args, bool protected_call = true , Object* CallbackCaller = nullptr , String callback = String() );

  lua_State* getState();

    

  // Lua functions
  static void LineHook(lua_State *L, lua_Debug *ar);
  static int luaPrint(lua_State* state);
  static int luaExposedFuncCall(lua_State* state);

  std::map<const char*, const Callable> exposedFuncs;

private:
  lua_State *state;
  bool threaded;
  bool executing;
  Vector<Callable> callables;

private:
  void exposeConstructors(  );
  void createVector2Metatable(  );
  void createVector3Metatable(  );
  void createColorMetatable(  );

  static void handleError( lua_State *L , int lua_error );

};

#endif