/*
 * MIT License
 *
 * Copyright (c) 2016 Mike Lischke
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "antlr-graps.h"

using namespace v8;

v8::Persistent<v8::Function> SourceContext::constructor;

//----------------------------------------------------------------------------------------------------------------------

SourceContext::SourceContext() : graps::SourceContextImpl()
{

}

//----------------------------------------------------------------------------------------------------------------------

SourceContext::~SourceContext()
{

}

//----------------------------------------------------------------------------------------------------------------------

void SourceContext::init(v8::Local<v8::Object> exports)
{
  Isolate *isolate = exports->GetIsolate();

  // Prepare constructor template.
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "SourceContext"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NODE_SET_PROTOTYPE_METHOD(tpl, "infoForSymbolAtPosition", infoForSymbolAtPosition);
  NODE_SET_PROTOTYPE_METHOD(tpl, "parse", parse);
  NODE_SET_PROTOTYPE_METHOD(tpl, "addDependency", addDependency);

  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "SourceContext"), tpl->GetFunction());
}

//----------------------------------------------------------------------------------------------------------------------

void SourceContext::New(const FunctionCallbackInfo<Value>& args)
{
  Isolate *isolate = args.GetIsolate();

  if (args.IsConstructCall())
  {
    // Invoked as constructor: `new MyObject(...)`.
    SourceContext *obj = new SourceContext();
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  }
  else
  {
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    const int argc = 1;
    Local<Value> argv[argc] = { args[0] };
    Local<Context> context = isolate->GetCurrentContext();
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    Local<Object> result = cons->NewInstance(context, argc, argv).ToLocalChecked();
    args.GetReturnValue().Set(result);
  }
}

//----------------------------------------------------------------------------------------------------------------------

void SourceContext::infoForSymbolAtPosition(const v8::FunctionCallbackInfo<v8::Value>& args)
{
  Isolate *isolate = args.GetIsolate();

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
  }

  SourceContextImpl *impl = dynamic_cast<SourceContextImpl *>(ObjectWrap::Unwrap<SourceContext>(args.Holder()));

  int64_t row = args[0]->IntegerValue();
  int64_t column = args[1]->IntegerValue();
  std::string info = impl->infoForSymbolAtPosition(row, column);

  args.GetReturnValue().Set(String::NewFromUtf8(isolate, info.c_str()));
}

//----------------------------------------------------------------------------------------------------------------------

void SourceContext::parse(const v8::FunctionCallbackInfo<v8::Value>& args)
{
  Isolate *isolate = args.GetIsolate();

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  if (!args[0]->IsString()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
  }

  SourceContextImpl *impl = dynamic_cast<SourceContextImpl *>(ObjectWrap::Unwrap<SourceContext>(args.Holder()));

  v8::String::Utf8Value source(args[0]->ToString());
  impl->parse(*source);

  Handle<Array> array = Array::New(isolate, impl->imports.size());
  for (size_t i = 0; i < impl->imports.size(); ++i)
    array->Set(i, String::NewFromUtf8(isolate, impl->imports[i].c_str()));

  args.GetReturnValue().Set(array);
}

//----------------------------------------------------------------------------------------------------------------------

void SourceContext::addDependency(const v8::FunctionCallbackInfo<v8::Value>& args)
{
  Isolate *isolate = args.GetIsolate();

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  SourceContextImpl *dep = dynamic_cast<SourceContextImpl *>(node::ObjectWrap::Unwrap<SourceContext>(args[0]->ToObject()));
  SourceContextImpl *impl = dynamic_cast<SourceContextImpl *>(ObjectWrap::Unwrap<SourceContext>(args.Holder()));
  impl->addDependency(dep);
}

//----------------------------------------------------------------------------------------------------------------------

void initialize(Local<Object> exports)
{
  SourceContext::init(exports);
}

//----------------------------------------------------------------------------------------------------------------------

NODE_MODULE(antlr4_graps, initialize)
