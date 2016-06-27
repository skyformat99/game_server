/*
 * Block_Wrap.cpp
 *
 *  Created on: 2016年2月19日
 *      Author: zhangyalei
 */

#include "V8_Wrap.h"
#include "Buffer_Wrap.h"
#include "Log.h"

extern Global<ObjectTemplate> _g_buffer_template;

Local<Object> wrap_buffer(Isolate* isolate, Block_Buffer *buf) {
	EscapableHandleScope handle_scope(isolate);

	Local<ObjectTemplate> localTemplate = Local<ObjectTemplate>::New(isolate, _g_buffer_template);
	localTemplate->SetInternalFieldCount(1);
	Local<External> buf_ptr = External::New(isolate, buf);
	//将指针存在V8对象内部
	Local<Object> buf_obj = localTemplate->NewInstance(isolate->GetCurrentContext()).ToLocalChecked();
	buf_obj->SetInternalField(0, buf_ptr);

	return handle_scope.Escape(buf_obj);
}

Block_Buffer *unwrap_buffer(Local<Object> obj) {
	Local<External> field = Local<External>::Cast(obj->GetInternalField(0));
	void* ptr = field->Value();
	return static_cast<Block_Buffer*>(ptr);
}

void buffer_reset(const FunctionCallbackInfo<Value>& args) {
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		buf->reset();
	}
}

void make_inner_message(const FunctionCallbackInfo<Value>& args) {
	if (args.Length() != 1) {
		LOG_ERROR("make_inner_message args error, length: %d\n", args.Length());
		return;
	}
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		int msg_id = args[0]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
		buf->make_inner_message(msg_id);
	}
}

void make_player_message(const FunctionCallbackInfo<Value>& args) {
	if (args.Length() != 3) {
		LOG_ERROR("make_player_message args error, length: %d\n", args.Length());
		return;
	}
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		int msg_id = args[0]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
		int status = args[1]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
		int player_cid = args[2]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
		buf->make_player_message(msg_id, status, player_cid);
	}
}

void finish_message(const FunctionCallbackInfo<Value>& args) {
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		buf->finish_message();
	}
}

void read_int8(const FunctionCallbackInfo<Value>& args) {
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		args.GetReturnValue().Set(buf->read_int8());
	} else {
		args.GetReturnValue().SetNull();
	}
}

void read_int16(const FunctionCallbackInfo<Value>& args) {
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		args.GetReturnValue().Set(buf->read_int16());
	} else {
		args.GetReturnValue().SetNull();
	}
}

void read_int32(const FunctionCallbackInfo<Value>& args) {
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		args.GetReturnValue().Set(buf->read_int32());
	} else {
		args.GetReturnValue().SetNull();
	}
}

void read_int64(const FunctionCallbackInfo<Value>& args) {
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		double value = buf->read_int64();
		args.GetReturnValue().Set(value);
	} else {
		args.GetReturnValue().SetNull();
	}
}

void read_uint8(const FunctionCallbackInfo<Value>& args) {
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		args.GetReturnValue().Set(buf->read_uint8());
	} else {
		args.GetReturnValue().SetNull();
	}
}

void read_uint16(const FunctionCallbackInfo<Value>& args) {
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		args.GetReturnValue().Set(buf->read_uint16());
	} else {
		args.GetReturnValue().SetNull();
	}
}

void read_uint32(const FunctionCallbackInfo<Value>& args) {
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		args.GetReturnValue().Set(buf->read_uint32());
	} else {
		args.GetReturnValue().SetNull();
	}
}

void read_uint64(const FunctionCallbackInfo<Value>& args) {
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		double value = buf->read_uint64();
		args.GetReturnValue().Set(value);
	} else {
		args.GetReturnValue().SetNull();
	}
}

void read_double(const FunctionCallbackInfo<Value>& args) {
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		double value = buf->read_double();
		args.GetReturnValue().Set(value);
	} else {
		args.GetReturnValue().SetNull();
	}
}

