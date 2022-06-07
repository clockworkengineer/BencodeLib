#pragma once
//
// C++ STL
//
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
// =========
// NAMESPACE
// =========
namespace BencodeLib
{
    //
    // BNode types.
    //
    enum class BNodeType
    {
        base = 0,
        dictionary,
        list,
        integer,
        string
    };
    //
    // Base BNode
    //
    struct BNode
    {
        using Ptr = std::unique_ptr<BNode>;
        struct Error : public std::exception
        {
        public:
            explicit Error(std::string errorMessage) : errorMessage(std::move(errorMessage)) {}
            [[nodiscard]] const char *what() const noexcept override
            {
                return (errorMessage.c_str());
            }
        private:
            std::string errorMessage;
        };
        explicit BNode(BNodeType nodeType = BNodeType::base) : nodeType(nodeType)
        {
        }
        virtual ~BNode() = default;
        BNode &operator[](const std::string &key);
        BNode &operator[](int index);
        BNodeType nodeType;
    };
    //
    // Dictionary BNode.
    //
    struct BNodeDict : BNode
    {
        using Entry = std::pair<std::string, BNode::Ptr>;
        explicit BNodeDict(std::vector<BNodeDict::Entry> &value) : BNode(BNodeType::dictionary),
                                                                   m_value(std::move(value))
        {
        }
        [[nodiscard]] bool contains(const std::string &key) const
        {
            if (auto it = std::find_if(m_value.begin(), m_value.end(), [&key](const Entry &entry) -> bool
                                       { return (entry.first == key); });
                it != m_value.end())
            {
                return (true);
            }
            return (false);
        }
        [[nodiscard]] int size() const
        {
            return (static_cast<int>(m_value.size()));
        }
        BNode &operator[](const std::string &key) const
        {
            if (auto it = std::find_if(m_value.begin(), m_value.end(), [&key](const Entry &entry) -> bool
                                       { return (entry.first == key); });
                it != m_value.end())
            {
                return (*it->second);
            }
            throw BNode::Error("BNode Error: Invalid key used in dictionary.");
        }
        [[nodiscard]] const std::vector<Entry> &dictionary() const
        {
            return (m_value);
        }
    private:
        std::vector<BNodeDict::Entry> m_value;
    };
    //
    // List BNode.
    //
    struct BNodeList : BNode
    {
        explicit BNodeList(std::vector<BNode::Ptr> &value) : BNode(BNodeType::list),
                                                             m_value(std::move(value))
        {
        }
        [[nodiscard]] int size() const
        {
            return (static_cast<int>(m_value.size()));
        }
        [[nodiscard]] const std::vector<BNode::Ptr> &list() const
        {
            return (m_value);
        }
        BNode &operator[](int index) const
        {
            if ((index >= 0) && (index < (static_cast<int>(m_value.size()))))
            {
                return (*m_value[index]);
            }
            throw BNode::Error("BNode Error: Invalid index used in list.");
        }
    private:
        std::vector<BNode::Ptr> m_value;
    };
    //
    // Integer BNode.
    //
    struct BNodeInteger : BNode
    {
        explicit BNodeInteger(int64_t value) : BNode(BNodeType::integer),
                                               m_value(value)
        {
        }
        [[nodiscard]] int64_t integer() const
        {
            return (m_value);
        }
    private:
        int64_t m_value = 0;
    };
    //
    // String BNode.
    //
    struct BNodeString : BNode
    {
        explicit BNodeString(std::string value) : BNode(BNodeType::string),
                                                  m_value(std::move(value))
        {
        }
        [[nodiscard]] std::string string() const
        {
            return (m_value);
        }
    private:
        std::string m_value;
    };
    //
    // Convert base BNode reference
    //
    template <typename T>
    T &BNodeRef(BNode &bNode)
    {
        if constexpr (std::is_same_v<T, BNodeString>)
        {
            if (bNode.nodeType != BNodeType::string)
            {
                throw BNode::Error("BNode Error: Node not a string.");
            }
        }
        else if constexpr (std::is_same_v<T, BNodeInteger>)
        {
            if (bNode.nodeType != BNodeType::integer)
            {
                throw BNode::Error("BNode Error: Node not an integer.");
            }
        }
        else if constexpr (std::is_same_v<T, BNodeList>)
        {
            if (bNode.nodeType != BNodeType::list)
            {
                throw BNode::Error("BNode Error: Node not a list.");
            }
        }
        else if constexpr (std::is_same_v<T, BNodeDict>)
        {
            if (bNode.nodeType != BNodeType::dictionary)
            {
                throw BNode::Error("BNode Error: Node not a dictionary.");
            }
        }
        return (static_cast<T &>(bNode));
    }
    //
    // Convert base BNode reference
    //
    template <typename T>
    const T &BNodeRef(const BNode &bNode)
    {
        if constexpr (std::is_same_v<T, BNodeString>)
        {
            if (bNode.nodeType != BNodeType::string)
            {
                throw BNode::Error("BNode Error: Node not a string.");
            }
        }
        else if constexpr (std::is_same_v<T, BNodeInteger>)
        {
            if (bNode.nodeType != BNodeType::integer)
            {
                throw BNode::Error("BNode Error: Node not an integer.");
            }
        }
        else if constexpr (std::is_same_v<T, BNodeList>)
        {
            if (bNode.nodeType != BNodeType::list)
            {
                throw BNode::Error("BNode Error: Node not a list.");
            }
        }
        else if constexpr (std::is_same_v<T, BNodeDict>)
        {
            if (bNode.nodeType != BNodeType::dictionary)
            {
                throw BNode::Error("BNode Error: Node not a dictionary.");
            }
        }
        return (static_cast<const T &>(bNode));
    }
    //
    // Index overloads
    //
    inline BNode &BNode::operator[](const std::string &key) // Dictionary
    {
        return (BNodeRef<BNodeDict>(*this)[key]);
    }
    inline BNode &BNode::operator[](int index) // List
    {
        return (BNodeRef<BNodeList>(*this)[index]);
    }
} // namespace BencodeLib