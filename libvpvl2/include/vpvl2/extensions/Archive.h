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
#ifndef VPVL2_EXTENSIONS_ARCHIVE_H_
#define VPVL2_EXTENSIONS_ARCHIVE_H_

#include <vpvl2/IEncoding.h>

#include <set>
#include <vector>

namespace vpvl2
{
namespace VPVL2_VERSION_NS
{
namespace extensions
{

class VPVL2_API Archive VPVL2_DECL_FINAL
{
public:
    typedef std::vector<std::string> EntryNames;
    typedef std::set<std::string> EntrySet;
    enum ErrorType {
        kNone,
        kGetCurrentFileError,
        kGoToNextFileError,
        kGoToFirstFileError,
        kOpenCurrentFileError,
        kReadCurrentFileError,
        kCloseCurrentFileError,
        kMaxError
    };

    explicit Archive(IEncoding *encoding);
    ~Archive();

    bool open(const IString *filename, EntryNames &entries);
    bool close();
    bool uncompress(const EntrySet &entries);
    bool uncompressEntry(const std::string &name);
    void setBasePath(const std::string &value);
    Archive::ErrorType error() const;
    const EntryNames entryNames() const;
    const std::string *dataRef(const std::string &name) const;

private:
    struct PrivateContext;
    PrivateContext *m_context;

    VPVL2_DISABLE_COPY_AND_ASSIGN(Archive)
};

} /* namespace extensions */
} /* namespace VPVL2_VERSION_NS */
using namespace VPVL2_VERSION_NS;

} /* namespace vpvl2 */

#endif
