#include "qsgfilamentnode.h"

#include "qfilament.h"

#include <filament/Engine.h>
#include <filament/Viewport.h>
QSGFilamentNode::QSGFilamentNode(const uint16_t viewId, QQuickItem *item, filament::Engine *engine)
    : m_item(item)
    , m_engine(engine)
    , m_viewId(viewId)
    , _renderFbo(nullptr) {
    m_window = m_item->window();

    connect(m_window, &QQuickWindow::screenChanged, this, [this]() {
        if (m_window->effectiveDevicePixelRatio() != m_dpr)
            m_item->update();
    });

    _multiSampleFormat.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    _multiSampleFormat.setMipmap(true);

    qDebug() << "Filament created, view id: " << viewId;
}

QSGTexture *QSGFilamentNode::texture() const {
    return QSGSimpleTextureNode::texture();
}

void QSGFilamentNode::sync() {
    qDebug() << "sync";

    m_dpr = m_window->effectiveDevicePixelRatio();
    const auto newSize = (rect().size() * m_dpr).toSize();

    // In case there is no qsgtexture attached to the node or the node has a new
    // size
    if (!texture() || (newSize != m_size)) {
        m_size = newSize;
        const auto width = static_cast<uint16_t>(newSize.width());
        const auto height = static_cast<uint16_t>(newSize.height());

        _renderFbo =
            std::make_unique<QOpenGLFramebufferObject>(QSize{400, 400}, _multiSampleFormat);

        if (texture()) {
            texture()->deleteLater();
        }

        qDebug() << "sync";


        tex_col = filament::Texture::Builder()
                      .width(width)
                      .height(height)
                      .levels(1)
                      .usage(filament::Texture::Usage::COLOR_ATTACHMENT |
                             filament::Texture::Usage::SAMPLEABLE)
                      .format(filament::Texture::InternalFormat::RGBA16F)
                      .build(*m_engine);

        if (!tex_col) {
            qDebug() << "tex_col fails";
        }

        tex_depth = filament::Texture::Builder()
                        .width(width)
                        .height(height)
                        .levels(1)
                        .usage(filament::Texture::Usage::DEPTH_ATTACHMENT)
                        .format(filament::Texture::InternalFormat::DEPTH24)
                        .build(*m_engine);
        if (!tex_col) {
            qDebug() << "tex_depth fails";
        }

        filament::RenderTarget::Builder render_target_builder =
            filament::RenderTarget::Builder();
        render_target_builder.texture(
            filament::RenderTarget::AttachmentPoint::COLOR, tex_col);
        render_target_builder.texture(
            filament::RenderTarget::AttachmentPoint::DEPTH, tex_depth);
        filament::RenderTarget *render_target =
            render_target_builder.build(*m_engine);

        if (!render_target) {
            qDebug("Failed to create the render target. (exiting).\n");
        }

        m_filaView->setRenderTarget(render_target);

        uint32_t tex_col_id = 0;
        tex_col->getId(*m_engine, (void *)&tex_col_id);

        qDebug() << "texture" << tex_col;

        QSGTexture *qsgtexture{nullptr};
        qsgtexture = QNativeInterface::QSGOpenGLTexture::fromNative(
            (ptrdiff_t)tex_col, m_window, QSize(width, height),
            QQuickWindow::TextureHasAlphaChannel);
        setTexture(qsgtexture);
    }
}
