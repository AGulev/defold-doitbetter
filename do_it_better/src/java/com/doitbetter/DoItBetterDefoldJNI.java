package com.doitbetter;

import android.app.Activity;
import android.app.Application;
import android.util.Log;

import org.json.JSONArray;
import org.json.JSONObject;
import org.json.JSONException;

import com.doitbetter.sdk.GameBoostSDK;
import com.doitbetter.sdk.outbus.GameBoostOutBus;
import com.doitbetter.sdk.network.models.requests.DIBSandboxStatus;

public class DoItBetterDefoldJNI {

    private static final String TAG = "DoItBetterDefoldJNI";

    private static final int MSG_SANDBOX_STATUS =         1;
    private static final int MSG_ENABLE_STATUS =          2;

    private static final int EVENT_SUCCESS =              1;
    private static final int EVENT_JSON_ERROR =           2;

    public static native void doItBetterAddToQueue(int msg, String json);

    private Activity activity;

    public DoItBetterDefoldJNI(Activity activity) {
        this.activity = activity;
    }

    public void initialize(String key) {
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                GameBoostSDK.Companion.initialize(activity.getApplication(), key, new GameBoostOutBus() {
                    @Override
                    public void send(DIBSandboxStatus sandboxStatus) {
                        sendSimpleMessage(MSG_SANDBOX_STATUS, EVENT_SUCCESS, "status", sandboxStatus.getSerializedName());
                    }

                    @Override
                    public void send(boolean boostEnabled) {
                        sendSimpleMessage(MSG_ENABLE_STATUS, EVENT_SUCCESS, "enabled", boostEnabled);
                    }

              });
            }
        });
    }

    public void enableLogging(boolean enable) {
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                GameBoostSDK.Companion.enableLogging(enable);
            }
        });
    }

    public void markAsDevelopment() {
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                GameBoostSDK.Companion.markAsDevelopment();
            }
        });
    }

    public void sendEvent(String eventName, String jsonString, String deduplicateID) {
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                GameBoostSDK.Companion.sendEvent(eventName, jsonString, deduplicateID);
            }
        });
    }

    private String getJsonConversionErrorMessage(String messageText) {
        String message = null;
          try {
              JSONObject obj = new JSONObject();
              obj.put("error", messageText);
              obj.put("event", EVENT_JSON_ERROR);
              message = obj.toString();
          } catch (JSONException e) {
              message = "{ \"error\": \"Error while converting simple message to JSON.\", \"event\": "+EVENT_JSON_ERROR+" }";
          }
        return message;
      }

    private void sendSimpleMessage(int msg, int eventId, String key_1, boolean value_1) {
      String message = null;
      try {
          JSONObject obj = new JSONObject();
          obj.put("event", eventId);
          obj.put(key_1, value_1);
          message = obj.toString();
      } catch (JSONException e) {
          message = getJsonConversionErrorMessage(e.getLocalizedMessage());
      }
      doItBetterAddToQueue(msg, message);
    }

    private void sendSimpleMessage(int msg, int eventId, String key_1, String value_1) {
      String message = null;
      try {
          JSONObject obj = new JSONObject();
          obj.put("event", eventId);
          obj.put(key_1, value_1);
          message = obj.toString();
      } catch (JSONException e) {
          message = getJsonConversionErrorMessage(e.getLocalizedMessage());
      }
      doItBetterAddToQueue(msg, message);
    }
}
