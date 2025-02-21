/*
 * Copyright 2021, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <memory>
#include <unordered_set>

#include "include/IComposerHal.h"
#include <utils/String8.h>
#include <hardware/hwcomposer2.h>

static constexpr uint32_t DISPLAYID_MASK_LEN = 8;

constexpr uint32_t getDisplayId(int32_t displayType, int32_t displayIndex) {
    return (displayType << DISPLAYID_MASK_LEN) | displayIndex;
}

namespace aidl::android::hardware::graphics::composer3::impl {

// Forward aidl call to Exynos HWC
class HalImpl : public IComposerHal {
  public:
    HalImpl() = default;
    virtual ~HalImpl() = default;

    bool initWithDevice(hwc2_device_t* device, bool requireReliablePresentFence);

    void getCapabilities(std::vector<Capability>* caps) override;
    void dumpDebugInfo(std::string* output) override;
    bool hasCapability(Capability cap) override;

    void registerEventCallback(EventCallback* callback) override;
    void unregisterEventCallback() override;

    int32_t acceptDisplayChanges(int64_t display) override;
    int32_t createLayer(int64_t display, int64_t* outLayer) override;
    int32_t createVirtualDisplay(uint32_t width, uint32_t height, AidlPixelFormat format,
                                 VirtualDisplay* outDisplay) override;
    int32_t destroyLayer(int64_t display, int64_t layer) override;
    int32_t destroyVirtualDisplay(int64_t display) override;
    int32_t getActiveConfig(int64_t display, int32_t* outConfig) override;
    int32_t getColorModes(int64_t display, std::vector<ColorMode>* outModes) override;

    int32_t getDataspaceSaturationMatrix(common::Dataspace dataspace,
                                         std::vector<float>* matrix) override;
    int32_t getDisplayAttribute(int64_t display, int32_t config, DisplayAttribute attribute,
                                int32_t* outValue) override;
    int32_t getDisplayBrightnessSupport(int64_t display, bool& outSupport) override;
    int32_t getDisplayCapabilities(int64_t display, std::vector<DisplayCapability>* caps) override;
    int32_t getDisplayConfigs(int64_t display, std::vector<int32_t>* configs) override;
    int32_t getDisplayConnectionType(int64_t display, DisplayConnectionType* outType) override;
    int32_t getDisplayIdentificationData(int64_t display, DisplayIdentification* id) override;
    int32_t getDisplayName(int64_t display, std::string* outName) override;
    int32_t getDisplayVsyncPeriod(int64_t display, int32_t* outVsyncPeriod) override;
    int32_t getDisplayedContentSample(int64_t display, int64_t maxFrames, int64_t timestamp,
                                      DisplayContentSample* samples) override;
    int32_t getDisplayedContentSamplingAttributes(int64_t display,
                                                  DisplayContentSamplingAttributes* attrs) override;
    int32_t getDisplayPhysicalOrientation(int64_t display, common::Transform* orientation) override;
    int32_t getDozeSupport(int64_t display, bool& outSupport) override;
    int32_t getHdrCapabilities(int64_t display, HdrCapabilities* caps) override;
    int32_t getOverlaySupport(OverlayProperties* caps) override;
    int32_t getMaxVirtualDisplayCount(int32_t* count) override;
    int32_t getPerFrameMetadataKeys(int64_t display,
                                    std::vector<PerFrameMetadataKey>* keys) override;

    int32_t getReadbackBufferAttributes(int64_t display, ReadbackBufferAttributes* attrs) override;
    int32_t getReadbackBufferFence(int64_t display,
                                   ndk::ScopedFileDescriptor* acquireFence) override;
    int32_t getRenderIntents(int64_t display, ColorMode mode,
                             std::vector<RenderIntent>* intents) override;
    int32_t getSupportedContentTypes(int64_t display, std::vector<ContentType>* types) override;
    int32_t presentDisplay(int64_t display, ndk::ScopedFileDescriptor& fence,
                           std::vector<int64_t>* outLayers,
                           std::vector<ndk::ScopedFileDescriptor>* outReleaseFences) override;
    int32_t setActiveConfig(int64_t display, int32_t config) override;
    int32_t setActiveConfigWithConstraints(
            int64_t display, int32_t config,
            const VsyncPeriodChangeConstraints& vsyncPeriodChangeConstraints,
            VsyncPeriodChangeTimeline* timeline) override;
    int32_t setBootDisplayConfig(int64_t display, int32_t config) override;
    int32_t clearBootDisplayConfig(int64_t display) override;
    int32_t getPreferredBootDisplayConfig(int64_t display, int32_t* config) override;
    int32_t getHdrConversionCapabilities(std::vector<common::HdrConversionCapability>*) override;
    int32_t setHdrConversionStrategy(const common::HdrConversionStrategy&, common::Hdr*) override;
    int32_t setAutoLowLatencyMode(int64_t display, bool on) override;
    int32_t setClientTarget(int64_t display, buffer_handle_t target,
                            const ndk::ScopedFileDescriptor& fence, common::Dataspace dataspace,
                            const std::vector<common::Rect>& damage) override;
    int32_t setColorMode(int64_t display, ColorMode mode, RenderIntent intent) override;
    int32_t setColorTransform(int64_t display, const std::vector<float>& matrix) override;
    int32_t setContentType(int64_t display, ContentType contentType) override;
    int32_t setDisplayBrightness(int64_t display, float brightness) override;
    int32_t setDisplayedContentSamplingEnabled(int64_t display, bool enable,
                                               FormatColorComponent componentMask,
                                               int64_t maxFrames) override;
    int32_t setLayerBlendMode(int64_t display, int64_t layer, common::BlendMode mode) override;
    int32_t setLayerBuffer(int64_t display, int64_t layer, buffer_handle_t buffer,
                           const ndk::ScopedFileDescriptor& acquireFence) override;
    int32_t setLayerColor(int64_t display, int64_t layer, Color color) override;
    int32_t setLayerColorTransform(int64_t display, int64_t layer,
                                   const std::vector<float>& matrix) override;
    int32_t setLayerCompositionType(int64_t display, int64_t layer, Composition type) override;
    int32_t setLayerCursorPosition(int64_t display, int64_t layer, int32_t x, int32_t y) override;
    int32_t setLayerDataspace(int64_t display, int64_t layer, common::Dataspace dataspace) override;
    int32_t setLayerDisplayFrame(int64_t display, int64_t layer,
                                 const common::Rect& frame) override;
    int32_t setLayerPerFrameMetadata(int64_t display, int64_t layer,
                            const std::vector<std::optional<PerFrameMetadata>>& metadata) override;
    int32_t setLayerPerFrameMetadataBlobs(int64_t display, int64_t layer,
                            const std::vector<std::optional<PerFrameMetadataBlob>>& blobs) override;
    int32_t setLayerPlaneAlpha(int64_t display, int64_t layer, float alpha) override;
    int32_t setLayerSidebandStream(int64_t display, int64_t layer,
                                   buffer_handle_t stream) override;
    int32_t setLayerSourceCrop(int64_t display, int64_t layer, const common::FRect& crop) override;
    int32_t setLayerSurfaceDamage(int64_t display, int64_t layer,
                                  const std::vector<std::optional<common::Rect>>& damage) override;
    int32_t setLayerTransform(int64_t display, int64_t layer, common::Transform transform) override;
    int32_t setLayerVisibleRegion(int64_t display, int64_t layer,
                          const std::vector<std::optional<common::Rect>>& visible) override;
    int32_t setLayerBrightness(int64_t display, int64_t layer, float brightness) override;
    int32_t setLayerZOrder(int64_t display, int64_t layer, uint32_t z) override;
    int32_t setOutputBuffer(int64_t display, buffer_handle_t buffer,
                            const ndk::ScopedFileDescriptor& releaseFence) override;
    int32_t setPowerMode(int64_t display, PowerMode mode) override;
    int32_t setReadbackBuffer(int64_t display, buffer_handle_t buffer,
                              const ndk::ScopedFileDescriptor& releaseFence) override;
    int32_t setVsyncEnabled(int64_t display, bool enabled) override;
    int32_t getDisplayIdleTimerSupport(int64_t display, bool& outSupport) override;
    int32_t setIdleTimerEnabled(int64_t display, int32_t timeout) override;
    int32_t setRefreshRateChangedCallbackDebugEnabled(int64_t display, bool enabled) override;
    int32_t getRCDLayerSupport(int64_t display, bool& outSupport) override;
    int32_t setLayerBlockingRegion(
            int64_t display, int64_t layer,
            const std::vector<std::optional<common::Rect>>& blockingRegion) override;
    int32_t validateDisplay(int64_t display, std::vector<int64_t>* outChangedLayers,
                            std::vector<Composition>* outCompositionTypes,
                            uint32_t* outDisplayRequestMask,
                            std::vector<int64_t>* outRequestedLayers,
                            std::vector<int32_t>* outRequestMasks,
                            ClientTargetProperty* outClientTargetProperty,
                            DimmingStage* outDimmingStage) override;
    int32_t setExpectedPresentTime(
            int64_t display,
            const std::optional<ClockMonotonicTimestamp> expectedPresentTime) override;

    EventCallback* getEventCallback() { return mEventCallback; }

protected:
    template <typename T>
    bool initDispatch(hwc2_function_descriptor_t desc, T* outPfn) {
        auto pfn = mDevice->getFunction(mDevice, desc);
        if (pfn) {
            *outPfn = reinterpret_cast<T>(pfn);
            return true;
        } else {
            ALOGE("failed to get hwcomposer2 function %d", desc);
            return false;
        }
    }

    virtual bool initDispatch() {
        if (!initDispatch(HWC2_FUNCTION_ACCEPT_DISPLAY_CHANGES, &mDispatch.acceptDisplayChanges) ||
            !initDispatch(HWC2_FUNCTION_CREATE_LAYER, &mDispatch.createLayer) ||
            !initDispatch(HWC2_FUNCTION_CREATE_VIRTUAL_DISPLAY, &mDispatch.createVirtualDisplay) ||
            !initDispatch(HWC2_FUNCTION_DESTROY_LAYER, &mDispatch.destroyLayer) ||
            !initDispatch(HWC2_FUNCTION_DESTROY_VIRTUAL_DISPLAY,
                          &mDispatch.destroyVirtualDisplay) ||
            !initDispatch(HWC2_FUNCTION_DUMP, &mDispatch.dump) ||
            !initDispatch(HWC2_FUNCTION_GET_ACTIVE_CONFIG, &mDispatch.getActiveConfig) ||
            !initDispatch(HWC2_FUNCTION_GET_CHANGED_COMPOSITION_TYPES,
                          &mDispatch.getChangedCompositionTypes) ||
            !initDispatch(HWC2_FUNCTION_GET_CLIENT_TARGET_SUPPORT,
                          &mDispatch.getClientTargetSupport) ||
            !initDispatch(HWC2_FUNCTION_GET_COLOR_MODES, &mDispatch.getColorModes) ||
            !initDispatch(HWC2_FUNCTION_GET_DISPLAY_ATTRIBUTE, &mDispatch.getDisplayAttribute) ||
            !initDispatch(HWC2_FUNCTION_GET_DISPLAY_CONFIGS, &mDispatch.getDisplayConfigs) ||
            !initDispatch(HWC2_FUNCTION_GET_DISPLAY_NAME, &mDispatch.getDisplayName) ||
            !initDispatch(HWC2_FUNCTION_GET_DISPLAY_REQUESTS, &mDispatch.getDisplayRequests) ||
            !initDispatch(HWC2_FUNCTION_GET_DISPLAY_TYPE, &mDispatch.getDisplayType) ||
            !initDispatch(HWC2_FUNCTION_GET_DOZE_SUPPORT, &mDispatch.getDozeSupport) ||
            !initDispatch(HWC2_FUNCTION_GET_HDR_CAPABILITIES, &mDispatch.getHdrCapabilities) ||
            !initDispatch(HWC2_FUNCTION_GET_MAX_VIRTUAL_DISPLAY_COUNT,
                          &mDispatch.getMaxVirtualDisplayCount) ||
            !initDispatch(HWC2_FUNCTION_GET_RELEASE_FENCES, &mDispatch.getReleaseFences) ||
            !initDispatch(HWC2_FUNCTION_PRESENT_DISPLAY, &mDispatch.presentDisplay) ||
            !initDispatch(HWC2_FUNCTION_REGISTER_CALLBACK, &mDispatch.registerCallback) ||
            !initDispatch(HWC2_FUNCTION_SET_ACTIVE_CONFIG, &mDispatch.setActiveConfig) ||
            !initDispatch(HWC2_FUNCTION_SET_CLIENT_TARGET, &mDispatch.setClientTarget) ||
            !initDispatch(HWC2_FUNCTION_SET_COLOR_MODE, &mDispatch.setColorMode) ||
            !initDispatch(HWC2_FUNCTION_SET_COLOR_TRANSFORM, &mDispatch.setColorTransform) ||
            !initDispatch(HWC2_FUNCTION_SET_CURSOR_POSITION, &mDispatch.setCursorPosition) ||
            !initDispatch(HWC2_FUNCTION_SET_LAYER_BLEND_MODE, &mDispatch.setLayerBlendMode) ||
            !initDispatch(HWC2_FUNCTION_SET_LAYER_BUFFER, &mDispatch.setLayerBuffer) ||
            !initDispatch(HWC2_FUNCTION_SET_LAYER_COLOR, &mDispatch.setLayerColor) ||
            !initDispatch(HWC2_FUNCTION_SET_LAYER_COMPOSITION_TYPE,
                          &mDispatch.setLayerCompositionType) ||
            !initDispatch(HWC2_FUNCTION_SET_LAYER_DATASPACE, &mDispatch.setLayerDataspace) ||
            !initDispatch(HWC2_FUNCTION_SET_LAYER_DISPLAY_FRAME, &mDispatch.setLayerDisplayFrame) ||
            !initDispatch(HWC2_FUNCTION_SET_LAYER_PLANE_ALPHA, &mDispatch.setLayerPlaneAlpha)) {
            ALOGE("failed to get hwcomposer2 functions %s(%d)", __FUNCTION__, __LINE__);
            return false;
        }

        if (hasCapability(Capability::SIDEBAND_STREAM)) {
            if (!initDispatch(HWC2_FUNCTION_SET_LAYER_SIDEBAND_STREAM,
                              &mDispatch.setLayerSidebandStream)) {
                ALOGE("failed to get hwcomposer2 functions %s(%d)", __FUNCTION__, __LINE__);
                return false;
            }
        }

        if (!initDispatch(HWC2_FUNCTION_SET_LAYER_SOURCE_CROP, &mDispatch.setLayerSourceCrop) ||
            !initDispatch(HWC2_FUNCTION_SET_LAYER_SURFACE_DAMAGE,
                          &mDispatch.setLayerSurfaceDamage) ||
            !initDispatch(HWC2_FUNCTION_SET_LAYER_TRANSFORM, &mDispatch.setLayerTransform) ||
            !initDispatch(HWC2_FUNCTION_SET_LAYER_VISIBLE_REGION,
                          &mDispatch.setLayerVisibleRegion) ||
            !initDispatch(HWC2_FUNCTION_SET_LAYER_Z_ORDER, &mDispatch.setLayerZOrder) ||
            !initDispatch(HWC2_FUNCTION_SET_OUTPUT_BUFFER, &mDispatch.setOutputBuffer) ||
            !initDispatch(HWC2_FUNCTION_SET_POWER_MODE, &mDispatch.setPowerMode) ||
            !initDispatch(HWC2_FUNCTION_SET_VSYNC_ENABLED, &mDispatch.setVsyncEnabled) ||
            !initDispatch(HWC2_FUNCTION_VALIDATE_DISPLAY, &mDispatch.validateDisplay)) {
            ALOGE("failed to get hwcomposer2 functions %s(%d)", __FUNCTION__, __LINE__);
            return false;
        }
        /* composer 2.2 */
        if (!initDispatch(HWC2_FUNCTION_GET_RENDER_INTENTS, &mDispatch.getRenderIntents) ||
            !initDispatch(HWC2_FUNCTION_SET_COLOR_MODE_WITH_RENDER_INTENT, &mDispatch.setColorModeWithRenderIntent)) {
            ALOGE("failed to get hwcomposer2.4 functions %s(%d)", __FUNCTION__, __LINE__);
            return false;
        }
        /* composer 2.3 */
        if (!initDispatch(HWC2_FUNCTION_GET_DISPLAY_IDENTIFICATION_DATA, &mDispatch.getDisplayIdentificationData) ||
            !initDispatch(HWC2_FUNCTION_GET_DISPLAY_CAPABILITIES, &mDispatch.getDisplayCapabilities) ||
            !initDispatch(HWC2_FUNCTION_GET_DISPLAY_BRIGHTNESS_SUPPORT, &mDispatch.getDisplayBrightnessSupport) ||
            !initDispatch(HWC2_FUNCTION_SET_DISPLAY_BRIGHTNESS, &mDispatch.setDisplayBrightness)) {
            ALOGE("failed to get hwcomposer2.4 functions %s(%d)", __FUNCTION__, __LINE__);
            return false;
        }
        /* composer 2.4 */
        if (!initDispatch(HWC2_FUNCTION_GET_DISPLAY_CONNECTION_TYPE, &mDispatch.getDisplayConnectionType) ||
            !initDispatch(HWC2_FUNCTION_GET_DISPLAY_VSYNC_PERIOD, &mDispatch.getDisplayVsyncPeriod) ||
            !initDispatch(HWC2_FUNCTION_SET_ACTIVE_CONFIG_WITH_CONSTRAINTS, &mDispatch.setActiveConfigWithConstraints) ||
            !initDispatch(HWC2_FUNCTION_SET_AUTO_LOW_LATENCY_MODE, &mDispatch.setAutoLowLatencyMode) ||
            !initDispatch(HWC2_FUNCTION_GET_SUPPORTED_CONTENT_TYPES, &mDispatch.getSupportedContentTypes)||
            !initDispatch(HWC2_FUNCTION_SET_ACTIVE_CONFIG_WITH_CONSTRAINTS, &mDispatch.setActiveConfigWithConstraints)||
            !initDispatch(HWC2_FUNCTION_SET_CONTENT_TYPE, &mDispatch.setContentType)) {
            ALOGE("failed to get hwcomposer2.4 functions %s(%d)", __FUNCTION__, __LINE__);
            return false;
        }

        return true;
    }


