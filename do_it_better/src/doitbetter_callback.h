#if defined(DM_PLATFORM_ANDROID) //|| defined(DM_PLATFORM_IOS)
#pragma once

#include "doitbetter_private.h"
#include <dmsdk/sdk.h>

namespace dmDoItBetter {

struct CallbackData
{
    MessageId msg;
    char* json;
};

void SetLuaCallback(lua_State* L, int pos);
void UpdateCallback();
void InitializeCallback();
void FinalizeCallback();

void AddToQueueCallback(MessageId type, const char*json);

} //namespace

#endif
