#include "document_components.hpp"
#include "xml_parser.hpp"
#include "document_renderer.hpp"

int main()
{

    // Create an XML parser and parse a document
    MicroSlopSuperOffice::XMLParser parser("example_document.xml");

    // Opening the document

    // Unfortunately, parsing the XML is a very expensive operation that takes a long time to complete.
    // This is because our image and equation components require expensive loading and rendering operations,
    // and the XML parser creates and loads these components during parsing.
    std::vector<std::shared_ptr<DocumentComponent>> components = parser.parse();


    // At this point, the document is fully loaded and we can render it.
    // Other logic for interacting with the document, such as editing, saving, etc. would also go here.

    // Create a renderer and render the document
    MicroSlopSuperOffice::DocumentRenderer renderer;
    renderer.renderDocument(components);

    return 0;
}