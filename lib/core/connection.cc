#include "connection.hh"
#include "core.hh"
#include <xcb/xcbext.h>
#include <iostream>
#include <sstream>

Napi::FunctionReference Connection::constructor;

Napi::Object Connection::Init(Napi::Env env, Napi::Object exports)
{
	Napi::HandleScope scope(env);

	auto classDefinition = DefineClass(env, "Connection", {
		InstanceMethod("connect", &Connection::Connect),
		InstanceMethod("connectionHasError", &Connection::ConnectionHasError),
		InstanceMethod("disconnect", &Connection::Disconnect),
		InstanceMethod("flush", &Connection::Flush),
		InstanceMethod("getFileDescriptor", &Connection::GetFileDescriptor),
		InstanceMethod("pollForEvent", &Connection::PollForEvent),
		InstanceMethod("pollForReply", &Connection::PollForReply)
	});

	constructor = Napi::Persistent(classDefinition);
	constructor.SuppressDestruct();

	exports.Set("Connection", classDefinition);
	return exports;
}

Connection::Connection(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Connection>(info)
{
	this->connection = nullptr;
}

void Connection::Connect(const Napi::CallbackInfo& info)
{
	auto env = info.Env();
	Napi::HandleScope scope(env);

	const char* displayName = nullptr;
	int screen = 0;

	if(info.Length() > 0)
	{
		if(!info[0].IsString())
		{
			Napi::TypeError::New(env, "Display name must be a string").ThrowAsJavaScriptException();
			return;
		}
		else
		{
			displayName = std::string(info[0].As<Napi::String>()).c_str();
		}
	}

	if(info.Length() > 1)
	{
		if(!info[1].IsNumber())
		{
			Napi::TypeError::New(env, "Screen must be a number").ThrowAsJavaScriptException();
			return;
		}
		else
		{
			screen = info[1].As<Napi::Number>();
		}
	}

	this->connection = xcb_connect(displayName, &screen);
	int error = this->ConnectionHasError(info).As<Napi::Number>();
	if(error)
	{
		this->Disconnect(info);
		std::ostringstream message;
		message << "Failed to connect to X server (Error " << error << ")";
		Napi::Error::New(env, message.str()).ThrowAsJavaScriptException();
	}
}

Napi::Value Connection::ConnectionHasError(const Napi::CallbackInfo& info)
{
	return Napi::Number::New(info.Env(), xcb_connection_has_error(this->connection));
}

void Connection::Disconnect(const Napi::CallbackInfo& info)
{
	xcb_disconnect(this->connection);
}

Napi::Value Connection::Flush(const Napi::CallbackInfo& info)
{
	return Napi::Number::New(info.Env(), xcb_flush(this->connection));
}

Napi::Value Connection::GetFileDescriptor(const Napi::CallbackInfo& info)
{
	return Napi::Number::New(info.Env(), xcb_get_file_descriptor(this->connection));
}

Napi::Value Connection::PollForEvent(const Napi::CallbackInfo& info)
{
	auto env = info.Env();
	auto generic_event = xcb_poll_for_event(this->connection);
	if(!generic_event)
	{
		return env.Null();
	}

	auto genericEventObject = Core::CreateGenericEventObject(info, generic_event);
	delete generic_event;

	return genericEventObject;
}

Napi::Value Connection::PollForReply(const Napi::CallbackInfo& info)
{
	auto env = info.Env();
	if(info.Length() != 1 || !info[0].IsNumber())
	{
		Napi::TypeError::New(env, "Request sequence number expected").ThrowAsJavaScriptException();
		return env.Undefined();
	}

	unsigned int request = info[0].As<Napi::Number>();
	void* reply;
	xcb_generic_error_t* error;
	if(!xcb_poll_for_reply(this->connection, request, &reply, &error))
	{
		return env.Null();
	}

	if(reply)
	{
		return Core::CreateGenericReplyObject(info, (xcb_generic_reply_t*) reply);
	}
	if(error)
	{
		return Core::CreateGenericErrorObject(info, error);
	}

	return env.Undefined();
}