//------------------------------------------------------------------------------
//  TextureFactoryTest.cc
//------------------------------------------------------------------------------
#include "Pre.h"
#include "UnitTest++/src/UnitTest++.h"
#include "Gfx/Resource/textureFactory.h"
#include "Gfx/Resource/texturePool.h"
#include "Gfx/Core/displayMgr.h"
#include "Gfx/Core/renderer.h"

#if ORYOL_OPENGL
#include "Gfx/gl/gl_impl.h"
#endif

using namespace Oryol;
using namespace _priv;

TEST(RenderTargetCreationTest) {

    #if !ORYOL_UNITTESTS_HEADLESS
    // setup a GL context
    auto gfxSetup = GfxSetup::Window(400, 300, "Oryol Test");
    displayMgr displayManager;
    displayManager.SetupDisplay(gfxSetup);
    
    // setup a meshFactory object
    texturePool texPool;
    class renderer renderer;
    renderer.setup();
    textureFactory factory;
    factory.Setup(&renderer, &displayManager, &texPool);
    
    // create a render target (no depth buffer)
    auto texSetup = TextureSetup::RenderTarget(320, 256);
    texSetup.ColorFormat = PixelFormat::RGBA8;
    texture tex0;
    tex0.Setup = texSetup;
    factory.SetupResource(tex0);
    CHECK(tex0.glTex != 0);
    CHECK(tex0.glFramebuffer != 0);
    CHECK(tex0.glDepthRenderbuffer == 0);
    CHECK(tex0.glDepthTexture == 0);
    const TextureAttrs& attrs0 = tex0.textureAttrs;
    CHECK(attrs0.Locator == Locator::NonShared());
    CHECK(attrs0.Type == TextureType::Texture2D);
    CHECK(attrs0.ColorFormat == PixelFormat::RGBA8);
    CHECK(attrs0.DepthFormat == PixelFormat::InvalidPixelFormat);
    CHECK(attrs0.TextureUsage == Usage::Immutable);
    CHECK(attrs0.Width == 320);
    CHECK(attrs0.Height == 256);
    CHECK(attrs0.Depth == 0);
    CHECK(1 == attrs0.NumMipMaps);
    CHECK(attrs0.IsRenderTarget);
    CHECK(!attrs0.HasDepthBuffer);
    CHECK(!attrs0.HasSharedDepthBuffer);
    CHECK(!attrs0.IsDepthTexture);
    
    // create a render target with depth buffer
    auto rtSetup = TextureSetup::RenderTarget(640, 480);
    rtSetup.ColorFormat = PixelFormat::RGBA8;
    rtSetup.DepthFormat = PixelFormat::D24S8;
    texture tex1;
    tex1.Setup = rtSetup;
    factory.SetupResource(tex1);
    CHECK(tex1.glTex != 0);
    CHECK(tex1.glFramebuffer != 0);
    CHECK(tex1.glDepthRenderbuffer != 0);
    CHECK(tex1.glDepthTexture == 0);
    const TextureAttrs& attrs1 = tex1.textureAttrs;
    CHECK(attrs1.Locator == Locator::NonShared());
    CHECK(attrs1.Type == TextureType::Texture2D);
    CHECK(attrs1.ColorFormat == PixelFormat::RGBA8);
    CHECK(attrs1.DepthFormat == PixelFormat::D24S8);
    CHECK(attrs1.TextureUsage == Usage::Immutable);
    CHECK(attrs1.Width == 640);
    CHECK(attrs1.Height == 480);
    CHECK(attrs1.Depth == 0);
    CHECK(1 == attrs1.NumMipMaps);
    CHECK(attrs1.IsRenderTarget);
    CHECK(attrs1.HasDepthBuffer);
    CHECK(!attrs1.HasSharedDepthBuffer);
    CHECK(!attrs1.IsDepthTexture);
    
    // create relative-size render target with depth buffer
    rtSetup = TextureSetup::RelSizeRenderTarget(1.0f, 1.0f);
    rtSetup.ColorFormat = PixelFormat::R5G6B5;
    rtSetup.DepthFormat = PixelFormat::D16;
    texture tex2;
    tex2.Setup = rtSetup;
    factory.SetupResource(tex2);
    CHECK(tex2.glTex != 0);
    CHECK(tex2.glFramebuffer != 0);
    CHECK(tex2.glDepthRenderbuffer != 0);
    CHECK(tex2.glDepthTexture == 0);
    const TextureAttrs& attrs2 = tex2.textureAttrs;
    CHECK(attrs2.Locator == Locator::NonShared());
    CHECK(attrs2.Type == TextureType::Texture2D);
    CHECK(attrs2.ColorFormat == PixelFormat::R5G6B5);
    CHECK(attrs2.DepthFormat == PixelFormat::D16);
    CHECK(attrs2.TextureUsage == Usage::Immutable);
    CHECK(attrs2.Width == 400);
    CHECK(attrs2.Height == 300);
    CHECK(attrs2.Depth == 0);
    CHECK(1 == attrs2.NumMipMaps);
    CHECK(attrs2.IsRenderTarget);
    CHECK(attrs2.HasDepthBuffer);
    CHECK(!attrs2.HasSharedDepthBuffer);
    CHECK(!attrs2.IsDepthTexture);
    
    // cleanup
    factory.DestroyResource(tex1);
    CHECK(tex1.glTex == 0);
    CHECK(tex1.glFramebuffer == 0);
    CHECK(tex1.glDepthRenderbuffer == 0);
    CHECK(tex1.glDepthTexture == 0);
    
    factory.DestroyResource(tex0);
    factory.DestroyResource(tex2);
    factory.Discard();
    renderer.discard();
    displayManager.DiscardDisplay();
    #endif
}