private:
    void initCaps();

    hwc2_device_t *mDevice;
    EventCallback* mEventCallback;
#ifdef USES_HWC_SERVICES
    std::unique_ptr<ExynosHWCCtx> mHwcCtx;
#endif
    std::unordered_set<Capability> mCaps;

    struct {
        HWC2_PFN_ACCEPT_DISPLAY_CHANGES acceptDisplayChanges;
        HWC2_PFN_CREATE_LAYER createLayer;
        HWC2_PFN_CREATE_VIRTUAL_DISPLAY createVirtualDisplay;
        HWC2_PFN_DESTROY_LAYER destroyLayer;
        HWC2_PFN_DESTROY_VIRTUAL_DISPLAY destroyVirtualDisplay;
        HWC2_PFN_DUMP dump;
        HWC2_PFN_GET_ACTIVE_CONFIG getActiveConfig;
        HWC2_PFN_GET_CHANGED_COMPOSITION_TYPES getChangedCompositionTypes;
        HWC2_PFN_GET_CLIENT_TARGET_SUPPORT getClientTargetSupport;
        HWC2_PFN_GET_COLOR_MODES getColorModes;
        HWC2_PFN_GET_DISPLAY_ATTRIBUTE getDisplayAttribute;
        HWC2_PFN_GET_DISPLAY_CONFIGS getDisplayConfigs;
        HWC2_PFN_GET_DISPLAY_NAME getDisplayName;
        HWC2_PFN_GET_DISPLAY_REQUESTS getDisplayRequests;
        HWC2_PFN_GET_DISPLAY_TYPE getDisplayType;
        HWC2_PFN_GET_DOZE_SUPPORT getDozeSupport;
        HWC2_PFN_GET_HDR_CAPABILITIES getHdrCapabilities;
        HWC2_PFN_GET_MAX_VIRTUAL_DISPLAY_COUNT getMaxVirtualDisplayCount;
        HWC2_PFN_GET_RELEASE_FENCES getReleaseFences;
        HWC2_PFN_PRESENT_DISPLAY presentDisplay;
        HWC2_PFN_REGISTER_CALLBACK registerCallback;
        HWC2_PFN_SET_ACTIVE_CONFIG setActiveConfig;
        HWC2_PFN_SET_CLIENT_TARGET setClientTarget;
        HWC2_PFN_SET_COLOR_MODE setColorMode;
        HWC2_PFN_SET_COLOR_TRANSFORM setColorTransform;
        HWC2_PFN_SET_CURSOR_POSITION setCursorPosition;
        HWC2_PFN_SET_LAYER_BLEND_MODE setLayerBlendMode;
        HWC2_PFN_SET_LAYER_BUFFER setLayerBuffer;
        HWC2_PFN_SET_LAYER_COLOR setLayerColor;
        HWC2_PFN_SET_LAYER_COMPOSITION_TYPE setLayerCompositionType;
        HWC2_PFN_SET_LAYER_DATASPACE setLayerDataspace;
        HWC2_PFN_SET_LAYER_DISPLAY_FRAME setLayerDisplayFrame;
        HWC2_PFN_SET_LAYER_PLANE_ALPHA setLayerPlaneAlpha;
        HWC2_PFN_SET_LAYER_SIDEBAND_STREAM setLayerSidebandStream;
        HWC2_PFN_SET_LAYER_SOURCE_CROP setLayerSourceCrop;
        HWC2_PFN_SET_LAYER_SURFACE_DAMAGE setLayerSurfaceDamage;
        HWC2_PFN_SET_LAYER_TRANSFORM setLayerTransform;
        HWC2_PFN_SET_LAYER_VISIBLE_REGION setLayerVisibleRegion;
        HWC2_PFN_SET_LAYER_Z_ORDER setLayerZOrder;
        HWC2_PFN_SET_OUTPUT_BUFFER setOutputBuffer;
        HWC2_PFN_SET_POWER_MODE setPowerMode;
        HWC2_PFN_SET_VSYNC_ENABLED setVsyncEnabled;
        HWC2_PFN_VALIDATE_DISPLAY validateDisplay;

        /* composer 2.2 */
        HWC2_PFN_SET_LAYER_FLOAT_COLOR setLayerFloatColor;
        HWC2_PFN_SET_LAYER_PER_FRAME_METADATA setLayerPerFrameMetadata;
        HWC2_PFN_GET_PER_FRAME_METADATA_KEYS getPerFrameMetadataKeys;
        HWC2_PFN_SET_READBACK_BUFFER setReadbackBuffer;
        HWC2_PFN_GET_READBACK_BUFFER_ATTRIBUTES getReadbackBufferAttributes;
        HWC2_PFN_GET_READBACK_BUFFER_FENCE getReadbackBufferFence;
        HWC2_PFN_GET_RENDER_INTENTS getRenderIntents;
        HWC2_PFN_SET_COLOR_MODE_WITH_RENDER_INTENT setColorModeWithRenderIntent;
        HWC2_PFN_GET_DATASPACE_SATURATION_MATRIX getDataspaceSaturationMatrix;

        /* composer 2.3 */
        HWC2_PFN_GET_DISPLAY_IDENTIFICATION_DATA getDisplayIdentificationData;
        HWC2_PFN_SET_LAYER_COLOR_TRANSFORM setLayerColorTransform;
        HWC2_PFN_GET_DISPLAYED_CONTENT_SAMPLING_ATTRIBUTES getDisplayedContentSamplingAttributes;
        HWC2_PFN_SET_DISPLAYED_CONTENT_SAMPLING_ENABLED setDisplayedContentSamplingEnabled;
        HWC2_PFN_GET_DISPLAYED_CONTENT_SAMPLE getDisplayedContentSample;
        HWC2_PFN_GET_DISPLAY_CAPABILITIES getDisplayCapabilities;
        HWC2_PFN_SET_LAYER_PER_FRAME_METADATA_BLOBS setLayerPerFrameMetadataBlobs;
        HWC2_PFN_GET_DISPLAY_BRIGHTNESS_SUPPORT getDisplayBrightnessSupport;
        HWC2_PFN_SET_DISPLAY_BRIGHTNESS setDisplayBrightness;

        /* composer 2.4 */
        HWC2_PFN_GET_DISPLAY_CONNECTION_TYPE getDisplayConnectionType;
        HWC2_PFN_GET_DISPLAY_VSYNC_PERIOD getDisplayVsyncPeriod;
        HWC2_PFN_SET_ACTIVE_CONFIG_WITH_CONSTRAINTS setActiveConfigWithConstraints;
        HWC2_PFN_SET_AUTO_LOW_LATENCY_MODE setAutoLowLatencyMode;
        HWC2_PFN_GET_SUPPORTED_CONTENT_TYPES getSupportedContentTypes;
        HWC2_PFN_SET_CONTENT_TYPE setContentType;
        HWC2_PFN_GET_CLIENT_TARGET_PROPERTY getClientTargetProperty;
        HWC2_PFN_SET_LAYER_GENERIC_METADATA setLayerGenericMetadata;
        HWC2_PFN_GET_LAYER_GENERIC_METADATA_KEY getLayerGenericMetadataKey;
    } mDispatch = {};
};

} // namespace aidl::android::hardware::graphics::composer3::impl
