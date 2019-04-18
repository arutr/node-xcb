#pragma once

#include <xcb/xcb.h>
#include <napi.h>

class Connection : public Napi::ObjectWrap<Connection>
{
	public:
		static Napi::Object Init(Napi::Env env, Napi::Object exports);
		Connection(const Napi::CallbackInfo& info);
	private:
		static Napi::FunctionReference constructor;

		void Connect(const Napi::CallbackInfo& info);
		Napi::Value ConnectionHasError(const Napi::CallbackInfo& info);
		void Disconnect(const Napi::CallbackInfo& info);
		Napi::Value Flush(const Napi::CallbackInfo& info);
		Napi::Value GetFileDescriptor(const Napi::CallbackInfo& info);
		Napi::Value PollForEvent(const Napi::CallbackInfo& info);
		Napi::Value PollForReply(const Napi::CallbackInfo& info);

		xcb_connection_t* connection;
};