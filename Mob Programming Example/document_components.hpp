#pragma once

#include <string>
#include <memory>
#include <chrono>
#include <thread>
#include "document_renderer.hpp"

namespace MicroSlopSuperOffice
{
    class DocumentRenderer; // Forward declaration to avoid circular dependency

    class DocumentComponent
    {
    public:
        virtual ~DocumentComponent() = default;
        virtual void render(std::shared_ptr<RenderCtx> ctx) const = 0;
    };

    class Paragraph : public DocumentComponent
    {
    public:
        void render(std::shared_ptr<RenderCtx> ctx) const override
        {
            // Render the paragraph
        }

        void setText(const std::string &text)
        {
            // Set the text of the paragraph
        }
        // ...
    };

    class Image : public DocumentComponent
    {
    public:
        Image(const std::string &source) : m_image_data(nullptr)
        {
            setSource(source);
            loadImageData(); // Simulate expensive image loading
        }

        void render(std::shared_ptr<RenderCtx> ctx) const override
        {
            // Render the image
        }
        void setSource(const std::string &source)
        {
            m_source = source;
            // Invalidate the current image data since the source has changed

            loadImageData(); // Simulate expensive image loading
        }
        // ...
    private:
        void loadImageData()
        {
            if (m_image_data != nullptr)
                delete[] m_image_data; // Clean up previous image data if it exists
            // Simulate the expensive operation of loading image data
            m_image_data = new char[100000000]; // Simulate large image data

            std::this_thread::sleep_for(std::chrono::seconds(5)); // Simulate long loading time
        }

        std::string m_source;
        char *m_image_data; // Simulate the image data, which is expensive to load
    };

    class Table : public DocumentComponent
    {
    public:
        void render(std::shared_ptr<RenderCtx> ctx) const override
        {
            // Render the table
        }

        void setData(int rows, int cols, const std::vector<std::vector<std::shared_ptr<DocumentComponent>>> &data)
        {
            // Set the data of the table
        }
        // ...
    };

    class Equation : public DocumentComponent
    {
    public:
        Equation(const std::string &formula) : m_rendered_equation(nullptr)
        {
            setFormula(formula);
            prerender_equation(); // Simulate expensive equation rendering
        }

        void render(std::shared_ptr<RenderCtx> ctx) const override
        {
            // Render the equation by setting the context to contain
            // the rendered version of the equation
        }

        void setFormula(const std::string &formula)
        {
            m_formula = formula;
            // Invalidate the current rendered equation since the formula has changed
            prerender_equation(); // Simulate expensive equation rendering
        }
        // ...
    private:
        void prerender_equation()
        {
            if (m_rendered_equation != nullptr)
                delete[] m_rendered_equation; // Clean up previous rendered equation if it exists

            // Simulate the expensive operation of rendering the equation
            m_rendered_equation = new char[1000000]; // Simulate large rendered equation data
            strcpy(m_rendered_equation, ("Rendered version of: " + m_formula).c_str());
            std::this_thread::sleep_for(std::chrono::seconds(3)); // Simulate long rendering time
        }

        std::string m_formula;
        char *m_rendered_equation; // Simulate the rendered equation, which is expensive to generate
    };
}
