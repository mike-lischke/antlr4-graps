/*
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *  Created by Mike Lischke on 03.09.16.
 *  Copyright © 2016 Mike Lischke. All rights reserved.
 *
 */

#include "antlr-graps.h"

using namespace v8;

v8::Persistent<v8::Function> GrammarSourceContext::constructor;
v8::Persistent<v8::Function> ANTLRGrammarService::constructor;

//----------------------------------------------------------------------------------------------------------------------

GrammarSourceContext::GrammarSourceContext(std::string const& source)
{

}

//----------------------------------------------------------------------------------------------------------------------

GrammarSourceContext::~GrammarSourceContext()
{

}

//----------------------------------------------------------------------------------------------------------------------

void GrammarSourceContext::init(v8::Local<v8::Object> exports)
{
  Isolate *isolate = exports->GetIsolate();

  // Prepare constructor template.
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "GrammarSourceContext"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  //NODE_SET_PROTOTYPE_METHOD(tpl, "plusOne", plusOne);

  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "GrammarSourceContext"), tpl->GetFunction());
}

//----------------------------------------------------------------------------------------------------------------------

void GrammarSourceContext::New(const FunctionCallbackInfo<Value>& args)
{
  Isolate *isolate = args.GetIsolate();

  if (args.IsConstructCall())
  {
    // Invoked as constructor: `new MyObject(...)`.
    std::string argument;
    if (!args[0]->IsUndefined())
    {
      v8::String::Utf8Value param1(args[0]->ToString());
      argument = *param1;
    }

    GrammarSourceContext *obj = new GrammarSourceContext(argument);
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

void GrammarSourceContext::plusOne(const v8::FunctionCallbackInfo<v8::Value>& args)
{/*
  Isolate *isolate = args.GetIsolate();

  GrammarSourceContext *obj = ObjectWrap::Unwrap<GrammarSourceContext>(args.Holder());
  //obj->value_ += 1;

  //args.GetReturnValue().Set(Number::New(isolate, obj->value_));
  */
}

//----------------- ANTLRGrammarService --------------------------------------------------------------------------------

ANTLRGrammarService::ANTLRGrammarService()
{

}

//----------------------------------------------------------------------------------------------------------------------

ANTLRGrammarService::~ANTLRGrammarService()
{

}

//----------------------------------------------------------------------------------------------------------------------

void ANTLRGrammarService::init(v8::Local<v8::Object> exports)
{
  Isolate *isolate = exports->GetIsolate();

  // Prepare constructor template.
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "ANTLRGrammarService"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "infoTextForSymbol", infoTextForSymbol);

  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "ANTLRGrammarService"), tpl->GetFunction());
}

//----------------------------------------------------------------------------------------------------------------------

void ANTLRGrammarService::New(const FunctionCallbackInfo<Value>& args)
{
  Isolate *isolate = args.GetIsolate();

  if (args.IsConstructCall())
  {
    // Invoked as constructor: `new MyObject(...)`.
    ANTLRGrammarService *obj = new ANTLRGrammarService();
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

void ANTLRGrammarService::infoTextForSymbol(const v8::FunctionCallbackInfo<v8::Value>& args)
{
  Isolate *isolate = args.GetIsolate();

  //ANTLRGrammarService *obj = ObjectWrap::Unwrap<ANTLRGrammarService>(args.Holder());
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "rule: a | b = rule2;"));
}

//----------------------------------------------------------------------------------------------------------------------

void initialize(Local<Object> exports) {
  ANTLRGrammarService::init(exports);
  GrammarSourceContext::init(exports);
}

//----------------------------------------------------------------------------------------------------------------------

NODE_MODULE(antlr_graps, initialize)
