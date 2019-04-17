#include "connection.hh"
#include <iostream>
#include <sstream>

Napi::FunctionReference Connection::constructor;

Napi::Object Connection::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);

    Napi::Function classDefinition = DefineClass(env, "Connection", {
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
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);

	const char* displayName = nullptr;
	int* screen = nullptr;

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
			screen = (int*) int(info[1].As<Napi::Number>());
		}
	}

	this->connection = xcb_connect(displayName, screen);
	int error = this->ConnectionHasError(info).As<Napi::Number>();
	if(error)
	{
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

void Connection::Flush(const Napi::CallbackInfo& info)
{
	xcb_flush(this->connection);
}

Napi::Value Connection::GetFileDescriptor(const Napi::CallbackInfo& info)
{
	return info.Env().Undefined();
}

Napi::Value Connection::PollForEvent(const Napi::CallbackInfo& info)
{
	return info.Env().Undefined();
}

Napi::Value Connection::PollForReply(const Napi::CallbackInfo& info)
{
	return info.Env().Undefined();
}