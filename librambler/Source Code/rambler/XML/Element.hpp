/**********************************************************************************************************************
 * @file    Element.hpp
 * @date    2014-06-25
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "NamespaceableNode.hpp"
#include "Attribute.hpp"
#include "TextNode.hpp"

#include "rambler/types.hpp"

namespace rambler { namespace XML {

    class Element : public NamespaceableNode, public std::enable_shared_from_this<Element> {
    public:
        static Element NoElement;

        Element();
        Element(String name);
        Element(String name, StrongPointer<Namespace> defaultNamespace);
        Element(StrongPointer<Namespace> xmlnamespace, String name);
        Element(StrongPointer<Namespace> xmlnamespace, String name, StrongPointer<Namespace> defaultNamespace);

        StrongPointer<Element> getPtr();
        StrongPointer<Element> getParent() const;

        void addChild(StrongPointer<Element> child);
        void addChild(StrongPointer<TextNode> child);

        std::vector<StrongPointer<Node>> getChildren() const;

        std::vector<StrongPointer<Element>> getElementsByName(String const name) const;
        std::vector<StrongPointer<Element>> getElementsByName(StrongPointer<Namespace> const xmlnamespace,
                                                              String const name) const;
        std::vector<StrongPointer<Element>> getElementsByNamespace(StrongPointer<Namespace> const xmlnamespace) const;

        StrongPointer<Element> getFirstElementByName(String const name) const;
        StrongPointer<Element> getFirstElementByName(StrongPointer<Namespace> const xmlnamespace,
                                                     String const name) const;
        StrongPointer<Element> getFirstElementByNamespace(StrongPointer<Namespace> const xmlnamespace) const;

        StrongPointer<Element> getLastElementByName(String const name) const;
        StrongPointer<Element> getLastElementByName(StrongPointer<Namespace> const xmlnamespace,
                                                    String const name) const;
        StrongPointer<Element> getLastElementByNamespace(StrongPointer<Namespace> const xmlnamespace) const;

        StrongPointer<Element> getElementByID(String const id) const;

        String getTextContent() const;

        virtual StrongPointer<Namespace> getNamespace() const override;
        StrongPointer<Namespace> getDefaultNamespace() const;
        void addNamespace(StrongPointer<Namespace> xmlnamespace);
        std::vector<StrongPointer<Namespace>> getNamespaces() const;
        StrongPointer<Namespace> getNamespaceByPrefix(String prefix) const;
        void setDefaultNamespace(StrongPointer<Namespace> xmlnamespace);

        void addAttribute(Attribute attribute);
        void addAttributes(std::set<Attribute> attributes);

        Attribute getAttribute(String name) const;
        Attribute getAttribute(StrongPointer<Namespace> xmlnamespace, String name) const;
        std::set<Attribute> getAttributes() const;

        void setAttributes(std::set<Attribute> attributes);

        void removeAttribute(String name);
        void removeAttribute(StrongPointer<Namespace> xmlnamespace, String name);

        virtual String getStringValue() const override;

        virtual bool isValid() const;

        bool operator == (Element const & other);
        bool operator != (Element const & other);
    private:
        StrongPointer<Namespace> defaultNamespace = Namespace::DefaultNamespace();
        std::vector<StrongPointer<Namespace>> namespaces;
        std::set<Attribute> attributes;

        WeakPointer<Element> parent;
        std::vector<StrongPointer<Node>> children;
    };

    bool equivalent(StrongPointer<Element> const anElement, StrongPointer<Element> const anotherElement);
    bool equivalentByName(StrongPointer<Element> const anElement, StrongPointer<Element> const anotherElement);
    bool equivalentByNameAndNamespace(StrongPointer<Element> const anElement, StrongPointer<Element> const anotherElement);

}}