void read_bool(const FunctionCallbackInfo<Value>& args) {
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		bool value = buf->read_bool();
		args.GetReturnValue().Set(value);
	} else {
		args.GetReturnValue().SetNull();
	}
}

void read_string(const FunctionCallbackInfo<Value>& args) {
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		std::string str = buf->read_string();
		Local<String> v8Str = String::NewFromUtf8(args.GetIsolate(), str.c_str(), v8::NewStringType::kNormal).ToLocalChecked();
		args.GetReturnValue().Set(v8Str);
	} else {
		args.GetReturnValue().SetNull();
	}
}

void write_int8(const FunctionCallbackInfo<Value>& args) {
	if (args.Length() != 1) {
		LOG_ERROR("write_int8 args error, length: %d\n", args.Length());
		return;
	}
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		int8_t value = args[0]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
		buf->write_int8(value);
	}
}

void write_int16(const FunctionCallbackInfo<Value>& args) {
	if (args.Length() != 1) {
		LOG_ERROR("write_int16 args error, length: %d\n", args.Length());
		return;
	}
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		int16_t value = args[0]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
		buf->write_int16(value);
	}
}

void write_int32(const FunctionCallbackInfo<Value>& args) {
	if (args.Length() != 1) {
		LOG_ERROR("write_int32 args error, length: %d\n", args.Length());
		return;
	}
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		int32_t value = args[0]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
		buf->write_int32(value);
	}
}

void write_int64(const FunctionCallbackInfo<Value>& args) {
	if (args.Length() != 1) {
		LOG_ERROR("write_int64 args error, length: %d\n", args.Length());
		return;
	}
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		int64_t value = args[0]->IntegerValue(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
		buf->write_int64(value);
	}
}

void write_uint8(const FunctionCallbackInfo<Value>& args) {
	if (args.Length() != 1) {
		LOG_ERROR("write_int8 args error, length: %d\n", args.Length());
		return;
	}
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		uint8_t value = args[0]->Uint32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
		buf->write_uint8(value);
	}
}

void write_uint16(const FunctionCallbackInfo<Value>& args) {
	if (args.Length() != 1) {
		LOG_ERROR("write_int16 args error, length: %d\n", args.Length());
		return;
	}
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		uint16_t value = args[0]->Uint32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
		buf->write_uint16(value);
	}
}

void write_uint32(const FunctionCallbackInfo<Value>& args) {
	if (args.Length() != 1) {
		LOG_ERROR("write_int32 args error, length: %d\n", args.Length());
		return;
	}
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		uint32_t value = args[0]->Uint32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
		buf->write_uint32(value);
	}
}

void write_uint64(const FunctionCallbackInfo<Value>& args) {
	if (args.Length() != 1) {
		LOG_ERROR("write_int64 args error, length: %d\n", args.Length());
		return;
	}
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		uint64_t value = args[0]->IntegerValue(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
		buf->write_uint64(value);
	}
}

void write_double(const FunctionCallbackInfo<Value>& args) {
	if (args.Length() != 1) {
		LOG_ERROR("write_double args error, length: %d\n", args.Length());
		return;
	}
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		double value = args[0]->NumberValue(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
		buf->write_double(value);
	}
}

void write_bool(const FunctionCallbackInfo<Value>& args) {
	if (args.Length() != 1) {
		LOG_ERROR("write_double args error, length: %d\n", args.Length());
		return;
	}
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		bool value = args[0]->BooleanValue(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
		buf->write_bool(value);
	}
}

void write_string(const FunctionCallbackInfo<Value>& args) {
	if (args.Length() != 1) {
		LOG_ERROR("write_string args error, length: %d\n", args.Length());
		return;
	}
	Block_Buffer *buf= unwrap_buffer(args.Holder());
	if (buf) {
		String::Utf8Value str(args[0]);
		const char* cstr = ToCString(str);
		buf->write_string(cstr);
	}
}
