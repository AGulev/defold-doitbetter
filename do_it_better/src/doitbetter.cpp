#define EXTENSION_NAME DoItBetter
#define LIB_NAME "DoItBetter"
#define MODULE_NAME "do_it_better"

#define DLIB_LOG_DOMAIN LIB_NAME

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_ANDROID)

#include "utils/LuaUtils.h"
#include "doitbetter_private.h"
#include "doitbetter_callback.h"
#include <stdlib.h>

namespace dmDoItBetter {

    static int Lua_Initialize(lua_State* L)
    {
        DM_LUA_STACK_CHECK(L, 0);
        if (lua_type(L, 1) != LUA_TSTRING) {
            return DM_LUA_ERROR("Expected string, got %s. Wrong type for Key variable '%s'.", luaL_typename(L, 1), lua_tostring(L, 1));
        }
        const char* key_lua = luaL_checkstring(L, 1);
        Initialize(key_lua);
        return 0;
    }

    static int Lua_SetLoggingEnabled(lua_State* L)
    {
        DM_LUA_STACK_CHECK(L, 0);
        bool enabled = luaL_checkbool(L, 1);
        SetLoggingEnabled(enabled);
        return 0;
    }

    static int Lua_MarkAsDevelopment(lua_State* L)
    {
        DM_LUA_STACK_CHECK(L, 0);
        MarkAsDevelopment();
        return 0;
    }

    static int Lua_SetCallback(lua_State* L)
    {
        DM_LUA_STACK_CHECK(L, 0);
        SetLuaCallback(L, 1);
        return 0;
    }

    static int Lua_SendEvent(lua_State* L)
    {
        const char* eventName = luaL_checkstring(L, 1);
        const char* deduplicateID = luaL_checkstring(L, 3);
        if (lua_type(L, 3) != LUA_TNONE) {
            lua_remove(L, 3);
        }
        lua_remove(L, 1);
        char* jsonString = 0;
        size_t json_length = 0;
        
        if (dmScript::LuaToJson(L, &jsonString, &json_length))
        {
            SendEvent(eventName, jsonString, deduplicateID);
            free(jsonString);
        } 
        return 0;
    }

    static const luaL_reg Module_methods[] =
    {
        {"initialize", Lua_Initialize},
        {"set_logging_enabled", Lua_SetLoggingEnabled},
        {"mark_as_development", Lua_MarkAsDevelopment},
        {"set_callback", Lua_SetCallback},
        {"send_event", Lua_SendEvent},
        {0, 0}
    };

    static void LuaInit(lua_State* L)
    {
        DM_LUA_STACK_CHECK(L, 0);
        luaL_register(L, MODULE_NAME, Module_methods);

        #define SETCONSTANT(name) \
        lua_pushnumber(L, (lua_Number) name); \
        lua_setfield(L, -2, #name); \

        SETCONSTANT(MSG_SANDBOX_STATUS)
        SETCONSTANT(MSG_ENABLE_STATUS)

        SETCONSTANT(EVENT_SUCCESS)
        SETCONSTANT(EVENT_JSON_ERROR)

        #undef SETCONSTANT

        const char* STATUS_SANDBOX =                  "sdbx";
        const char* STATUS_UNKNOWN =                  "ukwn";
        const char* STATUS_PRODUCTION =               "prod";

        #define SETCONSTANT(name) \
        lua_pushstring(L, name); \
        lua_setfield(L, -2, #name); \

        SETCONSTANT(STATUS_SANDBOX)
        SETCONSTANT(STATUS_UNKNOWN)
        SETCONSTANT(STATUS_PRODUCTION)

        #undef SETCONSTANT

        lua_pop(L, 1);
    }

    static dmExtension::Result AppInitializeDoItBetter(dmExtension::AppParams* params)
    {
        return dmExtension::RESULT_OK;
    }

    static dmExtension::Result InitializeDoItBetter(dmExtension::Params* params)
    {
        LuaInit(params->m_L);
        Initialize_Ext();
        InitializeCallback();
        return dmExtension::RESULT_OK;
    }

    static dmExtension::Result AppFinalizeDoItBetter(dmExtension::AppParams* params)
    {
        return dmExtension::RESULT_OK;
    }

    static dmExtension::Result FinalizeDoItBetter(dmExtension::Params* params)
    {
        FinalizeCallback();
        return dmExtension::RESULT_OK;
    }

    static dmExtension::Result UpdateDoItBetter(dmExtension::Params* params)
    {
        UpdateCallback();
        return dmExtension::RESULT_OK;
    }

} //namespace dmDoItBetter

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, dmDoItBetter::AppInitializeDoItBetter, dmDoItBetter::AppFinalizeDoItBetter, dmDoItBetter::InitializeDoItBetter, dmDoItBetter::UpdateDoItBetter, 0, dmDoItBetter::FinalizeDoItBetter)

#else

static  dmExtension::Result InitializeDoItBetter(dmExtension::Params* params)
{
    dmLogInfo("Registered extension DoItBetter (null)");
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeDoItBetter(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, 0, 0, InitializeDoItBetter, 0, 0, FinalizeDoItBetter)

#endif // Android
