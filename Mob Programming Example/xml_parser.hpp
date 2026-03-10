#pragma once

#include <vector>
#include <string>
#include <memory>
#include "document_components.hpp"

namespace MicroSlopSuperOffice
{
    class XMLParser
    {
    public:
        // Parses an XML document and returns a DocumentComponent
        std::vector<std::shared_ptr<DocumentComponent>> parse() const
        {
            // Parse the XML and create DocumentComponents
            std::vector<std::shared_ptr<DocumentComponent>> components;

            // For the example we'll just create some dummy components
            components.push_back(std::make_shared<Paragraph>());
            components.push_back(std::make_shared<Image>("example_image.png"));
            components.push_back(std::make_shared<Table>());
            components.push_back(std::make_shared<Paragraph>());
            components.push_back(std::make_shared<Equation>("\\rho \\left( \\frac{\\partial \\mathbf{u}}{\\partial t} + \\mathbf{u} \\cdot \\nabla \\mathbf{u} \\right) = -\\nabla p + \\mu \\nabla^2 \\mathbf{u} + \\mathbf{f}"));
            components.push_back(std::make_shared<Equation>("\\nabla \\cdot \\mathbf{u} = 0"));
            return components;
        }

        XMLParser(const std::string &filepath)
        {
            // Load the XML file and prepare for parsing
        }
    };
}
