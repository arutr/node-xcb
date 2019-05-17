#pragma once

#define CALLBACK_INFO const Napi::CallbackInfo& info

#include <xcb/xcb.h>
#include <napi.h>

class Connection : public Napi::ObjectWrap<Connection>
{
	public:
		static Napi::Object Init(Napi::Env env, Napi::Object exports);
		Connection(CALLBACK_INFO);
	private:
		static Napi::FunctionReference constructor;

		Napi::Value AllowEvents(CALLBACK_INFO);
		void 		Connect(CALLBACK_INFO);
		Napi::Value ConnectionHasError(CALLBACK_INFO);
		void 		Disconnect(CALLBACK_INFO);
		Napi::Value Flush(CALLBACK_INFO);
		Napi::Value GenerateId(CALLBACK_INFO);
		Napi::Value GetFileDescriptor(CALLBACK_INFO);
		Napi::Value PollForEvent(CALLBACK_INFO);
		Napi::Value PollForReply(CALLBACK_INFO);

		xcb_connection_t* connection;
};