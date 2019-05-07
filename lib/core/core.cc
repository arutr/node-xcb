#include "core.hh"

// xcb_void_cookie_t
// xcb_generate_id

Napi::Object CreateGenericErrorObject(const Napi::CallbackInfo& info, const xcb_generic_error_t* generic_error)
{
	auto env = info.Env();
	auto object = Napi::Object::New(env);
	object["responseType"] = Napi::Number::New(env, generic_error->response_type);
	object["errorCode"] = Napi::Number::New(env, generic_error->error_code);
	object["sequence"] = Napi::Number::New(env, generic_error->sequence);
	object["resourceId"] = Napi::Number::New(env, generic_error->resource_id);
	object["minorCode"] = Napi::Number::New(env, generic_error->minor_code);
	object["majorCode"] = Napi::Number::New(env, generic_error->major_code);
	object["pad0"] = Napi::Number::New(env, generic_error->pad0);
	object["pad"] = Napi::ArrayBuffer::New(env, (void*) generic_error->pad, sizeof(uint32_t) * 5);
	object["fullSequence"] = Napi::Number::New(env, generic_error->full_sequence);

	return object;
}


Napi::Object Core::CreateGenericEventObject(const Napi::CallbackInfo& info, const xcb_generic_event_t* generic_event)
{
	auto env = info.Env();
	auto object = Napi::Object::New(env);
	object["responseType"] = Napi::Number::New(env, generic_event->response_type);
	object["pad0"] = Napi::Number::New(env, generic_event->pad0);
	object["sequence"] = Napi::Number::New(env, generic_event->sequence);
	object["pad"] = Napi::ArrayBuffer::New(env, (void*) generic_event->pad, sizeof(uint32_t) * 7);
	object["fullSequence"] = Napi::Number::New(env, generic_event->full_sequence);

	return object;
}

Napi::Object Core::CreateGenericReplyObject(const Napi::CallbackInfo& info, const xcb_generic_reply_t* generic_reply)
{
	auto env = info.Env();
	auto object = Napi::Object::New(env);
	object["responseType"] = Napi::Number::New(env, generic_reply->response_type);
	object["pad0"] = Napi::Number::New(env, generic_reply->pad0);
	object["sequence"] = Napi::Number::New(env, generic_reply->sequence);
	object["length"] = Napi::Number::New(env, generic_reply->length);

	return object;
}