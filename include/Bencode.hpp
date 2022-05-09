#pragma once
//
// C++ STL
//
#include <string>
#include <stdexcept>
#include <memory>
//
// BNode types
//
#include "BNode.hpp"
// =========
// NAMESPACE
// =========
namespace BencodeLib
{

    // ===================================
    // Forward declarations for interfaces
    // ===================================

    class ISource;
    class IDestination;

    // ======================================
    // Forward declaration for implementation
    // ======================================

    class BencodeImplementation;

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
            explicit SyntaxError(std::string errorMessage = "Bencode Error : Syntax error detected.") : errorMessage(std::move(errorMessage)) {}
            [[nodiscard]] const char *what() const noexcept override
            {
                return (errorMessage.c_str());
            }

        private:
            const std::string errorMessage;
        };
        // ============
        // CONSTRUCTORS
        // ============
        Bencode();
        // ==========
        // DESTRUCTOR
        // ==========
        ~Bencode();
        // ==============
        // PUBLIC METHODS
        // ==============
        void decode(ISource &source);
        void decode(ISource &&source);
        void encode(IDestination &destination);
        void encode(IDestination &&destination);
        BNode &root();
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
        // =================
        // PRIVATE VARIABLES
        // =================
        std::unique_ptr<BencodeImplementation> m_imp;
    };
} // namespace BencodeLib
