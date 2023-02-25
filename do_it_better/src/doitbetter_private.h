#if defined(DM_PLATFORM_ANDROID)

#pragma once

namespace dmDoItBetter {

    // The same events and messages are in DoItBetterDefoldJNI.java
    // If you change enums here, pls nake sure you update the constants there as well

    enum MessageId
    {
        MSG_SANDBOX_STATUS =              1,
        MSG_ENABLE_STATUS =               2
    };

    enum MessageEvent
    {
        EVENT_SUCCESS =                   1,
        EVENT_JSON_ERROR =                2
    };
    
    void Initialize_Ext();

    void Initialize(const char* key);
    void SetLoggingEnabled(bool enabled);
    void MarkAsDevelopment();
    void SendEvent(const char* eventName, const char* jsonString, const char* deduplicateID);

} //namespace dmDoItBetter

#endif
