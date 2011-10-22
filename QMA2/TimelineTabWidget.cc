/* ----------------------------------------------------------------- */
/*                                                                   */
/*  Copyright (c) 2010-2011  hkrn                                    */
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

#include "TimelineTabWidget.h"
#include "BoneMotionModel.h"
#include "FaceMotionModel.h"
#include "TimelineWidget.h"
#include "VPDFile.h"
#include "util.h"

#include <QtGui/QtGui>
#include <vpvl/vpvl.h>

namespace
{

static const int kBoneTabIndex = 0;
static const int kFaceTabIndex = 1;

static BoneMotionModel *UIGetBoneModel(TimelineWidget *timeline)
{
    return static_cast<BoneMotionModel *>(timeline->tableView()->model());
}

static FaceMotionModel *UIGetFaceModel(TimelineWidget *timeline)
{
    return static_cast<FaceMotionModel *>(timeline->tableView()->model());
}

static void UIModelDeleteFrame(TimelineWidget *timeline)
{
    MotionBaseModel *model = static_cast<MotionBaseModel *>(timeline->tableView()->model());
    QModelIndexList indices = timeline->tableView()->selectionModel()->selectedIndexes();
    foreach (QModelIndex index, indices)
        model->deleteFrame(index);
}

static void UIModelInsertBoneFrame(TimelineWidget *timeline)
{
    BoneMotionModel *model = UIGetBoneModel(timeline);
    QModelIndexList indices = timeline->tableView()->selectionModel()->selectedIndexes();
    QTextCodec *codec = internal::getTextCodec();
    BoneMotionModel::KeyFramePairList boneFrames;
    foreach (QModelIndex index, indices) {
        vpvl::BoneKeyFrame *frame = new vpvl::BoneKeyFrame();
        QString name = model->data(index, BoneMotionModel::kNameRole).toString();
        frame->setName(reinterpret_cast<const uint8_t *>(codec->fromUnicode(name).constData()));
        frame->setDefaultInterpolationParameter();
        boneFrames.append(BoneMotionModel::KeyFramePair(index.column(), BoneMotionModel::KeyFramePtr(frame)));
    }
    model->setFrames(boneFrames);
}

static void UIModelInsertFaceFrame(TimelineWidget *timeline)
{
    FaceMotionModel *model = UIGetFaceModel(timeline);
    QModelIndexList indices = timeline->tableView()->selectionModel()->selectedIndexes();
    QTextCodec *codec = internal::getTextCodec();
    FaceMotionModel::KeyFramePairList faceFrames;
    foreach (QModelIndex index, indices) {
        vpvl::FaceKeyFrame *frame = new vpvl::FaceKeyFrame();
        QString name = model->data(index, BoneMotionModel::kNameRole).toString();
        frame->setName(reinterpret_cast<const uint8_t *>(codec->fromUnicode(name).constData()));
        frame->setWeight(0);
        faceFrames.append(FaceMotionModel::KeyFramePair(index.column(), FaceMotionModel::KeyFramePtr(frame)));
    }
    model->setFrames(faceFrames);
}

}

TimelineTabWidget::TimelineTabWidget(QSettings *settings,
                                     BoneMotionModel *bmm,
                                     FaceMotionModel *fmm,
                                     QWidget *parent) :
    QWidget(parent),
    m_settings(settings),
    m_boneTimeline(0),
    m_faceTimeline(0)
{
    m_tabWidget = new QTabWidget();
    m_boneTimeline = new TimelineWidget(bmm, this);
    m_tabWidget->insertTab(kBoneTabIndex, m_boneTimeline, "");
    m_faceTimeline = new TimelineWidget(fmm, this);
    m_tabWidget->insertTab(kFaceTabIndex, m_faceTimeline, "");
    connect(m_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(setCurrentTabIndex(int)));
    connect(m_boneTimeline, SIGNAL(motionDidSeek(float)), this, SIGNAL(motionDidSeek(float)));
    connect(m_faceTimeline, SIGNAL(motionDidSeek(float)), this, SIGNAL(motionDidSeek(float)));
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(10, 10, 10, 10);
    layout->addWidget(m_tabWidget);
    retranslate();
    setLayout(layout);
    restoreGeometry(m_settings->value("timelineTabWidget/geometry").toByteArray());
}

