#pragma once
//
// C++ STL
//
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <fstream>
#include <stdexcept>
#include <utility>
//
// Source/Destination interfaces
//
#include "ISource.hpp"
#include "IDestination.hpp"
//
// BNode types
//
#include "BNode.hpp"
// =========
// NAMESPACE
// =========
namespace BencodeLib
{
    // ================
    // CLASS DEFINITION
    // ================

    // using Integer = int64_t;
    
    class Bencode
    {
    public:
        // ==========================
        // PUBLIC TYPES AND CONSTANTS
        // ==========================
         using Integer = int64_t;
        //
        // Bencode syntax error.
        //
        struct SyntaxError : public std::exception
        {
        public:
            SyntaxError(const std::string &errorMessage = "Bencoding syntax error detected.") : errorMessage(errorMessage) {}
            virtual const char *what() const throw()
            {
                return (errorMessage.c_str());
            }

        private:
            std::string errorMessage;
        };
        // ============
        // CONSTRUCTORS
        // ============
        // ==========
        // DESTRUCTOR
        // ==========
        // ==============
        // PUBLIC METHODS
        // ==============
        void decode(ISource &source);
        void decode(ISource &&source);
        void encode(IDestination &destination);
        void encode(IDestination &&destination);
        BNode &operator*() { return (*m_bNodeRoot); }
        // ================
        // PUBLIC VARIABLES
        // ================
    private:
        // ===========================
        // PRIVATE TYPES AND CONSTANTS
        // ===========================
        // ===========================================
        // DISABLED CONSTRUCTORS/DESTRUCTORS/OPERATORS
        // ===========================================
        // ===============
        // PRIVATE METHODS
        // ===============
        Bencode::Integer extractPositiveInteger(ISource &source);
        std::string extractString(ISource &source);
        BNodePtr decodeString(ISource &source);
        BNodePtr decodeInteger(ISource &source);
        BNodePtr decodeDictionary(ISource &source);
        BNodePtr decodeList(ISource &source);
        BNodePtr decodeBNodes(ISource &source);
        void encodeBNodes(BNode *bNode, IDestination &destination);
        // =================
        // PRIVATE VARIABLES
        // =================
        BNodePtr m_bNodeRoot;
    };
} // namespace BencodeLib
