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
// Bencode types
//
#include "BNode.hpp"
#include "Bencoding.hpp"
// =========
// NAMESPACE
// =========
namespace BencodeLib
{
    // ================
    // CLASS DEFINITION
    // ================
    class Bencode
    {
    public:
        // ==========================
        // PUBLIC TYPES AND CONSTANTS
        // ==========================
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
        void encode(IDestination &destination);
        BNode *getRoot();
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
        long extractPositiveInteger(ISource &source);
        std::string extractString(ISource &source);
        std::unique_ptr<BNode> decodeString(ISource &source);
        std::unique_ptr<BNode> decodeInteger(ISource &source);
        std::unique_ptr<BNode> decodeDictionary(ISource &source);
        std::unique_ptr<BNode> decodeList(ISource &source);
        std::unique_ptr<BNode> decodeBNodes(ISource &source);
        void encodeBNodes(BNode *bNode, IDestination &destination);
        // =================
        // PRIVATE VARIABLES
        // =================
        std::string m_workBuffer;
        std::unique_ptr<BNode> m_bNodeRoot;
    };
} // namespace BencodeLib
