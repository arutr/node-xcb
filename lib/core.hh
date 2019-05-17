#pragma once

#include <xcb/xcb.h>
#include <napi.h>

namespace Core
{
	Napi::Object CreateGenericEventObject(const Napi::CallbackInfo& info, const xcb_generic_event_t* generic_event);
	Napi::Object CreateGenericErrorObject(const Napi::CallbackInfo& info, const xcb_generic_error_t* generic_error);
	Napi::Object CreateGenericReplyObject(const Napi::CallbackInfo& info, const xcb_generic_reply_t* generic_reply);
	Napi::Object CreateVoidCookie(const Napi::CallbackInfo& info, const xcb_void_cookie_t* void_cookie);
}