TimelineTabWidget::~TimelineTabWidget()
{
}

void TimelineTabWidget::loadPose(VPDFile *pose, vpvl::PMDModel *model)
{
    UIGetBoneModel(m_boneTimeline)->loadPose(pose, model, m_boneTimeline->frameIndex());
}

void TimelineTabWidget::retranslate()
{
    m_tabWidget->setTabText(0, tr("Bone"));
    m_tabWidget->setTabText(1, tr("Face"));
    setWindowTitle(tr("Motion Timeline"));
}

void TimelineTabWidget::savePose(VPDFile *pose, vpvl::PMDModel *model)
{
    UIGetBoneModel(m_boneTimeline)->savePose(pose, model, m_boneTimeline->frameIndex());
}


void TimelineTabWidget::addBoneFrameAtCurrentIndex(vpvl::Bone *bone)
{
    BoneMotionModel::KeyFramePairList boneFrames;
    vpvl::BoneKeyFrame *frame = new vpvl::BoneKeyFrame();
    frame->setDefaultInterpolationParameter();
    frame->setName(bone->name());
    frame->setPosition(bone->position());
    frame->setRotation(bone->rotation());
    boneFrames.append(BoneMotionModel::KeyFramePair(m_boneTimeline->frameIndex(), BoneMotionModel::KeyFramePtr(frame)));
    UIGetBoneModel(m_boneTimeline)->setFrames(boneFrames);
}

void TimelineTabWidget::addFaceFrameAtCurrentIndex(vpvl::Face *face)
{
    FaceMotionModel::KeyFramePairList faceFrames;
    vpvl::FaceKeyFrame *frame = new vpvl::FaceKeyFrame();
    frame->setName(face->name());
    frame->setWeight(face->weight());
    faceFrames.append(FaceMotionModel::KeyFramePair(m_faceTimeline->frameIndex(), FaceMotionModel::KeyFramePtr(frame)));
    UIGetFaceModel(m_faceTimeline)->setFrames(faceFrames);
}

void TimelineTabWidget::setCurrentFrameIndexZero()
{
    m_boneTimeline->setFrameIndex(0);
    m_faceTimeline->setFrameIndex(0);
}

void TimelineTabWidget::insertFrame()
{
    switch (m_tabWidget->currentIndex()) {
    case kBoneTabIndex:
        UIModelInsertBoneFrame(m_boneTimeline);
        break;
    case kFaceTabIndex:
        UIModelInsertFaceFrame(m_faceTimeline);
        break;
    }
}

void TimelineTabWidget::deleteFrame()
{
    switch (m_tabWidget->currentIndex()) {
    case kBoneTabIndex:
        UIModelDeleteFrame(m_boneTimeline);
        break;
    case kFaceTabIndex:
        UIModelDeleteFrame(m_faceTimeline);
        break;
    }
}


void TimelineTabWidget::copyFrame()
{
    switch (m_tabWidget->currentIndex()) {
    case kBoneTabIndex:
        UIGetBoneModel(m_boneTimeline)->copyFrames(m_boneTimeline->frameIndex());
        break;
    case kFaceTabIndex:
        UIGetFaceModel(m_faceTimeline)->copyFrames(m_faceTimeline->frameIndex());
        break;
    }
}

void TimelineTabWidget::pasteFrame()
{
    switch (m_tabWidget->currentIndex()) {
    case kBoneTabIndex:
        UIGetBoneModel(m_boneTimeline)->pasteFrame(m_boneTimeline->frameIndex());
        break;
    case kFaceTabIndex:
        UIGetFaceModel(m_faceTimeline)->pasteFrame(m_faceTimeline->frameIndex());
        break;
    }
}

void TimelineTabWidget::pasteReversedFrame()
{
    switch (m_tabWidget->currentIndex()) {
    case kBoneTabIndex:
        UIGetBoneModel(m_boneTimeline)->pasteReversedFrame(m_boneTimeline->frameIndex());
        break;
    default:
        pasteFrame();
    }
}

void TimelineTabWidget::setCurrentTabIndex(int index)
{
    switch (index) {
    case kBoneTabIndex:
        emit currentTabDidChange(kBone);
        break;
    case kFaceTabIndex:
        emit currentTabDidChange(kFace);
        break;
    }
}
