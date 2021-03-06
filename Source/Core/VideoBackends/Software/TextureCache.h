#pragma once

#include <memory>
#include "VideoBackends/Software/SWTexture.h"
#include "VideoBackends/Software/TextureEncoder.h"
#include "VideoCommon/TextureCacheBase.h"

namespace SW
{
class TextureCache : public TextureCacheBase
{
protected:
  void CopyEFB(AbstractStagingTexture* dst, const EFBCopyParams& params, u32 native_width,
               u32 bytes_per_row, u32 num_blocks_y, u32 memory_stride, const EFBRectangle& src_rect,
               bool scale_by_half, float y_scale, float gamma, bool clamp_top, bool clamp_bottom,
               const EFBCopyFilterCoefficients& filter_coefficients) override
  {
    TextureEncoder::Encode(dst, params, native_width, bytes_per_row, num_blocks_y, memory_stride,
                           src_rect, scale_by_half, y_scale, gamma);
  }
  void CopyEFBToCacheEntry(TCacheEntry* entry, bool is_depth_copy, const EFBRectangle& src_rect,
                           bool scale_by_half, EFBCopyFormat dst_format, bool is_intensity,
                           float gamma, bool clamp_top, bool clamp_bottom,
                           const EFBCopyFilterCoefficients& filter_coefficients) override
  {
    // TODO: If we ever want to "fake" vram textures, we would need to implement this
  }
};

}  // namespace SW
