/**

 Copyright (c) 2010-2014  hkrn

 All rights reserved.

 Redistribution and use in source and binary forms, with or
 without modification, are permitted provided that the following
 conditions are met:

 - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
 - Redistributions in binary form must reproduce the above
   copyright notice, this list of conditions and the following
   disclaimer in the documentation and/or other materials provided
   with the distribution.
 - Neither the name of the MMDAI project team nor the names of
   its contributors may be used to endorse or promote products
   derived from this software without specific prior written
   permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.

*/

#pragma once
#ifndef VPVL2_NVFX_EFFECTCONTEXT_H_
#define VPVL2_NVFX_EFFECTCONTEXT_H_

#include "vpvl2/Common.h"
#include "vpvl2/extensions/StringMap.h"

namespace vpvl2
{
namespace VPVL2_VERSION_NS
{

class IEffect;
class IApplicationContext;
class IString;

namespace nvfx
{

class VPVL2_API EffectContext VPVL2_DECL_FINAL
{
public:
    static bool initialize(const IApplicationContext::FunctionResolver *resolver);
    static void cleanup();
    static void enableIncludeCallback(const extensions::StringMap &includeBuffers, const extensions::StringList &includePaths);
    static void disableIncludeCallback();
    static void enableMessageCallback();
    static void disableMessageCallback();

    EffectContext();
    ~EffectContext();

    void getEffectArguments(const IApplicationContext *applicationContextRef, Array<const char *> &arguments);
    IEffect *compileFromFile(const IString *pathRef, IApplicationContext *applicationContextRef);
    IEffect *compileFromSource(const IString *source, IApplicationContext *applicationContextRef);
    void *internalContext() const;
};

} /* namespace nvfx */
} /* namespace VPVL2_VERSION_NS */
} /* namespace vpvl2 */

#endif
