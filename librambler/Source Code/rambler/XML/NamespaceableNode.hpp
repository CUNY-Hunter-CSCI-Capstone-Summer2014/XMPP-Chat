/**********************************************************************************************************************
 * @file    NamespaceableNode.hpp
 * @date    2014-06-29
 * @brief   <# Brief Description#>
 * @details <#Detailed Description#>
 **********************************************************************************************************************/

#pragma once

#include "NameableNode.hpp"
#include "Namespace.hpp"

namespace rambler { namespace XML {

    class NamespaceableNode : public NameableNode {
    public:
        virtual StrongPointer<Namespace const> getNamespace() const;
        String getQualifiedName() const;

        virtual bool operator < (NamespaceableNode const & other) const;
        virtual bool operator == (NamespaceableNode const & other) const;
        virtual bool operator != (NamespaceableNode const & other) const;
    protected:
        NamespaceableNode(Type type);
        NamespaceableNode(String name, Type type);
        NamespaceableNode(String name, StrongPointer<Namespace const> xmlnamespace, Type type);

        StrongPointer<Namespace const> const xmlnamespace = Namespace::DefaultNamespace();
    };
    
}}