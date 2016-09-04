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

#pragma once

#include <string>

#include <node.h>
#include <node_object_wrap.h>

#pragma GCC visibility push(default)

class GrammarSourceContext : public node::ObjectWrap
{
public:
  static void init(v8::Local<v8::Object> exports);

protected:
  static v8::Persistent<v8::Function> ctor;

  GrammarSourceContext(std::string const& source);
  virtual ~GrammarSourceContext();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void plusOne(const v8::FunctionCallbackInfo<v8::Value>& args);
};

class ANTLRGrammarService : public node::ObjectWrap
{
public:
  static void init(v8::Local<v8::Object> exports);

protected:
  static v8::Persistent<v8::Function> ctor;

  ANTLRGrammarService();
  virtual ~ANTLRGrammarService();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void infoTextForSymbol(const v8::FunctionCallbackInfo<v8::Value>& args);

};

#pragma GCC visibility pop
