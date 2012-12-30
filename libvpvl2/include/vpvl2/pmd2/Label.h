/* ----------------------------------------------------------------- */
/*                                                                   */
/*  Copyright (c) 2010-2013  hkrn                                    */
/*                                                                   */
/* All rights reserved.                                              */
/*                                                                   */
/* Redistribution and use in source and binary forms, with or        */
/* without modification, are permitted provided that the following   */
/* conditions are met:                                               */
/*                                                                   */
/* - Redistributions of source code must retain the above copyright  */
/*   notice, this list of conditions and the following disclaimer.   */
/* - Redistributions in binary form must reproduce the above         */
/*   copyright notice, this list of conditions and the following     */
/*   disclaimer in the documentation and/or other materials provided */
/*   with the distribution.                                          */
/* - Neither the name of the MMDAI project team nor the names of     */
/*   its contributors may be used to endorse or promote products     */
/*   derived from this software without specific prior written       */
/*   permission.                                                     */
/*                                                                   */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND            */
/* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,       */
/* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF          */
/* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE          */
/* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS */
/* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,          */
/* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED   */
/* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     */
/* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON */
/* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,   */
/* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY    */
/* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE           */
/* POSSIBILITY OF SUCH DAMAGE.                                       */
/* ----------------------------------------------------------------- */

#ifndef VPVL2_PMD2_LABEL_H_
#define VPVL2_PMD2_LABEL_H_

#include "vpvl2/Common.h"
#include "vpvl2/ILabel.h"
#include "vpvl2/pmd2/Model.h"

namespace vpvl2
{

class IEncoding;
class IString;

namespace pmd2
{

class VPVL2_API Label : public ILabel
{
public:
    Label(const uint8_t *name, const Array<IBone *> &bones, IEncoding *encoding, bool special);
    ~Label();

    const IString *name() const { return m_name; }
    const IString *englishName() const { return m_name; }
    bool isSpecial() const { return m_special; }
    int count() const { return m_boneRefs.count(); }
    IBone *bone(int index) const { return m_boneRefs.at(index); }
    IMorph *morph(int /* index */) const { return 0; }

    static bool preparse(uint8_t *&ptr, size_t &rest, Model::DataInfo &info);
    static bool loadLabels(const Array<Label *> &labels, const Array<Bone *> &bones, const Array<Morph *> &morphs);
    static size_t estimateTotalSize(const Array<Label *> &labels, const Model::DataInfo &info);

    void read(const uint8_t *data, const Model::DataInfo &info, size_t &size);
    size_t estimateSize(const Model::DataInfo &info) const;
    void write(uint8_t *data, const Model::DataInfo &info) const;

    IEncoding *m_encodingRef;
    IString *m_name;
    Array<IBone *> m_boneRefs;
    int m_index;
    bool m_special;
};

} /* namespace pmd2 */
} /* namespace vpvl2 */

#endif
