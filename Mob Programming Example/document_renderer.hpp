#pragma once

namespace MicroSlopSuperOffice
{
    class RenderCtx
    {
    public:
        // Context for rendering, e.g. current page, zoom level, etc.
    };

    class DocumentRenderer
    {
    public:
        void renderDocument(const std::vector<std::shared_ptr<DocumentComponent>> &components) const
        {
            auto ctx = std::make_shared<RenderCtx>();
            for (const auto &component : components)
            {
                component->render(ctx);
            }
        }

        // ...
    };
}